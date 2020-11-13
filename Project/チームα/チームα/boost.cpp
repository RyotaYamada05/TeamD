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
LPDIRECT3DTEXTURE9 CBoost::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoost::CBoost()
{
	m_nNum = 0;
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

	//���������m�ۂł��Ă�����
	if (pLocus != NULL)
	{
		//�����������Ăяo��
		pLocus->Init(pos, size);
		pLocus->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pLocus->SetRot(D3DXVECTOR3(rot.x, rot.y+ D3DXToRadian(180), rot.z));
		pLocus->BindTexture(m_pTexture);
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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/boost.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBoost::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBoost::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBoost::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBoost::Update(void)
{
	// 3D�|���S���X�V����
	CScene3D::Update();

	// ���[�U�[�𓮂�������
	BoostMove();
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

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
//	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// ���ʂ��i�����j���J�����O

	// �A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	// �`�揈��
	CScene3D::Draw();

	// �A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Z�o�b�t�@�߂�
//	pDevice->SetRenderState(D3DRS_ZENABLE, true);
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
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x - sinf(rot.y) * 70.0f, pos.y - 50.0f, pos.z - cosf(rot.y) * 70.0f);

	// �p�x
	SetRot(rot);

	// ���W
	SetPos(TargetPos + move);
}