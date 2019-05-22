#ifndef _SAI_FADE_IN_H_
#define _SAI_FADE_IN_H_

#include "sound.h"
#include <xapobase.h>
#pragma comment(lib,"xapobase.lib")

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
#define FADE_TIME	(0.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// SAI��I �t�F�C�h�C��(only for 2ch)
{
	float			fadeTime;		// �x���̕b��
}SAI_APO_FADE_IN;

//*****************************************************************************
// SAI_FADE_IN_APO (only for 2ch)
//*****************************************************************************
class __declspec(uuid("{80D4BED4-7605-4E4C-B29C-5479C375C599}"))SAI_FADE_IN_APO : public CXAPOParametersBase
{
public:
	SAI_FADE_IN_APO(SOUND_TOOL *svt);	// �������p
	~SAI_FADE_IN_APO() {};					// �I���p

	// LockForProcess�̃I�[�o�[���C�h
	STDMETHOD(LockForProcess)
		(UINT32 inputLockedParameterCount,
			const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS * pInputLockedParameters,
			UINT32 outputLockedParameterCount,
			const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS * pOutputLockedParameters)
		override;

	// Process�̃I�[�o�[���C�h
	STDMETHOD_(void, Process)
		(UINT32 inputProcessParameterCount,
			const XAPO_PROCESS_BUFFER_PARAMETERS * pInputProcessParameters,
			UINT32 outputProcessParameterCount,
			XAPO_PROCESS_BUFFER_PARAMETERS * pOutputProcessParameters,
			BOOL isEnabled)
		override;

	// OnSetParameters�̃I�[�o�[���C�g
	virtual void OnSetParameters
	(const void* pParameters, UINT32 ParameterByteSize);

private:
	static XAPO_REGISTRATION_PROPERTIES _regProps;

	// �t�H�[�}�b�g
	WAVEFORMATEX inFormat;
	WAVEFORMATEX outFormat;

	// WAV�t�@�C��
	WAV_FILE	wavFmt;

	// �t�F�C�h�p
	bool	isFade;		// true:�t�F�C�h�� false:�t�F�C�h����
	float	*backupBuf;
	int		fadeSample;
	int		fadeSampleIndex;

	IXAudio2SourceVoice *sourceVoice;

	// �p�����[�^
	SAI_APO_FADE_IN apoParameter[3];
};

#endif