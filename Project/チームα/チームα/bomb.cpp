//=================================================================================
//
// �{���N���X [bomb.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "shock.h"

//=================================================================================
// �}�N����`
//=================================================================================
#define BOMB_LIFE			(60)			// �{���̃��C�t
#define BOMB_GRAVITY_POWAR	(0.2f)			// �{���̏d��

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CBomb::m_apTexture[MAX_BOMB_TEXTURE] = {};
LPD3DXMESH CBomb::m_pMesh = NULL;
LPD3DXBUFFER CBomb::m_pBuffMat = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD CBomb::m_nNumMat = 0;					//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CBomb * CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, BULLET2_USER user)
{
	// �������m��
	CBomb *pBomb = new CBomb;

	if (pBomb != NULL)
	{
		// ����������
		pBomb->Init(pos, size, user);		// ���������
		pBomb->SetMove(move);					// �ړ���
		pBomb->SetLife(BOMB_LIFE);				// ���C�t�̏��
	}

	return pBomb;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CBomb::CBomb()
{
	m_fAddRotNum = 0.0f;
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CBomb::~CBomb()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BULLET2_USER user)
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
void CBomb::Uninit(void)
{
	// �I������
	CBullet2::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CBomb::Update(void)
{
	// �X�V����
	CBullet2::Update();

	// ��]
	AddRot();

	// ���W���󂯎��
	D3DXVECTOR3 pos = GetPos();

	// �G�t�F�N�g����
	//CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f));

	// �ړ��ʂ��󂯎��
	D3DXVECTOR3 move = GetMove();

	// ���W���n�ʂ���Ȃ�
	if (pos.y > 20.0f)
	{

		// �d�͂����Z
		SetMove(D3DXVECTOR3(move.x, move.y - BOMB_GRAVITY_POWAR, move.z));
	}
	else
	{
		SetMove(D3DXVECTOR3(move.x, 0.0f, move.z));
	}


}

//=================================================================================
// �`�揈��
//=================================================================================
void CBomb::Draw(void)
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
// �p�x�����Z
//=================================================================================
void CBomb::AddRot(void)
{
	m_fAddRotNum += 1.0f;

	// �p�x�̕ω�
	D3DXVECTOR3 rot = D3DXVECTOR3(GetRot().x, GetRot().y + D3DXToRadian(m_fAddRotNum), GetRot().z);

	// �p�x��n��
	SetRot(rot);
}


//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CBomb::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Explosion004.jpg",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/bomb.x",
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
void CBomb::UnLoad(void)
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

	for (int nCount = 0; nCount < MAX_BOMB_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}