//=============================================================================
//
// �����`�揈��[2D] [fastDraw2D.cpp]
// Author : �� �F��
//
//=============================================================================
#ifndef _FAST_DRAW_2D_H
#define _FAST_DRAW_2D_H

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �e�N�X�`���̓ǂݍ���
void LoadTexture
(LPDIRECT3DDEVICE9 device, TEXTURE *object, const char *path);

// �`�揈��(��ʓI�ȕ`�揈��)
void DrawNormalObject							
(LPDIRECT3DDEVICE9 device, TEXTURE object);

// �`�揈��(�ړ��p�E���S���W)
void DrawMoveCenterObject
(LPDIRECT3DDEVICE9 device, TEXTURE object);

// �`�揈��(��]�p�E���S���W)
void DrawRotCenterObject
(LPDIRECT3DDEVICE9 device, TEXTURE object, float angle, float Length);

// �`�揈��(�����X�N���[���p)
void DrawNumDataObject
(LPDIRECT3DDEVICE9 device, TEXTURE object, int no);

// �`�揈��(�A�j���[�V�����p)
void DrawAnimationObject
(LPDIRECT3DDEVICE9 device, TEXTURE object, int cntPattern,
	int PatternX, int PatternY);

// �`�揈��(�F�̕ύX�E���S���W)
void DrawColorCenterObject
(LPDIRECT3DDEVICE9 device, TEXTURE object);

// �`�揈��(�Q�[�W�E�F�̕ύX)
void DrawGaugeObject
(LPDIRECT3DDEVICE9 device, TEXTURE object, float length, int dir);

#endif 
