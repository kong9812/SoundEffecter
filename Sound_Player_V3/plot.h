//=============================================================================
//
// �v���b�g���� [plot.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _PLOT_H_
#define _PLOT_H_

#include "sound.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "soundControl.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// GNUPLOT�̎c���R�}���h
#define GNUPLOT_PRESIST			" -persist"

// �����p�X����Z�[�u�t�H���_�܂ł̃p�X
#define SAVE_PATH				"\\data\\GNUPLOT"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool OpenGnuplot(HWND hWnd);												// GNUPLOT�̓ǂݍ���
void OutputWaveGnuplot(SOUND_TOOL soundTool, char *path, short *otherWave);	// �v���b�g

#endif