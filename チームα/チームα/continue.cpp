//=============================================================================
//
// �R���e�B�j���[���� [continue.cpp]
// Author : �����D�I
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "continue.h"
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "ui.h"
#include "keyboard.h"
#include "sound.h"
#include "joypad.h"
#include "uiend.h"
#include "fade.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CUi *CContinue::m_pUi = NULL;							// ui�̃|�C���^

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CContinue *CContinue::Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CContinue *pContinue = new CContinue;

	pContinue->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pContinue;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CContinue::CContinue(int nPriority) : CScene(nPriority)
{
	memset(m_apContinue, 0, sizeof(m_apContinue));
	m_pUiEnd = NULL;
	m_bEnd = false;
	m_bTimeUp = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinue::~CContinue()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CContinue::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_nContinueCount = 0;

	m_nContinue = CONTINUE_LIMIT;

	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		if (m_apContinue[nCount] == NULL)
		{
			m_apContinue[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount*CONTINUE_INTERVAL, pos.y, 0.0f), D3DXVECTOR3(CONTINUE_SIZE_X, CONTINUE_SIZE_Y, 0.0f), CNumber::NUMBERTYPE_CONTINUE);
		}
	}

	if (m_pUiEnd == NULL)
	{
		m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, UI_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_CONTINUE_SIZE_X, UI_CONTINUE_SIZE_Y, 0.0f), CUiEnd::UIENDTYPE_CONTINUE);
	}

	AddTime(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CContinue::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		if (m_apContinue[nCount] != NULL)
		{
			m_apContinue[nCount]->Uninit();
			m_apContinue[nCount] = NULL;
		}
	}

	// �����[�X
	SetDeathFlag();
}

//=============================================================================
// �X�V����
//=============================================================================
void CContinue::Update(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetSound();

	if (m_bTimeUp == false)
	{

		m_nContinueCount++;
		if (m_nContinueCount % 60 == 0)
		{
			if (m_nContinue > 0)
			{
				AddTime(1);
			}
			else
			{
				if (m_pUiEnd != NULL)
				{
					m_pUiEnd->Uninit();
					m_pUiEnd = NULL;
				}

				CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, 500.0f, 0.0f), D3DXVECTOR3(400, 40, 0.0f), CUiEnd::UIENDTYPE_THANKS);
				m_bTimeUp = true;
				// �I������
				m_bEnd = true;
				return;
			}
		}

		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
			|| pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
		{
			m_bEnd = true;

			if (m_pUiEnd != NULL)
			{
				m_pUiEnd->Uninit();
				m_pUiEnd = NULL;
			}

			CFade *pFade = CManager::GetFade();
			pFade->SetFade(CManager::MODE_TYPE_GAME);
			pSound->Play(CSound::SOUND_LABEL_SE_START);
			return;
		}

		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && mode == CFade::FADE_MODE_NONE
			|| pKeyboard->GetTrigger(DIK_A) && mode == CFade::FADE_MODE_NONE)
		{
			if (m_nContinue > 0)
			{
				AddTime(1);
			}
			else
			{
				if (m_pUiEnd != NULL)
				{
					m_pUiEnd->Uninit();
					m_pUiEnd = NULL;
				}

				CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, 500.0f, 0.0f), D3DXVECTOR3(400, 40, 0.0f), CUiEnd::UIENDTYPE_THANKS);
				m_bTimeUp = true;
				// �I������
				m_bEnd = true;
				return;
			}
		}
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		m_bEnd = true;

		if (m_pUiEnd != NULL)
		{
			m_pUiEnd->Uninit();
			m_pUiEnd = NULL;
		}

		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
		pSound->Play(CSound::SOUND_LABEL_SE_START);
		return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CContinue::Draw(void)
{
	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		if (m_apContinue[nCount] != NULL)
		{
			m_apContinue[nCount]->Draw();
		}
	}
}

//=============================================================================
// �X�R�A���Z
//=============================================================================
void CContinue::AddTime(int nValue)
{
	if (m_bTimeUp == false)
	{
		m_nContinue -= nValue;

		for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
		{
			if (m_apContinue[nCount] != NULL)
			{
				m_apContinue[nCount]->SetNumber(m_nContinue % (int)powf(10, MAX_CONTINUE - nCount) / powf(10, MAX_CONTINUE - nCount - 1));
			}
		}
	}
}

//=============================================================================
// �I�����
//=============================================================================
bool CContinue::GetEnd(void)
{
	return m_bEnd;
}