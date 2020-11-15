//=============================================================================
//
// �u�[�X�^�[�̏��� [boost.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "boost.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CBoost::m_apTexture[MAX_LASER_TEXTURE] = {};
LPD3DXMESH CBoost::m_pMesh = NULL;
LPD3DXBUFFER CBoost::m_pBuffMat = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD CBoost::m_nNumMat = 0;				//�}�e���A�����̐�
int CBoost::m_nBoost = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoost::CBoost()
{
	D3DXVECTOR3 m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W
	D3DXVECTOR3 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ��]
	m_nNum = 0;
	m_nBoost = m_nBoost++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoost::~CBoost()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CBoost * CBoost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nNumber)
{
	//3D�|���S���N���X�̃|�C���^�ϐ�
	CBoost *pLocus = NULL;

	//�������̊m��
	pLocus = new CBoost;

	nNumber;

	//���������m�ۂł��Ă�����
	if (pLocus != NULL)
	{
		//�����������Ăяo��
		pLocus->Init(pos, size, nNumber);
		pLocus->SetRot(rot);					// �p�x
	}
	else
	{
		return NULL;
	}

	return pLocus;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBoost::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/razer.png",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/razer.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBoost::UnLoad(void)
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

	for (int nCount = 0; nCount < MAX_LASER_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
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
HRESULT CBoost::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size , const int nNum)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffMat = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	BindModel(model);
	BindTexture(m_apTexture[0]);

	m_nBoostNum = m_nBoost;
	m_nNum = nNum;

	// ����������
	CModel::Init(pos, size);		// ���������

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBoost::Uninit(void)
{
	m_nBoost = m_nBoost--;
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBoost::Update(void)
{
	// ���[�U�[�𓮂�������
	BoostMove();

	// 3D�|���S���X�V����
	CModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBoost::Draw(void)
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

	// ���f���̕`��
	CModel::Draw();
}

//=============================================================================
// �u�[�X�g�̍X�V����
//=============================================================================
void CBoost::BoostMove(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer(m_nNum);
	D3DXVECTOR3 rot = pPlayer->GetRot();
	static float frot = 0.0f;
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	if (1 == m_nBoostNum %2)
	{
		TargetPos = D3DXVECTOR3(pos.x - sinf(rot.y) * -50.0f, pos.y + 160.0f, pos.z - cosf(rot.y) * -50.0f);

		rot = D3DXVECTOR3(rot.x + D3DXToRadian(250.0f), rot.y + 0.0f, rot.z + 0.0f);
	}
	else
	{
		TargetPos = D3DXVECTOR3(pos.x - cosf(rot.y) * -50.0f, pos.y + 160.0f, pos.z - sinf(rot.y) * 50.0f);

		rot = D3DXVECTOR3(rot.x + D3DXToRadian(250.0f), rot.y + D3DXToRadian(60.0f), rot.z + 0.0f);
	}
	frot += D3DXToRadian(5.0f);

	// �p�x
	SetRot(D3DXVECTOR3(rot.x, rot.y, rot.z + frot));

	// ���W
	SetPos(TargetPos + move);
}