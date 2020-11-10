//=================================================================================
//
// ���[�U�[�N���X [laser.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "laser.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "shock.h"

//=================================================================================
// �}�N����`
//=================================================================================
#define LASER_LIFE			(100)			// �r�[���̃��C�t
#define LASER_FLASH_NUM		(0.1f)			// �_�ł̒l
#define LASER_SCALE_NUM		(0.1f)			// �g�k�̒l
#define LASER_SCALE_LIMIT	(5.0f)			// �g��̍ő�l

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CLaser::m_apTexture[MAX_LASER_TEXTURE] = {};
LPD3DXMESH CLaser::m_pMesh = NULL;
LPD3DXBUFFER CLaser::m_pBuffMat = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD CLaser::m_nNumMat = 0;				//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CLaser * CLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size, BULLET2_USER user)
{
	// �������m��
	CLaser *pLaser = new CLaser;

	if (pLaser != NULL)
	{
		// ����������
		pLaser->Init(pos, move, size, user);	// ���������
		pLaser->SetMove(move);					// �ړ���
		pLaser->SetLife(LASER_LIFE);			// ���C�t�̏��
		pLaser->SetRot(rot);					// �p�x
	}

	return pLaser;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CLaser::CLaser()
{
	m_fFlash = 0.5f;
	m_fFlashNum = LASER_FLASH_NUM;
	m_fScale = 1.0f;					// �g��p
	m_fScaleNum = LASER_SCALE_NUM;		// �g��p�̒l
	m_fSizeZ = 0.0f;
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CLaser::~CLaser()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CLaser::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, BULLET2_USER user)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffMat = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	BindModel(model);
	BindTexture(m_apTexture[0]);

	// ����������
	CBullet2::Init(pos, size, user, LASER_SPEED);		// ���������
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
	m_fSizeZ = size.z;									// �T�C�Y�̎擾
	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CLaser::Uninit(void)
{
	// �I������
	CBullet2::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CLaser::Update(void)
{
	// �X�V����
	CBullet2::Update();

	D3DXVECTOR3 pos = GetPos();

	// �g�k
	Scale();

	// �G�t�F�N�g����
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(EFFECT_LASER_SIZE_X, EFFECT_LASER_SIZE_X, 0.0f), D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), EFFECT_LASER_LIFE);

}

//=================================================================================
// �`�揈��
//=================================================================================
void CLaser::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_fFlash += m_fFlashNum;

	if (m_fFlash <= 0.5f)
	{
		m_fFlashNum *= -1;
	}
	
	if (m_fFlash >= 1.0f)
	{
		m_fFlashNum *= -1;
	}

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL*pMat;

	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(m_fFlash, m_fFlash, m_fFlash, 1.0f);
	}

	// ���f���̕`��
	CBullet2::Draw();
}

//=================================================================================
// �g�k����
//=================================================================================
void CLaser::Scale(void)
{
	// �g�k�̒l���Z
	m_fScale += m_fScaleNum;

	if (m_fScale <= LASER_SCALE_LIMIT)
	{
		// �T�C�Y�擾
		D3DXVECTOR3 size = GetSize();

		// �T�C�Y�̐ݒ�
		SetSize(D3DXVECTOR3(size.x, size.y, m_fSizeZ *m_fScale));
	}
	else
	{
		// �T�C�Y�擾
		D3DXVECTOR3 size = D3DXVECTOR3(GetSize());

		// �T�C�Y�̐ݒ�
		SetSize(D3DXVECTOR3(size));

	}
}

//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CLaser::Load(void)
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

//=================================================================================
// �e�N�X�`���A�����[�h
//=================================================================================
void CLaser::UnLoad(void)
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