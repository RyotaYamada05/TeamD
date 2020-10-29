//================================================
//
// ui処理 [ui.cpp]
// Author : 佐藤颯紀
//
//================================================

//================================================
// インクルード
//================================================

#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CUi::m_apTexture[UI_TYPE] = {};
//================================================
//クリエイト処理
//================================================
CUi* CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type)
{
	// オブジェクトを生成
	CUi* pUi = new CUi;

	// 初期化処理
	pUi->Init(pos,size,type);

	return pUi;
}

//================================================
//ロード処理
//================================================
HRESULT CUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み

	//ライフゲージバー
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/LifeBar.png", //ファイルの読み込み
		&m_apTexture[UITTYPE_LIFE]);

	//タイムの下
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Time002.png", //ファイルの読み込み
		&m_apTexture[UITYPE_TIME]);

	//プレイヤー文字
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Player001.png", //ファイルの読み込み
		&m_apTexture[UITYPE_PLAYER]);

	//エネミー文字
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Enemy001.png", //ファイルの読み込み
		&m_apTexture[UITYPE_ENEMY]);

	//ヒットした時
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Hit.png", //ファイルの読み込み
		&m_apTexture[UITYPE_HIT]);

	//勝った時
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Win.png", //ファイルの読み込み
		&m_apTexture[UITYPE_WIN]);

	//負けた時
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Lose1.png", //ファイルの読み込み
		&m_apTexture[UITYPE_LOSE]);

	//標準
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Lockon001.png", //ファイルの読み込み
		&m_apTexture[UITYPE_STANDARD]);

	//ロックオン
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Lockon.png", //ファイルの読み込み
		&m_apTexture[UITYPE_LOCKON]);

	return S_OK;
}

//================================================
//ロードの終了
//================================================
void CUi::Unload(void)
{
	for (int nCount = 0; nCount < UI_TYPE; nCount++)
	{
		//テクスチャの開放
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//================================================
//コンストラクタ
//================================================
CUi::CUi()
{
	m_nPattern = 0;
	m_nCounter = 0;
	m_nLockCounter = 0;
	m_nLockPattern = 0;
	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_type = UITYPE_NONE;
}

//================================================
//デストラクタ
//================================================
CUi::~CUi()
{

}

//================================================
//初期化処理
//================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type)
{
	m_pos = pos;	//位置情報
	m_size = size;	//サイズ
	m_type = type;	//タイプ

	CScene2d::Init(pos,size);	//CScene2dの初期化

	CScene2d::BindTexture(m_apTexture[type]);

	//位置設定
	CScene2d::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//サイズ設定
	CScene2d::SetPolygonSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//カラー設定
	CScene2d::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//ロックオンの場合
	if (m_type == UITYPE_LOCKON)
	{
		//テクスチャー設定
		CScene2d::SetAnim(m_nLockPattern, 0.5);
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CUi::Uninit(void)
{
	CScene2d::Uninit();
}

//================================================
//更新処理
//================================================
void CUi::Update(void)
{
	CScene2d::Update();

	//Hit!!がでたとき
	UiHit();

	//ロックオンの処理
	UiLockon();

	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_T))
	{
		Create(D3DXVECTOR3(UI_RESULT_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_WIN);
		Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_LOSE);
	}

	if (pKeyboard->GetTrigger(DIK_Y))
	{
		Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_WIN);
		Create(D3DXVECTOR3(UI_RESULT_POS_LEFT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_RESULT_SIZE_X, UI_RESULT_SIZE_Y, 0.0f), CUi::UITYPE_LOSE);
	}

	if (pKeyboard->GetTrigger(DIK_U))
	{
		Create(D3DXVECTOR3(UI_RESULT_POS_RIGHT_X, UI_RESULT_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_X, UI_LOCKON_SIZE_Y, 0.0f), CUi::UITYPE_LOCKON);
	}
}

//================================================
//描画処理
//================================================
void CUi::Draw(void)
{
	CScene2d::Draw();
}

//================================================
//ヒットした時に出るUIの処理
//================================================
void CUi::UiHit(void)
{
	D3DXCOLOR col = GetCol();

	if (m_type == UITYPE_HIT)
	{
		m_nPattern++;
		m_nCounter++;

		if (m_nCounter == 3)
		{
			col.a = 1.0f;
		}
		else if (m_nCounter == 5)
		{
			col.a = 0.0f;
			m_nCounter = 0.0f;
		}

		if (m_nPattern == 30)
		{
			m_nPattern = 0;
			Uninit();
			return;
		}
	}

	SetCol(col);
}

//================================================
//ヒットした時に出るUIの処理
//================================================
void CUi::UiLockon(void)
{
	if (m_type == UITYPE_LOCKON)
	{
		m_nLockCounter++;
		if (m_nLockCounter == 8)
		{
			m_nLockPattern++;
			CScene2d::SetAnim(m_nLockPattern, 0.5f);

			m_nLockCounter = 0;
		}
	}
	
}
