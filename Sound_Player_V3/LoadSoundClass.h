#ifndef _LOAD_SOUND_CLASS_H_
#define	_LOAD_SOUND_CLASS_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �`�����N��T�����[�v�p
#define FLAG_CHUNK_FMT		(1)			// fmt�̃t���O
#define FLAG_CHUNK_DATA		(1<<1)		// data�̃t���O
#define FLAG_CHUNK_END		(3)			// end�|�C���g
// �`�����N
#define CHUNK_FMT			("fmt ")	// fmt�̃`�����N
#define CHUNK_DATA			("data")	// data�̃`�����N
#define CHUNK_SIZE			(4)			// �`�����N�̃o�C�g��
// ����p
#define CHUNK_SAME			(0)			// memcpy�̖߂�l(����)

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct	// RIFF�`�����N 
{
	char	riffChunk[4];
	long	riffSize;
	char	waveChunk[4];
}RIFF_CHUNK;

typedef struct	// fmt �`�����N 
{
	char	fmtChunk[4];
	long	fmtSize;
	short	fmtFormatTag;
	short	fmtChannel;
	long	fmtSampleRate;
	long	fmtAvgBytesPerSec;
	short	fmtBlockAlign;
	short	fmtBitPerSample;
}FMT_CHUNK;

typedef struct	// data�`�����N 
{
	char	dataChunk[4];
	long	waveSize;
	short	*waveData;
}DATA_CHUNK;

typedef struct	// WAV�t�@�C�� 
{
	RIFF_CHUNK	riff;
	FMT_CHUNK	fmt;
	DATA_CHUNK	data;
}WAV_FILE;

//*****************************************************************************
// �N���X
//*****************************************************************************
class SAI_LOAD_WAV
{
public:
	SAI_LOAD_WAV() {};
	~SAI_LOAD_WAV() {};

	// �T�E���h�̓ǂݍ���
	bool OpenSound(HWND hWnd, char *fileName, char soundPath[]);

	// WAV�t�@�C���̓ǂݍ���(WAVEFORMATEX�\����)
	WAVEFORMATEX LoadWavFile(const char *path, WAV_FILE *wavfile);

	// �����p�X���擾
	char *GetOldPath(void) { return oldPath; };

private:
	char		oldPath[CHAR_MAX];	// �����̃p�X
};

#endif