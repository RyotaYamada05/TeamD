//=================================================================================
//
// ���[�U�[�N���X [beam.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "beam.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "shock.h"

//=================================================================================
// �}�N����`
//=================================================================================
#define BEAM_LIFE	(70)			// �r�[���̃��C�t

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CBeam::m_apTexture[MAX_BEAM_TEXTURE] = {};
LPD3DXMESH CBeam::m_pMesh = NULL;
LPD3DXBUFFER CBeam::m_pBuffMat = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD CBeam::m_nNumMat = 0;					//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CBeam * CBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, BULLET2_USER user)
{
	// �������m��
	CBeam *pBeam = new CBeam;

	if (pBeam != NULL)
	{
		// ����������
		pBeam->Init(pos, move, size, user);		// ���������
		pBeam->SetMove(move);					// �ړ���
		pBeam->SetLife(BEAM_LIFE);				// ���C�t�̏��
	}

	return pBeam;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CBeam::CBeam()
{

}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CBeam::~CBeam()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CBeam::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, BULLET2_USER user)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffMat = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	BindModel(model);
	BindTexture(m_apTexture[0]);

	// ����������
	CBullet2::Init(pos, size, user);		// ���������
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����

	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CBeam::Uninit(void)
{
	// �I������
	CBullet2::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CBeam::Update(void)
{
	// �X�V����
	CBullet2::Update();

	D3DXVECTOR3 pos = GetPos();

	// �G�t�F�N�g����
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f));
}

//=================================================================================
// �`�揈��
//=================================================================================
void CBeam::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL*pMat;

	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	// ���f���̕`��
	CBullet2::Draw();
}

//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CBeam::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Explosion004.jpg",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/beam.x",
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
void CBeam::UnLoad(void)
{
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

	for (int nCount = 0; nCount < MAX_BEAM_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}