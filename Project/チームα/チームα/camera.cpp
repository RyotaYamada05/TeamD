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

//=============================================================================
//�}�N����`
//=============================================================================
#define DISTANCE (1000.0f)			//���_�`�����_�̋���

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
	m_bTarget = true; //�^�[�Q�b�g�g�p
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
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����_�͑S��0���W������
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//������x�N�g��
		m_posV.x = m_posR.x + m_fDistance* sinf(m_f��) * cosf(m_f��);
		m_posV.y = m_posR.z + m_fDistance* cosf(m_f��);
		m_posV.z = m_posR.y + m_fDistance* sinf(m_f��) * sinf(m_f��);


		// �r���[�|�[�g�̐ݒ�
		//D3DVIEWPORT9 view_port[2];

		//if (m_nCameraNum <= 0)
		//{
		//	m_fMove = 5.0f;
		//	m_fDistance = DISTANCE;
		//	m_rot.y = 0.0f;
		//	m_posV = D3DXVECTOR3(0.0f, 0.0f, -m_fDistance);	//�ʒuz��m_fDistance��-�����֐ݒ肷��
		//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 20.0f);	//�����_�͑S��0���W������
		//	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


		//	m_fDistance = sqrtf(
		//		powf((m_posV.x - m_posR.x), 2) +
		//		powf((m_posV.z - m_posR.z), 2));
		//}
		//else
		//{
		//	m_fMove = 5.0f;
		//	m_fDistance = DISTANCE;
		//	m_rot.y = 0.0f;
		//	m_posV = D3DXVECTOR3(0.0f, 100.0f, -m_fDistance);	//�ʒuz��m_fDistance��-�����֐ݒ肷��
		//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 20.0f);	//�����_�͑S��0���W������
		//	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


		//	m_fDistance = sqrtf(
		//		powf((m_posV.x - m_posR.x), 2) +
		//		powf((m_posV.z - m_posR.z), 2));
		//}


		//m_fDistance = sqrtf(
		//	powf((m_posV.x - m_posR.x), 2) +
		//	powf((m_posV.z - m_posR.z), 2));


		break;

	case 1:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_f�� = D3DXToRadian(75.0f);
		m_f�� = D3DXToRadian(0.0f);
		m_rot.y = 0.0f;
		m_posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);			// �����_�͑S��0���W������
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

	if (CGame::GetPlayer(m_nCameraNum) != NULL)
	{

		D3DXVECTOR3 pPlayerPos1 = CGame::GetPlayer(m_nCameraNum)->GetPos();
		int nCamera2p = 0;

		if (m_nCameraNum == 0)
		{
			nCamera2p = 1;
		}
		else
		{
			nCamera2p = 0;
		}

	
		D3DXVECTOR3 pPlayerPos2 = CGame::GetPlayer(nCamera2p)->GetPos();
		D3DXVECTOR3 pPlayerPos2rot;


		//�L�[�{�[�h�N���X���̎擾
		CInputKeyboard *pKeyInput = CManager::GetKeyboard();

		// �W���C�p�b�h�̎擾
		//DIJOYSTATE js = CInputJoypad::GetStick(m_nCameraNum);

		if (pKeyInput->GetTrigger(DIK_TAB))
		{
			if (m_bTarget == false)
			{
				m_f�� = D3DXToRadian(75.0f);
				m_f�� = D3DXToRadian(0.0f);
				m_bTarget = true;
			}
			else
			{
				pPlayerPos2rot = pPlayerPos2;
				m_posRRot = pPlayerPos1 - pPlayerPos2;
				m_posVRot = m_posV;
				m_bTarget = false;
			}
		}

		if (m_bTarget == true)
		{
			m_f�� = atan2f(pPlayerPos1.z - pPlayerPos2.z, pPlayerPos1.x - pPlayerPos2.x);

			m_posVDest.x = m_posR.x + m_fDistance * sinf(m_f��) * cosf(m_f��) + pPlayerPos1.x - pPlayerPos2.x;
			m_posVDest.y = m_posR.y + m_fDistance * cosf(m_f��) + pPlayerPos1.y - pPlayerPos2.y;
			m_posVDest.z = m_posR.z + m_fDistance * sinf(m_f��) * sinf(m_f��) + pPlayerPos1.z - pPlayerPos2.z;

			m_posRDest = D3DXVECTOR3(pPlayerPos2.x, pPlayerPos2.y, pPlayerPos2.z);

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

#ifdef CAMERA_TEST
			/*m_f�� = atan2f(m_posRRot.z , m_posRRot.x);*/

			m_posVDest.x = m_posR.x + m_fDistance * sinf(m_f��) * cosf(m_f��) + pPlayerPos1.x - pPlayerPos2.x;
			m_posVDest.y = m_posR.y + m_fDistance * cosf(m_f��);
			m_posVDest.z = m_posR.z + m_fDistance * sinf(m_f��) * sinf(m_f��) + pPlayerPos1.z - pPlayerPos2.z;

			m_posRDest.x = m_posR.x * sinf(m_f��) * cosf(m_f��) + pPlayerPos1.x;
			m_posRDest.y = m_posR.y * cosf(m_f��);
			m_posRDest.z = m_posR.z * sinf(m_f��) * sinf(m_f��) + pPlayerPos1.z;

			/*m_posRDest = D3DXVECTOR3(pPlayerPos2.x, pPlayerPos2.y, pPlayerPos2.z);*/

			m_posV += (m_posVDest - m_posV); //�J�����t���[
			m_posR += (m_posRDest - m_posR); //�J�����t���[

			////m_f�� = atan2f(m_posRRot.z, m_posRRot.x);

			//m_posVDest.x = m_posR.x + m_fDistance * sinf(m_f��) * cosf(m_f��) + pPlayerPos1.x - pPlayerPos2rot.x;
			//m_posVDest.y = m_posR.y + m_fDistance * cosf(m_f��);
			//m_posVDest.z = m_posR.z + m_fDistance * sinf(m_f��) * sinf(m_f��) + pPlayerPos1.z - pPlayerPos2rot.z;

			////m_posRDest.x = m_posR.x + m_fDistance * sinf(m_f��) * cosf(m_f��) + m_posRRot.x;
			////m_posRDest.y = m_posR.y + m_fDistance * cosf(m_f��);
			////m_posRDest.z = m_posR.z + m_fDistance * sinf(m_f��) * sinf(m_f��) + m_posRRot.z;

			//m_posRDest = D3DXVECTOR3(pPlayerPos2rot);

			//m_posV += (m_posVDest - m_posV);
			//m_posR += (m_posRDest - m_posR);

			//// �L�����ړ����̃J�����̈ʒu
			////m_posV += (m_posVDest - m_posV) * 0.001f;

			//// �L�����ړ����̃J�����̌���
			////m_posR += (m_posRDest - m_posR) * 0.1f;
#endif //CAMERA_TEST

			m_posVDest.x = m_posR.x + m_fDistance * sinf(m_f��) * cosf(m_f��);
			m_posVDest.y = m_posR.y + m_fDistance * cosf(m_f��);
			m_posVDest.z = m_posR.z + m_fDistance * sinf(m_f��) * sinf(m_f��);

			m_posRDest = D3DXVECTOR3(pPlayerPos1.x, pPlayerPos1.y + 10, pPlayerPos1.z);

			m_posV += (m_posVDest - m_posV);
			m_posR += (m_posRDest - m_posR);

		}
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
