//=======================================================================================
//
// ゲーム処理 [bg.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
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
#include "bg.h"
#include "joypad.h"

#include "time.h"
#include "gauge.h"
#include "life.h"
//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_apCamera[MAX_PLAYER] = {};			// カメラクラスのポインタ変数
CLight *CGame::m_pLight = NULL;						// ライトクラスのポインタ変数
CMeshField *CGame::m_pMeshField = NULL;				// メッシュフィールド
CBg *CGame::m_pBg = NULL;							// 背景のポインタ
CPlayer *CGame::m_apPlayer[MAX_PLAYER] = {};		// プレイヤーのポインタ

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// クリエイト
//=======================================================================================
CGame* CGame::Create(void)
{
	// メモリ確保
	CGame* pGame = new CGame();

	// 初期化処理
	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_apCamera[nCount] = CCamera::Create();
	}

	//ライトクラスの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// プレイヤーの生成
	if (m_apPlayer[0] == NULL)
	{
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	if (m_apPlayer[1] == NULL)
	{
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// メッシュフィールド
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	// 背景
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	//タイム生成
	CTime::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ライフ生成
	//１Ｐのライフゲージ
	//CLife::Create(D3DXVECTOR3(300, 100.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(255, 140, 0, 255), CLife::LIFETYPE_FAST_PLAYER);
	//CLife::Create(D3DXVECTOR3(300, 200.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(60, 179, 113, 255), CLife::LIFETYPE_FAST_PLAYER);
	////２Ｐのライフゲージ
	//CLife::Create(D3DXVECTOR3(800, 100.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(255, 140, 0, 255), CLife::LIFETYPE_SECOND_PLAYER);
	//CLife::Create(D3DXVECTOR3(800, 200.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(60, 179, 113, 255), CLife::LIFETYPE_SECOND_PLAYER);

	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//カメラクラスの終了処理呼び出し
			m_apCamera[nCount]->Uninit();

			//メモリの破棄
			delete[] * m_apCamera;

			//メモリのクリア
			m_apCamera[nCount] = NULL;
		}
	}
	// メッシュフィールド
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
	}

	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
	}

	CManager::GetConection()->Uninit();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//カメラクラスの更新処理
			m_apCamera[nCount]->Update();
		}
	}

	// メッシュフィールド
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Update();
	}

	CManager::GetConection()->Update();
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
	// メッシュフィールド
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Draw();
	}

	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}
}

//=======================================================================================
// カメラの情報
//=======================================================================================
CCamera * CGame::GetCamera(int nCount)
{
	return m_apCamera[nCount];
}

//=======================================================================================
// ライトの情報
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// プレイヤーの情報
//=======================================================================================
CPlayer * CGame::GetPlayer(int nCount)
{
	return m_apPlayer[nCount];
}