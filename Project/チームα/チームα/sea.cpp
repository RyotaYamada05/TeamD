//=============================================================================
//
// �C�N���X [sea.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "sea.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CSea::m_apTexture[MAX_SEA_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSea::CSea()
{
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����i��]�j
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumVertex = 0;							// �����_��
	m_nNumIndex = 0;							// ���C���f�b�N�X��
	m_nNumPolygon = 0;							// ���|���S����
	m_fOne_SizeW = 0.0f;
	m_fOne_SizeH = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSea::~CSea()
{
}

//=============================================================================
// �|���S������
//=============================================================================
CSea * CSea::Create(void)
{
	CSea *pMeshField = new CSea;

	if (pMeshField != NULL)
	{
		pMeshField->Init();
	}

	return pMeshField;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CSea::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/sea000.jpeg",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CSea::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_SEA_TEXTURE; nCount++)
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
HRESULT CSea::Init(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	int nCount;

	int nCntIndex;
	int nCntIndex01 = 0;

	int nCntH;

	int nCntV;

	m_nNumVertex = (SEA_WIDTH + 1) * (SEA_HEIGHT + 1);
	m_nNumIndex = (SEA_WIDTH + 1) * SEA_HEIGHT * 2 + (SEA_HEIGHT - 1) * 2;
	m_nNumPolygon = SEA_WIDTH * SEA_HEIGHT * 2 + (SEA_HEIGHT - 1) * 4;

	m_fOne_SizeW = SEA_WIDTH_SIZE * 2 / SEA_WIDTH;
	m_fOne_SizeH = SEA_HEIGHT_SIZE * 2 / SEA_HEIGHT;

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

	for (nCntV = 0; nCntV < SEA_HEIGHT + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < SEA_WIDTH + 1; nCntH++)
		{
			// ���_�̐ݒ�
			pVtx[(nCntV * (SEA_HEIGHT + 1)) + nCntH].pos = D3DXVECTOR3(-SEA_WIDTH_SIZE + (nCntH * m_fOne_SizeW), -500.0f, SEA_HEIGHT_SIZE - (nCntV * m_fOne_SizeH));

			// �@���x�N�g���̐ݒ�
			pVtx[(nCntV * (SEA_HEIGHT + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �F�̐ݒ�
			pVtx[(nCntV * (SEA_HEIGHT + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntV * (SEA_HEIGHT + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
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
		if (((nCount + 2) % (((SEA_WIDTH + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = nCntIndex - 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = SEA_WIDTH + nCntIndex + 1;
		}
		else
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = SEA_WIDTH + nCntIndex + 1;

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
void CSea::Uninit(void)
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
void CSea::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSea::Draw(void)
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