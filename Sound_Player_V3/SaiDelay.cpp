#include "SaiDelay.h"

//=============================================================================
// APO�N���X�̓o�^
//=============================================================================
XAPO_REGISTRATION_PROPERTIES SAI_DELAY_APO::_regProps = {
	__uuidof(SAI_DELAY_APO),
	L"SAI_DELAY_APO",
	L"Copyright (C)2019 CHOI YAU KONG",
	1,
	0,
	XAPOBASE_DEFAULT_FLAG,
	1, 1, 1, 1 };

//=============================================================================
// �N���X�̏�����
//=============================================================================
SAI_DELAY_APO::SAI_DELAY_APO() : CXAPOParametersBase(&_regProps, (BYTE *)apoParameter, sizeof(SAI_APO_DELAY), false)
{
	// �p�����[�^�̏�����
	for (int i = 0; i < 3; i++)
	{
		apoParameter[i].wetVol		= DELAY_WET_VOLUME;
		apoParameter[i].dryVol		= DELAY_DRY_VOLUME;
		apoParameter[i].delayTime	= DELAY_TIME_DEFAULT;
		apoParameter[i].reverbVol	= DELAY_REVERB_VOLUME;
	}
}

//=============================================================================
// �N���X�̏I������
//=============================================================================
SAI_DELAY_APO::~SAI_DELAY_APO()
{
	// ���������
	free(backupBuf);
}

//=============================================================================
// LockForProcess�̃I�[�o�[���C�h
//=============================================================================
HRESULT SAI_DELAY_APO::LockForProcess
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

	// �x���������ł���T���v�����O��(2�b�̒x��)
	delaySample = inFormat.nSamplesPerSec * inFormat.nChannels * 2;

	// �������m��(2�b�̃T���v�����O)
	backupBuf = (float *)malloc(sizeof(float) * delaySample);

	return hr;
}

//=============================================================================
// OnSetParameters�̃I�[�o�[���C�h
//=============================================================================
void SAI_DELAY_APO::OnSetParameters
(const void* pParameters, UINT32 ParameterByteSize)
{
	SAI_APO_DELAY *tmpParameters = ((SAI_APO_DELAY *)pParameters);

	XAPOASSERT(sizeof(SAI_APO_DELAY) > 0);
	XAPOASSERT(pParameters != NULL);
	XAPOASSERT(ParameterByteSize == sizeof(SAI_APO_DELAY));
	XAPOASSERT(tmpParameters->dryVol >= 0);
	XAPOASSERT(tmpParameters->wetVol >= 0);
	XAPOASSERT(tmpParameters->reverbVol >= 0);
	XAPOASSERT(tmpParameters->delayTime >= 0);
	XAPOASSERT(tmpParameters->dryVol <= 1.0f);
	XAPOASSERT(tmpParameters->wetVol <= 1.0f);
	XAPOASSERT(tmpParameters->reverbVol <= 0.5f);
	XAPOASSERT(tmpParameters->delayTime <= 2.0f);

	// ������
	memset(backupBuf, 0, sizeof(float) * delaySample);

	// �ǂݍ��݈ʒu�̏�����
	readPos = 0;

	// �����o���ʒu�̏�����
	writePos = 0;
}

//=============================================================================
// Process�̃I�[�o�[���C�h
//=============================================================================
void SAI_DELAY_APO::Process
(UINT32 inputProcessParameterCount,
	const XAPO_PROCESS_BUFFER_PARAMETERS * pInputProcessParameters,
	UINT32 outputProcessParameterCount,
	XAPO_PROCESS_BUFFER_PARAMETERS * pOutputProcessParameters,
	BOOL isEnabled)
{
	if (isEnabled)
	{
		if (pInputProcessParameters->BufferFlags != XAPO_BUFFER_SILENT)
		{
			// ���̃p�����[�^�\���� = �g�p����p�����[�^�̃|�C�����[
			SAI_APO_DELAY *tmpParmeter = (SAI_APO_DELAY *)BeginProcess();

			int tmpDelaySample = (int)(delaySample * (tmpParmeter->delayTime / 2.0f));

			// ���o�͂̃o�b�t�@
			float *inputBuf = (float *)pInputProcessParameters->pBuffer;
			float *outputBuf = (float *)pOutputProcessParameters->pBuffer;

			for (int i = 0; i < ((int)pInputProcessParameters->ValidFrameCount * inFormat.nChannels); i++)
			{
				// �o�b�t�@�̕ۑ�
				backupBuf[writePos] = inputBuf[i] + backupBuf[readPos] * tmpParmeter->reverbVol;
				writePos++;
				if (writePos >= tmpDelaySample)	// �I�[�o�[�h�~
				{
					// 0�Ԗڂɖ߂�
					writePos = 0;
				}

				// ����
				readPos = (int)(writePos - tmpDelaySample);
				if (readPos < 0)	// �I�[�o�[�h�~
				{
					// 0�Ԗڂɖ߂�
					readPos += tmpDelaySample;
				}

				// ����
				outputBuf[i] = (backupBuf[readPos] * tmpParmeter->wetVol) + (inputBuf[i] * tmpParmeter->dryVol);
			}

			// �G���h�v���Z�X
			EndProcess();
		}
	}
}