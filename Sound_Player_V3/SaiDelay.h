#ifndef _SAI_DELAY_H_
#define _SAI_DELAY_H_

#include "LoadSoundClass.h"
#include "sound.h"
#include <xapobase.h>
#pragma comment(lib,"xapobase.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DELAY_WET_VOLUME		(0.0f)
#define DELAY_DRY_VOLUME		(0.0f)
#define DELAY_TIME_DEFAULT		(0.0f)
#define DELAY_REVERB_VOLUME		(0.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// SAI��I �x������(only for 2ch)
{
	float			wetVol;			// �E�F�b�g�̉���
	float			dryVol;			// �h���C�̉���
	float			delayTime;		// �x���̕b��
	float			reverbVol;		// �c���̉���

}SAI_APO_DELAY;

//*****************************************************************************
// SAI_DELAY_APO (only for 2ch)
//*****************************************************************************
class __declspec(uuid("{80D4BED4-7605-4E4C-B29C-5479C375C599}"))SAI_DELAY_APO : public CXAPOParametersBase
{
public:
	SAI_DELAY_APO();	// �������p
	~SAI_DELAY_APO();				// �I���p

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

	// �R�s�[�p
	float	*backupBuf;
	int		delaySample;
	int		readPos;
	int		writePos;
	bool	play;

	// �p�����[�^
	SAI_APO_DELAY apoParameter[3];
};

#endif