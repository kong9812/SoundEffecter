//=============================================================================
//
// �{�^���̃A�C�R������ [bottonIcon.cpp]
// Author : �� �F��
//
//=============================================================================
#include "buttonIcon.h"
#include "soundControl.h"


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void SetSongName(void);		// �����`�揈��

//=============================================================================
// �O���[�o���ϐ�:
//=============================================================================
TEXTURE	background;								// �w�i
TEXTURE buttonIconTexture[BUTTON_MAX];			// �{�^��
TEXTURE buttonLightTexture[BUTTON_MAX];			// �{�^���̃��C�g
TEXTURE volumeMeterBar[VOLUME_METER_BAR_MAX];	// �{�����[�����[�^�[�o�[
TEXTURE outputButton;							// �A�E�g�v�b�g�{�^��
TEXTURE	wavePlot;								// GNUPLOT�̏o�̓{�^��(�g�`)
LPD3DXFONT	soundName = NULL;					// �t�H���g�ւ̃|�C���^
int			SongFontCnt = 0;					// �t�H���g�J�E���^�[

float buttonRadian[BUTTON_MAX];					// �p�x(���W�A��)

int	  buttonUse;								// �g�p���̃{�^��

SOUND_CONTROL *soundControl;					// �T�E���h�R���g���[���N���X

//=============================================================================
// ������
//=============================================================================
HRESULT InitButtonIcon(int InitType, HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		for (int i = 0; i < BUTTON_MAX; i++)
		{
			// ������
			volumeMeterBar[0].texture = NULL;
			volumeMeterBar[1].texture = NULL;
			outputButton.texture	  = NULL;
			wavePlot.texture		  = NULL;

			// �e�N�X�`���̓ǂݍ���
			LoadTexture(pDevice, &outputButton, TEXTURE_OUTPUT);
			
			// �e�N�X�`���̓ǂݍ���
			LoadTexture(pDevice, &buttonIconTexture[i], TEXTURE_BUTTON_ICON);

			// �e�N�X�`���̓ǂݍ���
			LoadTexture(pDevice, &buttonLightTexture[i], TEXTURE_BUTTON_LIGHT);

			// �e�N�X�`���̓Ǎ���
			LoadTexture(pDevice, &buttonLightTexture[i], TEXTURE_BUTTON_LIGHT);

			// �e�N�X�`���̓Ǎ���
			LoadTexture(pDevice, &background, TEXTURE_BACKGROUND);

			// �t�H���g
			D3DXCreateFont(pDevice, 50, 25, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &soundName);
			
		}
	}

	{// ���̏�����

		{// �w�i
			background.pos	= BACKGROUND_POS;
			background.size = BACKGROUND_SIZE;
		}

		{// �{�^��
			for (int i = 0; i < BUTTON_MAX; i++)
			{
				buttonIconTexture[i].rot	= BUTTON_ROT;		// ��]
				buttonIconTexture[i].size	= BUTTON_SIZE;		// �T�C�Y
				buttonIconTexture[i].col	= BUTTON_COL;		// �F
				buttonRadian[i]				= BUTTON_RADIAN;	// �p�x(���W�A��)

				buttonLightTexture[i].size	= BUTTON_LIGHT_SIZE;// �T�C�Y
				buttonLightTexture[i].col	= BUTTON_OFF_COL;	// �F(�I�t)
			}

			buttonIconTexture[BUTTON_LIST::BUTTON_MAIN_VOL].pos			= BUTTON_POS_0;		// �ʒu0
			buttonLightTexture[BUTTON_LIST::BUTTON_MAIN_VOL].pos		= BUTTON_POS_0;		// �ʒu0
			buttonIconTexture[BUTTON_LIST::BUTTON_MAIN_VOL].rot			= BUTTON_ROT_0;		// ��]0

			buttonIconTexture[BUTTON_LIST::BUTTON_PAN_VOL].pos			= BUTTON_POS_1;		// �ʒu1
			buttonLightTexture[BUTTON_LIST::BUTTON_PAN_VOL].pos			= BUTTON_POS_1;		// �ʒu1
			buttonIconTexture[BUTTON_LIST::BUTTON_PAN_VOL].rot			= BUTTON_ROT_1;		// ��]1

			buttonIconTexture[BUTTON_LIST::BUTTON_FREQ].pos				= BUTTON_POS_2;		// �ʒu2
			buttonLightTexture[BUTTON_LIST::BUTTON_FREQ].pos			= BUTTON_POS_2;		// �ʒu2
			buttonIconTexture[BUTTON_LIST::BUTTON_FREQ].rot				= BUTTON_ROT_2;		// ��]2

			buttonIconTexture[BUTTON_LIST::BUTTON_DELAY_REVERB].pos		= BUTTON_POS_3;		// �ʒu3
			buttonLightTexture[BUTTON_LIST::BUTTON_DELAY_REVERB].pos	= BUTTON_POS_3;		// �ʒu3

			buttonIconTexture[BUTTON_LIST::BUTTON_FADE].pos				= BUTTON_POS_4;		// �ʒu4
			buttonLightTexture[BUTTON_LIST::BUTTON_FADE].pos			= BUTTON_POS_4;		// �ʒu4

			buttonIconTexture[BUTTON_LIST::BUTTON_WET_VOL].pos			= BUTTON_POS_5;		// �ʒu5
			buttonLightTexture[BUTTON_LIST::BUTTON_WET_VOL].pos			= BUTTON_POS_5;		// �ʒu5

			buttonIconTexture[BUTTON_LIST::BUTTON_DRY_VOL].pos			= BUTTON_POS_6;		// �ʒu6
			buttonLightTexture[BUTTON_LIST::BUTTON_DRY_VOL].pos			= BUTTON_POS_6;		// �ʒu6

			buttonIconTexture[BUTTON_LIST::BUTTON_DELAY_TIME].pos		= BUTTON_POS_7;		// �ʒu7
			buttonLightTexture[BUTTON_LIST::BUTTON_DELAY_TIME].pos		= BUTTON_POS_7;		// �ʒu7

			buttonIconTexture[BUTTON_LIST::BUTTON_REVERB_VOL].pos		= BUTTON_POS_8;		// �ʒu8
			buttonLightTexture[BUTTON_LIST::BUTTON_REVERB_VOL].pos		= BUTTON_POS_8;		// �ʒu8

			buttonIconTexture[BUTTON_LIST::BUTTON_FADE_TIME].pos		= BUTTON_POS_9;		// �ʒu9
			buttonLightTexture[BUTTON_LIST::BUTTON_FADE_TIME].pos		= BUTTON_POS_9;		// �ʒu9

			buttonUse													= INIT_BUTTON;		// �g�p���̃{�^��
		}

		{// �{�����[�����[�^�[�o�[
			for (int i = 0; i < VOLUME_METER_BAR_MAX; i++)
			{
				volumeMeterBar[i].col = VOLUME_METER_BAR_COL_0;
				volumeMeterBar[i].size = VOLUME_METER_BAR_SIZE;
			}
			volumeMeterBar[0].pos = VOLUME_METER_BAR_POS_0;
			volumeMeterBar[1].pos = VOLUME_METER_BAR_POS_1;
		}

		{// �A�E�g�v�b�g�{�^��
			outputButton.pos	= OUTPUT_BUTTON_POS;
			outputButton.size	= OUTPUT_BUTTON_SIZE;
			outputButton.col	= OUTPUT_BUTTON_COL_0;
		}

		{
			wavePlot.pos		= PLOT_POS;
			wavePlot.size		= PLOT_SIZE;
		}
	}

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		// ���_�t�H�[�}�b�g
		MakeVtxCenterData(&buttonIconTexture[i]);

		// ���_�t�H�[�}�b�g
		MakeVtxCenterData(&buttonLightTexture[i]);
	}

	// ���_�t�H�[�}�b�g
	MakeVtx4PointData(&volumeMeterBar[0]);
	MakeVtx4PointData(&volumeMeterBar[1]);
	MakeVtx4PointData(&outputButton);
	MakeVtx4PointData(&wavePlot);
	MakeVtx4PointData(&background);

	// �T�E���h�R���g���[��
	soundControl = new SOUND_CONTROL(hWnd);

	// �e�N�X�`���̓Ǎ���
	LoadTexture(pDevice, &wavePlot, TEXTURE_PLOT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitButtonIcon(void)
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		SAFE_RELEASE(buttonIconTexture[i].texture)
		SAFE_RELEASE(buttonLightTexture[i].texture)
	}

	SAFE_RELEASE(volumeMeterBar[0].texture)
	SAFE_RELEASE(volumeMeterBar[0].texture)
	SAFE_RELEASE(outputButton.texture)
	SAFE_RELEASE(wavePlot.texture)
	SAFE_RELEASE(background.texture)
	
	// �T�E���h�R���g���[��
	delete soundControl;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateButtonIcon(HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �����蔻��
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		// �p�����[�^�{�^���̓����蔻��
		if (CheckHitBB(GetMousePos(hWnd), buttonIconTexture[i].pos, CURSOR_SIZE / 32, buttonIconTexture[i].size))
		{
			if ((IsMouseLeftTriggered() == true))
			{
				buttonUse = i;
			}
		}

		// �F����
		buttonLightTexture[i].col = BUTTON_OFF_COL;
	}

	// �����o���{�^���̓����蔻��
	if (CheckHitBB(GetMousePos(hWnd), outputButton.pos, CURSOR_SIZE / 32, outputButton.size))
	{
		// �F����
		outputButton.col = OUTPUT_BUTTON_COL_1;

		if ((IsMouseLeftTriggered() == true))
		{
			// �����o��
			soundControl->OutputWav();
		
			SAFE_RELEASE(wavePlot.texture)

			// �e�N�X�`���̓Ǎ���
			LoadTexture(pDevice, &wavePlot, TEXTURE_PLOT);
		}
	}

	// �F����
	outputButton.col = OUTPUT_BUTTON_COL_0;

	if ((buttonUse != BUTTON_LIST::BUTTON_DELAY_REVERB) && (buttonUse != BUTTON_LIST::BUTTON_FADE))
	{
		// �E��]
		if (buttonIconTexture[buttonUse].rot.z < BUTTON_MAX_RADIAN)
		{
			// �E�{�^��
			if (GetKeyboardPress(DIK_RIGHT))
			{
				buttonIconTexture[buttonUse].rot.z += BUTTON_MOVE;

				// �v���Z�X
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}

		// ����]
		if (buttonIconTexture[buttonUse].rot.z > BUTTON_MIN_RADIAN)
		{
			// ���{�^��
			if (GetKeyboardPress(DIK_LEFT))
			{
				buttonIconTexture[buttonUse].rot.z -= BUTTON_MOVE;

				// �v���Z�X
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}
	}
	else
	{
		// �E��]
		if (buttonIconTexture[buttonUse].rot.z < BUTTON_MAX_RADIAN)
		{
			// �E�{�^��
			if (GetKeyboardPress(DIK_RIGHT))
			{
				buttonIconTexture[buttonUse].rot.z += BUTTON_NO_OFF;

				// �v���Z�X
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}

		// ����]
		if (buttonIconTexture[buttonUse].rot.z > BUTTON_MIN_RADIAN)
		{
			// ���{�^��
			if (GetKeyboardPress(DIK_LEFT))
			{
				buttonIconTexture[buttonUse].rot.z -= BUTTON_NO_OFF;

				// �v���Z�X
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}
	}

	// �g�p���̃{�^���F
	buttonLightTexture[buttonUse].col = BUTTON_ON_COL;

	// �{�����[�����[�^�[
	for (int i = 0; i < VOLUME_METER_BAR_MAX; i++)
	{
		if (soundControl->GetBalVolumeMeter(i) >= 0.5f)
		{
			volumeMeterBar[i].col = VOLUME_METER_BAR_COL_1;
		}
		else
		{
			volumeMeterBar[i].col = VOLUME_METER_BAR_COL_0;
		}
	}
}

//=============================================================================
// �����`�揈��
//=============================================================================
void SetSongName(void)
{
	// �t�H���g�p
	RECT rect = { 0, 600, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[CHAR_MAX];

	// �Ȗ�
	sprintf(str, _T("%s"), soundControl->GetSound()->GetFileName());
	soundName->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawButtonIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �`��
	DrawNormalObject(pDevice, background);

	// �{�^���̃A�C�R��
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		// �`��
		DrawRotCenterObject(pDevice, buttonIconTexture[i], buttonRadian[i], buttonIconTexture[i].size.x);

		// �`��
		DrawColorCenterObject(pDevice, buttonLightTexture[i]);
	}

	// �`��
	DrawGaugeObject(pDevice, volumeMeterBar[0], soundControl->GetBalVolumeMeter(0), GAUGE_DIRECTION::GAUGE_RIGHT);
	// �`��
	DrawGaugeObject(pDevice, volumeMeterBar[1], soundControl->GetBalVolumeMeter(1), GAUGE_DIRECTION::GAUGE_RIGHT);
	// �`��
	DrawColorCenterObject(pDevice, outputButton);
	// �`��
	DrawNormalObject(pDevice, wavePlot);

	// �����`�揈��
	SetSongName();

}

//=============================================================================
// �{�^���̏����擾
//=============================================================================
TEXTURE GetButtonTexture(int no)
{
	return buttonIconTexture[no];
}