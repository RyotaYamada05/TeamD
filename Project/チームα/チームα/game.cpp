//=======================================================================================
//
// ゲーム処理 [game.cpp]
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
#include "shape.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "gauge.h"
#include "life.h"
#include "ui.h"
#include "lockon.h"
#include "charge.h"
#include "bill.h"
#include "uistart.h"
#include "fire.h"
#include "bill.h"
#include "uistart.h"
#include "continue.h"
#include "uiend.h"
#include "sound.h"

//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_apCamera[MAX_PLAYER] = {};		// カメラクラスのポインタ変数
CLight *CGame::m_pLight = NULL;						// ライトクラスのポインタ変数
CMeshField *CGame::m_pMeshField = NULL;				// メッシュフィールド
CMeshShape *CGame::m_pSphere = NULL;				// メッシュスフィア
CBg *CGame::m_pBg = NULL;							// 背景のポインタ
CPlayer *CGame::m_apPlayer[MAX_PLAYER] = {};		// プレイヤーのポインタ
CTime *CGame::m_pTime = NULL;						// タイムのポインタ
CUi *CGame::m_pUi = NULL;							// uiのポインタ
CUiStart *CGame::m_pUiStart = NULL;
CLockon *CGame::m_pLockon = NULL;
CBill *CGame::m_pBill = NULL;
CContinue *CGame::m_pContinue = NULL;
CUiEnd *CGame::m_pUiEnd = NULL;
int CGame::m_nRoundNum = 0;
int CGame::m_aWinNum[MAX_PLAYER] = {};

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
	m_nRoundNum = 0;
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
		m_pUi = CUi::Create(D3DXVECTOR3(330.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);
		m_pUi = CUi::Create(D3DXVECTOR3(1060.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);

		m_pUi = CUi::Create(D3DXVECTOR3(330.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);
		m_pUi = CUi::Create(D3DXVECTOR3(1060.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);

		//UIのタイム生成
		m_pUi = CUi::Create(D3DXVECTOR3(640.0f, 50.0f, 0.0f), D3DXVECTOR3(UI_TIME_SIZE_X, UI_TIME_SIZE_Y, 0.0f), CUi::UITYPE_TIME);

		//UIのプレイヤー・エネミー文字の生成
		m_pUi = CUi::Create(D3DXVECTOR3(70.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
		m_pUi = CUi::Create(D3DXVECTOR3(75.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

		m_pUi = CUi::Create(D3DXVECTOR3(800.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
		m_pUi = CUi::Create(D3DXVECTOR3(805.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

		//標準生成
		m_pUi = CUi::Create(D3DXVECTOR3(UI_LOCKON_POS_LEFT_X, UI_LOCKON_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_SMALL_X, UI_LOCKON_SIZE_SMALL_Y, 0.0f), CUi::UITYPE_STANDARD);
		m_pUi = CUi::Create(D3DXVECTOR3(UI_LOCKON_POS_RIGHT_X, UI_LOCKON_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_SMALL_X, UI_LOCKON_SIZE_SMALL_Y, 0.0f), CUi::UITYPE_STANDARD);
	}

	//startのUI
	if (m_pUiStart == NULL)
	{
		//ready文字
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_LEFT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_RIGHT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
		//round文字
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_LEFT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_1);
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_RIGHT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_1);
	}

	// プレイヤーの生成
	if (m_apPlayer[0] == NULL)
	{
	
		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, -500.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	}
	if (m_apPlayer[1] == NULL)
	{
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(PLAYER2_POS_X, PLAYER2_POS_Y, PLAYER2_POS_Z), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	}

	//ビル
	if (m_pBill == NULL)
	{
		m_pBill = CBill::Create(D3DXVECTOR3(3000.0f, 0.0f, -4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(-3000.0f, 0.0f, -4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(3000.0f, 0.0f, 4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(-3000.0f, 0.0f, 4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(-2000.0f, 0.0f, .0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
	}

	// メッシュフィールド
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	CMeshShape::Load();
	//// メッシュスフィア
	//if (m_pSphere == NULL)
	//{
	//	m_pSphere = CMeshShape::Create();
	//}

	// 背景
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	//タイム
	if (m_pTime == NULL)
	{
		m_pTime = CTime::Create(D3DXVECTOR3(TIME_POS_X, TIME_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//BGM
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

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
			//カメラクラスの終了処理呼び出
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


	//CMeshShape::UnLoad();
	//// メッシュスフィア
	//if (m_pSphere != NULL)
	//{
	//	m_pSphere->Uninit();
	//}

	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
	}

	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);

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

	// メッシュスフィア
	if (m_pSphere != NULL)
	{
		m_pSphere->Update();
	}

	for (int nCount = 0; nCount < FIRE_NUM; nCount++)
	{
		// 炎の生成
		CFire::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f),
			D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
	}

	// ゲームの設定
	SetGame();

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

	//// メッシュスフィア
	//if (m_pSphere != NULL)
	//{
	//	m_pSphere->Draw();
	//}

	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}
}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{

		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			// プレイヤーの情報取得
			CPlayer *pPlayer = GetPlayer(nCount);
			bool bEnd = pPlayer->GetEnd();

			// どちらかが終わっていたら
			if (bEnd == true)
			{
				switch (nCount)
				{
				case 0:
					m_aWinNum[1]++;
					break;
				case 1:
					m_aWinNum[0]++;
					break;
				default:
					break;
				}

				if (m_aWinNum[0] < 2 && m_aWinNum[1] < 2)
				{
					// ラウンドを進める
					m_nRoundNum++;

					// 初期化処理
					ResetGame();

				}
				else
				{
					//最後に出すUI
					if (m_pUiEnd == NULL)
					{
						m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, UI_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_CONTINUE_SIZE_X, UI_CONTINUE_SIZE_Y, 0.0f), CUiEnd::UIENDTYPE_CONTINUE);
						m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, 500.0f, 0.0f), D3DXVECTOR3(400, 40, 0.0f), CUiEnd::UIENDTYPE_THANKS);
					}

					//コンテニューのタイム
					if (m_pContinue == NULL)
					{
						m_pContinue = CContinue::Create(D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
				break;
			}
		}
	}
}

//=======================================================================================
// ゲームのリセット関数
//=======================================================================================
void CGame::ResetGame(void)
{
	if (m_apPlayer[0] != NULL)
	{
		m_apPlayer[0]->Init(D3DXVECTOR3(0.0f, 50.0f, -500.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));

		// ロゴの終了
		m_apPlayer[0]->SetWinToLose(false);
	}
	if (m_apPlayer[1] != NULL)
	{
		m_apPlayer[1]->Init(D3DXVECTOR3(PLAYER2_POS_X, PLAYER2_POS_Y, PLAYER2_POS_Z), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
		m_apPlayer[1]->SetWinToLose(false);
	}

	//タイム
	if (m_pTime != NULL)
	{
		m_pTime->Init(D3DXVECTOR3(TIME_POS_X, TIME_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

		switch (m_nRoundNum)
		{
		case 1:
			//ready文字
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_LEFT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_RIGHT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			//round文字
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_LEFT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_2);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_RIGHT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_2);

			break;
		case 2:
			//ready文字
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_LEFT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_RIGHT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			//round文字
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_LEFT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_3);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_RIGHT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_3);

			break;
		default:
			break;
		
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


//=======================================================================================
// uistartの情報
//=======================================================================================
CUiStart * CGame::GetUiStart(void)
{
	return m_pUiStart;
}

//=======================================================================================
// uiendの情報
//=======================================================================================
CUiEnd *CGame::GetUiEnd(void)
{
	return m_pUiEnd;
}

CMeshShape * CGame::GetSphere()
{
	return m_pSphere;
}

//=======================================================================================
// ロックオンの情報
//=======================================================================================
CLockon * CGame::GetLockon(void)
{
	return m_pLockon;
}

//=======================================================================================
// ビルの情報
//=======================================================================================
CBill * CGame::GetBill(void)
{
	return m_pBill;
}

//=======================================================================================
// コンテニューの情報
//=======================================================================================
CContinue * CGame::GetContinue(void)
{
	return m_pContinue;
}

