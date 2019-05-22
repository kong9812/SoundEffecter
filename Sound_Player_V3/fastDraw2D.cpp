//=============================================================================
// < SMASH STARS >
// �����`�揈��[2D] [fastDraw2D.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "fastDraw2D.h"

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void LoadTexture(LPDIRECT3DDEVICE9 device, TEXTURE *object, const char *path)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,	// �f�o�C�X�ւ̃|�C���^
	path,								// �t�@�C���̖��O
	&object->texture);					// �ǂݍ��ރ������[
}

//=============================================================================
// �`�揈��(��ʓI�ȕ`�揈��)
//=============================================================================
void DrawNormalObject(LPDIRECT3DDEVICE9 device, TEXTURE object)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�ړ��p�E���S���W)
//=============================================================================
void DrawMoveCenterObject(LPDIRECT3DDEVICE9 device, TEXTURE object)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// ���_���W�̐ݒ�(���S���W)
	SetVtxCenterData(&object);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(��]�p�E���S���W)
//=============================================================================
void DrawRotCenterObject(LPDIRECT3DDEVICE9 device, TEXTURE object, float radian, float Length)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// ���_���W�̐ݒ�(���S���W)
	SetVtxRotData(&object, radian, Length);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}


//=============================================================================
// �`�揈��(�����X�N���[���p)
//=============================================================================
void DrawNumDataObject(LPDIRECT3DDEVICE9 device, TEXTURE object, int no)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// �e�N�X�`�����W�̐ݒ�(�����X�N���[���p)
	SetTextureNumData(&object, no);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�A�j���[�V�����p)
//=============================================================================
void DrawAnimationObject(LPDIRECT3DDEVICE9 device, TEXTURE object,
	int cntPattern, int PatternX, int PatternY)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// ���_���W�̐ݒ�(���S���W)
	SetVtxCenterData(&object);

	// �e�N�X�`�����W�̐ݒ�(�����X�N���[���p)
	SetTextureAnimationData(&object, cntPattern, PatternX, PatternY);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�F�̕ύX�E���S���W)
//=============================================================================
void DrawColorCenterObject(LPDIRECT3DDEVICE9 device, TEXTURE object)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// ���_���W�̐ݒ�(���S���W)
	SetVtxCenterData(&object);

	// �F�̕ύX
	SetAllDiffuseData(&object);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�Q�[�W�p�E�F�̕ύX)
//=============================================================================
void DrawGaugeObject(LPDIRECT3DDEVICE9 device, TEXTURE object, float length, int dir)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, object.texture);

	// �F�̕ύX
	SetAllDiffuseData(&object);

	// ���_���W�̐ݒ�(���S���W)
	SetVtx4PointGaugeDate(&object, length, dir);

	// �|���S���̕`��
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &object.vertexWk, sizeof(VERTEX_2D));
}
