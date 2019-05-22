//=============================================================================
//
// 音データの書き出し処理 [waveOut.h]
// Author : 蔡 友剛
//
//=============================================================================
#include "waveOut.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void OutWavFile(SOUND_TOOL *soundTool);	// ファイルの書き出し

//=============================================================================
// グローバル変数:
//=============================================================================
float	*backupBuf;
int		delaySample;
int		readPos;
int		writePos;
short	*tmpData;

//=============================================================================
// 波形データ
//=============================================================================
void SetWaveData(SOUND_TOOL *soundTool, char *oldPath, SOUND_PARAMETER parameter)
{
	// 遅延が発生できるサンプリング数(2秒の遅延)
	delaySample = (int)(soundTool->svtBase.wavFmt.fmt.fmtSampleRate *
		soundTool->svtBase.wavFmt.fmt.fmtChannel * 2);

	// メモリ確保(2秒のサンプリング)
	backupBuf = (float *)malloc(sizeof(float) * delaySample);

	// 初期化
	memset(backupBuf, 0, sizeof(float) * delaySample);

	// 読み込み位置の初期化
	readPos = 0;

	// 書き出し位置の初期化
	writePos = 0;

	// ファイルサイズ
	//int tmpSize = soundTool->svtBase.wavFmt.data.waveSize + (soundTool->svtBase.wavFmt.fmt.fmtChannel * soundTool->svtBase.wavFmt.fmt.fmtSampleRate * 2 * sizeof(short));

	// 書き換えるデータ[Output]
	tmpData = (short *)malloc(soundTool->svtBase.wavFmt.data.waveSize);
	//tmpData = (short *)malloc(tmpSize);
	memset(tmpData, 0, sizeof(tmpData));

	// 仮の遅延サンプリング
	int tmpDelaySample = (int)(delaySample * (parameter.delayTime / 2.0f));

	// フェイド
	int fadeSample = (int)(parameter.fadeTime * soundTool->svtBase.wavFmt.fmt.fmtChannel * 
		soundTool->svtBase.wavFmt.fmt.fmtSampleRate);
	int fadeSampleIndex = 0;

	for (int i = 0; i < soundTool->svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
	//for (int i = 0; i < tmpSize / (int)sizeof(short); i++)
	{
		// バッファの保存
		backupBuf[writePos] = (float)(soundTool->svtBase.wavFmt.data.waveData[i] + backupBuf[readPos] * parameter.reverbVol);
		writePos++;
		if (writePos >= tmpDelaySample)	// オーバー防止
		{
			// 0番目に戻る
			writePos = 0;
		}

		// 結果
		readPos = (int)(writePos - tmpDelaySample);
		if (readPos < 0)	// オーバー防止
		{
			// 0番目に戻る
			readPos += tmpDelaySample;
		}

		// ディレイ結果
		tmpData[i] = (short)((backupBuf[readPos] * parameter.wetVol) + (soundTool->svtBase.wavFmt.data.waveData[i] * parameter.dryVol));
	
		// フェイド
		if (fadeSampleIndex < fadeSample)
		{
			float tmp = (float)fadeSampleIndex / (float)fadeSample;
			tmpData[i] = (short)(tmpData[i] * tmp);

			fadeSampleIndex++;
		}
	}

	// 更新
	OutputWaveGnuplot(*soundTool, oldPath, tmpData);

	// ファイルの書き出し
	OutWavFile(soundTool);

	// メモリ解放
	free(backupBuf);

	// メモリ解放
	free(tmpData);
}

//=============================================================================
// ファイルの書き出し
//=============================================================================
void OutWavFile(SOUND_TOOL *soundTool)
{
	FILE *fp;

	// ファイルの準備
	fopen_s(&fp, "test.wav", "wb");

	// RIFFの書き出し
	fwrite(&soundTool->svtBase.wavFmt.riff, sizeof(RIFF_CHUNK), 1, fp);

	// FMTの書き出し
	fwrite(&soundTool->svtBase.wavFmt.fmt, sizeof(FMT_CHUNK), 1, fp);

	// DATAの書き出し
	fwrite(&soundTool->svtBase.wavFmt.data.dataChunk, sizeof(soundTool->svtBase.wavFmt.data.dataChunk), 1, fp);
	fwrite(&soundTool->svtBase.wavFmt.data.waveSize, sizeof(soundTool->svtBase.wavFmt.data.waveSize), 1, fp);
	fwrite(tmpData, soundTool->svtBase.wavFmt.data.waveSize, 1, fp);

	// ファイルクローズ
	fclose(fp);
}