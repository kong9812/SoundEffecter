//=============================================================================
//
// ���_���� [basic.cpp]
// Author : �� �F��
//
//=============================================================================
#include "basic.h"

//=============================================================================
// ���_�t�H�[�}�b�g(���_���)
// ����:���_���i�[���[�N	���WX,Y,Z	�T�C�YX,Y
//=============================================================================
HRESULT MakeVtx4PointData(TEXTURE *object)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = D3DXVECTOR3(object->pos.x, object->pos.y, object->pos.z);
	object->vertexWk[1].vtx = D3DXVECTOR3(object->pos.x + object->size.x, object->pos.y, object->pos.z);
	object->vertexWk[2].vtx = D3DXVECTOR3(object->pos.x, object->pos.y + object->size.y, object->pos.z);
	object->vertexWk[3].vtx = D3DXVECTOR3(object->pos.x + object->size.x, object->pos.y + object->size.y, object->pos.z);

	// rhw�̐ݒ�
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	object->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�t�H�[�}�b�g(���S���W)
//=============================================================================
HRESULT MakeVtxCenterData(TEXTURE *object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx.x = object->pos.x - object->size.x;
	object->vertexWk[0].vtx.y = object->pos.y - object->size.y;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->pos.x + object->size.x;
	object->vertexWk[1].vtx.y = object->pos.y - object->size.y;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->pos.x - object->size.x;
	object->vertexWk[2].vtx.y = object->pos.y + object->size.y;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->pos.x + object->size.x;
	object->vertexWk[3].vtx.y = object->pos.y + object->size.y;
	object->vertexWk[3].vtx.z = 0.0f;

	// rhw�̐ݒ�
	object->vertexWk[0].rhw =
	object->vertexWk[1].rhw =
	object->vertexWk[2].rhw =
	object->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	object->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�t�H�[�}�b�g(�����e�N�X�`�����_���)
// ����:���_���i�[���[�N	���WX,Y,Z	�T�C�YX,Y
//=============================================================================
HRESULT MakeCutVtx4PointData(TEXTURE *object, int PatternX, int PatternY, int cntPattern)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx = D3DXVECTOR3(object->pos.x, object->pos.y, object->pos.z);
	object->vertexWk[1].vtx = D3DXVECTOR3(object->pos.x + object->size.x, object->pos.y, object->pos.z);
	object->vertexWk[2].vtx = D3DXVECTOR3(object->pos.x, object->pos.y + object->size.y, object->pos.z);
	object->vertexWk[3].vtx = D3DXVECTOR3(object->pos.x + object->size.x, object->pos.y + object->size.y, object->pos.z);

	// rhw�̐ݒ�
	object->vertexWk[0].rhw =
		object->vertexWk[1].rhw =
		object->vertexWk[2].rhw =
		object->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	object->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	object->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % PatternX;
	int y = cntPattern / PatternX;
	float sizeX = 1.0f / PatternX;
	float sizeY = 1.0f / PatternY;

	object->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	object->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	object->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	object->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�(���_���)
// ����:���_���i�[���[�N	���WX,Y,Z	�T�C�YX,Y
//=============================================================================
void SetVtx4PointData(TEXTURE *object)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx.x = object->pos.x;
	object->vertexWk[0].vtx.y = object->pos.y;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->pos.x + object->size.x;
	object->vertexWk[1].vtx.y = object->pos.y;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->pos.x;
	object->vertexWk[2].vtx.y = object->pos.y + object->size.y;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->pos.x + object->size.x;
	object->vertexWk[3].vtx.y = object->pos.y + object->size.y;
	object->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���_���W�̐ݒ�(���S���W)
//=============================================================================
void SetVtxCenterData(TEXTURE *object)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx.x = object->pos.x - object->size.x;
	object->vertexWk[0].vtx.y = object->pos.y - object->size.y;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->pos.x + object->size.x;
	object->vertexWk[1].vtx.y = object->pos.y - object->size.y;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->pos.x - object->size.x;
	object->vertexWk[2].vtx.y = object->pos.y + object->size.y;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->pos.x + object->size.x;
	object->vertexWk[3].vtx.y = object->pos.y + object->size.y;
	object->vertexWk[3].vtx.z = 0.0f;
}


//=============================================================================
// ���_���W�̐ݒ�(��])
//=============================================================================
void SetVtxRotData(TEXTURE *object, float angle, float Length)
{
	// ���_���W�̐ݒ�
	object->vertexWk[0].vtx.x = object->pos.x - cosf(D3DXToDegree(angle) + object->rot.z) * Length;
	object->vertexWk[0].vtx.y = object->pos.y - sinf(D3DXToDegree(angle) + object->rot.z) * Length;
	object->vertexWk[0].vtx.z = 0.0f;

	object->vertexWk[1].vtx.x = object->pos.x + cosf(D3DXToDegree(angle) - object->rot.z) * Length;
	object->vertexWk[1].vtx.y = object->pos.y - sinf(D3DXToDegree(angle) - object->rot.z) * Length;
	object->vertexWk[1].vtx.z = 0.0f;

	object->vertexWk[2].vtx.x = object->pos.x - cosf(D3DXToDegree(angle) - object->rot.z) * Length;
	object->vertexWk[2].vtx.y = object->pos.y + sinf(D3DXToDegree(angle) - object->rot.z) * Length;
	object->vertexWk[2].vtx.z = 0.0f;

	object->vertexWk[3].vtx.x = object->pos.x + cosf(D3DXToDegree(angle) + object->rot.z) * Length;
	object->vertexWk[3].vtx.y = object->pos.y + sinf(D3DXToDegree(angle) + object->rot.z) * Length;
	object->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���_���W�̐ݒ�(�Q�[�W�p)
//=============================================================================
void SetVtx4PointGaugeDate(TEXTURE *object, float Length, int dir)
{
	// �����
	if (dir == GAUGE_UP)
	{
		// ���_���W�̐ݒ�
		object->vertexWk[0].vtx = D3DXVECTOR3(object->pos.x, object->pos.y + Length, object->pos.z);
		object->vertexWk[1].vtx = D3DXVECTOR3(object->pos.x + object->size.x, object->pos.y + Length, object->pos.z);
		object->vertexWk[2].vtx = D3DXVECTOR3(object->pos.x, object->pos.y + object->size.y, object->pos.z);
		object->vertexWk[3].vtx = D3DXVECTOR3(object->pos.x + object->size.x, object->pos.y + object->size.y, object->pos.z);
	}

	// �E����
	else if (dir == GAUGE_RIGHT)
	{
		// ���_���W�̐ݒ�
		object->vertexWk[0].vtx = D3DXVECTOR3(object->pos.x, object->pos.y, object->pos.z);
		object->vertexWk[1].vtx = D3DXVECTOR3(object->pos.x + (object->size.x * Length), object->pos.y, object->pos.z);
		object->vertexWk[2].vtx = D3DXVECTOR3(object->pos.x, object->pos.y + object->size.y, object->pos.z);
		object->vertexWk[3].vtx = D3DXVECTOR3(object->pos.x + (object->size.x * Length), object->pos.y + object->size.y, object->pos.z);
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�����X�N���[���p)
//=============================================================================
void SetTextureNumData(TEXTURE *object, int number)
{
	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.1f * number, 0.0f);
	object->vertexWk[1].tex = D3DXVECTOR2(0.1f * (number + 1), 0.0f);
	object->vertexWk[2].tex = D3DXVECTOR2(0.1f * number, 1.0f);
	object->vertexWk[3].tex = D3DXVECTOR2(0.1f * (number + 1), 1.0f);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�w�i�X�N���[���p)
//=============================================================================
void SetTextureScrollData(TEXTURE *object, float distance)
{
	// �e�N�X�`�����W�̐ݒ�
	object->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f + distance);
	object->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f + distance);
	object->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f + distance);
	object->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f + distance);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�A�j���[�V�����p)
//=============================================================================
void SetTextureAnimationData(TEXTURE *object, int cntPattern, int PatternX, int PatternY)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % PatternX;
	int y = cntPattern / PatternX;
	float sizeX = 1.0f / PatternX;
	float sizeY = 1.0f / PatternY;

	object->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	object->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	object->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	object->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���ˌ��̐ݒ�(�꒸�_����)
//=============================================================================
void SetSingleDiffuseData(TEXTURE *object, int no)
{
	// ���ˌ��̐ݒ�
	object->vertexWk[no].diffuse = object->col;
}

//=============================================================================
// ���ˌ��̐ݒ�(�S���_)
//=============================================================================
void SetAllDiffuseData(TEXTURE *object)
{
	// ���ˌ��̐ݒ�
	object->vertexWk[0].diffuse = object->col;
	object->vertexWk[1].diffuse = object->col;
	object->vertexWk[2].diffuse = object->col;
	object->vertexWk[3].diffuse = object->col;
}
