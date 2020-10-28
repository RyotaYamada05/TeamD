//=====================================================
//
// 2D�����N���X�w�b�_�[ [2d_explosion.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "2d_explosion.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// �}�N����`
//=====================================================
#define EXPLOSION_ANIME_SPEED_2D	(5)
#define EXPLOSION_ANIME_PATTERN_2D	(15)

//=====================================================
// static������s
//=====================================================
LPDIRECT3DTEXTURE9 C2dExplosion::m_pTexture = NULL;			// �|���S���̃e�N�X�`��

//=====================================================
// �|���S������
//=====================================================
C2dExplosion * C2dExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������m��
	C2dExplosion *p2dExplosion = new C2dExplosion;

	if (p2dExplosion != NULL)
	{
		// ����������
		p2dExplosion->Init(pos, size);
	}

	return p2dExplosion;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
C2dExplosion::C2dExplosion()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
C2dExplosion::~C2dExplosion()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT C2dExplosion::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// �e�N�X�`���ݒ�
	BindTexture(m_pTexture);

	// �A�j���[�V�����ݒ�
	InitAnimation(EXPLOSION_ANIME_SPEED_2D, EXPLOSION_ANIME_PATTERN_2D, 0);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void C2dExplosion::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void C2dExplosion::Update(void)
{
	// �X�V����
	CBillboard::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void C2dExplosion::Draw(void)
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
HRESULT C2dExplosion::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/2dExplosion.png", &m_pTexture);
	return S_OK;
}

//=====================================================
// �e�N�X�`���A�����[�h
//=====================================================
void C2dExplosion::UnLoad(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}