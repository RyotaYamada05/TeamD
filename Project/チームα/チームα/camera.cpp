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
#define DISTANCE (300.0f)	//���_�`�����_�̋���

//=============================================================================
//�J�����N���X�̃R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	//�e�����o�ϐ��̃N���A
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�J�����̍��W
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�J�����̍��W�i�ړI�n�j
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����_�i�ړI�n�j
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_fDistance = 0.0f;	//���_�`�����_�̋���
	m_fMove = 0.0f;	//�ړ���
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
	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_rot.y = 0.0f;
	m_posV = D3DXVECTOR3(0.0f, 150.0f, -m_fDistance);	//�ʒuz��m_fDistance��-�����֐ݒ肷��
	m_posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//�����_�͑S��0���W������
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fDistance = sqrtf(
		powf((m_posV.x - m_posR.x), 2) +
		powf((m_posV.z - m_posR.z), 2));

	return S_OK;
}

//=============================================================================
//�J�����N���X�̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
//�J�����N���X�̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�N���X���̎擾
	CInput *pInput = CManager::GetKeyboard();

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
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}
