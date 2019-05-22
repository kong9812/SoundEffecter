#include "LoadSoundClass.h"

//=============================================================================
// �T�E���h�̓ǂݍ���
//=============================================================================
bool SAI_LOAD_WAV::OpenSound(HWND hWnd, char *fileName, char soundPath[])
{
	OPENFILENAME ofn;
	char path[CHAR_MAX];
	WIN32_FIND_DATA fileData;

	// �J�����g�f�B���N�g�������o��
	GetCurrentDirectory(MAX_PATH, oldPath);

	path[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));  //�\���̂�0�ŃN���A
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrInitialDir = oldPath;
	ofn.lpstrFilter = "sound file(*.wav)\0*.wav\0\0";
	ofn.lpstrFile = path;
	ofn.nMaxFile = sizeof(path);
	ofn.lpstrDefExt = "wav";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	strcpy(soundPath, path);

	// �t�@�C���������o��
	FindFirstFile(ofn.lpstrFile, &fileData);

	// �t�@�C����
	memcpy(fileName, fileData.cFileName, sizeof(char)*CHAR_MAX);
	//fileName = fileData.cFileName;

	// �J�����g�f�B���N�g����ݒ肷��
	SetCurrentDirectory(oldPath);

	return TRUE;
}

//*****************************************************************************
// WAV�t�@�C���̓ǂݍ���(WAVEFORMATEX�\����)
//*****************************************************************************
WAVEFORMATEX SAI_LOAD_WAV::LoadWavFile(const char *path, WAV_FILE  *wavfile)
{
	WAVEFORMATEX	pcm;				// WAVEFORMATEX�\����
	FILE			*fp;				// �t�@�C���\����							
	int				chunkFlag = NULL;	// �`�����N��T�����[�v�̃t���O

	{// ���[�J���ϐ��̏�����
		memset(&pcm, 0, sizeof(WAVEFORMATEX));
		memset(&fp, 0, sizeof(FILE));
	}
	// �t�@�C���̏���
	fopen_s(&fp, path, "rb");

	// RIFF�̓ǂݍ���
	fread(&wavfile->riff, sizeof(RIFF_CHUNK), 1, fp);

	// FMT��DATA�̓ǂݍ���
	while (chunkFlag != FLAG_CHUNK_END)
	{
		char	chunk[CHUNK_SIZE];
		long	size = 0;

		// �`�����N�ƃT�C�Y�̓ǂݍ���
		fread(&chunk, sizeof(chunk), 1, fp);
		fread(&size, sizeof(size), 1, fp);

		// fmt�`�����N
		if (memcmp(chunk, CHUNK_FMT, CHUNK_SIZE) == CHUNK_SAME)
		{
			// �`�����N�ƃT�C�Y��ݒ�
			memcpy(wavfile->fmt.fmtChunk, chunk, CHUNK_SIZE);
			wavfile->fmt.fmtSize = size;

			// �t�H�[�}�b�gID����ǂݍ���
			fread(&wavfile->fmt.fmtFormatTag,
				sizeof(FMT_CHUNK) - 8, 1, fp);

			// �t���O����
			chunkFlag += FLAG_CHUNK_FMT;

			continue;
		}

		// data�`�����N
		if (memcmp(chunk, CHUNK_DATA, CHUNK_SIZE) == CHUNK_SAME)
		{
			// �`�����N�ƃT�C�Y��ݒ�
			memcpy(wavfile->data.dataChunk, CHUNK_DATA, CHUNK_SIZE);
			wavfile->data.waveSize = size;

			// �������m��
			wavfile->data.waveData = (short *)malloc(wavfile->data.waveSize);

			// �g�`�̓ǂݍ���
			fread(wavfile->data.waveData, wavfile->data.waveSize, 1, fp);

			// �t���O����
			chunkFlag += FLAG_CHUNK_DATA;

			continue;
		}

		// ���̃`�����N
		else
		{
			// size����skip
			fseek(fp, size, SEEK_CUR);
		}
	}

	/* wav�\���̂̏����� */
	pcm.cbSize = 0;
	pcm.nChannels = wavfile->fmt.fmtChannel;
	pcm.wBitsPerSample = wavfile->fmt.fmtBitPerSample;
	pcm.nSamplesPerSec = wavfile->fmt.fmtSampleRate;
	pcm.wFormatTag = WAVE_FORMAT_PCM;
	pcm.nBlockAlign = (wavfile->fmt.fmtChannel*wavfile->fmt.fmtBitPerSample) / 8;
	pcm.nAvgBytesPerSec = wavfile->fmt.fmtSampleRate*pcm.nBlockAlign;

	fclose(fp);

	return pcm;
}
