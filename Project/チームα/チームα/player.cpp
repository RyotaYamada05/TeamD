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
#include "charge.h"
#include "camera.h"
#include "life.h"
#include "game.h"
#include "beam.h"
#include "particle.h"
#include "bomb.h"

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
LPD3DXMESH CPlayer::m_pMesh = NULL;			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CPlayer::m_nNumMat = 0;				// �}�e���A�����̐�
int CPlayer::m_nPlayerAll = 0;				// �v���C���[�̑���

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// �v���C���[�̔ԍ�����
	pPlayer->m_nPlayerNum = m_nPlayerAll++;

	// ����������
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// ���f�����[�h
//=============================================================================
HRESULT CPlayer::LoadModel(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���f���̐���

	D3DXLoadMeshFromX("data/model/ti-muiro.x",		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);


	// ����I��
	return S_OK;
}

//=============================================================================
// ���f���A�����[�h
//=============================================================================
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
	m_pCharge = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nDushFlame = 0;
	m_nDushInterCnt = 0;
	m_bJump = false;
	m_bDush = false;
	m_bDushInter = false;
	m_nPlayerNum = 0;						// �v���C���[�̔ԍ�
	m_fAngle = 0.0f;
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
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���f���̏���ݒ�
	MODEL model;
	model.dwNumMat = m_nNumMat;
	model.pBuffer = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	CModel::BindModel(model);

	//�ʒu�̐ݒ�
	m_pos = pos;

	switch (m_nPlayerNum)
	{
	//1P�������ꍇ
	case 0:
		//1P�̃��C�t�Q�[�W		if (m_pLife[0] == NULL)
		{
			//1P���ɑ̗̓Q�[�W�𐶐�
			m_pLife[0] = CLife::Create(D3DXVECTOR3(LIFE_POS_LEFT_X, LIFE_POS_UP_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}


		//1P�̃��C�t�Q�[�W
		if (m_pLife[1] == NULL)
		{

			//2P���ɑ̗̓Q�[�W�𐶐�
			m_pLife[1] = CLife::Create(D3DXVECTOR3(LIFE_POS_RIGHT_X, LIFE_POS_DOWN_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}


		//�P�o�̒e�̃`���[�W�Q�[�W
		if (m_pCharge == NULL)
		{
			//2P���ɑ̗̓Q�[�W�𐶐�
			m_pCharge = CCharge::Create(D3DXVECTOR3(CHARGE_POS_LEFT_X, CHARGE_POS_Y, 0.0f),
				D3DXVECTOR3(MAX_CHARGE, CHARGE_SIZE_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
		}

		m_rot = D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f);

		// ���f���^�C�v�ݒ�
		SetType(MODEL_TYPE_PLAYER1);
		break;

	//2P�������ꍇ
	case 1:
		//�Q�o�̃��C�t�Q�[�W
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(LIFE_POS_RIGHT_X, LIFE_POS_UP_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//�P�o�̃��C�t�Q�[�W		
		if (m_pLife[1] == NULL)
		{
			
			m_pLife[1] = CLife::Create(D3DXVECTOR3(LIFE_POS_LEFT_X, LIFE_POS_DOWN_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}

		//�Q�o�̒e�̃`���[�W�Q�[�W
		if (m_pCharge == NULL)
		{

			m_pCharge = CCharge::Create(D3DXVECTOR3(CHARGE_POS_RIGHT_X, CHARGE_POS_Y, 0.0f),
				D3DXVECTOR3(MAX_CHARGE, CHARGE_SIZE_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		m_rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);

		// ���f���^�C�v�ݒ�
		SetType(MODEL_TYPE_PLAYER2);

		break;

			
	default:
		break;
	}

	// ������	
	CModel::Init(m_pos, size);

	//rot������
	CModel::SetRot(m_rot);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
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

	D3DXVECTOR3 size = m_pLife[0]->GetSize();
	if (size.x <= 0)
	{
		//Uninit();
		return;
	}
	//�ʒu�ֈړ��ʂ����Z
	m_pos += m_move;

	// �n�ʂ̐���
	GroundLimit();

		switch (m_nPlayerNum)
	{
	case 0:
		if (CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
		{
			m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Get��() + D3DXToRadian(90.0f));
		}

		break;

	case 1:
		if (CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
		{
			m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Get��() + D3DXToRadian(90.0f));
		}

		break;
	}

	// ���W����^����
	CModel::SetPos(m_pos);
	CModel::SetRot(m_rot);
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

	// �r�[���̏���
	beam();

	// �{���̏���
	bomb();
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
		m_fAngle = CGame::GetCamera(m_nPlayerNum)->Get��();

		if (js.lX < -50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Get��() - D3DXToRadian(180.0f));
			}

			// �W���C�p�b�h����

			m_pos.x += sinf(m_fAngle)* PLAYER_SPEED;
			m_pos.z -= cosf(m_fAngle)* PLAYER_SPEED;
		}
		else if (js.lX > 50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Get��());
			}

			// �W���C�p�b�h����
			m_pos.x -= sinf(m_fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(m_fAngle)* PLAYER_SPEED;
		}
		else
		{

		}

		if (js.lY < -50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Get��() + D3DXToRadian(90.0f));
			}

			// �W���C�p�b�h����
			m_pos.x -= cosf(m_fAngle)* PLAYER_SPEED;
			m_pos.z -= sinf(m_fAngle)* PLAYER_SPEED;
		}
		else if (js.lY > 50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Get��() + D3DXToRadian(-90.0f));
			}
			// �W���C�p�b�h����

			m_pos.x += cosf(m_fAngle)* PLAYER_SPEED;
			m_pos.z += sinf(m_fAngle)* PLAYER_SPEED;
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
				m_fAngle = CGame::GetCamera(m_nPlayerNum)->Get��();

				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				// �W���C�p�b�h����				
				m_move.x += sinf(m_fAngle)* PLAYER_DUSH;
				m_move.z -= cosf(m_fAngle)* PLAYER_DUSH;

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
				m_fAngle = CGame::GetCamera(m_nPlayerNum)->Get��();

				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				m_move.x -= sinf(m_fAngle)* PLAYER_DUSH;
				m_move.z += cosf(m_fAngle)* PLAYER_DUSH;

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

		int nNum = rand() % 3;

		if (nNum % 3 == 0)
		{
			// �ΉԂ̐���
			for (int nCount = 0; nCount < 2; nCount++)
			{
				CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 25.0f, m_pos.z), D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE, SPARK_SPPED);
			}
		}
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

//=============================================================================
// �r�[��
//=============================================================================
void CPlayer::beam(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// L�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nPlayerNum) && m_bJump == false
		|| pKeyboard->GetTrigger(DIK_L) && m_bJump == false)
	{
		switch (m_nPlayerNum)
		{
		case 0:
			//�o���b�g�̐���
			CBeam::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, -BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL1);
			break;

		case 1:
			//�o���b�g�̐���
			CBeam::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL2);
			break;
		}
	}
}

//=============================================================================
// �{��
//=============================================================================
void CPlayer::bomb(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// L�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) && m_bJump == false
		|| pKeyboard->GetTrigger(DIK_V) && m_bJump == false)
	{
		switch (m_nPlayerNum)
		{
		case 0:
			//�o���b�g�̐���
			CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
				D3DXVECTOR3(0.0f, BOMB_MOVE_Y, -BOMB_SPEED),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL1);
			break;

		case 1:
			//�o���b�g�̐���
			CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y +50.0f, m_pos.z), 
				D3DXVECTOR3(0.0f, BOMB_MOVE_Y, BOMB_SPEED),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL2);
			break;
		}
	}

}

CLife * CPlayer::GetLife(int nNumber)
{
	return m_pLife[nNumber];
}

D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

CCharge * CPlayer::GetCgarge(void)
{
	return m_pCharge;
}
