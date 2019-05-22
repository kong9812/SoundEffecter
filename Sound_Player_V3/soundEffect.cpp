//=============================================================================
//
// ���� [.cpp]
// Author : �� �F��
//
//=============================================================================
#include "soundEffect.h"
#include "soundControl.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SOUND_EFFECT::SOUND_EFFECT(SOUND_TOOL *soundTool,IXAudio2MasteringVoice *masterVoice)
{
	// �}�X�^�[�{�C�X�̃A�h���X�R�s�[
	tmpMasterVoice = masterVoice;

	// �A�E�g�v�b�g�f�B�e�[��
	XAUDIO2_VOICE_DETAILS voiceDetails;
	soundTool->svtBase.sourceVoice->GetVoiceDetails(&voiceDetails);

	// �f�B���C
	IUnknown *saiDelayApo = (IXAPO *)new SAI_DELAY_APO;
	// �t�F�C�h
	IUnknown *saiFadeApo = (IXAPO *)new SAI_FADE_IN_APO(soundTool);
	// �{�����[�����[�^�[
	IUnknown *volumeMeterAPO;
	XAudio2CreateVolumeMeter(&volumeMeterAPO);

	// �f�B���C�̃p�����[�^
	delayParameters.wetVol		= 0.0f;
	delayParameters.dryVol		= 0.0f;
	delayParameters.delayTime	= 0.0f;
	delayParameters.reverbVol	= 0.0f;
	delayUse					= false;
	// �t�F�C�h�̃p�����[�^
	fadeParameters.fadeTime		= 0.0f;
	fadeUse						= false;
	// �{�����[�����[�^�[
	volumeMeter.ChannelCount = 2;
	volumeMeter.pPeakLevels = (float *)malloc(sizeof(float) * 2);
	volumeMeter.pRMSLevels = (float *)malloc(sizeof(float) * 2);
	memset(volumeMeter.pPeakLevels, 0, sizeof(volumeMeter.pPeakLevels));
	memset(volumeMeter.pRMSLevels, 0, sizeof(volumeMeter.pRMSLevels));

	// �f�B�X�N���v�^
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY].InitialState = delayUse;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY].OutputChannels = voiceDetails.InputChannels;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_DELAY].pEffect = saiDelayApo;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN].InitialState = fadeUse;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN].OutputChannels = voiceDetails.InputChannels;
	sourceDescriptor[SOURCE_VOICE_EFFECT::SOURCE_EFFECT_FADE_IN].pEffect = saiFadeApo;

	// �A�E�g�v�b�g�f�B�e�[��
	tmpMasterVoice->GetVoiceDetails(&voiceDetails);

	masterDescriptor.InitialState = true;
	masterDescriptor.OutputChannels = voiceDetails.InputChannels;
	masterDescriptor.pEffect = volumeMeterAPO;

	// �`�F��
	chain[EFFECT_CHAIN_SOURCE].EffectCount = SOURCE_VOICE_EFFECT::SOURCE_EFFECT_MAX;
	chain[EFFECT_CHAIN_SOURCE].pEffectDescriptors = sourceDescriptor;
	chain[EFFECT_CHAIN_MASTER].EffectCount = MASTER_VOICE_EFFECT::MASTER_EFFECT_MAX;
	chain[EFFECT_CHAIN_MASTER].pEffectDescriptors = &masterDescriptor;

	// �G�t�F�N�g�̐ݒu
	soundTool->svtBase.sourceVoice->SetEffectChain(&chain[EFFECT_CHAIN_SOURCE]);
	soundTool->svtBase.sourceVoice->SetEffectParameters(0, &delayParameters, sizeof(delayParameters));
	soundTool->svtBase.sourceVoice->SetEffectParameters(1, &fadeParameters, sizeof(fadeParameters));
	tmpMasterVoice->SetEffectChain(&chain[EFFECT_CHAIN_MASTER]);

	// APO�̉��
	saiDelayApo->Release();
	saiFadeApo->Release();
	volumeMeterAPO->Release();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SOUND_EFFECT::~SOUND_EFFECT(void)
{
	free(volumeMeter.pPeakLevels);
	free(volumeMeter.pRMSLevels);
}

//=============================================================================
// �G�t�F�N�g
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
// �{�����[�����[�^�[
//=============================================================================
float SOUND_EFFECT::GetVolumeMeter(int no)
{
	tmpMasterVoice->GetEffectParameters(0, &volumeMeter, sizeof(volumeMeter));
	
	return volumeMeter.pPeakLevels[no];
}