//=============================================================================
//
// �T�E���h�G�t�F�N�g���� [soundEffect.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _SOUND_EFFECT_H_
#define _SOUND_EFFECT_H_

#include "main.h"
#include "SaiDelay.h"
#include "SaiFadeIn.h"
#include <xapobase.h>
#pragma comment (lib, "xapobase.lib")
#include <xaudio2fx.h>

//*****************************************************************************
// �萔��`
//*****************************************************************************
enum EFFECT_CHAIN
{
	EFFECT_CHAIN_SOURCE,
	EFFECT_CHAIN_MASTER,
	EFFECT_CHAIN_MAX
};

enum SOURCE_VOICE_EFFECT
{
	SOURCE_EFFECT_DELAY,
	SOURCE_EFFECT_FADE_IN,
	SOURCE_EFFECT_MAX
};

enum MASTER_VOICE_EFFECT
{
	MASTER_EFFECT_VOLUME_METER,
	MASTER_EFFECT_MAX
};


//*****************************************************************************
// �N���X
//*****************************************************************************
class SOUND_EFFECT
{
public:

	// �R���X�g���N�^
	SOUND_EFFECT(SOUND_TOOL *soundTool,IXAudio2MasteringVoice *masterVoice);
	// �f�X�g���N�^
	~SOUND_EFFECT(void);		

	// �G�t�F�N�g
	HRESULT SetEffect(SOUND_TOOL *soundTool, int no, float percentage);

	// �{�����[�����[�^�[
	float GetVolumeMeter(int no);

	// �p�����[�^�\���̂��擾
	SAI_APO_DELAY GetDelayParmeters(void) { return delayParameters; };
	bool GetDelayState(void) { return delayUse; };
	SAI_APO_FADE_IN GetFadeParameters(void) { return fadeParameters; };
	bool GetFadeState(void) { return fadeUse; };

private:
	IXAudio2MasteringVoice *tmpMasterVoice;	// �}�X�^�[�{�C�X

	XAUDIO2_EFFECT_CHAIN		chain[2];					// �G�t�F�N�g�`�F��
	XAUDIO2_EFFECT_DESCRIPTOR	masterDescriptor;			// �G�t�F�N�g�f�B�X�N���v�^
	XAUDIO2_EFFECT_DESCRIPTOR	sourceDescriptor[2];		// �G�t�F�N�g�f�B�X�N���v�^

	SAI_APO_DELAY	delayParameters;		// �p�����[�^�\����
	bool delayUse;
	SAI_APO_FADE_IN fadeParameters;			// �p�����[�^�\����
	bool fadeUse;

	XAUDIO2FX_VOLUMEMETER_LEVELS volumeMeter;	// �{�����[�����[�^�[

};

#endif