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
#include "shape.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "gauge.h"
#include "life.h"
#include "ui.h"

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_apCamera[MAX_PLAYER] = {};			// �J�����N���X�̃|�C���^�ϐ�
CLight *CGame::m_pLight = NULL;						// ���C�g�N���X�̃|�C���^�ϐ�
CMeshField *CGame::m_pMeshField = NULL;				// ���b�V���t�B�[���h
CMeshShape *CGame::m_pSphere = NULL;				// ���b�V���X�t�B�A
CBg *CGame::m_pBg = NULL;							// �w�i�̃|�C���^
CPlayer *CGame::m_apPlayer[MAX_PLAYER] = {};			// �v���C���[�̃|�C���^

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

	//Ui�̃��[�h
	CUi::Load();
	//UI���C�t�Q�[�W�̐���
	CUi::Create(D3DXVECTOR3(330.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);
	CUi::Create(D3DXVECTOR3(1060.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);

	CUi::Create(D3DXVECTOR3(330.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);
	CUi::Create(D3DXVECTOR3(1060.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);

	//UI�̃^�C������
	CUi::Create(D3DXVECTOR3(640.0f, 50.0f, 0.0f), D3DXVECTOR3(UI_TIME_SIZE_X, UI_TIME_SIZE_Y, 0.0f), CUi::UITYPE_TIME);

	//UI�̃v���C���[�E�G�l�~�[�����̐���
	CUi::Create(D3DXVECTOR3(70.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
	CUi::Create(D3DXVECTOR3(75.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

	CUi::Create(D3DXVECTOR3(800.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
	CUi::Create(D3DXVECTOR3(805.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

	// �v���C���[�̐���
	if (m_apPlayer[0] == NULL)
	{
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f));
	}
	if (m_apPlayer[1] == NULL)
	{
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 500.0f), D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	CMeshShape::Load();
	// ���b�V���X�t�B�A
	if (m_pSphere == NULL)
	{
		m_pSphere = CMeshShape::Create();
	}

	// �w�i
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	//�^�C������
	CTime::Create(D3DXVECTOR3(585.0f, 55.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


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
	//ui
	CUi::Unload();

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
	}

	CMeshShape::UnLoad();
	// ���b�V���X�t�B�A
	if (m_pSphere != NULL)
	{
		m_pSphere->Uninit();
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

	// ���b�V���X�t�B�A
	if (m_pSphere != NULL)
	{
		m_pSphere->Update();
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

	// ���b�V���X�t�B�A
	if (m_pSphere != NULL)
	{
		m_pSphere->Draw();
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

CMeshShape * CGame::GetSphere()
{
	return m_pSphere;
}
