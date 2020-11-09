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
#include <stdio.h>
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
#define LBX_XFAILE_NAME "data/Text/motion_LBX.txt"	//LBX��X�t�@�C���p�X

//���f���p�[�c���
MODELFILLE g_modelfile[MODEL_PARTS];

//=============================================================================
// static������
//=============================================================================
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
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_nNumKey = 0;
	m_apKeyInfo = NULL;
	m_nKey = 0;;
	m_nCountMotion = 0;
	memset(&m_Motion, 0, sizeof(m_Motion));
	m_MotionState = M_MOTION_STATE_IDOL;
	m_nFlame = 0;
		 
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
	//�ʒu�̐ݒ�
	m_pos = pos;

	switch (m_nPlayerNum)
	{
	//1P�������ꍇ
	case 0:
		//1P�̃��C�t�Q�[�W		
		if (m_pLife[0] == NULL)
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

		break;

	default:
		break;
	}
	//�t�@�C���ǂݍ���
	if (FAILED(ReadFile()))
	{
		return E_FAIL;
	}

	//���f���p�[�c�����J��Ԃ�
	for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
	{
		//���f���̐���
		m_apModelAnime[nCntModel] = CModelAnime::Create(g_modelfile[nCntModel].xFileName,
			g_modelfile[nCntModel].offsetPos, g_modelfile[nCntModel].offsetRot);

		//�e�q�\���̐ݒ�
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//�e���f���̏ꍇ
			if (nCntModel == 0)
			{
				m_apModelAnime[nCntModel]->SetParent(NULL);
			}
			//�q���f���̏ꍇ
			else
			{
				//�����̐e����ݒ肷��
				m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[g_modelfile[nCntModel].nParent]);
			}
		}
	}
	
	//�A�j���[�V�����̐ݒ�
	SetMotion(M_MOTION_STATE_IDOL);
	SetMotion(M_MOTION_STATE_DUSH);
	//SetMotion(M_MOTION_STATE_JUMP);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModelNum = 0; nCntModelNum < MODEL_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�I������
			m_apModelAnime[nCntModelNum]->Uninit();

			//�������̍폜
			delete m_apModelAnime[nCntModelNum];

			//�������̃N���A
			m_apModelAnime[nCntModelNum] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	
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

	//�A�j���[�V�����̍X�V����
	UpdateMotion();

}

//=============================================================================
// �A�j���[�V�����̍X�V����
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey[MODEL_PARTS];	//���݃L�[�Ǝ��̃L�[���
	KEY *pKeyNext[MODEL_PARTS];
	D3DXVECTOR3 diffPos, diffRot, startPos, startRot, setPos, setRot;
	float fRateMotion;	//���݃L�[���玟�L�[�̑��Βl

	//���݃L�[���ő�L�[�������̏ꍇ
	if (m_nKey < m_Motion[m_MotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
		{
			m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey];

			//���݃L�[�̎擾
			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];

			if (m_nKey + 1 == m_Motion[m_MotionState].nNumKey)
			{
				m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[0];
			}
			else
			{
				m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey + 1];
			}

			//���L�[�̎擾
			pKeyNext[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		//���Βl�̎Z�o
		fRateMotion = (float)m_nCountMotion / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

		for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
				diffPos.x = (pKeyNext[nCntModel]->fPosX - startPos.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.y = (pKeyNext[nCntModel]->fPosY - startPos.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.z = (pKeyNext[nCntModel]->fPosZ - startPos.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

				//1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
				diffRot.x = (pKeyNext[nCntModel]->fRotX - startRot.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.y = (pKeyNext[nCntModel]->fRotY - startRot.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.z = (pKeyNext[nCntModel]->fRotZ - startRot.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
		
				setPos.x = diffPos.x * m_nCountMotion + startPos.x;
				setPos.y = diffPos.y * m_nCountMotion + startPos.y;
				setPos.z = diffPos.z * m_nCountMotion + startPos.z;
						
				setRot.x = diffRot.x * m_nCountMotion + startRot.x;
				setRot.y = diffRot.y * m_nCountMotion + startRot.y;
				setRot.z = diffRot.z * m_nCountMotion + startRot.z;

				D3DXVECTOR3 pos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 rot = m_apModelAnime[nCntModel]->GetRotAnime();

				//�ʒu�ɍX�V�p�̈ʒu�����Z
				pos += setPos;

				//�����ɍX�V�p�̌��������Z
				rot += setRot;
				
				//�ʒu�̐ݒ�
				m_apModelAnime[nCntModel]->SetPosAnime(setPos);

				//�����̐ݒ�
				m_apModelAnime[nCntModel]->SetRotAnime(setRot);
			}
		}
	
		//���[�V�����J�E���^�[�̉��Z
		m_nCountMotion++;

		//���݃L�[�̍Đ��t���[���ɒB������
		if (m_nCountMotion == m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame)
		{
			//�L�[���P�i�߂�
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//���[�v����Ȃ�
		if (m_Motion[m_MotionState].bLoop == true)
		{
			m_nKey = 0;
		}
		else
		{
			return;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �`�揈��
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModelNum = 0; nCntModelNum < MODEL_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}
}

//=============================================================================
// ���[�V�����Z�b�g����
//=============================================================================
void CPlayer::SetMotion(MOTION_STATE motion)
{
	m_MotionState = motion;
	m_nKey = 0;
	D3DXVECTOR3 pos, rot;

	for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//�J�n�ʒu
			pos.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			pos.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			pos.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

			//�J�n����
			rot.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			rot.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			rot.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//�ʒu�̐ݒ�
			m_apModelAnime[nCntModel]->SetPosAnime(pos);

			//�����̐ݒ�
			m_apModelAnime[nCntModel]->SetRotAnime(rot);
		}
	}
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
			SetMotion(M_MOTION_STATE_JUMP);
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
			//�e��������Q�[�W�����炷
			m_pCharge->Reduce(50, true);
			break;

		case 1:
			//�o���b�g�̐���
			CBeam::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL2);
			//�e��������Q�[�W�����炷
			m_pCharge->Reduce(50, true);
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
			//�e��������Q�[�W�����炷
			m_pCharge->Reduce(50, true);
			break;

		case 1:
			//�o���b�g�̐���
			CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y +50.0f, m_pos.z), 
				D3DXVECTOR3(0.0f, BOMB_MOVE_Y, BOMB_SPEED),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL2);
			//�e��������Q�[�W�����炷
			m_pCharge->Reduce(50, true);
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

//=============================================================================
// �t�@�C���ǂݍ��ݏ���
//=============================================================================
HRESULT CPlayer::ReadFile(void)
{
	FILE *pFile = NULL;	//FILE�|�C���^
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	//���f���̃C���f�b�N�X
	int nMotionType = 0;	//���[�V�����̃^�C�v
	int nKeyNum = 0;//�L�[�ԍ�
	int nMotionNum = 0;	//���[�V�����ԍ�

	//�t�@�C���I�[�v��
	pFile = fopen(LBX_XFAILE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			if (strcmp(aModeName, "MODEL_FILENAME") == 0)
			{
				//X�t�@�C���̖��O
				sscanf(aHeadData, "%*s %*s %s %*s %*s", g_modelfile[nModelIndex].xFileName);
				nModelIndex++;
			}

			if (strcmp(aModeName, "CHARACTERSET") == 0)
			{
				nModelIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aModeName, "END_CHARACTERSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					if (strcmp(aModeName, "PARTSSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aModeName, "END_PARTSSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							if (strcmp(aModeName, "PARENT") == 0)
							{
								//�e�q���̐ݒ�
								sscanf(aHeadData, "%*s %*s %d", &g_modelfile[nModelIndex].nParent);
							}
							if (strcmp(aModeName, "POS") == 0)
							{
								//�ʒu�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetPos.x, 
									&g_modelfile[nModelIndex].offsetPos.y, &g_modelfile[nModelIndex].offsetPos.z);
							}
							if (strcmp(aModeName, "ROT") == 0)
							{
								//�����̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetRot.x,
									&g_modelfile[nModelIndex].offsetRot.y, &g_modelfile[nModelIndex].offsetRot.z);
							}
						}
						nModelIndex++;
					}
				}
			}

			//���[�V�����Z�b�g
			if (strcmp(aModeName, "MOTIONSET") == 0)
			{
				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aModeName, "END_MOTIONSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					//���[�v���̎擾
					if (strcmp(aModeName, "LOOP") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
					}

					//�L�[���̎擾
					if (strcmp(aModeName, "NUM_KEY") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
					}

					if (strcmp(aModeName, "KEYSET") == 0)
					{
						//END_KEYSET�ɂȂ�܂ŌJ��Ԃ�
						while (strcmp(aModeName, "END_KEYSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							//�t���[�����̎擾
							if (strcmp(aModeName, "FRAME") == 0)
							{
								sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
							}

							//�e�L�[�̃I�t�Z�b�g���̎擾
							if (strcmp(aModeName, "KEY") == 0)
							{
								//END_KEY�ɂȂ�܂ŌJ��Ԃ�
								while (strcmp(aModeName, "END_KEY") != 0)
								{
									//���ǂݍ���Ń��[�h���𒊏o
									fgets(aHeadData, sizeof(aHeadData), pFile);
									sscanf(aHeadData, "%s", aModeName);

									//�ʒu�̎擾
									if (strcmp(aModeName, "POS") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
									}

									//�����̎擾
									if (strcmp(aModeName, "ROT") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
									}
								}
								//�ǂݏI�������J�E���g��1�i�߂�
								nKeyNum++;
							}
						}
						nKeyNum = 0;
						nMotionNum++;
					}
				}
				nMotionNum = 0;
				nMotionType++;
			}

		} while (strcmp(aModeName, "END_SCRIPT") != 0);


		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK);

		return	E_FAIL;
	}
}
