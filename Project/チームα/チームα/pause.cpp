//=============================================================================
//
//  [Pause.cpp]
// Author : ���� �D�I
//
//=============================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "pause.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "joypad.h"
#include "scene.h"
#include "uipause.h"
#include "sound.h"

//=======================================================================================
//�ÓI�����o�ϐ��錾
//=======================================================================================
LPDIRECT3DTEXTURE9 CPause::m_pTexture[1] = {};
CUiPause *CPause::m_apPauselogo[MAX_PAUSE] = {};

//=======================================================================================
// �^�C�g���N���X�̃R���X�g���N�^
//=======================================================================================
CPause::CPause(int nPriority) : CScene(nPriority)
{
	m_pScene = NULL;
	m_SelectPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=======================================================================================
// �^�C�g���N���X�̃f�X�g���N�^
//=======================================================================================
CPause::~CPause()
{

}

//=======================================================================================
// �^�C�g���N���X�̃N���G�C�g����
//=======================================================================================
CPause* CPause::Create(void)
{
	CPause* pPause = new CPause();

	pPause->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	
	return pPause;
}

//=======================================================================================
// �^�C�g���N���X�̃e�N�X�`���ǂݍ��ݏ���
//=======================================================================================
HRESULT CPause::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/pause001.png", 
		&m_pTexture[0]);

	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏���������
//=======================================================================================
HRESULT CPause::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene == NULL)
	{
		m_pScene = CScene2d::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		//�e�N�X�`���̐ݒ�
		m_pScene->BindTexture(m_pTexture[0]);
	}

	if (m_apPauselogo[0] == NULL)
	{
		m_apPauselogo[0] = CUiPause::Create(D3DXVECTOR3(UIPAUSE_START_POS_X, UIPAUSE_START_POS_Y, 0.0f), D3DXVECTOR3(UIPAUSE_SIZE_X, UIPAUSE_SIZE_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CUiPause::UIPAUSETYPE_START);
	}

	if (m_apPauselogo[1] == NULL)
	{
		m_apPauselogo[1] = CUiPause::Create(D3DXVECTOR3(UIPAUSE_TITLE_POS_X, UIPAUSE_TITLE_POS_Y, 0.0f), D3DXVECTOR3(UIPAUSE_SIZE_X, UIPAUSE_SIZE_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), CUiPause::UIPAUSETYPE_TITLE);
	}

	m_SelectPos = D3DXVECTOR3(UIPAUSE_START_POS_X, UIPAUSE_START_POS_Y, 0.0f);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CScene::OBJTYPE_PAUSE);

	//�t���O��true�ɂ���
	SetPause(true);
	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏I������
//=======================================================================================
void CPause::Uninit(void)
{
	if (m_pScene != NULL)
	{
		if (m_pScene != NULL)
		{
			m_pScene->Uninit();
			m_pScene = NULL;
		}
	}

	for (int nCount = 0; nCount < MAX_PAUSE; nCount++)
	{
		if (m_apPauselogo[nCount] != NULL)
		{
			m_apPauselogo[nCount]->Uninit();
			m_apPauselogo[nCount] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=======================================================================================
// �^�C�g���N���X�̍X�V����
//=======================================================================================
void CPause::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	Select();
}

//=======================================================================================
// �^�C�g���N���X�̕`�揈��
//=======================================================================================
void CPause::Draw(void)
{

}

//=======================================================================================
// �I������
//=======================================================================================
void CPause::Select(void)
{
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	//���͂����݂���
	if (js.lX != 0.0f || js.lY != 0.0f)
	{
		if (js.lY < -5)
		{
			m_SelectPos = D3DXVECTOR3(UIPAUSE_START_POS_X, UIPAUSE_START_POS_Y, 0.0f);
		}

		if (js.lY > 5)
		{
			m_SelectPos = D3DXVECTOR3(UIPAUSE_TITLE_POS_X, UIPAUSE_TITLE_POS_Y, 0.0f);
		}
	}

	if (m_SelectPos.y == UIPAUSE_START_POS_Y)
	{
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0))
		{
			SetPause(false);
			Uninit();
			return;
		}
	}

	if (m_SelectPos.y == UIPAUSE_TITLE_POS_Y)
	{
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0))
		{
			SetPause(false);
			CFade *pFade = CManager::GetFade();
			pFade->SetFade(CManager::MODE_TYPE_TITLE);
			Uninit();
			return;
		}
	}
}