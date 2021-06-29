//=================================================================================
//
// ���N���X [sand.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "sand.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//=================================================================================
// �}�N����`
//=================================================================================
#define SAND_LIFE			(100)		// �̗�
#define SAND_SCALE_NUM		(0.5f)		// �X�P�[���̒l
#define SAND_SCALE_LIMIT	(5.0f)		// �X�P�[���̍ő��

//=================================================================================
// static������
//=================================================================================
LPDIRECT3DTEXTURE9 CSand::m_apTexture[MAX_SAND_TEXTURE] = {};
LPD3DXMESH CSand::m_pMesh = NULL;
LPD3DXBUFFER CSand::m_pBuffMat = NULL;			//�}�e���A�����ւ̃|�C���^
DWORD CSand::m_nNumMat = 0;						//�}�e���A�����̐�

//=================================================================================
// �C���X�^���X����
//=================================================================================
CSand * CSand::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �������m��
	CSand *pSand = new CSand;

	if (pSand != NULL)
	{
		// ����������
		pSand->Init(pos, move, size);		// ���������
		pSand->SetRot(rot);					// ����
	}

	return pSand;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CSand::CSand()
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
CSand::~CSand()
{

}

//=================================================================================
// ����������
//=================================================================================
HRESULT CSand::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
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

	// �ŏ��̃T�C�Y�擾
	m_FirstSize = size;

	// �g�k�̔{��
	m_fScale = 1.0f;

	// �X�P�[���𑝂₷�l
	m_fScaleNum = SAND_SCALE_NUM;

	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CSand::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CSand::Update(void)
{
	// �X�V����
	CModel::Update();

	// �g��
	ScaleUp();
}

//=================================================================================
// �`�揈��
//=================================================================================
void CSand::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �����x���Z
	m_fAlphaNum += 0.005f;

	D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		// ����
		pMat[nCntMat].MatD3D.Diffuse.a -= 0.5f;
	}

	// ���f���̕`��
	CModel::Draw();
}

//=================================================================================
// �g��̏���
//=================================================================================
void CSand::ScaleUp(void)
{
	// �X�P�[���̉��Z
	m_fScale += m_fScaleNum;

	// �T�C�Y�̎擾
	D3DXVECTOR3 size =
		D3DXVECTOR3(m_FirstSize.x * m_fScale, m_FirstSize.y * m_fScale, m_FirstSize.z * m_fScale);

	// �T�C�Y��n��
	SetSize(size);

	// �I���t���O
	if (m_fScale >= SAND_SCALE_LIMIT)
	{
		// �I������
		Uninit();

		return;
	}
}

//=================================================================================
// �e�N�X�`�����[�h
//=================================================================================
HRESULT CSand::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/sand003.png",
		&m_apTexture[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/sand003.x",
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
void CSand::UnLoad(void)
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

	for (int nCount = 0; nCount < MAX_SAND_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}