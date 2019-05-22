//=============================================================================
//
// �T�E���h�R���g���[�� [soundControl.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _SOUND_CONTROL_
#define _SOUND_CONTROL_

#include "main.h"
#include "sound.h"
#include "soundEffect.h"
#include "buttonIcon.h"
#include "plot.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �p�����[�^�̏����l
//-------------�Đ��p-------------//
#define INIT_MAIN_VOL		(1.0f)		// ���C���{������
#define MAX_MAIN_VOL		(1.0f)
#define MIN_MAIN_VOL		(0.0f)

#define INIT_PAN_VOL		(0.0f)		// �p�����H�����[��
#define MAX_PAN_VOL			(1.0f)
#define MIN_PAN_VOL			(-1.0f)

#define INIT_FREQ			(1.0f)		// (�Đ����g��)�s�[�`
#define MAX_FREQ			(2.0f)
#define MIN_FREQ			(-1.0f)

//-------�f�B���C�{���o�[�u-------//
#define INIT_DELAY_REVERB	(false)		// �f�B���C�{���o�[�u

#define INIT_WET_VOL		(0.0f)		// �E�F�b�g�{�C�X�̃{�����[��
#define MAX_WET_VOL			(0.5f)
#define MIN_WET_VOL			(0.0f)

#define INIT_DRY_VOL		(0.0f)		// �h���C�{�C�X�̃{�����[��
#define MAX_DRY_VOL			(0.5f)
#define MIN_DRY_VOL			(0.0f)

#define INIT_DELAY_TIME		(0.0f)		// �f�B���C�^�C��
#define MAX_DELAY_TIME		(2.0f)
#define MIN_DELAY_TIME		(0.0f)

#define INIT_REVERB_VOL		(0.0f)		// �c���̃{�����[��
#define MAX_REVERB_VOL		(0.5f)
#define MIN_REVERB_VOL		(0.0f)

//------------�t�F�C�h------------//
#define INIT_FADE			(false)		// �t�F�C�h

#define INIT_FADE_TIME		(0.0f)		// �t�F�C�h�^�C��
#define MAX_FADE_TIME		(10.0f)
#define MIN_FADE_TIME		(0.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct
{
	//--------�Đ��p--------//
	float mainVol;		// ���C���{������			
	float panVol;		// �p�����H�����[��
	float freq;			// (�Đ����g��)�s�[�`

	//--�f�B���C�{���o�[�u--// 
	bool  delayReverb;	// �f�B���C�{���o�[�u
	float wetVol;		// �E�F�b�g�{�C�X�̃{�����[��
	float dryVol;		// �h���C�{�C�X�̃{�����[��
	float delayTime;	// �f�B���C�^�C��		
	float reverbVol;	// �c���̃{�����[�� 

	//-------�t�F�C�h-------//
	bool  fade;			// �t�F�C�h
	float fadeTime;		// �t�F�C�h�^�C��		

}SOUND_PARAMETER;				

//*****************************************************************************
// �N���X
//*****************************************************************************
class SOUND_CONTROL
{
public:
	SOUND_CONTROL(HWND hWnd);			// �R���X�g���N�^
	~SOUND_CONTROL();					// �f�X�g���N�^

	void soundControlProcess(int no, float percentage);		// �v���Z�X

	float GetBalVolumeMeter(int no);						// �{�����[�����[�^�[

	// ���̏����o��
	void OutputWav(void);

	// sound���擾
	SOUND *GetSound(void) { return sound; };

private:
	SOUND				*sound;			// �T�E���h�p
	SOUND_EFFECT		*soundEffect;	// �T�E���h�G�t�F�N�g�p
	SOUND_TOOL			soundTool;		// �T�E���h�p

	SOUND_PARAMETER		soundParameter;	// �p�����[�^�\����

	float				tmpVolMeter;
	float				volMeter;
	int					frameCnt;
								
};
#endif