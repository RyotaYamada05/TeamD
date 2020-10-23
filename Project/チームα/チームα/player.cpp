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
#include "bullet.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED			(5.0f)				// �v���C���[�̈ړ���
#define PLAYER_DUSH				(10.0f)				// �v���C���[�̃_�b�V��
#define PLAYER_DUSH_INTER		(80)				// �_�b�V�����ł��钷��
#define DUSH_NONE_TIME			(100)				// �_�b�V���ł��Ȃ�����
#define PLAYER_JUMP				(5.0f)				// �W�����v�̏���
#define GRAVITY_POWAR			(0.05f)				// �d�͂̋���
#define PLAYER_FALL				(-8.0f)				// �}�~���̏���

//=============================================================================
// static������
//=============================================================================
LPD3DXMESH CPlayer::m_pMesh = NULL;
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD CPlayer::m_nNumMat = 0;				//�}�e���A�����̐�
int CPlayer::m_nPlayerAll = 0;

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;
	pPlayer->Init(pos, size);

	// �v���C���[�̔ԍ�����
	pPlayer->m_nPlayerNum = m_nPlayerAll++;

	return pPlayer;
}

//=============================================================================
// ���f�����[�h
//=============================================================================
HRESULT CPlayer::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���f���̐���
	D3DXLoadMeshFromX("data/model/box.x",
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

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
	m_nDushFlame = 0;
	m_nDushInterCnt = 0;
	m_bJump = false;
	m_bDush = false;
	m_bDushInter = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
	m_nPlayerAll = 0;
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
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_V))
	{
		CBullet::Create(m_pos, D3DXVECTOR3(200.0f, 200.0f, 0.0f), CBullet::BULLET_USER_PL1);
	}
	// �v���C���[�̐���
	PlayerControl();

	// �_�b�V�����Ă��Ȃ��Ƃ�
	if (m_bDush == false)
	{
		// �d�͂�������
		m_move.y -= GRAVITY_POWAR;
		m_pos.y += m_move.y;		// ����
	}

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
	// �`�揈��
	CModel::Draw();
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	// �_�b�V�����Ă��Ȃ��Ƃ�
	if (m_bDush == false)
	{
		// �v���C���[�̈ړ�����
		Walk();
	}

	// �W�����v�̏���
	Jump();

	// �}�~���̏���
	Fall();

	// ����̏���
	Dush();
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

	if (js.lX != 0.0f || js.lY != 0)
	{
		float fAngle = CGame::GetCamera(m_nPlayerNum)->Get��();

		if (js.lX < -50.0f)
		{
			// �W���C�p�b�h����
			m_pos.x += sinf(fAngle)* PLAYER_SPEED;
			m_pos.z -= cosf(fAngle)* PLAYER_SPEED;
		}
		else if (js.lX > 50.0f)
		{
			// �W���C�p�b�h����
			m_pos.x -= sinf(fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(fAngle)* PLAYER_SPEED;
		}
		else
		{

		}

		if (js.lY < -50.0f)
		{
			// �W���C�p�b�h����
			m_pos.x -= cosf(fAngle)* PLAYER_SPEED;
			m_pos.z -= sinf(fAngle)* PLAYER_SPEED;
		}
		else if (js.lY > 50.0f)
		{
			// �W���C�p�b�h����
			m_pos.x += cosf(fAngle)* PLAYER_SPEED;
			m_pos.z += sinf(fAngle)* PLAYER_SPEED;
		}
		else
		{

		}
	}

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

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(1, m_nPlayerNum) && m_bJump == false 
		|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false )
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

//=============================================================================
// �}�~��
//=============================================================================
void CPlayer::Fall(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ�
	if (pKeyboard->GetTrigger(DIK_B) && m_bJump == true ||
		CManager::GetJoypad()->GetJoystickTrigger(2, m_nPlayerNum) && m_bJump == true)
	{
		// �W�����v�̏���
		m_move.y = 0.0f;
		m_move.y = PLAYER_FALL;
	}
}

//=============================================================================
// �_�b�V��
//=============================================================================
void CPlayer::Dush(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �W�����v���g����Ƃ�
	if (m_bDushInter == false)
	{
		// X�{�^���̎�
		if (CManager::GetJoypad()->GetJoystickTrigger(0, m_nPlayerNum))
		{
			// �W���C�p�b�h�̎擾
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fAngle = atan2f((float)js.lX, (float)js.lY);

				// �W���C�p�b�h����
				m_move.x += sinf(-D3DX_PI /2)* PLAYER_DUSH;
				m_move.z -= cosf(-D3DX_PI /2)* PLAYER_DUSH;
				m_bDush = true;

			}
		}

		// B�{�^���̎�
		if (CManager::GetJoypad()->GetJoystickTrigger(3, m_nPlayerNum))
		{
			// �W���C�p�b�h�̎擾
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fAngle = atan2f((float)js.lX, (float)js.lY);

				// �W���C�p�b�h����
				m_move.x += sinf(D3DX_PI / 2)* PLAYER_DUSH;
				m_move.z -= cosf(D3DX_PI / 2)* PLAYER_DUSH;
				m_bDush = true;

			}
		}


		// W�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.z += cosf(0)*PLAYER_DUSH;
			m_bDush = true;
		}
		// S�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.z += cosf(D3DX_PI)*PLAYER_DUSH;
			m_bDush = true;
		}
		// A�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.x -= sinf(D3DX_PI / 2)*PLAYER_DUSH;
			m_bDush = true;
		}
		// D�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.x += sinf(D3DX_PI / 2)*PLAYER_DUSH;
			m_bDush = true;
		}
	}
	else
	{
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		m_nDushInterCnt++;
	}

	// �_�b�V�����Ă���Ƃ�
	if (m_bDush == true)
	{
		// �_�b�V�����I���܂ł��J�E���g
		m_nDushFlame++;
	}

	// �_�b�V�����I���t���[��
	if (m_nDushFlame >= PLAYER_DUSH_INTER)
	{
		m_nDushFlame = 0;
		m_bDush = false;
		m_bDushInter = true;
	}

	// �_�b�V�����ł���悤�ɂȂ�t���[��
	if (m_nDushInterCnt >= DUSH_NONE_TIME)
	{
		m_nDushInterCnt = 0;
		m_bDushInter = false;
	}
}

D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
