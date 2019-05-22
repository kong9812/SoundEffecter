//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 蔡 友剛
//
//=============================================================================
#include "sound.h"

//=============================================================================
// 初期化
//=============================================================================
SOUND::SOUND(void)
{
	// COMライブラリの初期化
	if (SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		// 成功+1
		initCheck++;

		// XAudio2オブジェクトの作成
		if (SUCCEEDED(XAudio2Create(&xAudio2)))
		{
			XAUDIO2_DEBUG_CONFIGURATION debugConfig{ NULL };
			debugConfig.LogThreadID = true;
			debugConfig.TraceMask = XAUDIO2_LOG_WARNINGS;
			debugConfig.TraceMask = debugConfig.TraceMask | XAUDIO2_LOG_FUNC_CALLS | XAUDIO2_LOG_DETAIL;
			debugConfig.BreakMask = XAUDIO2_LOG_ERRORS;

			xAudio2->SetDebugConfiguration(&debugConfig);

			// 成功+1
			initCheck++;

			// マスターボイスの作成
			if (SUCCEEDED(xAudio2->CreateMasteringVoice(&masteringVoice)))
			{
				// 成功+1
				initCheck++;

				// クラスnew
				wavFile = new SAI_LOAD_WAV;
			}
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
SOUND::~SOUND(void)
{
	// マスターボイス
	if (masteringVoice != NULL)
	{
		masteringVoice->DestroyVoice();
		masteringVoice = NULL;
	}

	// インターフェース
	if (xAudio2 != NULL)
	{
		xAudio2->Release();
		xAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();

	// ボリュームのメモリ解放
	free(channelVolume);

	// クラスdelete
	delete wavFile;
}

//=============================================================================
// 初期化の結果
//=============================================================================
bool SOUND::InitCheck()
{
	// 初期化成功 = 三回のSUCCEEDED
	if (initCheck != SOUND_INIT_SUCCEEDED)
	{
		return false;
	}

	return true;
}

//=============================================================================
// マスターボイスを取得
//=============================================================================
IXAudio2MasteringVoice *SOUND::GetMasterVoice(void)
{
	return masteringVoice;
}

//==============================================================
// ロードサウンド
//==============================================================
IXAudio2SourceVoice *SOUND::LoadXAudio2Voice(HWND hWnd, SOUND_TOOL *svt)
{
	IXAudio2SourceVoice *sourceVoice = NULL;	// ソースボイス
	WAVEFORMATEX		pcm;					// WAVEFORMATEX構造体
	XAUDIO2_BUFFER		buffer;					// バッファ

	{// ローカル変数の初期化

		// 構造体の初期化
		memset(&pcm, 0, sizeof(WAVEFORMATEX));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// ファイルのパスを取得
		wavFile->OpenSound(hWnd, fileName, soundPath);

		// wavファイルの読み込み(WAVEFORMATEX構造体)
		pcm = wavFile->LoadWavFile(soundPath, &svt->svtBase.wavFmt);

		// バッファの設定
		buffer.pAudioData	= (BYTE *)svt->svtBase.wavFmt.data.waveData;
		buffer.Flags		= XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes	= svt->svtBase.wavFmt.data.waveSize;
		buffer.LoopCount	= XAUDIO2_LOOP_INFINITE;
	}

	// ソースボイスの作成
	if (FAILED(xAudio2->CreateSourceVoice(&sourceVoice, &pcm, NULL, XAUDIO2_MAX_FREQ_RATIO)))
	{
		return NULL;
	}

	// バッファを提出
	if (FAILED(sourceVoice->SubmitSourceBuffer(&buffer)))
	{
		return NULL;
	}

	{// ボリュームの初期化
		// メモリ確保[チャンネル数]
		channelVolume = (float *)malloc(svt->svtBase.wavFmt.fmt.fmtChannel * sizeof(float));
		for (int i = 0; i < svt->svtBase.wavFmt.fmt.fmtChannel; i++)
		{
			channelVolume[i] = SOUND_DEFAULT_VOLUME;
		}
	}

	return sourceVoice;
}

//=============================================================================
// 再生
//=============================================================================
HRESULT SOUND::PlayVoice(SOUND_TOOL *svt)
{
	// ボイスと再生状態のチェック
	if ((svt->svtBase.sourceVoice != NULL) && (!svt->svtBase.isPlay))
	{
		// 再生
		svt->svtBase.sourceVoice->Start();

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// 停止
//=============================================================================
HRESULT SOUND::StopVoice(SOUND_TOOL *svt)
{
	// ボイスと再生状態のチェック
	if ((svt->svtBase.sourceVoice != NULL) && (svt->svtBase.isPlay))
	{
		// 停止
		svt->svtBase.sourceVoice->Stop();

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// 一時停止
//=============================================================================
HRESULT SOUND::PauseVoice(SOUND_TOOL *svt)
{
	// ボイスと再生状態のチェック
	if ((svt->svtBase.sourceVoice != NULL) && (svt->svtBase.isPlay))
	{
		// 一時停止
		svt->svtBase.sourceVoice->Stop(XAUDIO2_PLAY_TAILS);

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// メインボリュム
//=============================================================================
HRESULT SOUND::SetMainVolume(SOUND_TOOL *svt,float volume)
{
	// ボイスのチェック
	if (svt->svtBase.sourceVoice != NULL)
	{
		// メインボリュム
		svt->svtBase.sourceVoice->SetVolume(volume);

		return S_OK;
	}

	return S_FALSE;
}

//==============================================================
// パンボリューム
//==============================================================
HRESULT SOUND::SetPanVolume(SOUND_TOOL *svt, float panVolume)
{
	// ボイスのチェック
	if (svt->svtBase.sourceVoice != NULL)
	{
		float vol[4];
		float tmpVolume = panVolume + 1.0f;
		float radian = D3DXToRadian((tmpVolume / 2.0f) * 90.0f);

		// Left
		vol[0] = sinf(radian);
		vol[1] = 0.0f;

		// Right
		vol[2] = 0.0f;
		vol[3] = cosf(radian);

		svt->svtBase.sourceVoice->SetOutputMatrix
		(masteringVoice, svt->svtBase.wavFmt.fmt.fmtChannel, 2, vol);

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// (frequency ratio)ピーチ
//=============================================================================
HRESULT SOUND::SetPitch(SOUND_TOOL *svt,float pich)
{
	// ボイスとパラメータのチェック
	if ((svt->svtBase.sourceVoice != NULL) && 
		(pich > XAUDIO2_MIN_FREQ_RATIO) &&
		(pich < XAUDIO2_MAX_FREQ_RATIO))
	{
		// ピーチを設定
		return svt->svtBase.sourceVoice->SetFrequencyRatio(pich);
	}
	return S_FALSE;
}
float SOUND::GetPitch(SOUND_TOOL *svt)
{
	float pitch = 0;

	// ボイスのチェック
	if (svt->svtBase.sourceVoice != NULL)
	{
		// ピーチを取得
		svt->svtBase.sourceVoice->GetFrequencyRatio(&pitch);

		return pitch;
	}

	return pitch;
}
