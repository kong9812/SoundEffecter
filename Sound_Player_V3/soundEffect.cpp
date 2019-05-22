//=============================================================================
//
// 処理 [.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "soundEffect.h"
#include "soundControl.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SOUND_EFFECT::SOUND_EFFECT(SOUND_TOOL *soundTool,IXAudio2MasteringVoice *masterVoice)
{
	// マスターボイスのアドレスコピー
	tmpMasterVoice = masterVoice;

	// アウトプットディテール
	XAUDIO2_VOICE_DETAILS voiceDetails;
	soundTool->svtBase.sourceVoice->GetVoiceDetails(&voiceDetails);

	// ディレイ
	IUnknown *saiDelayApo = (IXAPO *)new SAI_DELAY_APO;
	// フェイド
	IUnknown *saiFadeApo = (IXAPO *)new SAI_FADE_IN_APO(soundTool);
	// ボリュームメーター
	IUnknown *volumeMeterAPO;
	XAudio2CreateVolumeMeter(&volumeMeterAPO);

	// ディレイのパラメータ
	delayParameters.wetVol		= 0.0f;
	delayParameters.dryVol		= 0.0f;
	delayParameters.delayTime	= 0.0f;
	delayParameters.reverbVol	= 0.0f;
	delayUse					= false;
	// フェイドのパラメータ
	fadeParameters.fadeTime		= 0.0f;
	fadeUse						= false;
	// ボリュームメーター
	volumeMeter.ChannelCount = 2;
	volumeMeter.pPeakLevels = (float *)malloc(sizeof(float) * 2);
	volumeMeter.pRMSLevels = (float *)malloc(sizeof(float) * 2);
	memset(volumeMeter.pPeakLevels, 0, sizeof(volumeMeter.pPeakLevels));
	memset(volumeMeter.pRMSLevels, 0, sizeof(volumeMeter.pRMSLevels));

	// ディスクリプタ
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY].InitialState = delayUse;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY].OutputChannels = voiceDetails.InputChannels;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY].pEffect = saiDelayApo;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN].InitialState = fadeUse;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN].OutputChannels = voiceDetails.InputChannels;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN].pEffect = saiFadeApo;

	// アウトプットディテール
	tmpMasterVoice->GetVoiceDetails(&voiceDetails);

	masterDescriptor.InitialState = true;
	masterDescriptor.OutputChannels = voiceDetails.InputChannels;
	masterDescriptor.pEffect = volumeMeterAPO;

	// チェン
	chain[EFFECT_CHAIN_SOURCE].EffectCount = SOURCE_VOICE_EFFECT::SOURCE_EFFECT_MAX;
	chain[EFFECT_CHAIN_SOURCE].pEffectDescriptors = sourceDescriptor;
	chain[EFFECT_CHAIN_MASTER].EffectCount = MASTER_VOICE_EFFECT::MASTER_EFFECT_MAX;
	chain[EFFECT_CHAIN_MASTER].pEffectDescriptors = &masterDescriptor;

	// エフェクトの設置
	soundTool->svtBase.sourceVoice->SetEffectChain(&chain[EFFECT_CHAIN_SOURCE]);
	soundTool->svtBase.sourceVoice->SetEffectParameters(0, &delayParameters, sizeof(delayParameters));
	soundTool->svtBase.sourceVoice->SetEffectParameters(1, &fadeParameters, sizeof(fadeParameters));
	tmpMasterVoice->SetEffectChain(&chain[EFFECT_CHAIN_MASTER]);

	// APOの解放
	saiDelayApo->Release();
	saiFadeApo->Release();
	volumeMeterAPO->Release();
}

//=============================================================================
// デストラクタ
//=============================================================================
SOUND_EFFECT::~SOUND_EFFECT(void)
{
	free(volumeMeter.pPeakLevels);
	free(volumeMeter.pRMSLevels);
}

//=============================================================================
// エフェクト
//=============================================================================
HRESULT SOUND_EFFECT::SetEffect(SOUND_TOOL *soundTool, int no, float percentage)
{
	switch(no)
	{
	case BUTTON_LIST::BUTTON_DELAY_REVERB:
		if (!delayUse)
		{
			delayUse = true;
			soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY,
				&delayParameters, sizeof(delayParameters));
			return soundTool->svtBase.sourceVoice->EnableEffect(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY);
		}
		else
		{
			delayUse = false;
			return soundTool->svtBase.sourceVoice->DisableEffect(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY);
		}
		break;
	case BUTTON_LIST::BUTTON_WET_VOL:
		delayParameters.wetVol = percentage * MAX_WET_VOL;
		return soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY,
			&delayParameters, sizeof(delayParameters));
		break;
	case BUTTON_LIST::BUTTON_DRY_VOL:
		delayParameters.dryVol = percentage * MAX_DRY_VOL;
		return soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY,
			&delayParameters, sizeof(delayParameters));
		break;
	case BUTTON_LIST::BUTTON_DELAY_TIME:
		delayParameters.delayTime = percentage * MAX_DELAY_TIME;
		return soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY,
			&delayParameters, sizeof(delayParameters));
		break;
	case BUTTON_LIST::BUTTON_REVERB_VOL:
		delayParameters.reverbVol = percentage * MAX_REVERB_VOL;
		return soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY,
			&delayParameters, sizeof(delayParameters));
		break;
	case BUTTON_LIST::BUTTON_FADE:
		if (!fadeUse)
		{
			fadeUse = true;
			soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN,
				&fadeParameters, sizeof(fadeParameters));
			return soundTool->svtBase.sourceVoice->EnableEffect(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN);
		}
		else
		{
			fadeUse = false;
			return soundTool->svtBase.sourceVoice->DisableEffect(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN);
		}
		break;
	case BUTTON_LIST::BUTTON_FADE_TIME:
		fadeParameters.fadeTime = percentage * MAX_FADE_TIME;
		return soundTool->svtBase.sourceVoice->SetEffectParameters(SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN,
			&fadeParameters, sizeof(fadeParameters));
		break;
	default:
		return E_FAIL;
		break;
	}
}

//=============================================================================
// ボリュームメーター
//=============================================================================
float SOUND_EFFECT::GetVolumeMeter(int no)
{
	tmpMasterVoice->GetEffectParameters(0, &volumeMeter, sizeof(volumeMeter));
	
	return volumeMeter.pPeakLevels[no];
}