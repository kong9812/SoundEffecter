//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �� �F��
//
//=============================================================================
#include "sound.h"

//=============================================================================
// ������
//=============================================================================
SOUND::SOUND(void)
{
	// COM���C�u�����̏�����
	if (SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		// ����+1
		initCheck++;

		// XAudio2�I�u�W�F�N�g�̍쐬
		if (SUCCEEDED(XAudio2Create(&xAudio2)))
		{
			XAUDIO2_DEBUG_CONFIGURATION debugConfig{ NULL };
			debugConfig.LogThreadID = true;
			debugConfig.TraceMask = XAUDIO2_LOG_WARNINGS;
			debugConfig.TraceMask = debugConfig.TraceMask | XAUDIO2_LOG_FUNC_CALLS | XAUDIO2_LOG_DETAIL;
			debugConfig.BreakMask = XAUDIO2_LOG_ERRORS;

			xAudio2->SetDebugConfiguration(&debugConfig);

			// ����+1
			initCheck++;

			// �}�X�^�[�{�C�X�̍쐬
			if (SUCCEEDED(xAudio2->CreateMasteringVoice(&masteringVoice)))
			{
				// ����+1
				initCheck++;

				// �N���Xnew
				wavFile = new SAI_LOAD_WAV;
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
SOUND::~SOUND(void)
{
	// �}�X�^�[�{�C�X
	if (masteringVoice != NULL)
	{
		masteringVoice->DestroyVoice();
		masteringVoice = NULL;
	}

	// �C���^�[�t�F�[�X
	if (xAudio2 != NULL)
	{
		xAudio2->Release();
		xAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();

	// �{�����[���̃��������
	free(channelVolume);

	// �N���Xdelete
	delete wavFile;
}

//=============================================================================
// �������̌���
//=============================================================================
bool SOUND::InitCheck()
{
	// ���������� = �O���SUCCEEDED
	if (initCheck != SOUND_INIT_SUCCEEDED)
	{
		return false;
	}

	return true;
}

//=============================================================================
// �}�X�^�[�{�C�X���擾
//=============================================================================
IXAudio2MasteringVoice *SOUND::GetMasterVoice(void)
{
	return masteringVoice;
}

//==============================================================
// ���[�h�T�E���h
//==============================================================
IXAudio2SourceVoice *SOUND::LoadXAudio2Voice(HWND hWnd, SOUND_TOOL *svt)
{
	IXAudio2SourceVoice *sourceVoice = NULL;	// �\�[�X�{�C�X
	WAVEFORMATEX		pcm;					// WAVEFORMATEX�\����
	XAUDIO2_BUFFER		buffer;					// �o�b�t�@

	{// ���[�J���ϐ��̏�����

		// �\���̂̏�����
		memset(&pcm, 0, sizeof(WAVEFORMATEX));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �t�@�C���̃p�X���擾
		wavFile->OpenSound(hWnd, fileName, soundPath);

		// wav�t�@�C���̓ǂݍ���(WAVEFORMATEX�\����)
		pcm = wavFile->LoadWavFile(soundPath, &svt->svtBase.wavFmt);

		// �o�b�t�@�̐ݒ�
		buffer.pAudioData	= (BYTE *)svt->svtBase.wavFmt.data.waveData;
		buffer.Flags		= XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes	= svt->svtBase.wavFmt.data.waveSize;
		buffer.LoopCount	= XAUDIO2_LOOP_INFINITE;
	}

	// �\�[�X�{�C�X�̍쐬
	if (FAILED(xAudio2->CreateSourceVoice(&sourceVoice, &pcm, NULL, XAUDIO2_MAX_FREQ_RATIO)))
	{
		return NULL;
	}

	// �o�b�t�@���o
	if (FAILED(sourceVoice->SubmitSourceBuffer(&buffer)))
	{
		return NULL;
	}

	{// �{�����[���̏�����
		// �������m��[�`�����l����]
		channelVolume = (float *)malloc(svt->svtBase.wavFmt.fmt.fmtChannel * sizeof(float));
		for (int i = 0; i < svt->svtBase.wavFmt.fmt.fmtChannel; i++)
		{
			channelVolume[i] = SOUND_DEFAULT_VOLUME;
		}
	}

	return sourceVoice;
}

//=============================================================================
// �Đ�
//=============================================================================
HRESULT SOUND::PlayVoice(SOUND_TOOL *svt)
{
	// �{�C�X�ƍĐ���Ԃ̃`�F�b�N
	if ((svt->svtBase.sourceVoice != NULL) && (!svt->svtBase.isPlay))
	{
		// �Đ�
		svt->svtBase.sourceVoice->Start();

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// ��~
//=============================================================================
HRESULT SOUND::StopVoice(SOUND_TOOL *svt)
{
	// �{�C�X�ƍĐ���Ԃ̃`�F�b�N
	if ((svt->svtBase.sourceVoice != NULL) && (svt->svtBase.isPlay))
	{
		// ��~
		svt->svtBase.sourceVoice->Stop();

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// �ꎞ��~
//=============================================================================
HRESULT SOUND::PauseVoice(SOUND_TOOL *svt)
{
	// �{�C�X�ƍĐ���Ԃ̃`�F�b�N
	if ((svt->svtBase.sourceVoice != NULL) && (svt->svtBase.isPlay))
	{
		// �ꎞ��~
		svt->svtBase.sourceVoice->Stop(XAUDIO2_PLAY_TAILS);

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// ���C���{������
//=============================================================================
HRESULT SOUND::SetMainVolume(SOUND_TOOL *svt,float volume)
{
	// �{�C�X�̃`�F�b�N
	if (svt->svtBase.sourceVoice != NULL)
	{
		// ���C���{������
		svt->svtBase.sourceVoice->SetVolume(volume);

		return S_OK;
	}

	return S_FALSE;
}

//==============================================================
// �p���{�����[��
//==============================================================
HRESULT SOUND::SetPanVolume(SOUND_TOOL *svt, float panVolume)
{
	// �{�C�X�̃`�F�b�N
	if (svt->svtBase.sourceVoice != NULL)
	{
		float vol[4];
		float tmpVolume = panVolume + 1.0f;
		float radian = D3DXToRadian((tmpVolume / 2.0f) * 90.0f);

		// Left
		vol[0] = sinf(radian);
		vol[1] = 0.0f;

		// Right
		vol[2] = 0.0f;
		vol[3] = cosf(radian);

		svt->svtBase.sourceVoice->SetOutputMatrix
		(masteringVoice, svt->svtBase.wavFmt.fmt.fmtChannel, 2, vol);

		return S_OK;
	}

	return S_FALSE;
}

//=============================================================================
// (frequency ratio)�s�[�`
//=============================================================================
HRESULT SOUND::SetPitch(SOUND_TOOL *svt,float pich)
{
	// �{�C�X�ƃp�����[�^�̃`�F�b�N
	if ((svt->svtBase.sourceVoice != NULL) && 
		(pich > XAUDIO2_MIN_FREQ_RATIO) &&
		(pich < XAUDIO2_MAX_FREQ_RATIO))
	{
		// �s�[�`��ݒ�
		return svt->svtBase.sourceVoice->SetFrequencyRatio(pich);
	}
	return S_FALSE;
}
float SOUND::GetPitch(SOUND_TOOL *svt)
{
	float pitch = 0;

	// �{�C�X�̃`�F�b�N
	if (svt->svtBase.sourceVoice != NULL)
	{
		// �s�[�`���擾
		svt->svtBase.sourceVoice->GetFrequencyRatio(&pitch);

		return pitch;
	}

	return pitch;
}
