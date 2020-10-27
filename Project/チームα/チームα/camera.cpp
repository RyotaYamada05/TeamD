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

//=============================================================================
//�}�N����`
//=============================================================================
#define DISTANCE (1000.0f)			//���_�`�����_�̋���
int CCamera::m_nCountAll = 0;		// �J�����̐�

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
	m_nNum = m_nCountAll++;						// �J�����̔ԍ�
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

	// �r���[�|�[�g�̐ݒ�
	//D3DVIEWPORT9 view_port[2];

	switch (m_nNum)
	{
	case 0:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_rot.y = 0.0f;
		m_posV = D3DXVECTOR3(0.0f, 300.0f, m_fDistance);	//�ʒuz��m_fDistance��-�����֐ݒ肷��
		m_posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//�����_�͑S��0���W������
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		m_fDistance = sqrtf(
			powf((m_posV.x - m_posR.x), 2) +
			powf((m_posV.z - m_posR.z), 2));


		//// �r���[�|�[�g�̍�����W
		//view_port[0].X = 0;
		//view_port[0].Y = 0;

		//// �r���[�|�[�g�̕�
		//view_port[0].Width = SCREEN_WIDTH / 2;

		//// �r���[�|�[�g�̍���
		//view_port[0].Height = SCREEN_HEIGHT;

		//// �r���[�|�[�g�[�x�ݒ�
		//view_port[0].MinZ = 0.0f;
		//view_port[0].MaxZ = 1.0f;

		//// �r���[�|�[�g�ݒ�
		//if (FAILED(pDevice->SetViewport(&view_port[0])))
		//{
		//	return false;
		//}

		break;

	case 1:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_rot.y = 0.0f;
		m_posV = D3DXVECTOR3(0.0f, 300.0f, -m_fDistance);	// �ʒuz��m_fDistance��-�����֐ݒ肷��
		m_posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);			// �����_�͑S��0���W������
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		m_fDistance = sqrtf(
			powf((m_posV.x - m_posR.x), 2) +
			powf((m_posV.z - m_posR.z), 2));


		//// �r���[�|�[�g�̍�����W
		//view_port[1].X = SCREEN_WIDTH / 2;
		//view_port[1].Y = 0;

		//// �r���[�|�[�g�̕�
		//view_port[1].Width = SCREEN_WIDTH;

		//// �r���[�|�[�g�̍���
		//view_port[1].Height = SCREEN_HEIGHT;

		//// �r���[�|�[�g�[�x�ݒ�
		//view_port[1].MinZ = 0.0f;
		//view_port[1].MaxZ = 1.0f;

		//// �r���[�|�[�g�ݒ�
		//if (FAILED(pDevice->SetViewport(&view_port[1])))
		//{
		//	return false;
		//}

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
	m_nCountAll = 0;
}

//=============================================================================
//�J�����N���X�̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pInput = CManager::GetKeyboard();

	//�����_�̍�����
	if (pInput->GetPress(DIK_Q))
	{
		m_rot.y += 5.0f;
		m_posR.x = m_posV.x + sinf(D3DXToRadian(m_rot.y))*m_fDistance;
		m_posR.z = m_posV.z + cosf(D3DXToRadian(m_rot.y))*m_fDistance;
	}
	//�����_�̉E����
	if (pInput->GetPress(DIK_E))
	{
		m_rot.y -= 5.0f;
		m_posR.x = m_posV.x + sinf(D3DXToRadian(m_rot.y))*m_fDistance;
		m_posR.z = m_posV.z + cosf(D3DXToRadian(m_rot.y))*m_fDistance;
	}


	//���_�i�J�������W�j�̍�����
	if (pInput->GetPress(DIK_RIGHT))
	{
		m_rot.y -= 5;
		m_posV.x = m_posR.x - sinf(D3DXToRadian(m_rot.y)) * m_fDistance;
		m_posV.z = m_posR.z - cosf(D3DXToRadian(m_rot.y)) * m_fDistance;
	}
	//���_�i�J�������W�j�̉E����
	if (pInput->GetPress(DIK_LEFT))
	{
		m_rot.y += 5;
		m_posV.x = m_posR.x - sinf(D3DXToRadian(m_rot.y)) * m_fDistance;
		m_posV.z = m_posR.z - cosf(D3DXToRadian(m_rot.y)) * m_fDistance;
	}

	// �L�����ړ����̃J�����̈ʒu
	//m_posV += (m_posVDest - m_posV) * 0.001f;

	// �L�����ړ����̃J�����̌���
	//m_posR += (m_posRDest - m_posR) * 0.1f;

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
