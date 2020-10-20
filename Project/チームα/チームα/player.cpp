//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED	(5.0f)				// �v���C���[�̈ړ���
#define PLAYER_JUMP		(5.0f)				// �W�����v�̏���
#define GRAVITY_POWAR	(0.25f)				// �d�͂̋���

//=============================================================================
// static������
//=============================================================================
LPD3DXMESH CPlayer::m_pMesh = NULL;
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD CPlayer::m_nNumMat = 0;	//�}�e���A�����̐�

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// ���f�����[�h
//=============================================================================
HRESULT CPlayer::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXLoadMeshFromX("data/model/box.x",
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh

	);

	// ����I��
	return S_OK;

}

void CPlayer::Unload(void)
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
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	pScore = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	MODEL model;
	model.dwNumMat = m_nNumMat;
	model.pBuffer = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	CModel::BindModel(model);

	// ������
	CModel::Init(pos, rot);
	m_pos = pos;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
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

	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �v���C���[�̐���
	PlayerControl();

	// �d�͂�������
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// ����

	// �n�ʂ̐���
	GroundLimit();

	// ���W����^����
	CModel::SetPos(m_pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	// �v���C���[�̈ړ�����
	Walk();

	// �W�����v�̏���
	Jump();
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// W�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_W))
	{
		m_pos.z += cosf(0)*PLAYER_SPEED;
	}
	// S�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_S))
	{
		m_pos.z += cosf(D3DX_PI)*PLAYER_SPEED;
	}
	// A�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_A))
	{
		m_pos.x -= sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}
	// D�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_D))
	{
		m_pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}

	// �ړ��ʉ��Z
	m_pos += m_move;
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ�
	if (pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false)
	{
		// �W�����v�̏���
		m_move.y = 0.0f;
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
	}

	// �ړ��ʉ��Z
	m_pos += m_move;
}

//=============================================================================
// �n�ʂ̐���
//=============================================================================
void CPlayer::GroundLimit(void)
{
	// ���n�̏���
	if (m_pos.y <= 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = 0.0f;
		m_bJump = false;
	}

}