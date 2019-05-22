//=============================================================================
//
// �{�^���̃A�C�R������ [buttonIcon.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _BUTTONICON_H_
#define _BUTTONICON_H_

#include "main.h"
#include "basic.h"
#include "input.h"
#include "Collider.h"
#include "fastDraw2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �w�i
#define TEXTURE_BACKGROUND		_T("data/texture/UI/background.PNG")
#define BACKGROUND_SIZE			D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT)
#define BACKGROUND_POS			D3DXVECTOR3(0.0f,0.0f,0.0f)

// �{�^��
#define TEXTURE_BUTTON_ICON		_T("data/texture/UI/button.png")
#define BUTTON_ROT				D3DXVECTOR3(0.0f,0.0f,0.0f)
#define BUTTON_SIZE				D3DXVECTOR2(50.0f,50.0f)
#define BUTTON_COL				D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)
#define BUTTON_RADIAN			(1.0f)
#define BUTTON_MAX_RADIAN		(D3DXToRadian(180))
#define BUTTON_MIN_RADIAN		(D3DXToRadian(0))
#define BUTTON_MAX				(10)
#define BUTTON_MOVE				(D3DXToRadian(2))
#define BUTTON_NO_OFF			(D3DXToRadian(180))
#define RadianToPercentage(radian) ((radian) / D3DXToRadian(180))	// 0 �` 1�̊���
#define INIT_BUTTON				(0)

// �{�^���̃��C�g
#define TEXTURE_BUTTON_LIGHT	_T("data/texture/UI/buttonLight.png")
#define BUTTON_LIGHT_SIZE		D3DXVECTOR2(5.0f,5.0f)
#define BUTTON_OFF_COL			D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)
#define BUTTON_ON_COL			D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)

// �ʒu
#define BUTTON_POS_0			D3DXVECTOR3(450.0f,550.0f,0.0f)
#define BUTTON_ROT_0			D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(180))
#define BUTTON_POS_1			D3DXVECTOR3(550.0f,550.0f,0.0f)
#define BUTTON_ROT_1			D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(90))
#define BUTTON_POS_2			D3DXVECTOR3(650.0f,550.0f,0.0f)
#define BUTTON_ROT_2			D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(90))
#define BUTTON_POS_3			D3DXVECTOR3(750.0f,550.0f,0.0f)
#define BUTTON_POS_4			D3DXVECTOR3(850.0f,550.0f,0.0f)
#define BUTTON_POS_5			D3DXVECTOR3(450.0f,650.0f,0.0f)
#define BUTTON_POS_6			D3DXVECTOR3(550.0f,650.0f,0.0f)
#define BUTTON_POS_7			D3DXVECTOR3(650.0f,650.0f,0.0f)
#define BUTTON_POS_8			D3DXVECTOR3(750.0f,650.0f,0.0f)
#define BUTTON_POS_9			D3DXVECTOR3(850.0f,650.0f,0.0f)

// �{�����[�����[�^�[�o�[
#define VOLUME_METER_BAR_MAX	(2)		
#define VOLUME_METER_BAR_POS_0	D3DXVECTOR3(50.0f,50.0f,0.0f)
#define VOLUME_METER_BAR_POS_1	D3DXVECTOR3(50.0f,150.0f,0.0f)
#define VOLUME_METER_BAR_SIZE	D3DXVECTOR2(1100.0f,100.0f)
#define VOLUME_METER_BAR_COL_0	D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define VOLUME_METER_BAR_COL_1	D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)

// �{�����[�����[�^�[�o�[
#define TEXTURE_OUTPUT		_T("data/texture/UI/Export.png")
#define OUTPUT_BUTTON_POS	D3DXVECTOR3(1150.0f,650.0f,0.0f)
#define OUTPUT_BUTTON_SIZE	D3DXVECTOR2(50.0f,50.0f)
#define OUTPUT_BUTTON_COL_0	D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)
#define OUTPUT_BUTTON_COL_1	D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)

// �v���b�g
#define TEXTURE_PLOT		_T("data/GNUPLOT/Wave.png")
#define PLOT_POS			D3DXVECTOR3(50.0f,275.0f,0.0f)
#define PLOT_SIZE			D3DXVECTOR2(1000.0f,200.0f)

// �t�H���g
#define FONT_ESC			(27)	// ESC�L�[
#define FONT_SPEED			(0.5f)	// �X�N���[���X�s�[�h
#define FONT_SIZE			(6)		// �����\���p(10 * ���� + null����)

//*****************************************************************************
// �萔��`
//*****************************************************************************
enum BUTTON_LIST
{
	BUTTON_MAIN_VOL,
	BUTTON_PAN_VOL,
	BUTTON_FREQ,
	BUTTON_DELAY_REVERB,
	BUTTON_FADE,
	BUTTON_WET_VOL,
	BUTTON_DRY_VOL,
	BUTTON_DELAY_TIME,
	BUTTON_REVERB_VOL,
	BUTTON_FADE_TIME
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitButtonIcon(int InitType, HWND hWnd);	// ������
void UninitButtonIcon(void);						// �I������
void UpdateButtonIcon(HWND hWnd);					// �X�V����
void DrawButtonIcon(void);							// �`�揈��

TEXTURE GetButtonTexture(int no);					// �{�^���̏����擾

#endif