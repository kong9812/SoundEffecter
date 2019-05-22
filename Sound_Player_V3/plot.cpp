//=============================================================================
//
// �v���b�g���� [plot.cpp]
// Author : �� �F��
//
//=============================================================================
#include "plot.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
WIN32_FIND_DATA		findGnuplot;			// �t�@�C�����
char				gnuplotPath[MAX_PATH];	// �t�@�C���̃p�X

//=============================================================================
// GNUPLOT�̓ǂݍ���
//=============================================================================
bool OpenGnuplot(HWND hWnd)
{
	OPENFILENAME ofn;

	gnuplotPath[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));		//�\���̂�0�ŃN���A
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrInitialDir = "C:\\gnuplot\\bin";	// �e�X�g�pPC��GNUPLOT�p�X( �Ȃ��Ă����v @_@ )
	ofn.lpstrFilter = "gnuplot(*.exe)\0*.exe\0\0";
	ofn.lpstrFile = gnuplotPath;
	ofn.nMaxFile = sizeof(gnuplotPath);
	ofn.lpstrDefExt = "exe";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	// �t�@�C���������o��
	FindFirstFile(ofn.lpstrFile, &findGnuplot);

	return TRUE;
}

//=============================================================================
// �g�` (GNUPLOT)
// �c��:����(? �U��(? �d��(? ���̑傫��(? 
// ����:����(�o�C�g)
//=============================================================================
void OutputWaveGnuplot(SOUND_TOOL soundTool, char *oldPath, short *otherWave)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE *gnuplot;				// GNUPLOT
	double max;					// �ő�l
	double min;					// �ŏ��l
	double x, y;				// GNUPLOT���̍��W
	char filePath[CHAR_MAX];

	// �p�X�ƃR�}���h������
	strcat(gnuplotPath, GNUPLOT_PRESIST);

	// �Z�[�u�p�X�Ə����p�X������
	strcpy(filePath, oldPath);

	// �Z�[�u�p�X�ƃZ�[�u�t�H���_�p�X������
	strcat(filePath, SAVE_PATH);

	if (otherWave == NULL)
	{
		// �ő�l�ƍŏ��l
		min = max = soundTool.svtBase.wavFmt.data.waveData[0];
		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			if (soundTool.svtBase.wavFmt.data.waveData[i] < min) min = soundTool.svtBase.wavFmt.data.waveData[i];
			if (soundTool.svtBase.wavFmt.data.waveData[i] > max) max = soundTool.svtBase.wavFmt.data.waveData[i];
		}

		// �O���t
		gnuplot = _popen(gnuplotPath, "w");										// GNUPLOT���������݃��[�h�ŊJ��
		fprintf(gnuplot, "set title \"wave \" \n");								// �^�C�g���̐ݒ�
		fprintf(gnuplot, "set xrange [0:%d]\n", soundTool.svtBase.wavFmt.data.waveSize / sizeof(short));// x�͈̔�
		fprintf(gnuplot, "set yrange [%f:%f]\n", min, max);						// y�͈̔�
		fprintf(gnuplot, "set terminal png\n");									// �摜�o�͂̏���
		fprintf(gnuplot, "set term png size 1000,300\n");						// �摜�̃T�C�Y
		fprintf(gnuplot, "plot '-' with lines linetype 1 title \"wave\"\n");	// �v���b�g

		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			x = i;
			y = soundTool.svtBase.wavFmt.data.waveData[i];
			fprintf(gnuplot, "%f\t%f\n", x, y);
		}
	}
	else
	{
		// �ő�l�ƍŏ��l
		min = max = otherWave[0];
		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			if (otherWave[i] < min) min = otherWave[i];
			if (otherWave[i] > max) max = otherWave[i];
		}

		// �O���t
		gnuplot = _popen(gnuplotPath, "w");										// GNUPLOT���������݃��[�h�ŊJ��
		fprintf(gnuplot, "set title \"wave \" \n");								// �^�C�g���̐ݒ�
		fprintf(gnuplot, "set xrange [0:%d]\n", soundTool.svtBase.wavFmt.data.waveSize / sizeof(short));// x�͈̔�
		fprintf(gnuplot, "set yrange [%f:%f]\n", min, max);						// y�͈̔�
		fprintf(gnuplot, "set terminal png\n");									// �摜�o�͂̏���
		fprintf(gnuplot, "set term png size 1000,300\n");						// �摜�̃T�C�Y
		fprintf(gnuplot, "plot '-' with lines linetype 1 title \"wave\"\n");	// �v���b�g

		for (int i = 0; i < soundTool.svtBase.wavFmt.data.waveSize / (int)sizeof(short); i++)
		{
			x = i;
			y = otherWave[i];
			fprintf(gnuplot, "%f\t%f\n", x, y);
		}
	}

	fprintf(gnuplot, "e\n");
	fprintf(gnuplot, "set output '%s\\\\Wave.png'\n", filePath);
	fprintf(gnuplot, "replot '%s\\\\Data.txt'using 1:2 w l title 'OutputData' lw 2\n", filePath); 	// �e�L�X�g�f�[�^�̃v���b�g	
	fprintf(gnuplot, "set output\n");

	// GNUPLOT�̉�ʂ����
	_pclose(gnuplot);

	// �Z�[�u�p�X�ƃt�@�C����������
	strcat(filePath, "\\Wave.png");

	// �J�����g�f�B���N�g����ݒ肷��
	SetCurrentDirectory(oldPath);

}