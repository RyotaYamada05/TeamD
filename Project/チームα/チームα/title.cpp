//=======================================================================================
//
// 背景描画処理 [bg.cpp]
// Author : 伊藤　航
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "title.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "conection.h"
#include "tcp_client.h"
#include "fade.h"
#include "titlelogo.h"

//=======================================================================================
//静的メンバ変数宣言
//=======================================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[1] = {};
CTitlelogo *CTitle::m_apTitlelogo[MAX_TITLE] = {};

//=======================================================================================
// タイトルクラスのコンストラクタ
//=======================================================================================
CTitle::CTitle()
{
	m_pScene = NULL;
	m_bModechenge = false;
}

//=======================================================================================
// タイトルクラスのデストラクタ
//=======================================================================================
CTitle::~CTitle()
{

}

//=======================================================================================
// タイトルクラスのクリエイト処理
//=======================================================================================
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle();

	pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	return pTitle;
}

//=======================================================================================
// タイトルクラスのテクスチャ読み込み処理
//=======================================================================================
HRESULT CTitle::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg001.png", &m_pTexture[0]);
		return S_OK;
}

//=======================================================================================
// タイトルクラスの初期化処理
//=======================================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene == NULL)
	{
		m_pScene = CScene2d::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		//テクスチャの設定
		m_pScene->BindTexture(m_pTexture[0]);
	}

	
	if (m_apTitlelogo[0] == NULL)
	{
		m_apTitlelogo[0] = CTitlelogo::Create(D3DXVECTOR3(TITLE_UI_POS_X, TITLE_UI_POS_Y, 0.0f), D3DXVECTOR3(TITLE_UI_SIZE, TITLE_UI_SIZE, 0.0f), CTitlelogo::LOGOTIPE_UI);
	}
	if (m_apTitlelogo[1] == NULL)
	{
		m_apTitlelogo[1] = CTitlelogo::Create(D3DXVECTOR3(TITLE_PLESS_POS_X, TITLE_PLESS_POS_Y, 0.0f), D3DXVECTOR3(TITLE_PLESS_SIZE_X, TITLE_PLESS_SIZE_Y, 0.0f), CTitlelogo::LOGOTIPE_PRESS);
	}
	if (m_apTitlelogo[2] == NULL)
	{
		m_apTitlelogo[2] = CTitlelogo::Create(D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f), D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f), CTitlelogo::LOGOTIPE_TITLE);
	}
	return S_OK;
}

//=======================================================================================
// タイトルクラスの終了処理
//=======================================================================================
void CTitle::Uninit(void)
{
	if (m_apTitlelogo[0] != NULL)
	{
		m_apTitlelogo[0]->Uninit();
		m_apTitlelogo[0] = NULL;
	}

	if (m_apTitlelogo[1] != NULL)
	{
		m_apTitlelogo[1]->Uninit();
		m_apTitlelogo[1] = NULL;
	}

	if (m_apTitlelogo[2] != NULL)
	{
		m_apTitlelogo[2]->Uninit();
		m_apTitlelogo[2] = NULL;
	}

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}

	
	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// タイトルクラスの更新処理
//=======================================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();


	if (pKey->GetTrigger(DIK_RETURN))
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}
}

//=======================================================================================
// タイトルクラスの描画処理
//=======================================================================================
void CTitle::Draw(void)
{

}