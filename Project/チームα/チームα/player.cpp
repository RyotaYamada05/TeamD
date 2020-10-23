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
#include "life.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED			(10.0f)				// �v���C���[�̈ړ���
#define PLAYER_DUSH				(15.0f)				// �v���C���[�̃_�b�V��
#define PLAYER_DUSH_INTER		(80)				// �_�b�V�����ł��钷��
#define DUSH_NONE_TIME			(100)				// �_�b�V���ł��Ȃ�����
#define PLAYER_JUMP				(5.0f)				// �W�����v�̏���
#define GRAVITY_POWAR			(0.05f)				// �d�͂̋���
#define PLAYER_FALL				(-8.0f)				// �}�~���̏���
#define GROUND_RIMIT			(0.0f)				// �n�ʂ̐���

//=============================================================================
// static������
//=============================================================================
LPD3DXMESH CPlayer::m_pMesh = NULL;			//���b�V�����ւ̃|�C���^
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

	// �v���C���[�̔ԍ�����
	pPlayer->m_nPlayerNum = m_nPlayerAll++;

	pPlayer->Init(pos, size);


	return pPlayer;
}

//=============================================================================
// ���f�����[�h
//=============================================================================
HRESULT CPlayer::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���f���̐���
	D3DXLoadMeshFromX("data/model/TestBox1.x",
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
	memset(m_pLife, 0, sizeof(m_pLife));
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

	m_pos = pos;

	//���C�t�̃��[�h
	CLife::Load();

	switch (m_nPlayerNum)
	{
	case 0:
		//�P�o�̃��C�t�Q�[�W
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(130.0f,30.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//�P�o�̃��C�t�Q�[�W
		if (m_pLife[1] == NULL)
		{
			m_pLife[1] = CLife::Create(D3DXVECTOR3(860.0f, 65.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}
		break;

	case 1:
		//�Q�o�̃��C�t�Q�[�W
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(130.0f, 65.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}

		//�Q�o�̃��C�t�Q�[�W
		if (m_pLife[1] == NULL)
		{
			m_pLife[1] = CLife::Create(D3DXVECTOR3(860.0f, 30.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}
		break;

			
	default:
		break;
	}


//	CLife::Create(D3DXVECTOR3(300, 200.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(60, 179, 113, 255), CLife::LIFETYPE_FAST_PLAYER);


	// ������
	CModel::Init(m_pos, rot);

	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// �I������
	CModel::Uninit();

	//���C�t�̃A�����[�h
	CLife::Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//�ʒu�̎擾
	m_pos = CModel::GetPos();
	
	// �v���C���[�̐���
	PlayerControl();

	// �_�b�V�����Ă��Ȃ��Ƃ�
	if (m_bDush == false)
	{
		// �d�͂�������
		m_move.y -= GRAVITY_POWAR;
		m_pos.y += m_move.y;		// ����
	}

	//�ʒu�ֈړ��ʂ����Z
	m_pos += m_move;

	// �n�ʂ̐���
	GroundLimit();

	switch (m_nPlayerNum)
	{
	case 0:
		//R2�g���K�[�܂���V�L�[����������
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) ||
			pKeyboard->GetTrigger(DIK_V))
		{
			//�o���b�g�̐���
			CBullet::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CBullet::BULLET_USER_PL1);
		}
		break;

	case 1:
		//R2�g���K�[�܂���V�L�[����������
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) ||
			pKeyboard->GetTrigger(DIK_V))
		{
			//�o���b�g�̐���
			CBullet::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CBullet::BULLET_USER_PL2);
		}
		break;
	}

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
		float fAngle = atan2f((float)js.lX, (float)js.lY);

		if (m_nPlayerNum == 0)
		{
			// �W���C�p�b�h����
			m_pos.x += sinf(-fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(-fAngle)* PLAYER_SPEED;
		}
		else
		{
			// �W���C�p�b�h����
			m_pos.x += sinf(+fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(+fAngle)* -PLAYER_SPEED;

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
		m_pos.x += sinf(-D3DX_PI / 2)*PLAYER_SPEED;
	}
	// D�L�[���������Ƃ�
	if (pKeyboard->GetPress(DIK_D))
	{
		m_pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, m_nPlayerNum) && m_bJump == false
		|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false )
	{
			// �W�����v�̏���
			m_move.y = 0.0f;
			m_move.y = PLAYER_JUMP;
			m_bJump = true;
	}
}

//=============================================================================
// �n�ʂ̐���
//=============================================================================
void CPlayer::GroundLimit(void)
{
	// ���n�̏���
	if (m_pos.y <= GROUND_RIMIT)
	{
		m_move.y = GROUND_RIMIT;
		m_pos.y = GROUND_RIMIT;
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
		CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nPlayerNum) && m_bJump == true)
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
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, m_nPlayerNum))
		{
			// �W���C�p�b�h�̎擾
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fAngle = atan2f((float)js.lX, (float)js.lY);

				// �W���C�p�b�h����
				m_move.x += sinf(-D3DX_PI / 2)* PLAYER_DUSH;
				m_move.z -= cosf(-D3DX_PI / 2)* PLAYER_DUSH;
				m_bDush = true;

			}
		}

		// B�{�^���̎�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, m_nPlayerNum))
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

CLife * CPlayer::GetLife(int nNumber)
{
	return m_pLife[nNumber];
}
