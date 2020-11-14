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
#include "2d_explosion.h"
#include "smoke.h"
#include "sand.h"
#include "bill.h"
#include "laser.h"
#include "locus.h"
#include "boost.h"
#include "sound.h"
#include "ui.h"
#include "time.h"
#include "missile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED			(15.0f)				// �v���C���[�̈ړ���
#define PLAYER_DUSH				(30.0f)				// �v���C���[�̃_�b�V��
#define PLAYER_DUSH_INTER		(80)				// �_�b�V�����ł��钷��
#define DUSH_NONE_TIME			(50)				// �_�b�V���ł��Ȃ�����
#define PLAYER_JUMP				(9.0f)				// �W�����v�̏���
#define GRAVITY_POWAR			(0.1f)				// �d�͂̋���
#define PLAYER_FALL				(-12.0f)			// �}�~���̏���
#define GROUND_RIMIT			(0.0f)				// �n�ʂ̐���
#define PLAYE_ROT_Y_FRONT		(D3DXToRadian(90.0f))	//�v���C���[�̏c���O
#define PLAYE_ROT_Y_LEFT		(D3DXToRadian(180.0f))	//�v���C���[�̏c����
#define PLAYE_ROT_Y_RIGHT		(D3DXToRadian(0.0f))	//�v���C���[�̏c���E
#define PLAYE_ROT_Y_BUCK		(D3DXToRadian(-90.0f))	//�v���C���[�̏c����
#define STICK_SENSITIVITY		(50.0f)					//�X�e�B�b�N���x
#define STATE_DAMAGE_TIME		(100)				// �_���[�W��Ԃ̃J�E���g
#define STATE_EXPLOSION_TIME	(30)				// ������Ԃ̃J�E���g
#define STATE_EXPLOSION_END		(500)				// ������Ԃ̏I���t���[��
#define PLAYER_BOMB_INTER		(150)				// �{���̑ҋ@�t���[��
#define PLAYER_MISSILE			(150)				// �~�T�C���̑ҋ@�t���[��
#define PLAYER_LASER_INTER		(300)				// ���[�U�[�̑ҋ@�t���[��
#define LBX_XFAILE_NAME "data/Text/motion_LBX.txt"	//LBX�̃t�@�C���p�X
#define GANDAMU_XFAILE_NAME "data/Text/motion_gandamu.txt"	//�K���_���̃t�@�C���p�X

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
MODELFILLE g_modelfile[MAX_MODEL_PARTS];	//���f���p�[�c���.

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
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nDushFlame = 0;
	m_nDushInterCnt = 0;
	m_bJump = false;
	m_bDush = false;
	m_bDushInter = false;
	m_nPlayerNum = 0;						// �v���C���[�̔ԍ�
	m_fAngle = 0.0f;
	m_state = PLAYER_STATE_NONE;
	m_nStateCounter = 0;
	m_bEnd = false;
	memset(m_pWinLose, 0, sizeof(m_pWinLose));
	m_bFall = false;	
	m_bWalk = false;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_nNumKey = 0;
	m_apKeyInfo = NULL;
	m_nKey = 0;;
	m_nCountMotion = 0;
	m_nMotionInterval = 0;
	memset(&m_Motion, 0, sizeof(m_Motion));
	m_MotionState = MOTION_IDOL;
	memset(m_pBoost,0,sizeof(m_pBoost));
	m_bWinLose = false;
	m_bMotionPlaing = false;
	m_bEntered = false;
	m_bWinLose = false;
	m_bDraw = false;
	m_bArmor = false;
	m_nBombInter = 0;
	m_nMissileInter = 0;
	m_nLaserInter = 0;
	m_bAttack = false;
	m_bWin = false;
	m_pDraw = NULL;

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
	pScore = NULL;
	memset(m_pLife, 0, sizeof(m_pLife));
	m_pCharge = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nDushFlame = 0;
	m_nDushInterCnt = 0;
	m_bJump = false;
	m_bDush = false;
	m_bDushInter = false;
	m_fAngle = 0.0f;
	m_state = PLAYER_STATE_NONE;
	m_nStateCounter = 0;
	m_bEnd = false;
	m_bFall = false;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_nNumKey = 0;
	m_apKeyInfo = NULL;
	m_nKey = 0;;
	m_nCountMotion = 0;
	memset(&m_Motion, 0, sizeof(m_Motion));
	m_MotionState = MOTION_IDOL;
	memset(m_pBoost, 0, sizeof(m_pBoost));
	m_bWinLose = false;
	m_bDraw = false;
	//CLife::SetReady(true);
	m_nBombInter = 0;							// �{���̃C���^�[�o��
	m_nLaserInter = 0;;							// ���[�U�[�̃C���^�[�o��
	m_bAttack = false;
	m_bWin = true;
	m_pDraw = NULL;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_pWinLose[nCount] = NULL;
	}

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

				D3DXVECTOR3(0.0f, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//1P�̃��C�t�Q�[�W
		if (m_pLife[1] == NULL)
		{
			//2P���ɑ̗̓Q�[�W�𐶐�
			m_pLife[1] = CLife::Create(D3DXVECTOR3(LIFE_POS_RIGHT_X, LIFE_POS_DOWN_Y, 0.0f),
				D3DXVECTOR3(0.0f, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}

		//�P�o�̒e�̃`���[�W�Q�[�W
		if (m_pCharge == NULL)
		{
			//2P���ɑ̗̓Q�[�W�𐶐�
			m_pCharge = CCharge::Create(D3DXVECTOR3(CHARGE_POS_LEFT_X, CHARGE_POS_Y, 0.0f),
				D3DXVECTOR3(MAX_CHARGE, CHARGE_SIZE_Y, 0.0f), D3DCOLOR_RGBA(87, 210, 128, 255));
		}

		//ROT�̏����l�ݒ�i�G�̕����j
		m_rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);
		m_rotDest = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);
		break;

		//2P�������ꍇ
	case 1:
		//�Q�o�̃��C�t�Q�[�W
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(LIFE_POS_RIGHT_X, LIFE_POS_UP_Y, 0.0f),
				D3DXVECTOR3(0.0f, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//�P�o�̃��C�t�Q�[�W		
		if (m_pLife[1] == NULL)
		{
			m_pLife[1] = CLife::Create(D3DXVECTOR3(LIFE_POS_LEFT_X, LIFE_POS_DOWN_Y, 0.0f),
				D3DXVECTOR3(0.0f, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}

		//�Q�o�̒e�̃`���[�W�Q�[�W
		if (m_pCharge == NULL)
		{
			m_pCharge = CCharge::Create(D3DXVECTOR3(CHARGE_POS_RIGHT_X, CHARGE_POS_Y, 0.0f),
				D3DXVECTOR3(MAX_CHARGE, CHARGE_SIZE_Y, 0.0f), D3DCOLOR_RGBA(87, 210, 128, 255));
		}

		//ROT�̏����l�ݒ�i�G�̕����j
		m_rotDest = D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f);

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
	for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] == NULL)
		{
			//���f���̐���
			m_apModelAnime[nCntModel] = CModelAnime::Create(g_modelfile[nCntModel].xFileName,
				g_modelfile[nCntModel].offsetPos, g_modelfile[nCntModel].offsetRot);
		}
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
	//�ҋ@���[�V�����̍Đ�
	SetMotion(MOTION_IDOL);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_PARTS; nCntModelNum++)
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

	// �{���ƃ��[�U�[�̃t���[�����Z
	m_nBombInter++;
	m_nLaserInter++;
	m_nMissileInter++;

	// �Â����W�擾
	m_OldPos = m_pos;

	// �v���C���[�̏��
	PlayerState();

	// �_�b�V�����Ă��Ȃ��Ƃ�
	if (m_bDush == false)
	{
		// �d�͂�������
		m_move.y -= GRAVITY_POWAR;
		m_pos.y += m_move.y;		// ����
	}
	// �n�ʂ̐���
	GroundLimit();

	// ���[�V�������
	MotionState();

	//�A�j���[�V�����̍X�V����
	UpdateMotion();
	// �I���t���O
	switch (m_nPlayerNum)
	{
	case 0:
	{
		PLAYER_STATE state = CGame::GetPlayer(1)->GetState();

		if (state == PLAYER_STATE_EXPLOSION || state == PLAYER_STATE_DRAW)
		{
			m_bWin = true;
			return;
		}
	}
	break;

	case 1:
	{
		PLAYER_STATE state = CGame::GetPlayer(0)->GetState();

		if (state == PLAYER_STATE_EXPLOSION || state == PLAYER_STATE_DRAW)
		{
			m_bWin = true;
			return;
		}
	}
	break;

	default:
		break;
	}

	if (m_pLife[0] != NULL)	
	{
		float fLife = m_pLife[0]->GetLife();
		// �I������
		if (fLife <= 0.0f && m_pLife[0]->GetReadey() == false)
		{
			// �������
			m_state = PLAYER_STATE_EXPLOSION;

			//Uninit();
			return;
		}
	}

	// �^�C�����~�b�g
	TimeLimit();

	// �v���C���[�̐���
	PlayerControl();

	//�ʒu�ֈړ��ʂ����Z
	m_pos += m_move;

	while (m_rotDest.y - m_rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - m_rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	m_rot += (m_rotDest - m_rot)*0.1f;

	//�^�[�Q�b�gON
	if (CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
	{
		//�p�x�ݒ�
		m_rotDest.y = CGame::GetCamera(m_nPlayerNum)->Get��();
	}
	else //�^�[�Q�b�gOFF
	{
	}

	//�͈͊O�ɍs���Ȃ��悤�ɂ��鏈��
	MapLimit();

	// �O��
	Locus();
}

//=============================================================================
// �A�j���[�V�����̍X�V����
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey[MAX_MODEL_PARTS];
	D3DXVECTOR3 diffPos, diffRot, startPos, startRot, setPos, setRot;

	//���݃L�[���ő�L�[�������̏ꍇ
	if (m_nKey < m_Motion[m_MotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
		{
			m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey];

			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
				diffPos.x = (pKey[nCntModel]->fPosX - startPos.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.y = (pKey[nCntModel]->fPosY - startPos.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.z = (pKey[nCntModel]->fPosZ - startPos.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

				//1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
				diffRot.x = (pKey[nCntModel]->fRotX - startRot.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.y = (pKey[nCntModel]->fRotY - startRot.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.z = (pKey[nCntModel]->fRotZ - startRot.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

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
			m_nMotionInterval++;

			if (m_nMotionInterval == 10)
			{
				m_bMotionPlaing = false;
				
				//���n�E�U���E���E�u�[�X�g���[�V�����̎������͂�true�E�W�����v��false
				if ((m_MotionState == MOTION_LANDING || m_MotionState == MOTION_ATTACK ||
					m_MotionState == MOTION_LEFTBOOST || m_MotionState == MOTION_RIGHTBOOST)
					&& m_bEntered == true && m_bJump == false)
				{
					SetMotion(MOTION_WALK);
				}
				else if (m_bJump == false)
				{
					SetMotion(MOTION_IDOL);
				}
			}
			
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

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��i�����j���J�����O

	for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{

			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
}

//=============================================================================
// ���[�V�����Z�b�g����
//=============================================================================
void CPlayer::SetMotion(MOTION_STATE motion)
{

	if (m_Motion[m_MotionState].bLoop == false && 
		m_bMotionPlaing == true)
	{
			return;
	}

	m_nKey = 0;
	m_nCountMotion = 0;
	m_nMotionInterval = 0;
	D3DXVECTOR3 pos, rot;
	
	m_MotionState = motion;
	m_bMotionPlaing = true;

	for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
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

	switch (m_MotionState)
	{
	case MOTION_IDOL:

		// ���G�t���O�̉���
		m_bArmor = false;
		m_bAttack = false;
		break;

	case MOTION_DAMAGE:

		// ���G�t���O
		m_bArmor = true;
		break;
	case MOTION_ATTACK:

		// �U���t���O
		m_bAttack = true;
		break;
	}
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::PlayerState(void)
{
	CSound *pSound = CManager::GetSound();

	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		// �ʏ���

		break;

	case PLAYER_STATE_DAMAGE:

		// �_���[�W���󂯂���
		m_nStateCounter++;

		// ���ȏ��
		if (m_MotionState == MOTION_DAMAGE && m_bMotionPlaing == false)
		{
			m_nStateCounter = 0;
			m_state = PLAYER_STATE_NORMAL;
		}
		break;

	case PLAYER_STATE_EXPLOSION:
		// �������
		m_nStateCounter++;

		// �����������S�̏o��
		if (m_bWinLose == false)
		{
			switch (m_nPlayerNum)
			{
			case 0:

				m_bWinLose = true;
				CGame::GetPlayer(1)->SetWinToLose(true);

				if (m_pWinLose[0] == NULL)
				{
					// 1P���������Ƃ�
					m_pWinLose[0] = CUi::Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_WIN);
				}

				if (m_pWinLose[1] == NULL)
				{
					m_pWinLose[1] = CUi::Create(D3DXVECTOR3(UI_RESULT_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_LOSE);
				}
				break;

			case 1:
				m_bWinLose = true;

				CGame::GetPlayer(0)->SetWinToLose(true);

				if (m_pWinLose[0] == NULL)
				{
					// 2P���������Ƃ�
					m_pWinLose[0] = CUi::Create(D3DXVECTOR3(UI_RESULT_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_WIN);
				}

				if (m_pWinLose[1] == NULL)
				{
					m_pWinLose[1] = CUi::Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_LOSE);
				}

				break;
			}
		}
		// ��莞�Ԃ�
		if (m_nStateCounter % STATE_EXPLOSION_TIME == 0)
		{
			D3DXVECTOR3 TargetPos =
				D3DXVECTOR3(m_pos.x + rand() % 50 + rand() % 50 - rand() % 50 - rand() % 50,
					m_pos.y + rand() % 100 + rand() % 100 - rand() % 50 - rand() % 50,
					m_pos.z + rand() % 50 + rand() % 50 - rand() % 50 - rand() % 50);

			// �����̐���
			C2dExplosion::Create(TargetPos,
				D3DXVECTOR3(EXPLOSION_SIZE_X_2D, EXPLOSION_SIZE_Y_2D, EXPLOSION_SIZE_Z_2D));
			//������
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION_DEAH);

		}

		if (m_nStateCounter >= STATE_EXPLOSION_END)
		{
			//���������~�߂�
			pSound->Stop(CSound::SOUND_LABEL_SE_EXPLOSION_DEAH);
			// �I���̃t���O
			m_bEnd = true;
		//	m_nStateCounter = PLAYER_STATE_NONE;

			switch (m_nPlayerNum)
			{
			case 0:
			{
				CPlayer *pPlayer = CGame::GetPlayer(1);

				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{
					// ���C�t�̏���
					if (m_pLife[nCount] != NULL)
					{
						m_pLife[nCount]->Uninit();
						m_pLife[nCount] = NULL;
					}

					if (m_pWinLose[nCount] != NULL)
					{
						m_pWinLose[nCount]->Uninit();
						m_pWinLose[nCount] = NULL;
					}

					if (pPlayer->m_pLife[nCount] != NULL)
					{
						pPlayer->m_pLife[nCount]->Uninit();
						pPlayer->m_pLife[nCount] = NULL;
					}
					if (pPlayer->m_pWinLose[nCount] != NULL)
					{
						pPlayer->m_pWinLose[nCount]->Uninit();
						pPlayer->m_pWinLose[nCount] = NULL;
					}
				}
			}
			break;

			case 1:
			{
				CPlayer *pPlayer = CGame::GetPlayer(0);
				// ���C�t�̏���
				if (m_pLife[1] != NULL)
				{
					m_pLife[1]->Uninit();
					m_pLife[1] = NULL;
				}

				if (pPlayer != NULL)
				{
					for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
					{
						// ���C�t�̏���
						if (m_pLife[nCount] != NULL)
						{
							m_pLife[nCount]->Uninit();
							m_pLife[nCount] = NULL;
						}
						if (m_pWinLose[nCount] != NULL)
						{

							m_pWinLose[nCount]->Uninit();
							m_pWinLose[nCount] = NULL;
						}

						if (pPlayer->m_pLife[nCount] != NULL)
						{
							pPlayer->m_pLife[nCount]->Uninit();
							pPlayer->m_pLife[nCount] = NULL;
						}

						if (pPlayer->m_pWinLose[nCount] != NULL)
						{
							pPlayer->m_pWinLose[nCount]->Uninit();
							pPlayer->m_pWinLose[nCount] = NULL;
						}
					}
				}
			}
			}
			break;
	case PLAYER_STATE_DRAW:
		if (m_bDraw == false)
		{
			m_bDraw = true;
		}
		switch (m_nPlayerNum)
		{
		case 0:

			if (m_pDraw == NULL)
			{
				m_pDraw = CUi::Create(D3DXVECTOR3(UI_RESULT_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_DRAW);
			}
			break;
		case 1:

			if (m_pDraw == NULL)
			{
				m_pDraw = CUi::Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_DRAW);
			}
			break;

		}

		// ���������̔���
		m_nStateCounter++;

		if (m_nStateCounter >= STATE_EXPLOSION_END)
		{
			// �I���̃t���O
			m_bEnd = true;

			switch (m_nPlayerNum)
			{
			case 0:
			{
				CPlayer *pPlayer = CGame::GetPlayer(1);

				if (pPlayer != NULL)
				{
					for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
					{
						// ���C�t�̏���
						if (m_pLife[nCount] != NULL)
						{
							m_pLife[nCount]->Uninit();
							m_pLife[nCount] = NULL;
						}
						if (pPlayer->m_pLife[nCount] != NULL)
						{
							pPlayer->m_pLife[nCount]->Uninit();
							pPlayer->m_pLife[nCount] = NULL;
						}
					}

					if (m_pDraw != NULL)
					{
						m_pDraw->Uninit();
						m_pDraw = NULL;
					}

					if (pPlayer->m_pDraw != NULL)
					{
						pPlayer->m_pDraw->Uninit();
						pPlayer->m_pDraw = NULL;
					}
				}
			}
			break;

			case 1:
			{
				CPlayer *pPlayer = CGame::GetPlayer(0);

				if (pPlayer != NULL)
				{
					for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
					{
						// ���C�t�̏���
						if (m_pLife[nCount] != NULL)
						{
							m_pLife[nCount]->Uninit();
							m_pLife[nCount] = NULL;
						}
						if (pPlayer->m_pLife[nCount] != NULL)
						{
							pPlayer->m_pLife[nCount]->Uninit();
							pPlayer->m_pLife[nCount] = NULL;
						}
					}

					if (m_pDraw != NULL)
					{
						m_pDraw->Uninit();
						m_pDraw = NULL;
					}

					if (pPlayer->m_pDraw != NULL)
					{
						pPlayer->m_pDraw->Uninit();
						pPlayer->m_pDraw = NULL;
					}

				}

			}
			break;

			default:
				break;
			}
		}
		}
	}
}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer::MotionState(void)
{
	switch (m_MotionState)
	{
	case MOTION_IDOL:
		//	m_MotionState = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		// �U�����[�V����
		if (m_nKey >= 1 && m_nKey <= 3)
		{
			if (m_bArmor == false)
			{
				// ����̓����蔻��
				WeaponCollision();
			}
		}
		break;
	case MOTION_DAMAGE:
		
		break;
	}
}

//=============================================================================
// ����̓����蔻��
//=============================================================================
void CPlayer::WeaponCollision(void)
{
	CPlayer *pPlayer = NULL;

	// �v���C���[���̎擾
	switch (m_nPlayerNum)
	{
	case 0:
		pPlayer = CGame::GetPlayer(1);
		break;
	case 1:
		pPlayer = CGame::GetPlayer(0);
		break;
	}

	if (pPlayer != NULL)
	{
		//�ʒu�̎擾
		D3DXVECTOR3 targetPos = pPlayer->GetPos();

		if (pPlayer->GetArmor() == false)
		{
			D3DXVECTOR3 Top = D3DXVECTOR3(
				m_apModelAnime[20]->GetMtxWorld()._41,
				m_apModelAnime[20]->GetMtxWorld()._42,
				m_apModelAnime[20]->GetMtxWorld()._43);

			// �����蔻��
			if (targetPos.x - PLAYER_COLLISION_X / 2 <= Top.x + WEAPON_COLLISION_X / 2 &&
				targetPos.x + PLAYER_COLLISION_X / 2 >= Top.x - WEAPON_COLLISION_X / 2 &&
				targetPos.y - 0.0f <= Top.y + WEAPON_COLLISION_Y / 2 &&
				targetPos.y + PLAYER_COLLISION_Y >= Top.y - WEAPON_COLLISION_Y / 2 &&
				targetPos.z - PLAYER_COLLISION_Z / 2 <= Top.z + WEAPON_COLLISION_Z / 2 &&
				targetPos.z + PLAYER_COLLISION_Z / 2 >= Top.z - WEAPON_COLLISION_Z / 2)
			{
				// �����̐���
				C2dExplosion::Create(D3DXVECTOR3(targetPos.x, 250.0f, targetPos.z),
					D3DXVECTOR3(EXPLOSION_SIZE_X_2D, EXPLOSION_SIZE_Y_2D, EXPLOSION_SIZE_Z_2D));

				// �v���C���[���̎擾
				switch (m_nPlayerNum)
				{
				case 0:

					CGame::GetCamera(1)->SetTarget(false);

					for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
					{
						CGame::GetPlayer(1)->GetLife(nCount)->Decrease(100, m_nPlayerNum, true);

					}

					CGame::GetPlayer(1)->SetMotion(MOTION_DAMAGE);

					break;
				case 1:
					CGame::GetCamera(0)->SetTarget(false);

					for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
					{
						CGame::GetPlayer(0)->GetLife(nCount)->Decrease(100, m_nPlayerNum, true);

					}

					CGame::GetPlayer(0)->SetMotion(MOTION_DAMAGE);

					break;
				}
			}
		}

	}
}

//=============================================================================
// �^�C������
//=============================================================================
void CPlayer::TimeLimit(void)
{
	// �^�C���擾
	CTime *pTime = CGame::GetTime();

	if (pTime != NULL)
	{
		// �������Ԃ�
		if (pTime->GetTime() <= 0)
		{
			pTime->SetTime(0);

			if (m_nPlayerNum == 0)
			{
				float fSizeX[MAX_PLAYER] = { 0.0f, 0.0f };

				fSizeX[0] = m_pLife[0]->GetSize().x;
				fSizeX[1] = CGame::GetPlayer(1)->GetLife(0)->GetSize().x;

				// ���s����
				if (fSizeX[0] > fSizeX[1])
				{
					// 1P����������
					CPlayer *pPlayer = CGame::GetPlayer(1);
					pPlayer->SetState(PLAYER_STATE_EXPLOSION);

					return;
				}
				else if (fSizeX[0] < fSizeX[1])
				{
					// 2P����������
					CPlayer *pPlayer = CGame::GetPlayer(0);
					pPlayer->SetState(PLAYER_STATE_EXPLOSION);

					return;
				}
				else
				{
					for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
					{
						// 2P����������
						CPlayer *pPlayer = CGame::GetPlayer(nCount);
						pPlayer->SetState(PLAYER_STATE_DRAW);
					}
				}
			}
		}
	}
}


//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	if (m_pLife[0]->GetReadey() == false)
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

		switch (m_nPlayerNum)
		{
		case 0:
			// �{���̏���
			bomb();
			break;

		case 1:
			// �~�T�C���̏���
			Missile();
			break;
		}

		// ���[�U�[�̏���
		Laser();
	}
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

	CSound *pSound = CManager::GetSound();

	if (m_bAttack == false)
	{
		if (pKeyboard->GetTrigger(DIK_I) ||
			CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, m_nPlayerNum))
		{
			//�U�����[�V�������Đ�
			SetMotion(MOTION_ATTACK);
		}
	}
	//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f) && m_bAttack == false)
	{
		//���͂���ɂ���
		m_bEntered = true;

		//�_���[�W���󂯂Ă��Ȃ��Ƃ��݈̂ړ�����
		if (m_MotionState != MOTION_DAMAGE)
		{
			//�W�����v���Ă��Ȃ��Ƃ�
			if (m_bJump == false && m_bWalk == false)
			{
				m_bWalk = true;
				//���s���[�V�����̍Đ�
				SetMotion(MOTION_WALK);
			}
			//�X�e�B�b�NX�̓��͂����x�����Ă���
			if (js.lX < -STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(270.0f);

				m_pos.x += cosf(m_fAngle)* PLAYER_SPEED;
				m_pos.z -= sinf(m_fAngle)* PLAYER_SPEED;
			}

			else if (js.lX > STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(90.0f);

				m_pos.x -= cosf(m_fAngle)* PLAYER_SPEED;
				m_pos.z += sinf(m_fAngle)* PLAYER_SPEED;
			}
			else
			{
			}
			//�X�e�B�b�NY�̓��͂����x�𒴂��Ă���
			if (js.lY < -STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle;

				m_pos.x -= sinf(m_fAngle)* PLAYER_SPEED;
				m_pos.z -= cosf(m_fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(315.0f);
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(45.0f);
				}
			}

			else if (js.lY > STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(180.0f);
				m_pos.x += sinf(m_fAngle)* PLAYER_SPEED;
				m_pos.z += cosf(m_fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(225.0f);
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(135.0f);
				}
			}

		}
		// W�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_W))
		{
			m_rotDest.y = D3DXToDegree(m_fAngle);
			m_pos.z += cosf(0)*PLAYER_SPEED;
		}
		// S�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_S))
		{
			m_rotDest.y = sin(m_fAngle);
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
	else
	{
		m_bEntered = false;
		if (m_bWalk == true)
		{
			//�ҋ@���[�V�������Đ�
			SetMotion(MOTION_IDOL);
			m_bWalk = false;
		}
	}


}
//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	CSound *pSound = CManager::GetSound();
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, m_nPlayerNum) && m_bJump == false	
			|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false)
	{
		// �W�����v�̏���
		m_move.y = 0.0f;
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
		m_bWalk = false;

		//�W�����v���[�V�����̍Đ�
		SetMotion(MOTION_JUMP);
		pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
	}
}

//=============================================================================
// �n�ʂ̐���
//=============================================================================
void CPlayer::GroundLimit(void)
{
	CSound *pSound = CManager::GetSound();

	// ���n�̏���
	if (m_pos.y <= GROUND_RIMIT)
	{
		if (m_bJump == true)
		{
			SetMotion(MOTION_LANDING);
		}
		m_move.y = 0.0f;
		m_pos.y = GROUND_RIMIT;
		m_bJump = false;
		
		if (m_bFall == true)
		{
			// �}�~�����g�p���Ă��Ȃ���Ԃɂ���
			m_bFall = false;

			// ���̐���
			CSmoke::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
				D3DXVECTOR3(SMOKE_SIZE_X, SMOKE_SIZE_Y, SMOKE_SIZE_Z));

			//���n��
			pSound->Play(CSound::SOUND_LABEL_SE_SAND);

		}
	}
}

//=============================================================================
// �}�~���̏���
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
		m_bFall = true;
	}
}

//=============================================================================
// �_�b�V���̏���
//=============================================================================
void CPlayer::Dush(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CSound *pSound = CManager::GetSound();

	// �_�b�V�����g����Ƃ�
	if (m_bDushInter == false)
	{
		//�J�����p�x�擾
		m_fAngle = CGame::GetCamera(m_nPlayerNum)->Get��();

		// X�{�^���̎�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, m_nPlayerNum))
		{
			// �W���C�p�b�h�̎擾
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			//���͂����݂���
			if (js.lX != 0.0f || js.lY != 0.0f)
			{
				//�ړ��ʏ�����
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�_�b�V�����ړ��ʐݒ�
				m_move.x += cosf(m_fAngle)* PLAYER_DUSH;
				m_move.z -= sinf(m_fAngle)* PLAYER_DUSH;

				m_bDush = true;
				m_bWalk = false;
				//�^�[�{��
				pSound->Play(CSound::SOUND_LABEL_SE_TURBO);

				// �n��ɂ�����
				if (m_bJump == false)
				{
					// ���̐���
					CSand::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(m_rot.x + 0.0f, m_rot.y, m_rot.z+0.0f),
						D3DXVECTOR3(SAND_SIZE_X, SAND_SIZE_Y, SAND_SIZE_Z));
				}
				D3DXVECTOR3 TargetPos = D3DXVECTOR3(m_pos.x - sinf(m_rot.y) * 70.0f, m_pos.y - 50.0f, m_pos.z - cosf(m_rot.y) * 70.0f);


				for (int nCount = 0; nCount <= MAX_BOOST; nCount++)
				{
					if (m_pBoost[nCount] == NULL)
					{
						// �u�[�X�g����
						m_pBoost[nCount] = CBoost::Create(TargetPos + m_move,
							D3DXVECTOR3(m_rot.x + D3DXToRadian(270.0f), m_rot.y + 0.0f, m_rot.z + 0.0f), D3DXVECTOR3(BOOST_SIZE_X, BOOST_SIZE_Y, BOOST_SIZE_Z), m_nPlayerNum);
					}
				}

				//���u�[�X�g���[�V�����̍Đ�
				SetMotion(MOTION_LEFTBOOST);

				// �n��ɂ�����
				if (m_bJump == false)
				{
					// ���̐���
					CSand::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(m_rot.x + 0.0f, m_rot.y, m_rot.z+0.0f),
						D3DXVECTOR3(SAND_SIZE_X, SAND_SIZE_Y, SAND_SIZE_Z));
				}
			}
		}

		// B�{�^���̎�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, m_nPlayerNum))
		{
			// �W���C�p�b�h�̎擾
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				//�ړ��ʏ�����
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//�_�b�V�����ړ��ʐݒ�
				m_move.x -= cosf(m_fAngle)* PLAYER_DUSH;
				m_move.z += sinf(m_fAngle)* PLAYER_DUSH;

				m_bDush = true;
				//�E�u�[�X�g���[�V�����̍Đ�
				SetMotion(MOTION_RIGHTBOOST);
				//�^�[�{��
				pSound->Play(CSound::SOUND_LABEL_SE_TURBO);				

				// �n��ɂ�����
				if (m_bJump == false)
				{
					// ���̐���
					CSand::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(m_rot.x , m_rot.y + 3.14f, m_rot.z + 0.0f),
						D3DXVECTOR3(SAND_SIZE_X, SAND_SIZE_Y, SAND_SIZE_Z));
				}
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

			D3DXVECTOR3 TargetPos = D3DXVECTOR3(m_pos.x - sinf(m_rot.y) * 70.0f, m_pos.y - 50.0f, m_pos.z - cosf(m_rot.y) * 70.0f);

			for (int nCount = 0; nCount < MAX_BOOST; nCount++)
			{
				if (m_pBoost[nCount] == NULL)
				{
					// �u�[�X�g����
					m_pBoost[nCount] = CBoost::Create(TargetPos + m_move,
						D3DXVECTOR3(m_rot.x + D3DXToRadian(270.0f), m_rot.y + 0.0f, m_rot.z + 0.0f), D3DXVECTOR3(BOOST_SIZE_X, BOOST_SIZE_Y, BOOST_SIZE_Z), m_nPlayerNum);
				}
			}
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

		//int nNum = rand() % 3;

		//if (nNum % 3 == 0)
		//{
		//	// �ΉԂ̐���
		//	for (int nCount = 0; nCount < 2; nCount++)
		//	{
		//		CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 25.0f, m_pos.z), D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
		//			D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE, SPARK_SPPED);
		//	}
		//}
	}

	// �_�b�V�����I���t���[��
	if (m_nDushFlame >= PLAYER_DUSH_INTER)
	{
		m_nDushFlame = 0;
		m_bDush = false;
		m_bDushInter = true;


		for (int nCount = 0; nCount < MAX_BOOST; nCount++)
		{
			if (m_pBoost[nCount] != NULL)
			{
				m_pBoost[nCount]->Uninit();
				m_pBoost[nCount] = NULL;
			}
		}

	}

	// �_�b�V�����ł���悤�ɂȂ�t���[��
	if (m_nDushInterCnt >= DUSH_NONE_TIME)
	{
		m_nDushInterCnt = 0;
		m_bDushInter = false;
	}
}

//=============================================================================
// �r�[���̏���
//=============================================================================
void CPlayer::beam(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CSound *pSound = CManager::GetSound();

	// L�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nPlayerNum) && m_bJump == false || pKeyboard->GetTrigger(DIK_L) && m_bJump == false )
	{
		switch (m_nPlayerNum)
		{
		case 0:
			if (CCharge::GetCharge(0) > PLAYER_LASER)
			{

				//�o���b�g�̐���
				CBeam::Create(D3DXVECTOR3(m_pos.x, 200.0f, m_pos.z), D3DXVECTOR3(0.0f, 100.0f, -BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL1);
				//�e��������Q�[�W�����炷
				m_pCharge->Reduce(PLAYER_LASER, true, 0);
				pSound->Play(CSound::SOUND_LABEL_SE_BULLET);
			}
			break;

		case 1:
			
			if (CCharge::GetCharge(1) > PLAYER_LASER)
			{
				//�o���b�g�̐���
				CBeam::Create(D3DXVECTOR3(m_pos.x, 200.0f, m_pos.z), D3DXVECTOR3(0.0f, 100.0f, BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL2);
				//�e��������Q�[�W�����炷
				m_pCharge->Reduce(PLAYER_LASER, true, 1);
				pSound->Play(CSound::SOUND_LABEL_SE_BULLET);
			}
			break;
		}
	}
}

//=============================================================================
// �O�Ղ̏���
//=============================================================================
void CPlayer::Locus(void)
{
	// �Â����W�擾
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		m_apModelAnime[19]->GetOldMtxWorld()._41,
		m_apModelAnime[19]->GetOldMtxWorld()._42,
		m_apModelAnime[19]->GetOldMtxWorld()._43);

	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		m_apModelAnime[20]->GetOldMtxWorld()._41,
		m_apModelAnime[20]->GetOldMtxWorld()._42,
		m_apModelAnime[20]->GetOldMtxWorld()._43);

	D3DXVECTOR3 Origin = D3DXVECTOR3(
		m_apModelAnime[19]->GetMtxWorld()._41,
		m_apModelAnime[19]->GetMtxWorld()._42,
		m_apModelAnime[19]->GetMtxWorld()._43);

	D3DXVECTOR3 Top = D3DXVECTOR3(
		m_apModelAnime[20]->GetMtxWorld()._41,
		m_apModelAnime[20]->GetMtxWorld()._42,
		m_apModelAnime[20]->GetMtxWorld()._43);

	// �O�Ղ̐���
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		D3DXVECTOR3(m_rot.x, m_rot.y, m_rot.z), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE);

}

//=============================================================================
// �~�T�C��
//=============================================================================
void CPlayer::Missile(void)
{
	if (m_nMissileInter >= PLAYER_BOMB_INTER)
	{
		// �L�[�{�[�h�X�V
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();
		CSound *pSound = CManager::GetSound();

		// L�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) && m_bJump == false
			|| pKeyboard->GetTrigger(DIK_V) && m_bJump == false)
		{
			m_nMissileInter = 0;
			switch (m_nPlayerNum)
			{
			case 0:
				if (CCharge::GetCharge(0) > PLAYER_BOMB)
				{
					//�o���b�g�̐���
					CMissile::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(MISSILE_SIZE_X, MISSILE_SIZE_Y, MISSILE_SIZE_Z),
						CMissile::MISSILE_USER_PL1, MISSILE_SPPED);

					//���ˉ�
					pSound->Play(CSound::SOUND_LABEL_SE_BULLET2);
					//�e��������Q�[�W�����炷

					if (m_pCharge != NULL)
					{
						m_pCharge->Reduce(PLAYER_BOMB, true, 0);
					}
				}
				break;

			case 1:

				if (CCharge::GetCharge(1) > PLAYER_BOMB)
				{
					//�o���b�g�̐���
					CMissile::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(MISSILE_SIZE_X, MISSILE_SIZE_Y, MISSILE_SIZE_Z),
						CMissile::MISSILE_USER_PL2, MISSILE_SPPED);

					//���ˉ�
					pSound->Play(CSound::SOUND_LABEL_SE_BULLET2);

					if (m_pCharge != NULL)
					{
						//�e��������Q�[�W�����炷
						m_pCharge->Reduce(PLAYER_BOMB, true, 1);
					}
				}
				break;
			}
		}
	}

}

//=============================================================================
// �{���̏���
//=============================================================================
void CPlayer::bomb(void)
{
	if (m_nBombInter >= PLAYER_BOMB_INTER)
	{
		// �L�[�{�[�h�X�V
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();
		CSound *pSound = CManager::GetSound();

		// L�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) && m_bJump == false
			|| pKeyboard->GetTrigger(DIK_V) && m_bJump == false)
		{
			m_nBombInter = 0;
			switch (m_nPlayerNum)
			{
			case 0:
				if (CCharge::GetCharge(0) > PLAYER_BOMB)
				{
					//�o���b�g�̐���
					CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(0.0f, BOMB_MOVE_Y, 0.0f),
						D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL1);

					//���ˉ�
					pSound->Play(CSound::SOUND_LABEL_SE_BULLET2);
					//�e��������Q�[�W�����炷

					if (m_pCharge != NULL)
					{
						m_pCharge->Reduce(PLAYER_BOMB, true, 0);
					}
				}
				break;

			case 1:

				if (CCharge::GetCharge(1) > PLAYER_BOMB)
				{
					//�o���b�g�̐���
					CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
						D3DXVECTOR3(0.0f, BOMB_MOVE_Y, BOMB_SPEED),
						D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL2);

					//���ˉ�
					pSound->Play(CSound::SOUND_LABEL_SE_BULLET2);

					if (m_pCharge != NULL)
					{
						//�e��������Q�[�W�����炷
						m_pCharge->Reduce(PLAYER_BOMB, true, 1);
					}
				}
				break;
			}
		}
	}
}

//=============================================================================
// ���[�U�[
//=============================================================================
void CPlayer::Laser(void)
{
	if (m_pLife[0] != NULL)
	{
		float fSizeX = m_pLife[0]->GetSize().x;

		if (m_nLaserInter >= PLAYER_LASER_INTER && fSizeX <= 200.0f)
		{
			// �L�[�{�[�h�X�V
			CInputKeyboard *pKeyboard = CManager::GetKeyboard();

			// M�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
			if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, m_nPlayerNum) && m_bJump == false
				|| pKeyboard->GetTrigger(DIK_M) && m_bJump == false)
			{
				m_nLaserInter = 0;

				switch (m_nPlayerNum)
				{
				case 0:
					//�o���b�g�̐���
					CLaser::Create(/*D3DXVECTOR3(m_pos.x + sinf(m_rot.z)+200.0f, m_pos.y, m_pos.z + cosf(m_rot.z)+200.0f)*/m_pos,
						D3DXVECTOR3(0.0f, 0.0f, -LASER_SPEED),
						D3DXVECTOR3(0.0f, m_rot.y, 0.0f),

						D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Y, LASER_SIZE_Z),
						CBullet2::BULLET2_USER_PL1);

					//�e��������Q�[�W�����炷
					if (m_pCharge != NULL)
					{

						m_pCharge->Reduce(150, true, 0);
					}
					break;

				case 1:
					//�o���b�g�̐���

					CLaser::Create(m_pos,
						D3DXVECTOR3(0.0f, 0.0f, LASER_SPEED),
						D3DXVECTOR3(0.0f, m_rot.y, 0.0f),

						D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Y, LASER_SIZE_Z),
						CBullet2::BULLET2_USER_PL2);

					//�e��������Q�[�W�����炷
					if (m_pCharge != NULL)
					{

						m_pCharge->Reduce(150, true, 1);
					}
					break;
				}
			}
		}
	}
}

//=============================================================================
// �͈͊O�ɍs���Ȃ��悤�ɂ��鏈��
//=============================================================================
void CPlayer::MapLimit(void)
{
	//�E
	if (m_pos.x > MAP_LIMIT)
	{
		m_pos.x = MAP_LIMIT;
	}

	//��
	if (m_pos.x <-MAP_LIMIT)
	{
		m_pos.x = -MAP_LIMIT;
	}

	//��
	if (m_pos.z > MAP_LIMIT)
	{
		m_pos.z = MAP_LIMIT;
	}

	//��O
	if (m_pos.z <-MAP_LIMIT)
	{
		m_pos.z = -MAP_LIMIT;
	}
}

//=============================================================================
// �u���b�N�̏�ɏ�����Ƃ�
//=============================================================================
void CPlayer::BlockUp(void)
{
	if (m_bJump == true)
	{
		//���n���[�V�����̍Đ�
		SetMotion(MOTION_LANDING);
	}
	m_move.y = 0.0f;
	m_bJump = false;

	if (m_bFall == true)
	{
		// �}�~�����g�p���Ă��Ȃ���Ԃɂ���
		m_bFall = false;
	}
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
	int nKeyNum = 0;		//�L�[�ԍ�
	int nMotionNum = 0;		//���[�V�����ԍ�
	if (m_nPlayerNum == 0)
	{
		//�t�@�C���I�[�v��
		pFile = fopen(LBX_XFAILE_NAME, "r");
	}
	else
	{
		//�t�@�C���I�[�v��
		pFile = fopen(GANDAMU_XFAILE_NAME, "r");
	}

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

				//�C���f�b�N�X���P�i�߂�
				nModelIndex++;
			}

			if (strcmp(aModeName, "CHARACTERSET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
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
						//�C���f�b�N�X���P�i�߂�
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
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}

void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//=============================================================================
// �����������S�t���O�̐ݒ�
//=============================================================================
void CPlayer::SetWinToLose(bool bFlag)
{
	m_bWinLose = bFlag;
}

void CPlayer::SetState(PLAYER_STATE state)
{
	m_state = state;
}


bool CPlayer::GetSetWinLose(void)
{
	return m_bWinLose;
}

//=============================================================================
// ���C�t�̏��
//=============================================================================
CLife * CPlayer::GetLife(int nNumber)
{
	return m_pLife[nNumber];
}

//=============================================================================
// ���W�̏��
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �Â����W���
//=============================================================================
D3DXVECTOR3 CPlayer::GetOldPos(void)
{
	return m_OldPos;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �`���[�W�̏��
//=============================================================================
CCharge * CPlayer::GetCgarge(void)
{
	return m_pCharge;
}
//=============================================================================
// �G���h���
//=============================================================================
bool CPlayer::GetEnd(void)
{
	return m_bEnd;
}

//=============================================================================
// �v���C���[��Ԃ̏��
//=============================================================================
CPlayer::PLAYER_STATE CPlayer::GetState(void)
{
	return m_state;
}

bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//=============================================================================
// �����������
//=============================================================================
bool CPlayer::GetDraw(void)
{
	return m_bDraw;
}

//=============================================================================
// ���G�t���O�̏��
//=============================================================================
bool CPlayer::GetArmor(void)
{
	return m_bArmor;
}

//=============================================================================
// �����̃t���O
//=============================================================================
bool CPlayer::GetWin(void)
{
	return m_bWin;
}