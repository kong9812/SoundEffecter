//=============================================================================
//
// �T�E���h�R���g���[�� [soundControl.h]
// Author : �� �F��
//
//=============================================================================
#include "soundControl.h"
#include "waveOut.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SOUND_CONTROL::SOUND_CONTROL(HWND hWnd)
{
	// �T�E���h�̏�����
	sound = new SOUND();

	// �T�E���h�̓ǂݍ���
	soundTool.svtBase.sourceVoice = sound->LoadXAudio2Voice(hWnd, &soundTool);

	// �Đ�
	sound->PlayVoice(&soundTool);

	// �T�E���h�̏�����
	soundEffect = new SOUND_EFFECT(&soundTool, sound->GetMasterVoice());

	// �p�����[�^�\����
	soundParameter.mainVol		= INIT_MAIN_VOL;		// ���C���{������		
	soundParameter.panVol		= INIT_PAN_VOL;			// �p�����H�����[��
	soundParameter.freq			= INIT_FREQ;			// (�Đ����g��)�s�[�`
	soundParameter.delayReverb	= INIT_DELAY_REVERB;	// �f�B���C�{���o�[�u
	soundParameter.wetVol		= INIT_WET_VOL;			// �E�F�b�g�{�C�X�̃{�����[��
	soundParameter.dryVol		= INIT_DRY_VOL;			// �h���C�{�C�X�̃{�����[��
	soundParameter.delayTime	= INIT_DELAY_TIME;		// �f�B���C�^�C��		
	soundParameter.reverbVol	= INIT_REVERB_VOL;		// �c���̃{�����[�� 
	soundParameter.fade			= INIT_FADE;			// �t�F�C�h
	soundParameter.fadeTime		= INIT_FADE_TIME;		// �t�F�C�h�^�C��		

	// �v���b�g�̃p�X���擾
	OpenGnuplot(hWnd);
	OutputWaveGnuplot(soundTool, sound->GetWavFile()->GetOldPath(), NULL);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SOUND_CONTROL::~SOUND_CONTROL(void)
{
	// ���̒�~
	sound->StopVoice(&soundTool);

	// �\�[�X�{�C�X�̃��������
	if (soundTool.svtBase.sourceVoice != NULL)
	{
		soundTool.svtBase.sourceVoice->DestroyVoice();
		soundTool.svtBase.sourceVoice = NULL;
	}

	delete soundEffect;
	delete sound;
}	

//=============================================================================
// �v���Z�X
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
// ���̏����o��
//=============================================================================
void SOUND_CONTROL::OutputWav(void)
{
	//--�f�B���C�{���o�[�u--// 
	soundParameter.delayReverb = soundEffect->GetDelayState();				// �f�B���C�{���o�[�u
	soundParameter.wetVol = soundEffect->GetDelayParmeters().wetVol;		// �E�F�b�g�{�C�X�̃{�����[��
	soundParameter.dryVol = soundEffect->GetDelayParmeters().dryVol;		// �h���C�{�C�X�̃{�����[��
	soundParameter.delayTime = soundEffect->GetDelayParmeters().delayTime;	// �f�B���C�^�C��		
	soundParameter.reverbVol = soundEffect->GetDelayParmeters().reverbVol;	// �c���̃{�����[�� 

	//-------�t�F�C�h-------//
	soundParameter.fade		= soundEffect->GetFadeState();					// �t�F�C�h
	soundParameter.fadeTime = soundEffect->GetFadeParameters().fadeTime;	// �t�F�C�h�^�C��		

	SetWaveData(&soundTool, sound->GetWavFile()->GetOldPath(), soundParameter);
}

//=============================================================================
// �{�����[�����[�^�[
//=============================================================================
float SOUND_CONTROL::GetBalVolumeMeter(int no)
{
	// �{�����[�����[�^�[
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