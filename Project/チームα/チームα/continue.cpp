//=============================================================================
//
// コンティニュー処理 [continue.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルード
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
//静的メンバ変数宣言
//=============================================================================
CUi *CContinue::m_pUi = NULL;							// uiのポインタ

//=============================================================================
// クリエイト関数
//=============================================================================
CContinue *CContinue::Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CContinue *pContinue = new CContinue;

	pContinue->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pContinue;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CContinue::CContinue()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CContinue::~CContinue()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CContinue::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ナンバーテクスチャをロード
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
// 終了処理
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

	// リリース
	Release();

	// ナンバーテクスチャをアンロード
	CNumber::Unload();
}

//=============================================================================
// 更新処理
//=============================================================================
void CContinue::Update(void)
{

	// キーボード更新
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
// 描画処理
//=============================================================================
void CContinue::Draw(void)
{
	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		m_apContinue[nCount]->Draw();
	}
}

//=============================================================================
// スコア加算
//=============================================================================
void CContinue::AddTime(int nValue)
{
	m_nContinue -= nValue;

	for (int nCount = 0; nCount < MAX_CONTINUE; nCount++)
	{
		m_apContinue[nCount]->SetNumber(m_nContinue % (int)powf(10, MAX_CONTINUE - nCount) / powf(10, MAX_CONTINUE - nCount - 1));
	}
}
