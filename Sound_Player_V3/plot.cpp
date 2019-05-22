//=============================================================================
//
// プロット処理 [plot.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "plot.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
WIN32_FIND_DATA		findGnuplot;			// ファイル情報
char				gnuplotPath[MAX_PATH];	// ファイルのパス

//=============================================================================
// GNUPLOTの読み込み
//=============================================================================
bool OpenGnuplot(HWND hWnd)
{
	OPENFILENAME ofn;

	gnuplotPath[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));		//構造体を0でクリア
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrInitialDir = "C:\\gnuplot\\bin";	// テスト用PCのGNUPLOTパス( なくても大丈夫 @_@ )
	ofn.lpstrFilter = "gnuplot(*.exe)\0*.exe\0\0";
	ofn.lpstrFile = gnuplotPath;
	ofn.nMaxFile = sizeof(gnuplotPath);
	ofn.lpstrDefExt = "exe";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	// ファイル名を取り出す
	FindFirstFile(ofn.lpstrFile, &findGnuplot);

	return TRUE;
}

//=============================================================================
// 波形 (GNUPLOT)
// 縦軸:音圧(? 振幅(? 電圧(? 音の大きさ(? 
// 横軸:時間(バイト)
//=============================================================================
void OutputWaveGnuplot(SOUND_TOOL soundTool, char *oldPath, short *otherWave)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE *gnuplot;				// GNUPLOT
	double max;					// 最大値
	double min;					// 最小値
	double x, y;				// GNUPLOT中の座標
	char filePath[CHAR_MAX];

	// パスとコマンドを結合
	strcat(gnuplotPath, GNUPLOT_PRESIST);

	// セーブパスと初期パスを結合
	strcpy(filePath, oldPath);

	// セーブパスとセーブフォルダパスを結合
	strcat(filePath, SAVE_PATH);

	if (otherWave == NULL)
	{
		// 最大値と最小値
		min = max = soundTool.svtBase.wavFmt.data.waveData[0];
		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			if (soundTool.svtBase.wavFmt.data.waveData[i] < min) min = soundTool.svtBase.wavFmt.data.waveData[i];
			if (soundTool.svtBase.wavFmt.data.waveData[i] > max) max = soundTool.svtBase.wavFmt.data.waveData[i];
		}

		// グラフ
		gnuplot = _popen(gnuplotPath, "w");										// GNUPLOTを書き込みモードで開く
		fprintf(gnuplot, "set title \"wave \" \n");								// タイトルの設定
		fprintf(gnuplot, "set xrange [0:%d]\n", soundTool.svtBase.wavFmt.data.waveSize / sizeof(short));// xの範囲
		fprintf(gnuplot, "set yrange [%f:%f]\n", min, max);						// yの範囲
		fprintf(gnuplot, "set terminal png\n");									// 画像出力の準備
		fprintf(gnuplot, "set term png size 1000,300\n");						// 画像のサイズ
		fprintf(gnuplot, "plot '-' with lines linetype 1 title \"wave\"\n");	// プロット

		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			x = i;
			y = soundTool.svtBase.wavFmt.data.waveData[i];
			fprintf(gnuplot, "%f\t%f\n", x, y);
		}
	}
	else
	{
		// 最大値と最小値
		min = max = otherWave[0];
		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			if (otherWave[i] < min) min = otherWave[i];
			if (otherWave[i] > max) max = otherWave[i];
		}

		// グラフ
		gnuplot = _popen(gnuplotPath, "w");										// GNUPLOTを書き込みモードで開く
		fprintf(gnuplot, "set title \"wave \" \n");								// タイトルの設定
		fprintf(gnuplot, "set xrange [0:%d]\n", soundTool.svtBase.wavFmt.data.waveSize / sizeof(short));// xの範囲
		fprintf(gnuplot, "set yrange [%f:%f]\n", min, max);						// yの範囲
		fprintf(gnuplot, "set terminal png\n");									// 画像出力の準備
		fprintf(gnuplot, "set term png size 1000,300\n");						// 画像のサイズ
		fprintf(gnuplot, "plot '-' with lines linetype 1 title \"wave\"\n");	// プロット

		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			x = i;
			y = otherWave[i];
			fprintf(gnuplot, "%f\t%f\n", x, y);
		}
	}

	fprintf(gnuplot, "e\n");
	fprintf(gnuplot, "set output '%s\\\\Wave.png'\n", filePath);
	fprintf(gnuplot, "replot '%s\\\\Data.txt'using 1:2 w l title 'OutputData' lw 2\n", filePath); 	// テキストデータのプロット	
	fprintf(gnuplot, "set output\n");

	// GNUPLOTの画面を閉じる
	_pclose(gnuplot);

	// セーブパスとファイル名を結合
	strcat(filePath, "\\Wave.png");

	// カレントディレクトリを設定する
	SetCurrentDirectory(oldPath);

}