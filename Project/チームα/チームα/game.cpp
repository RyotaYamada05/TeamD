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

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_pCamera = NULL;			// �J�����N���X�̃|�C���^�ϐ�
CLight *CGame::m_pLight = NULL;				// ���C�g�N���X�̃|�C���^�ϐ�
CMeshField *CGame::m_pMeshField = NULL;		// ���b�V���t�B�[���h

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
	m_pDarts = NULL;
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
	CGame* pGame = new CGame();

	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�J�����N���X�̃C���X�^���X����
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		if (FAILED(m_pCamera->Init()))
		{
			return -1;
		}
	}

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �v���C���[
	CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���b�V���t�B�[���h
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return S_OK;
}

//=======================================================================================
// 
//=======================================================================================
void CGame::Uninit(void)
{
	
	if (m_pCamera != NULL)
	{
		//�J�����N���X�̏I�������Ăяo��
		m_pCamera->Uninit();

		//�������̔j��
		delete m_pCamera;

		//�������̃N���A
		m_pCamera = NULL;
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
	}

	CManager::GetConection()->Uninit();
}

//=======================================================================================
// 
//=======================================================================================
void CGame::Update(void)
{
	
	if (m_pCamera != NULL)
	{
		//�J�����N���X�̍X�V����
		m_pCamera->Update();
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Update();
	}

	CManager::GetConection()->Update();

}

//=======================================================================================
// 
//=======================================================================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Draw();
	}

	//RECT rect = { 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
	//char str[256];

	////D3DXVECTOR3 pos = CManager::GetConection()->GetPos();
	//int nScore = CManager::GetConection()->GetScore();

	//wsprintf(str, "SCORE : %d\n", nScore);

	//// �e�L�X�g�`��
	//m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

CLight * CGame::GetLight(void)
{
	return m_pLight;
}
