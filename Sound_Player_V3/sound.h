//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "LoadSoundClass.h"
#include <xaudio2.h>
#pragma comment (lib, "xaudio2.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SOUND_INIT_SUCCEEDED				(3)
#define SOUND_DEFAULT_VOLUME				(1.0f)
#define SOUND_LOOP_CNT_NOPE					(XAUDIO2_NO_LOOP_REGION)
#define SOUND_LOOP_CNT_INFINITE				(XAUDIO2_LOOP_INFINITE)

//*****************************************************************************
//�\���̐錾
//*****************************************************************************
typedef struct
{
	IXAudio2SourceVoice *sourceVoice;		// �ύX���Ȃ��ł�������! DONT CHANGE ANYTHING!
	IXAudio2SubmixVoice *mainSubmixVoice;	// �ύX���Ȃ��ł�������! DONT CHANGE ANYTHING!
	IXAudio2SubmixVoice *DrySubmixVoice;	// �ύX���Ȃ��ł�������! DONT CHANGE ANYTHING!
	IXAudio2SubmixVoice *WetSubmixVoice;	// �ύX���Ȃ��ł�������! DONT CHANGE ANYTHING!
	WAV_FILE			wavFmt;				// �ύX���Ȃ��ł�������! DONT CHANGE ANYTHING!
	bool				isPlay;				// �ύX���Ȃ��ł�������! DONT CHANGE ANYTHING!
	int					loopCnt;			// ���[�v�p�J�E���^�[
}SOUND_BASE;

typedef struct
{
	float				freqPich;			// �s�[�`
	
}SOUND_SECONDARY;

typedef struct
{
	SOUND_BASE		svtBase;			// SVT�̃x�[�X����
	SOUND_SECONDARY	svtSecondary;		// SVT�̊�{�p�����[�^

}SOUND_TOOL;

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class SOUND
{
public:
	SOUND(void);	// ������
	~SOUND(void);	// �I������

	// ���[�h�T�E���h�֐�
	IXAudio2SourceVoice *LoadXAudio2Voice(HWND hWnd, SOUND_TOOL *svt);

	// �������̌���(True:���� False:���s)
	bool InitCheck();

	// �}�X�^�[�{�C�X���擾
	IXAudio2MasteringVoice *GetMasterVoice(void);

	// �Đ�
	HRESULT PlayVoice(SOUND_TOOL *svt);

	// �Đ�
	HRESULT StopVoice(SOUND_TOOL *svt);

	// �ꎞ��~
	HRESULT PauseVoice(SOUND_TOOL *svt);

	// ���C���{������
	HRESULT SetMainVolume(SOUND_TOOL *svt, float volume);

	// �p���{�����[��
	HRESULT SetPanVolume(SOUND_TOOL *svt, float panVolume);

	// (frequency ratio)�s�[�`
	HRESULT SetPitch(SOUND_TOOL *svt,float pitch);
	float	GetPitch(SOUND_TOOL *svt);

	// WAV�t�@�C�����擾
	SAI_LOAD_WAV *GetWavFile(void) { return wavFile; };

	// �t�@�C����
	char *GetFileName(void) { return fileName; };

private:
	SAI_LOAD_WAV			*wavFile;					// wav�t�@�C���̓ǂݍ��ݗp�N���X

	IXAudio2MasteringVoice	*masteringVoice = NULL;		// �}�X�^�[�{�C�X
	IXAudio2				*xAudio2		= NULL;		// XAudio2�̃C���^�[�t�F�C�X
	
	int						initCheck		= 0;		// �������̌���
	float					*channelVolume	= NULL;		// �{�����[��
	char					fileName[CHAR_MAX];			// �T�E���h�̖��O
	char					soundPath[CHAR_MAX];		// �T�E���h�t�@�C���̃p�X
};

#endif