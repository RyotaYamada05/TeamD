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
#include "ui.h"

#include "charge.h"
//=======================================================================================
// static初期化
//=======================================================================================

CCamera *CGame::m_apCamera[MAX_PLAYER] = {};			// カメラクラスのポインタ変数
CLight *CGame::m_pLight = NULL;						// ライトクラスのポインタ変数
CMeshField *CGame::m_pMeshField = NULL;				// メッシュフィールド
CBg *CGame::m_pBg = NULL;							// 背景のポインタ

CPlayer *CGame::m_apPlayer[MAX_PLAYER] = {};		// プレイヤーのポインタ
CTime *CGame::m_pTime = NULL;						// タイムのポインタ
CUi *CGame::m_pUi = NULL;							// uiのポインタ
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
		
		//カメラクラスのクリエイト
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


	//ui
	if (m_pUi == NULL)
	{
		//UIライフゲージ(外枠)の生成
		CUi::Create(D3DXVECTOR3(330.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);
		CUi::Create(D3DXVECTOR3(1060.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);

		CUi::Create(D3DXVECTOR3(330.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);
		CUi::Create(D3DXVECTOR3(1060.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);

		//UIのタイム生成
		CUi::Create(D3DXVECTOR3(640.0f, 50.0f, 0.0f), D3DXVECTOR3(UI_TIME_SIZE_X, UI_TIME_SIZE_Y, 0.0f), CUi::UITYPE_TIME);

		//UIのプレイヤー・エネミー文字の生成
		CUi::Create(D3DXVECTOR3(70.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
		CUi::Create(D3DXVECTOR3(75.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

		CUi::Create(D3DXVECTOR3(800.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
		CUi::Create(D3DXVECTOR3(805.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

		//標準生成
		CUi::Create(D3DXVECTOR3(UI_LOCKON_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CUi::UITYPE_STANDARD);
		CUi::Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CUi::UITYPE_STANDARD);
	}

	// プレイヤーの生成
	if (m_apPlayer[0] == NULL)
	{
	
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	}
	if (m_apPlayer[1] == NULL)
	{

		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, -500.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
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


	//タイム
	if (m_pTime == NULL)
	{
		CTime::Create(D3DXVECTOR3(TIME_POS_X, TIME_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//フォントの生成
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);


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


	//オブジェクトの破棄
	Release();
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

//=======================================================================================
// タイムの情報
//=======================================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

//=======================================================================================
// uiの情報
//=======================================================================================
CUi * CGame::GetUi(void)
{
	return m_pUi;
}
