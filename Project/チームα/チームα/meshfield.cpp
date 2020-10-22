//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "meshfield.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_apTexture[MAX_MESHFIELD_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshField::CMeshField()
{
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �����i��]�j
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumVertex = 0;							// �����_��
	m_nNumIndex = 0;					// ���C���f�b�N�X��
	m_nNumPolygon = 0;					// ���|���S����
	m_fOne_SizeW = 0.0f;
	m_fOne_SizeH = 0.0f;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// �|���S������
//=============================================================================
CMeshField * CMeshField::Create(void)
{
	CMeshField *pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		pMeshField->Init();
	}

	return pMeshField;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CMeshField::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/stone_00124.jpg",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CMeshField::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MESHFIELD_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	int nCount;

	int nCntIndex;
	int nCntIndex01 = 0;

	int nCntH;

	int nCntV;

	m_nNumVertex = (FIELD_WIDTH + 1) * (FIELD_HEIGHT + 1);
	m_nNumIndex = (FIELD_WIDTH + 1) * FIELD_HEIGHT * 2 + (FIELD_HEIGHT - 1) * 2;
	m_nNumPolygon = FIELD_WIDTH * FIELD_HEIGHT * 2 + (FIELD_HEIGHT - 1) * 4;

	m_fOne_SizeW = FIELD_WIDTH_SIZE * 2 / FIELD_WIDTH;
	m_fOne_SizeH = FIELD_HEIGHT_SIZE * 2 / FIELD_HEIGHT;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < FIELD_HEIGHT + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < FIELD_WIDTH + 1; nCntH++)
		{
			// ���_�̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].pos = D3DXVECTOR3(-FIELD_WIDTH_SIZE + (nCntH * m_fOne_SizeW), 0.0f, FIELD_HEIGHT_SIZE - (nCntV * m_fOne_SizeH));

			// �@���x�N�g���̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �F�̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCount = 0, nCntIndex = 0; nCount < m_nNumIndex; nCount += 2)
	{
		if (((nCount + 2) % (((FIELD_WIDTH + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = nCntIndex - 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = FIELD_WIDTH + nCntIndex + 1;
		}
		else
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = FIELD_WIDTH + nCntIndex + 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}

	}
	// ���_�f�[�^���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(
		&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(m_pIdxBuff);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, m_apTexture[0]);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);

}