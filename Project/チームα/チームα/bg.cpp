//=================================================================================
//
// �w�i�N���X [bg.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE] = {};
LPD3DXMESH CBg::m_pMesh = NULL;
LPD3DXBUFFER CBg::m_pBuffMat = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD CBg::m_nNumMat = 0;	//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CBg * CBg::Create(void)
{
	CBg *pBg = new CBg;

	if (pBg != NULL)
	{
		// ����������
		pBg->Init();
	}

	return pBg;
}

//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CBg::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/sky.jpg",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/dome.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=================================================================================
// �e�N�X�`���A�����[�h
//=================================================================================
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}

	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CBg::CBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CBg::~CBg()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CBg::Init(void)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffer = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	CModel::BindModel(model);

	m_pos = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(BG_SIZE_X, BG_SIZE_Y, BG_SIZE_Z);

	// ���W����^����
	CModel::SetPos(m_pos);

	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CBg::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CBg::Update(void)
{
}

//=================================================================================
// �`�揈��
//=================================================================================
void CBg::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ێ��p
	D3DXMATERIAL* pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	DWORD ambient;

	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	pDevice->LightEnable(0, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale,
		m_size.x,
		m_size.y,
		m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_apTexture[0]);

	// ���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Ambient.r = 1.0f;
		pMat[nCntMat].MatD3D.Ambient.g = 1.0f;
		pMat[nCntMat].MatD3D.Ambient.b = 1.0f;
		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_apTexture[0]);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// ���f���p�[�c
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	pDevice->LightEnable(0, TRUE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�f�o�C�X���̎擾

//	CModel::Draw();
}