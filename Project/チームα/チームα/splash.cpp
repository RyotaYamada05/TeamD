//=====================================================
//
// �X�v���b�V���N���X [splash.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "splash.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// �}�N����`
//=====================================================
#define SPLASH_ANIME_SPEED		(5)		// �A�j���[�V�����̑���
#define SPLASH_ANIME_PATTERN	(8)		// �A�j���[�V�����̃p�^�[����

//=====================================================
// static������s
//=====================================================
LPDIRECT3DTEXTURE9 CSplash::m_pTexture = NULL;			// �|���S���̃e�N�X�`��

//=====================================================
// �|���S������
//=====================================================
CSplash * CSplash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������m��
	CSplash *pSplash = new CSplash;

	if (pSplash != NULL)
	{
		// ����������
		pSplash->Init(pos, size);
	}

	return pSplash;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CSplash::CSplash()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSplash::~CSplash()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CSplash::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// �e�N�X�`���ݒ�
	BindTexture(m_pTexture);

	// �A�j���[�V�����ݒ�
	InitAnimation(SPLASH_ANIME_SPEED, SPLASH_ANIME_PATTERN, 0);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CSplash::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CSplash::Update(void)
{
	// �X�V����
	CBillboard::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CSplash::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[

	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// 2D�|���S���`�揈��
	CBillboard::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[

	// Z�o�b�t�@�߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	pDevice->LightEnable(0, TRUE);

}

//=====================================================
// �e�N�X�`�����[�h
//=====================================================
HRESULT CSplash::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/splash.png", &m_pTexture);
	return S_OK;
}

//=====================================================
// �e�N�X�`���A�����[�h
//=====================================================
void CSplash::UnLoad(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}