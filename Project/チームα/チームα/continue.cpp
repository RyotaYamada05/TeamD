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
CContinue::CContinue()
{

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
	// �i���o�[�e�N�X�`�������[�h
	CNumber::Load();

	m_nContinueCount = 0;

	m_nContinue = CONTINUE_LIMIT;

	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		m_apContinue[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount*CONTINUE_INTERVAL, pos.y, 0.0f), D3DXVECTOR3(CONTINUE_SIZE_X, CONTINUE_SIZE_Y, 0.0f), CNumber::NUMBERTYPE_CONTINUE);
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

	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		m_pUi = NULL;
	}

	// �����[�X
	Release();

	// �i���o�[�e�N�X�`�����A�����[�h
	CNumber::Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CContinue::Update(void)
{

	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	CSound *pSound = CManager::GetSound();

	m_nContinueCount++;
	if (m_nContinueCount % 60 == 0)
	{
		if (m_nContinue > 0)
		{
			AddTime(1);
		}
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0))
	{
		if (m_nContinue > 0)
		{
			AddTime(1);
			pSound->Play(CSound::SOUND_LABEL_SE_COUNTDOWN);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CContinue::Draw(void)
{
	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		m_apContinue[nCount]->Draw();
	}
}

//=============================================================================
// �X�R�A���Z
//=============================================================================
void CContinue::AddTime(int nValue)
{
	m_nContinue -= nValue;

	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		m_apContinue[nCount]->SetNumber(m_nContinue % (int)powf(10, MAX_CONTINUE - nCount) / powf(10, MAX_CONTINUE - nCount - 1));
	}
}
