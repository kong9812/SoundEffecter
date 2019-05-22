#include "SaiFadeIn.h"

//=============================================================================
// APO�N���X�̓o�^
//=============================================================================
XAPO_REGISTRATION_PROPERTIES SAI_FADE_IN_APO::_regProps = {
	__uuidof(SAI_FADE_IN_APO),
	L"SAI_FADE_IN_APO",
	L"Copyright (C)2019 CHOI YAU KONG",
	1,
	0,
	XAPOBASE_DEFAULT_FLAG,
	1, 1, 1, 1 };

//=============================================================================
// �N���X�̏�����
//=============================================================================
SAI_FADE_IN_APO::SAI_FADE_IN_APO(SOUND_TOOL *svt) : CXAPOParametersBase(&_regProps, (BYTE *)apoParameter, sizeof(SAI_APO_FADE_IN), false)
{
	// �p�����[�^�̏�����
	for (int i = 0; i < 3; i++)
	{
		apoParameter[i].fadeTime = FADE_TIME;
	}

	// wavFile�̃R�s�[
	wavFmt = svt->svtBase.wavFmt;

	// �\�[�X�{�C�X�A�h���X�̃R�s�[
	sourceVoice = svt->svtBase.sourceVoice;
}

//=============================================================================
// LockForProcess�̃I�[�o�[���C�h
//=============================================================================
HRESULT SAI_FADE_IN_APO::LockForProcess
(UINT32 inputLockedParameterCount,
	const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS * pInputLockedParameters,
	UINT32 outputLockedParameterCount,
	const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS * pOutputLockedParameters)
{
	const HRESULT hr = CXAPOParametersBase::LockForProcess(
		inputLockedParameterCount,
		pInputLockedParameters,
		outputLockedParameterCount,
		pOutputLockedParameters);

	if (SUCCEEDED(hr))
	{
		memcpy(&inFormat, pInputLockedParameters[0].pFormat, sizeof(inFormat));
		memcpy(&outFormat, pOutputLockedParameters[0].pFormat, sizeof(outFormat));
	}

	return hr;
}

//=============================================================================
// OnSetParameters�̃I�[�o�[���C�h
//=============================================================================
void SAI_FADE_IN_APO::OnSetParameters
(const void* pParameters, UINT32 ParameterByteSize)
{
	SAI_APO_FADE_IN *tmpParameters = ((SAI_APO_FADE_IN *)pParameters);

	XAPOASSERT(sizeof(SAI_APO_FADE_IN) > 0);
	XAPOASSERT(pParameters != NULL);
	XAPOASSERT(ParameterByteSize == sizeof(SAI_APO_FADE_IN));
	XAPOASSERT(tmpParameters->fadeTime <= 0.0f);
	XAPOASSERT(tmpParameters->fadeTime >= 10.0f);

	// �t�F�C�h�\�̏��
	isFade			= false;
	fadeSample		= (int)(tmpParameters->fadeTime * wavFmt.fmt.fmtChannel * wavFmt.fmt.fmtSampleRate);
	fadeSampleIndex = 0;
}

//=============================================================================
// Process�̃I�[�o�[���C�h
//=============================================================================
void SAI_FADE_IN_APO::Process
(UINT32 inputProcessParameterCount,
	const XAPO_PROCESS_BUFFER_PARAMETERS * pInputProcessParameters,
	UINT32 outputProcessParameterCount,
	XAPO_PROCESS_BUFFER_PARAMETERS * pOutputProcessParameters,
	BOOL isEnabled)
{
	if (isEnabled)
	{
		// ���̃p�����[�^�\���� = �g�p����p�����[�^�̃|�C�����[
		SAI_APO_FADE_IN *tmpParmeter = (SAI_APO_FADE_IN *)BeginProcess();

		// �Đ��ʒu
		XAUDIO2_VOICE_STATE state;
		sourceVoice->GetState(&state);

		// �t�F�C�h
		if (state.SamplesPlayed % (wavFmt.data.waveSize / (int)sizeof(long)) == 0)
		{
			// �t�F�C�h�\�̏��
			isFade = false;
			fadeSample = (int)(tmpParmeter->fadeTime * wavFmt.fmt.fmtChannel * wavFmt.fmt.fmtSampleRate);
			fadeSampleIndex = 0;

		}
		if ((!isFade) && (pInputProcessParameters->BufferFlags != XAPO_BUFFER_SILENT))
		{
			// ���o�͂̃o�b�t�@
			float *inputBuf = (float *)pInputProcessParameters->pBuffer;
			float *outputBuf = (float *)pOutputProcessParameters->pBuffer;

			for (int i = 0; i < ((int)pInputProcessParameters->ValidFrameCount * wavFmt.fmt.fmtChannel); i++)
			{
				float tmp = (float)fadeSampleIndex / (float)fadeSample;
				outputBuf[i] = inputBuf[i] * tmp;

				fadeSampleIndex++;

				if (fadeSampleIndex >= fadeSample)
				{
					// �t�F�C�h����
					isFade = true;
				}
			}
			// �G���h�v���Z�X
			EndProcess();
		}
	}

}