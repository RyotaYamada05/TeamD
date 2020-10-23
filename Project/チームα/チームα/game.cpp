//=======================================================================================
//
// �Q�[������ [bg.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "board.h"
#include "model.h"
#include "manager.h"
#include "conection.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_apCamera[MAX_CAMERA] = {};			// �J�����N���X�̃|�C���^�ϐ�
CLight *CGame::m_pLight = NULL;						// ���C�g�N���X�̃|�C���^�ϐ�
CMeshField *CGame::m_pMeshField = NULL;				// ���b�V���t�B�[���h
CBg *CGame::m_pBg = NULL;							// �w�i�̃|�C���^
CPlayer *CGame::m_apPlayer[MAX_PLAYER] = {};		// �v���C���[�̃|�C���^

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�J�����N���X�̃C���X�^���X����
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		m_apCamera[nCount] = CCamera::Create();

		if (m_apCamera[nCount] != NULL)
		{
			// �J�����̏�����
			if (FAILED(m_apCamera[nCount]->Init()))
			{
				return -1;
			}
		}
	}

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �v���C���[�̐���
	if (m_apPlayer[0] == NULL)
	{
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	if (m_apPlayer[1] == NULL)
	{
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	// �w�i
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//�J�����N���X�̏I�������Ăяo��
			m_apCamera[nCount]->Uninit();
		}
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
	}

	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
	}

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̕`��
		m_apPlayer[nCount] = NULL;
	}

	CManager::GetConection()->Uninit();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//�J�����N���X�̍X�V����
			m_apCamera[nCount]->Update();
		}
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Update();
	}

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̍X�V
		m_apPlayer[0]->Update();

		// �v���C���[�̍X�V
		m_apPlayer[1]->Update();
	}


	CManager::GetConection()->Update();

}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			m_apCamera[nCount]->SetCamera();
		}
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Draw();
	}

	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̕`��
		m_apPlayer[nCount]->Draw();
	}
}

//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera * CGame::GetCamera(int nCount)
{
	return m_apCamera[nCount];
}

//=======================================================================================
// ���C�g�̏��
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// �v���C���[�̏��
//=======================================================================================
CPlayer * CGame::GetPlayer(int nCount)
{
	return m_apPlayer[nCount];
}