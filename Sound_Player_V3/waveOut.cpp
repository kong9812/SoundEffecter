//=============================================================================
//
// ���f�[�^�̏����o������ [waveOut.h]
// Author : �� �F��
//
//=============================================================================
#include "waveOut.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void OutWavFile(SOUND_TOOL *soundTool);	// �t�@�C���̏����o��

//=============================================================================
// �O���[�o���ϐ�:
//=============================================================================
float	*backupBuf;
int		delaySample;
int		readPos;
int		writePos;
short	*tmpData;

//=============================================================================
// �g�`�f�[�^
//=============================================================================
void SetWaveData(SOUND_TOOL *soundTool, char *oldPath, SOUND_PARAMETER parameter)
{
	// �x���������ł���T���v�����O��(2�b�̒x��)
	delaySample = (int)(soundTool->svtBase.wavFmt.fmt.fmtSampleRate *
		soundTool->svtBase.wavFmt.fmt.fmtChannel * 2);

	// �������m��(2�b�̃T���v�����O)
	backupBuf = (float *)malloc(sizeof(float) * delaySample);

	// ������
	memset(backupBuf, 0, sizeof(float) * delaySample);

	// �ǂݍ��݈ʒu�̏�����
	readPos = 0;

	// �����o���ʒu�̏�����
	writePos = 0;

	// �t�@�C���T�C�Y
	//int tmpSize = soundTool->svtBase.wavFmt.data.waveSize + (soundTool->svtBase.wavFmt.fmt.fmtChannel * soundTool->svtBase.wavFmt.fmt.fmtSampleRate * 2 * sizeof(short));

	// ����������f�[�^[Output]
	tmpData = (short *)malloc(soundTool->svtBase.wavFmt.data.waveSize);
	//tmpData = (short *)malloc(tmpSize);
	memset(tmpData, 0, sizeof(tmpData));

	// ���̒x���T���v�����O
	int tmpDelaySample = (int)(delaySample * (parameter.delayTime / 2.0f));

	// �t�F�C�h
	int fadeSample = (int)(parameter.fadeTime * soundTool->svtBase.wavFmt.fmt.fmtChannel * 
		soundTool->svtBase.wavFmt.fmt.fmtSampleRate);
	int fadeSampleIndex = 0;

	for (int i = 0; i < soundTool->svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
	//for (int i = 0; i < tmpSize / (int)sizeof(short); i++)
	{
		// �o�b�t�@�̕ۑ�
		backupBuf[writePos] = (float)(soundTool->svtBase.wavFmt.data.waveData[i] + backupBuf[readPos] * parameter.reverbVol);
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

		// �f�B���C����
		tmpData[i] = (short)((backupBuf[readPos] * parameter.wetVol) + (soundTool->svtBase.wavFmt.data.waveData[i] * parameter.dryVol));
	
		// �t�F�C�h
		if (fadeSampleIndex < fadeSample)
		{
			float tmp = (float)fadeSampleIndex / (float)fadeSample;
			tmpData[i] = (short)(tmpData[i] * tmp);

			fadeSampleIndex++;
		}
	}

	// �X�V
	OutputWaveGnuplot(*soundTool, oldPath, tmpData);

	// �t�@�C���̏����o��
	OutWavFile(soundTool);

	// ���������
	free(backupBuf);

	// ���������
	free(tmpData);
}

//=============================================================================
// �t�@�C���̏����o��
//=============================================================================
void OutWavFile(SOUND_TOOL *soundTool)
{
	FILE *fp;

	// �t�@�C���̏���
	fopen_s(&fp, "test.wav", "wb");

	// RIFF�̏����o��
	fwrite(&soundTool->svtBase.wavFmt.riff, sizeof(RIFF_CHUNK), 1, fp);

	// FMT�̏����o��
	fwrite(&soundTool->svtBase.wavFmt.fmt, sizeof(FMT_CHUNK), 1, fp);

	// DATA�̏����o��
	fwrite(&soundTool->svtBase.wavFmt.data.dataChunk, sizeof(soundTool->svtBase.wavFmt.data.dataChunk), 1, fp);
	fwrite(&soundTool->svtBase.wavFmt.data.waveSize, sizeof(soundTool->svtBase.wavFmt.data.waveSize), 1, fp);
	fwrite(tmpData, soundTool->svtBase.wavFmt.data.waveSize, 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);
}