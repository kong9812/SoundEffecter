//=============================================================================
//
// サウンドコントロール [soundControl.h]
// Author : 蔡 友剛
//
//=============================================================================
#include "soundControl.h"
#include "waveOut.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SOUND_CONTROL::SOUND_CONTROL(HWND hWnd)
{
	// サウンドの初期化
	sound = new SOUND();

	// サウンドの読み込み
	soundTool.svtBase.sourceVoice = sound->LoadXAudio2Voice(hWnd, &soundTool);

	// 再生
	sound->PlayVoice(&soundTool);

	// サウンドの初期化
	soundEffect = new SOUND_EFFECT(&soundTool, sound->GetMasterVoice());

	// パラメータ構造体
	soundParameter.mainVol		= INIT_MAIN_VOL;		// メインボリュム		
	soundParameter.panVol		= INIT_PAN_VOL;			// パンヴォリューム
	soundParameter.freq			= INIT_FREQ;			// (再生周波数)ピーチ
	soundParameter.delayReverb	= INIT_DELAY_REVERB;	// ディレイ＋リバーブ
	soundParameter.wetVol		= INIT_WET_VOL;			// ウェットボイスのボリューム
	soundParameter.dryVol		= INIT_DRY_VOL;			// ドライボイスのボリューム
	soundParameter.delayTime	= INIT_DELAY_TIME;		// ディレイタイム		
	soundParameter.reverbVol	= INIT_REVERB_VOL;		// 残響のボリューム 
	soundParameter.fade			= INIT_FADE;			// フェイド
	soundParameter.fadeTime		= INIT_FADE_TIME;		// フェイドタイム		

	// プロットのパスを取得
	OpenGnuplot(hWnd);
	OutputWaveGnuplot(soundTool, sound->GetWavFile()->GetOldPath(), NULL);
}

//=============================================================================
// デストラクタ
//=============================================================================
SOUND_CONTROL::~SOUND_CONTROL(void)
{
	// 音の停止
	sound->StopVoice(&soundTool);

	// ソースボイスのメモリ解放
	if (soundTool.svtBase.sourceVoice != NULL)
	{
		soundTool.svtBase.sourceVoice->DestroyVoice();
		soundTool.svtBase.sourceVoice = NULL;
	}

	delete soundEffect;
	delete sound;
}	

//=============================================================================
// プロセス
//=============================================================================
void SOUND_CONTROL::soundControlProcess(int no, float percentage)
{
	switch (no)
	{
	case BUTTON_LIST::BUTTON_MAIN_VOL:
		soundParameter.mainVol = percentage * MAX_MAIN_VOL;
		sound->SetMainVolume(&soundTool, soundParameter.mainVol);
		break;
	case BUTTON_LIST::BUTTON_PAN_VOL:
		soundParameter.panVol = (percentage * 2.0f) - 1.0f;
		sound->SetPanVolume(&soundTool, -soundParameter.panVol);
		break;
	case BUTTON_LIST::BUTTON_FREQ:
		soundParameter.freq = 1.0f + ((percentage * 2.0f) - 1.0f);
		sound->SetPitch(&soundTool, soundParameter.freq);
		break;
	case BUTTON_LIST::BUTTON_DELAY_REVERB:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	case BUTTON_LIST::BUTTON_WET_VOL:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	case BUTTON_LIST::BUTTON_DRY_VOL:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	case BUTTON_LIST::BUTTON_DELAY_TIME:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	case BUTTON_LIST::BUTTON_REVERB_VOL:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	case BUTTON_LIST::BUTTON_FADE:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	case BUTTON_LIST::BUTTON_FADE_TIME:
		soundEffect->SetEffect(&soundTool, no, percentage);
		break;
	default:
		break;
	}
}

//=============================================================================
// 音の書き出し
//=============================================================================
void SOUND_CONTROL::OutputWav(void)
{
	//--ディレイ＋リバーブ--// 
	soundParameter.delayReverb = soundEffect->GetDelayState();				// ディレイ＋リバーブ
	soundParameter.wetVol = soundEffect->GetDelayParmeters().wetVol;		// ウェットボイスのボリューム
	soundParameter.dryVol = soundEffect->GetDelayParmeters().dryVol;		// ドライボイスのボリューム
	soundParameter.delayTime = soundEffect->GetDelayParmeters().delayTime;	// ディレイタイム		
	soundParameter.reverbVol = soundEffect->GetDelayParmeters().reverbVol;	// 残響のボリューム 

	//-------フェイド-------//
	soundParameter.fade		= soundEffect->GetFadeState();					// フェイド
	soundParameter.fadeTime = soundEffect->GetFadeParameters().fadeTime;	// フェイドタイム		

	SetWaveData(&soundTool, sound->GetWavFile()->GetOldPath(), soundParameter);
}

//=============================================================================
// ボリュームメーター
//=============================================================================
float SOUND_CONTROL::GetBalVolumeMeter(int no)
{
	// ボリュームメーター
	tmpVolMeter += soundEffect->GetVolumeMeter(no);
	frameCnt++;

	//if (frameCnt >= 10)
	//{
		volMeter = tmpVolMeter;
		frameCnt = 0;
		tmpVolMeter = 0;
	//}

	return volMeter;
}