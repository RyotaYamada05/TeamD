//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : 
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "scene3D.h"
#include "billboard.h"
#include "board.h"
#include "model.h"
#include "tcp_client.h"
#include "title.h"
#include "game.h"
#include "conection.h"
#include "result.h"
#include "fade.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "camera.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = NULL;	//�����_���[�N���X�̃|�C���^�ϐ�
CInputKeyboard *CManager::m_pInput = NULL	;//���͏����N���X�̃|�C���^�ϐ�
CConection *CManager::m_pConection = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[�N���X�̃C���X�^���X����
	m_pRenderer = new CRenderer;

	//���������m�ۂł�����
	if (m_pRenderer != NULL)
	{
		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pInput = new CInputKeyboard;

	//���������m�ۂł�����
	if (m_pInput != NULL)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}


	//���͏����N���X�̃C���X�^���X����
	m_pJoypad = new CInputJoypad;

	//���������m�ۂł�����
	if (m_pJoypad != NULL)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}


	m_pConection = new CConection;
	if (m_pConection != NULL)
	{
		if (FAILED(m_pConection->Init()))
		{
			m_pConection->Uninit();
			return -1;
		}
	}
	m_pTitle = CTitle::Create();
	m_pFade = CFade::Create();

	//�S�e�N�X�`���̓ǂݍ���
	LoadAll();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�e�N�X�`���̔j��
	UnLoadAll();
	
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;

		m_pFade = NULL;
	}

	if (m_pInput != NULL)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pInput->Uninit();

		//�������̍폜
		delete m_pInput;

		//�������̃N���A
		m_pInput = NULL;
	}

	if (m_pJoypad != NULL)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pJoypad->Uninit();

		//�������̍폜
		delete m_pInput;

		//�������̃N���A
		m_pJoypad = NULL;
	}

	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̏I�������Ăяo��
		m_pRenderer->Uninit();

		//�������̍폜
		delete m_pRenderer;

		//�������̃N���A
		m_pRenderer = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != NULL)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pInput->Update();
	}

	if (m_pJoypad != NULL)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pJoypad->Update();
	}


	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̍X�V�����Ăяo��
		m_pRenderer->Update();
	}

	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	if (m_mode == MODE_TYPE_TITLE && m_pInput->GetTrigger(DIK_RETURN))
	{
		m_pFade->SetFade(MODE_TYPE_GAME);
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Draw();
	}
}

//=============================================================================
//�e�N�X�`���̑S���[�h����
//=============================================================================
void CManager::LoadAll(void)
{
	CPlayer::LoadModel();
	CScene3D::Load();
	CBoard::Load();
	CTitle::Load();
	CResult::Load();
	CMeshField::Load();
	CBg::Load();
}

//=============================================================================
//�e�N�X�`���̑S�A�����[�h����
//=============================================================================
void CManager::UnLoadAll(void)
{
	CScene3D::UnLoad();
	CBoard::UnLoad();
	CPlayer::Unload();
	CMeshField::UnLoad();
	CBg::UnLoad();
}

void CManager::SetMode(MODE_TYPE mode)
{
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			m_pTitle = NULL;
		}
		break;

	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			m_pGame = NULL;
		}
		break;

	case MODE_TYPE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			m_pResult = NULL;
		}
		break;

	}
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		
		break;

	case MODE_TYPE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		
		break;

	case MODE_TYPE_RESULT:
		if (m_pGame == NULL)
		{
			m_pResult = CResult::Create();
		}
		

		break;
	default:
		break;
	}
}

//=============================================================================
//�Q�[�����[�h���̎擾
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//�����_���[���擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//�L�[�{�[�h���擾
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CConection *CManager::GetConection(void)
{
	return m_pConection;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}
