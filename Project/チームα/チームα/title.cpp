//=======================================================================================
//
// 背景描画処理 [bg.cpp]
// Author : 伊藤　航
//
//=======================================================================================

//=======================================================================================
// 
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

LPDIRECT3DTEXTURE9 CTitle::m_pTexture[1] = {};

//=======================================================================================
// 
//=======================================================================================
CTitle::CTitle()
{
	m_pScene = NULL;
	m_bModechenge = false;
}

//=======================================================================================
// 
//=======================================================================================
CTitle::~CTitle()
{

}

//=======================================================================================
// 
//=======================================================================================
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle();

	pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	return pTitle;
}

//=======================================================================================
// 
//=======================================================================================
HRESULT CTitle::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/derttitle.jpg", &m_pTexture[0]);
		return S_OK;
}

//=======================================================================================
// 
//=======================================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene == NULL)
	{
		m_pScene = CScene2d::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		m_pScene->BindTexture(m_pTexture[0]);
	}

	return S_OK;
}

//=======================================================================================
// 
//=======================================================================================
void CTitle::Uninit(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}
}

//=======================================================================================
// 
//=======================================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();

	CManager::MODE_TYPE type = CManager::GetMode();

	if (pKey->GetTrigger(DIK_RETURN) && type == CManager::MODE_TYPE_GAME )
	{
		CManager::SetMode(CManager::MODE_TYPE_GAME);
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}
}

//=======================================================================================
// 
//=======================================================================================
void CTitle::Draw(void)
{

}