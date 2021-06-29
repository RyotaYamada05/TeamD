//=======================================================================================
//
//  [tutorial.cpp]
// Author : �����D�I
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "tutorial.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"

//=======================================================================================
//�ÓI�����o�ϐ��錾
//=======================================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[1] = {};

//=======================================================================================
// �^�C�g���N���X�̃R���X�g���N�^
//=======================================================================================
CTutorial::CTutorial(int nPriority) : CScene(nPriority)
{
	m_pScene = NULL;
}
//=======================================================================================
// �^�C�g���N���X�̃f�X�g���N�^
//=======================================================================================
CTutorial::~CTutorial()
{

}

//=======================================================================================
// �^�C�g���N���X�̃N���G�C�g����
//=======================================================================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial();

	pTutorial->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	return pTutorial;
}

//=======================================================================================
// �^�C�g���N���X�̃e�N�X�`���ǂݍ��ݏ���
//=======================================================================================
HRESULT CTutorial::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/tutorial.png", &m_pTexture[0]);
	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏���������
//=======================================================================================
HRESULT CTutorial::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene == NULL)
	{
		m_pScene = CScene2d::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		//�e�N�X�`���̐ݒ�
		m_pScene->BindTexture(m_pTexture[0]);
	}
	
	CSound *pSound = CManager::GetSound();
	//pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏I������
//=======================================================================================
void CTutorial::Uninit(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}


	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=======================================================================================
// �^�C�g���N���X�̍X�V����
//=======================================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �R���g���[����start���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	//�G���^�[�L�[���������Ƃ�
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

}

//=======================================================================================
// �^�C�g���N���X�̕`�揈��
//=======================================================================================
void CTutorial::Draw(void)
{

}
