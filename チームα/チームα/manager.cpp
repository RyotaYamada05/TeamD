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
#include "model.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "life.h"
#include "ui.h"
#include "charge.h"
#include "2d_explosion.h"
#include "beam.h"
#include "effect.h"
#include "particle.h"
#include "shock.h"
#include "bomb.h"
#include "lockon.h"
#include "explosion.h"
#include "smoke.h"
#include "sand.h"
#include "number.h"
#include "bill.h"
#include "uistart.h"
#include "titlelogo.h"
#include "uiend.h"
#include "sound.h"
#include "tutorial.h"
#include "splash.h"
#include "laser.h"
#include "missile.h"
#include "fire.h"
#include "sea.h"
#include "boost.h"
#include "pause.h"
#include "uipause.h"
#include "locus.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = NULL;	//�����_���[�N���X�̃|�C���^�ϐ�
CInputKeyboard *CManager::m_pInput = NULL	;//���͏����N���X�̃|�C���^�ϐ�
CConection *CManager::m_pConection = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;
CSound *CManager::m_pSound = NULL;			//�T�E���h�N���X�̃|�C���^
CScene *CManager::m_pScene = NULL;
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

	//�T�E���h�̃C���X�^���X����
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	//�^�C�g���N���X�̃N���G�C�g
	//m_pTitle = CTitle::Create();

	//�t�F�[�h�N���X�̃N���G�C�g
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
		//�t�F�[�h�N���X�̏I�������Ăяo��
		m_pFade->Uninit();

		//�������̔j��
		delete m_pFade;

		//�������̃N���A
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
		//�t�F�[�h�N���X�̍X�V�����Ăяo��
		m_pFade->Update();
	}

	/*switch (m_mode)
	{
	case MODE_TYPE_GAME:
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0))
		{
			m_pScene->GetPause(false);
		}

		else if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0))
		{
			m_pScene->GetPause(true);
		}
		break;
	}*/
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
	CTitle::Load();
	CResult::Load();
	CMeshField::Load();
	CBg::Load();	
	CLife::Load();
	CUi::Load();
	CCharge::Load();
	CLife::Load();
	C2dExplosion::Load();
	CBeam::Load();
	CEffect::Load();
	CParticle::Load();
	CShock::Load();
	CBomb::Load();
	CLockon::Load();
	CNumber::Load();
	CBill::LoadModel();
	CUiStart::Load();
	CTitlelogo::Load();
	CExplosion::Load();
	CSmoke::Load();
	CSand::Load();
	CUiEnd::Load();
	CTutorial::Load();
	CBill::LoadModel();
	CSplash::Load();
	CLaser::Load();
	CLocus::Load();
	CFire::Load();
	CBoost::Load();
	CSea::Load();
	CPause::Load();
	CUiPause::Load();
}

//=============================================================================
//�e�N�X�`���̑S�A�����[�h����
//=============================================================================
void CManager::UnLoadAll(void)
{
	CMeshField::UnLoad();
	CBg::UnLoad();
	CLife::Unload();
	CUi::Unload();
	CCharge::Unload();	
	C2dExplosion::UnLoad();
	CBeam::UnLoad();
	CEffect::UnLoad();
	CParticle::UnLoad();
	CShock::UnLoad();
	CBomb::UnLoad();
	CLockon::Unload();
	CBill::Unload();
	CUiStart::Unload();
	CTitlelogo::Unload();
	CExplosion::UnLoad();
	CSmoke::UnLoad();
	CSand::UnLoad();
	CSplash::UnLoad();
	CLaser::UnLoad();

	CFire::UnLoad();
	CBoost::UnLoad();
	CUiPause::UnLoad();
	CLockon::Unload();
	CNumber::Unload();
	CUiEnd::Unload();
	CSea::UnLoad();
	CLocus::UnLoad();
}

//=============================================================================
//�Q�[�����[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	CSound *pSound = CManager::GetSound();

	//���݃��[�h�̏I��
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			m_pTitle = NULL;
		}
		break;

	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = NULL;
		}
		break;

	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
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

	CScene::ReleaseAll();

	//���[�h��ݒ�
	m_mode = mode;

	//�ݒ肳�ꂽ���[�h���N���G�C�g
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		
		break;

	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
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

//=============================================================================
//�t�F�[�h���擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//�W���C�p�b�h���擾
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}

//=============================================================================
//�W���C�p�b�h���擾
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}
