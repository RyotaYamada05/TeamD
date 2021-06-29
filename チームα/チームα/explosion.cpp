//=================================================================================
//
// �����N���X [explosion.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//=================================================================================
// �}�N����`
//=================================================================================
#define EXPLOSION_LIFE			(100)		// �̗�
#define EXPLOSION_SCALE_NUM		(0.05f)		// �X�P�[���̒l
#define EXPLOSION_SCALE_LIMIT	(5.0f)		// �X�P�[���̍ő��
#define EXPLOSION_ADD_ROT		(0.1f)		// �p�x�̉��Z��
#define EXPLOSION_SUB_ALPHA		(0.005f)	// �����x�̌��Z��

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_apTexture[MAX_EXPLOSION_TEXTURE] = {};
LPD3DXMESH CExplosion::m_pMesh = NULL;
LPD3DXBUFFER CExplosion::m_pBuffMat = NULL;			//�}�e���A�����ւ̃|�C���^
DWORD CExplosion::m_nNumMat = 0;					//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	// �������m��
	CExplosion *pExplosion = new CExplosion;

	if (pExplosion != NULL)
	{
		// ����������
		pExplosion->Init(pos, move, size);		// ���������
	}

	return pExplosion;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CExplosion::CExplosion()
{
	m_fScale = 0.0f;		// �g�k�p
	m_fScaleNum = 0.0f;		// �g�k�p�̒l
	m_FirstSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAddRotNum = 0.0f;
	m_fAlphaNum = 0.0f;
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CExplosion::~CExplosion()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffMat = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	BindModel(model);
	BindTexture(m_apTexture[0]);

	// ����������
	CModel::Init(pos, size);				// ���������
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����

	// �ŏ��̃T�C�Y�擾
	m_FirstSize = size;

	// �g�k�̔{��
	m_fScale = 1.0f;

	// �X�P�[���𑝂₷�l
	m_fScaleNum = EXPLOSION_SCALE_NUM;

	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CExplosion::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CExplosion::Update(void)
{
	// �X�V����
	CModel::Update();

	// ��]�̉��Z
	AddRot();

	// �g��
	ScaleUp();
}

//=================================================================================
// �`�揈��
//=================================================================================
void CExplosion::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �����x���Z
	m_fAlphaNum += EXPLOSION_SUB_ALPHA;

	D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// ���Ȕ���
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		// ����
		pMat[nCntMat].MatD3D.Diffuse.a -= m_fAlphaNum;
	}

	// ���f���̕`��
	CModel::Draw();
}

//=================================================================================
// �g��̏���
//=================================================================================
void CExplosion::ScaleUp(void)
{
	// �X�P�[���̉��Z
	m_fScale += m_fScaleNum;

	// �T�C�Y�̎擾
	D3DXVECTOR3 size =
		D3DXVECTOR3(m_FirstSize.x * m_fScale, m_FirstSize.y * m_fScale, m_FirstSize.z * m_fScale);

	// �T�C�Y��n��
	SetSize(size);

	// �I���t���O
	if (m_fScale >= EXPLOSION_SCALE_LIMIT)
	{
		// �I������
		Uninit();

		return;
	}
}

//=================================================================================
// �p�x�����Z
//=================================================================================
void CExplosion::AddRot(void)
{
	m_fAddRotNum += EXPLOSION_ADD_ROT;

	// �p�x�̕ω�
	D3DXVECTOR3 rot = D3DXVECTOR3(GetRot().x, GetRot().y + D3DXToRadian(m_fAddRotNum), GetRot().z);

	// �p�x��n��
	SetRot(rot);
}

//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CExplosion::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Explosion004.jpg",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/Explosion.x",
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
void CExplosion::UnLoad(void)
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

	for (int nCount = 0; nCount < MAX_EXPLOSION_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}