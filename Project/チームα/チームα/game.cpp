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

#include "time.h"
#include "gauge.h"
#include "life.h"
//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_apCamera[MAX_PLAYER] = {};			// �J�����N���X�̃|�C���^�ϐ�
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
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_apCamera[nCount] = CCamera::Create();
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
	//�^�C������
	CTime::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���C�t����
	//�P�o�̃��C�t�Q�[�W
	//CLife::Create(D3DXVECTOR3(300, 100.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(255, 140, 0, 255), CLife::LIFETYPE_FAST_PLAYER);
	//CLife::Create(D3DXVECTOR3(300, 200.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(60, 179, 113, 255), CLife::LIFETYPE_FAST_PLAYER);
	////�Q�o�̃��C�t�Q�[�W
	//CLife::Create(D3DXVECTOR3(800, 100.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(255, 140, 0, 255), CLife::LIFETYPE_SECOND_PLAYER);
	//CLife::Create(D3DXVECTOR3(800, 200.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(60, 179, 113, 255), CLife::LIFETYPE_SECOND_PLAYER);

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
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//�J�����N���X�̏I�������Ăяo��
			m_apCamera[nCount]->Uninit();

			//�������̔j��
			delete[] * m_apCamera;

			//�������̃N���A
			m_apCamera[nCount] = NULL;
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

	CManager::GetConection()->Uninit();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
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

	CManager::GetConection()->Update();
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
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