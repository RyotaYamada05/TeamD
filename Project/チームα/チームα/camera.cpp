//=============================================================================
//
// ���C������ [camera.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "lockon.h"
#include "ui.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define DISTANCE					(1000.0f)				//���_�`�����_�̋���
#define PLAYER_HEIGHT				(100.0f)				//�����_�̍���
#define PLAYE_ROT_VERTICAL_FRONT	(D3DXToRadian(0.0f))	//�v���C���[�̏c���O
#define PLAYE_ROT_VERTICAL_LEFT		(D3DXToRadian(180.0f))	//�v���C���[�̏c����
#define PLAYE_ROT_VERTICAL_RIGHT	(D3DXToRadian(0.0f))	//�v���C���[�̏c���E
#define PLAYE_ROT_VERTICAL_BUCK		(D3DXToRadian(-90.0f))	//�v���C���[�̏c����
#define WIN_START_ROT_VERTICAL		(D3DXToRadian(90.0f))	//�������c����]�̊J�n�p
#define WIN_START_ROT_HORIZONTAL	(D3DXToRadian(40.0f))	//������������]�̊J�n�p
#define WIN_START_DISTANCE			(1500.0f)				//�������̊J�n����
#define WIN_END_ROT_VERTICAL		(D3DXToRadian(360.0f+90.0f))	//�������c����]�̏I���p
#define WIN_END_ROT_HORIZONTAL		(D3DXToRadian(100.0f))	//������������]�̏I���p
#define WIN_END_DISTANCE			(500.0f)				//�������̏I������
#define WIN_ROT_MOVE_SUBTRACTION	(0.1f)					//�������̉�����]�p�x�ω���
#define LOSE_ROT_VERTICAL			(D3DXToRadian(90.0f))	//�������c����]�̊J�n�p
#define LOSE_START_DISTANCE			(500.0f)				//�������̊J�n����
#define LOSE_END_DISTANCE			(1000.0f)				//�������̏I������

//=============================================================================
// static������
//=============================================================================
int CCamera::m_nCameraAll = 0;

//=============================================================================
// �N���G�C�g
//=============================================================================
CCamera * CCamera::Create(void)
{
	// ����������
	CCamera *pCamera = new CCamera;

	pCamera->Init();

	return pCamera;
}

//=============================================================================
//�J�����N���X�̃R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	//�e�����o�ϐ��̃N���A
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̍��W
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̍��W�i�ړI�n�j
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_�i�ړI�n�j
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_fDistance = 0.0f;							// ���_�`�����_�̋���
	m_fMove = 0.0f;								// �ړ���
	m_nCameraNum = m_nCameraAll++;						// �J�����̔ԍ�

	m_bTarget = false; //�^�[�Q�b�g�g�p
}

//=============================================================================
//�J�����N���X�̃f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
//�J�����N���X�̏���������
//=============================================================================
HRESULT CCamera::Init(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	switch (m_nCameraNum)
	{
	case 0:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_rot.y = 0.0f;
		m_f�� = D3DXToRadian(75.0f);
		m_f�� = D3DXToRadian(0.0f);

		m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);	//�����_�͑S��0���W������
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//������x�N�g��
		m_posV.x = m_posR.x + m_fDistance* sinf(m_f��) * cosf(m_f��);
		m_posV.y = m_posR.z + m_fDistance* cosf(m_f��);
		m_posV.z = m_posR.y + m_fDistance* sinf(m_f��) * sinf(m_f��);

		
		break;

	case 1:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_f�� = D3DXToRadian(75.0f);
		m_f�� = D3DXToRadian(0.0f);
		m_rot.y = 0.0f;

		m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);			// �����_�͑S��0���W������
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_posV.x = m_posR.x + m_fDistance* sinf(m_f��) * cosf(m_f��);
		m_posV.y = m_posR.z + m_fDistance* cosf(m_f��);
		m_posV.z = m_posR.y + m_fDistance* sinf(m_f��) * sinf(m_f��);

		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
//�J�����N���X�̏I������
//=============================================================================
void CCamera::Uninit(void)
{
	m_nCameraAll = 0;
}

//=============================================================================
//�J�����N���X�̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	static bool bPlayerWin = false;
	static int nWinPlayer = 0;

	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	D3DXVECTOR3 pPlayerPos[MAX_PLAYER];

	if (pKeyInput->GetTrigger(DIK_P))
	{
		bPlayerWin = TRUE;
	}

	if (CGame::GetPlayer(m_nCameraNum) != NULL)
	{

		pPlayerPos[m_nCameraNum] = CGame::GetPlayer(m_nCameraNum)->GetPos();

		int nCameraSecond = 0;

		if (m_nCameraNum == 0)
		{

			nCameraSecond = 1;
		}
		else
		{

			nCameraSecond = 0;
		}


		pPlayerPos[nCameraSecond] = CGame::GetPlayer(nCameraSecond)->GetPos();

		if (bPlayerWin)
		{
			nWinPlayer = 0;
			EndUpdate(pPlayerPos, nWinPlayer);
		}
		else
		{
			NomalUpdate(pPlayerPos);
		}
	}
}


//=============================================================================
//�J�����N���X�̎�����X�V����
//=============================================================================
void CCamera::EndUpdate(D3DXVECTOR3 PlayerPos[], int nWinPlayer)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();


	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nCameraNum);


	//�����J��������
	if (nWinPlayer == m_nCameraNum)
	{
		//��]�J�n�ʒu�w��
		static float f�� = WIN_START_ROT_VERTICAL;
		static float f�� = WIN_START_ROT_HORIZONTAL;
		static float fDistance = WIN_START_DISTANCE;


		//�ω���
		f�� += (WIN_END_ROT_VERTICAL - WIN_START_ROT_VERTICAL) / 100.0f * WIN_ROT_MOVE_SUBTRACTION;
		f�� += (WIN_END_ROT_HORIZONTAL - WIN_START_ROT_HORIZONTAL) / 100.0f * WIN_ROT_MOVE_SUBTRACTION;

		m_posVDest.x = PlayerPos[m_nCameraNum].x + fDistance * sinf(f��) * cosf(f��);

		m_posVDest.y = PlayerPos[m_nCameraNum].y + fDistance * cosf(f��);

		if (m_posVDest.y <= 2)
		{
			m_posVDest.y = 2;
		}


		fDistance -= (WIN_START_DISTANCE - WIN_END_DISTANCE) / 100.0f * WIN_ROT_MOVE_SUBTRACTION;

		if (fDistance <= WIN_END_DISTANCE)
		{
			
			fDistance = WIN_END_DISTANCE;
		}


		if (f�� >= WIN_END_ROT_VERTICAL)
		{
			
			f�� = WIN_END_ROT_VERTICAL;
		}


		if (f�� >= WIN_END_ROT_HORIZONTAL)
		{
			f�� = WIN_END_ROT_HORIZONTAL;
		}

		m_posVDest.z = PlayerPos[m_nCameraNum].z + fDistance * sinf(f��) * sinf(f��);

		m_posRDest = D3DXVECTOR3(PlayerPos[m_nCameraNum].x, PlayerPos[m_nCameraNum].y + PLAYER_HEIGHT, PlayerPos[m_nCameraNum].z);


		m_posV += (m_posVDest - m_posV); //�J�����t���[
		m_posR += (m_posRDest - m_posR); //�J�����t���[
	}
	else
	{
		static float f�� = WIN_START_ROT_VERTICAL;

	
		static float fDistance = LOSE_START_DISTANCE;

		fDistance++;

	
		if (fDistance >= LOSE_END_DISTANCE)
		{
			fDistance = LOSE_END_DISTANCE;
		}

		m_posVDest.x = PlayerPos[m_nCameraNum].x + fDistance * sinf(m_f��) * cosf(f��);

		m_posVDest.y = PlayerPos[m_nCameraNum].y + fDistance * cosf(m_f��);

		if (m_posVDest.y <= 2)
		{
			m_posVDest.y = 2;
		}

		m_posVDest.z = PlayerPos[m_nCameraNum].z + fDistance * sinf(m_f��) * sinf(f��);

		m_posRDest = D3DXVECTOR3(PlayerPos[m_nCameraNum].x, PlayerPos[m_nCameraNum].y + PLAYER_HEIGHT, PlayerPos[m_nCameraNum].z);

		m_posV += (m_posVDest - m_posV); //�J�����t���[
		m_posR += (m_posRDest - m_posR); //�J�����t���[
	}
}

//=============================================================================
//�J�����N���X�̎����O�X�V����
//=============================================================================
void CCamera::NomalUpdate(D3DXVECTOR3 PlayerPos[])
{
	CLockon *pLockon = CGame::GetLockon();
	int nCameraSecond = 0;

	if (m_nCameraNum == 0)
	{
		nCameraSecond = 1;
	}
	else
	{
		nCameraSecond = 0;
	}

	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nCameraNum);

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R3, m_nCameraNum) || pKeyInput->GetTrigger(DIK_TAB))
	{
		if (m_bTarget == false)
		{
			m_f�� = D3DXToRadian(75.0f);
			m_bTarget = true;
		}
		else
		{
		
			m_bTarget = false;
		}
	}

			
	if (m_bTarget == true)
	{
		m_f�� = atan2f(PlayerPos[m_nCameraNum].z - PlayerPos[nCameraSecond].z, PlayerPos[m_nCameraNum].x - PlayerPos[nCameraSecond].x);


		m_posVDest.x = m_posR.x + m_fDistance * sinf(m_f��) * cosf(m_f��) + PlayerPos[m_nCameraNum].x - PlayerPos[nCameraSecond].x;
		m_posVDest.y = m_posR.y + m_fDistance * cosf(m_f��) + PlayerPos[m_nCameraNum].y - PlayerPos[nCameraSecond].y;
		m_posVDest.z = m_posR.z + m_fDistance * sinf(m_f��) * sinf(m_f��) + PlayerPos[m_nCameraNum].z - PlayerPos[nCameraSecond].z;


		if (m_nCameraNum == 0)
		{
			pLockon->Create(D3DXVECTOR3(UI_LOCKON_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_X, UI_LOCKON_SIZE_Y, 0.0f), CLockon::LOCKONTYPE_FAST_PLAYER);
		}

		if (m_nCameraNum == 1)
		{
			pLockon->Create(D3DXVECTOR3(UI_LOCKON_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_X, UI_LOCKON_SIZE_Y, 0.0f), CLockon::LOCKONTYPE_SECOND_PLAYER);
		}
		if (PlayerPos[nCameraSecond].x <= PlayerPos[m_nCameraNum].x + 10 && PlayerPos[m_nCameraNum].x - 10 <= PlayerPos[nCameraSecond].x  &&
			PlayerPos[nCameraSecond].z <= PlayerPos[m_nCameraNum].z + 10 && PlayerPos[m_nCameraNum].z - 10 <= PlayerPos[nCameraSecond].z)
		{
			m_bTarget = false;
		}

		m_posRDest = D3DXVECTOR3(PlayerPos[nCameraSecond].x, PlayerPos[nCameraSecond].y + PLAYER_HEIGHT, PlayerPos[nCameraSecond].z);

		m_posV += (m_posVDest - m_posV); //�J�����t���[
		m_posR += (m_posRDest - m_posR); //�J�����t���[
	}
	else
	{
		// �L�[�{�[�h�X�V
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		//���_�i�J�������W�j�̍�����
		if (pKeyInput->GetPress(DIK_LEFT))
		{
			m_f�� += D3DXToRadian(1.0f);
		}
		//���_�i�J�������W�j�̉E����
		if (pKeyInput->GetPress(DIK_RIGHT))
		{
			m_f�� -= D3DXToRadian(1.0f);
		}
		//���_�i�J�������W�j�̏����
		if (pKeyInput->GetPress(DIK_UP) && m_f�� >= D3DXToRadian(10.0f))
		{
			m_f�� -= D3DXToRadian(1.0f);
		}
		//���_�i�J�������W�j�̉�����
		if (pKeyInput->GetPress(DIK_DOWN) && m_f�� <= D3DXToRadian(170.0f))
		{
			m_f�� += D3DXToRadian(1.0f);
		}

		m_posVDest.x = PlayerPos[m_nCameraNum].x + m_fDistance * sinf(m_f��) * cosf(m_f��);

		m_posVDest.y = PlayerPos[m_nCameraNum].y + m_fDistance * cosf(m_f��);

		if (m_posVDest.y <= 2)
		{
			m_posVDest.y = 2;
		}

		m_posVDest.z = PlayerPos[m_nCameraNum].z + m_fDistance * sinf(m_f��) * sinf(m_f��);

		m_posRDest = D3DXVECTOR3(PlayerPos[m_nCameraNum].x, PlayerPos[m_nCameraNum].y + PLAYER_HEIGHT, PlayerPos[m_nCameraNum].z);

		m_posV += (m_posVDest - m_posV);
		m_posR += (m_posRDest - m_posR);

	}
}

//=============================================================================
//�J�����N���X�̃Z�b�g����
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT / 2,
		10.0f,
		100000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

D3DXVECTOR3 CCamera::GetposV(void)
{
	return m_posV;
}

D3DXVECTOR3 CCamera::GetposR(void)
{
	return m_posR;
}

D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}

bool CCamera::GetTargetBool(void)
{
	return m_bTarget;
}

float CCamera::Get��(void)
{
	return m_f��;
}

float CCamera::Get��(void)
{
	return m_f��;
}