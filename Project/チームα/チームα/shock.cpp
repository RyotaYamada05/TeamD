//=================================================================================
//
// �Ռ��N���X [shock.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "shock.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//=================================================================================
// �}�N����`
//=================================================================================
#define SHOCK_LIFE			(100)		// �̗�
#define SHOCK_SCALE_NUM		(0.05f)	// �X�P�[���̒l

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CShock::m_apTexture[MAX_SHOCK_TEXTURE] = {};
LPD3DXMESH CShock::m_pMesh = NULL;
LPD3DXBUFFER CShock::m_pBuffMat = NULL;			//�}�e���A�����ւ̃|�C���^
DWORD CShock::m_nNumMat = 0;					//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CShock * CShock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	// �������m��
	CShock *pShock = new CShock;

	if (pShock != NULL)
	{
		// ����������
		pShock->Init(pos, move, size);		// ���������
	}

	return pShock;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CShock::CShock()
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
CShock::~CShock()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CShock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffer = m_pBuffMat;
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
	m_fScaleNum = SHOCK_SCALE_NUM;

	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CShock::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CShock::Update(void)
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
void CShock::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �����x���Z
	m_fAlphaNum += 0.01f;

	D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
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
void CShock::ScaleUp(void)
{
	// �X�P�[���̉��Z
	m_fScale += m_fScaleNum;

	// �T�C�Y�̎擾
	D3DXVECTOR3 size = 
		D3DXVECTOR3(m_FirstSize.x * m_fScale, m_FirstSize.y * m_fScale, m_FirstSize.z * m_fScale);

	// �T�C�Y��n��
	SetSize(size);
	
	// �I���t���O
	if (m_fScale >= 3.5f)
	{
		// �I������
		Uninit();

		return;
	}
}

//=================================================================================
// �p�x�����Z
//=================================================================================
void CShock::AddRot(void)
{
	m_fAddRotNum += 0.3f;

	// �p�x�̕ω�
	D3DXVECTOR3 rot = D3DXVECTOR3(GetRot().x , GetRot().y + D3DXToRadian(m_fAddRotNum), GetRot().z);

	// �p�x��n��
	SetRot(rot);
}

//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CShock::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/shock.jpg",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/shock.x",
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
void CShock::UnLoad(void)
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

	for (int nCount = 0; nCount < MAX_SHOCK_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}