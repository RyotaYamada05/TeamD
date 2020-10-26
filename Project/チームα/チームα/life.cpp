//=============================================================================
// 
// ライフゲージ処理(life.h)
// Author : 佐藤颯紀
//
//=============================================================================

#include "Life.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "main.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CLife::m_apTexture[LIFETYPE_PLAYER_MAX] = {};

//================================================
//クリエイト処理
//================================================
CLife* CLife::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type)
{
	// オブジェクトを生成
	CLife* pLife = new CLife;

	// 初期化処理
	pLife->Init(pos, size, col, type);

	return pLife;
}

//================================================
//画像の読み込み
//================================================
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Life001.png", //ファイルの読み込み
		&m_apTexture[LIFETYPE_FAST_PLAYER]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Life002.png", //ファイルの読み込み
		&m_apTexture[LIFETYPE_SECOND_PLAYER]);

	return S_OK;
}

//================================================
//テクスチャの破棄
//================================================
void CLife::Unload(void)
{
	for (int nCount = 0; nCount < LIFETYPE_PLAYER_MAX; nCount++)
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
CLife::CLife()
{
	m_nCounter = 0;
	m_nCounterLife = 0;
	m_bLife = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//カラー
	m_type = LIFETYPE_NONE;		//タイプ

}

//================================================
//デストラクタ
//================================================
CLife::~CLife()
{

}

//================================================
//初期化処理
//================================================
HRESULT CLife::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type)
{
	m_pos = pos;		//位置情報
	m_size = size;		//サイズ
	m_col = col;		//カラー
	m_type = type;		//タイプ

	CGauge::Init(pos, size);	//CGaugeの初期化

	CGauge::BindTexture(m_apTexture[type]); //テクスチャーの取得

	//位置設定
	CGauge::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//サイズ設定
	CGauge::SetSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//カラー設定
	CGauge::SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CLife::Uninit(void)
{
	CGauge::Uninit();
}

//================================================
//更新処理
//================================================
void CLife::Update(void)
{
	CGauge::Update();

	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//位置の取得
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR col = GetCol();

	
	//Tキー押したら
	if (pKeyboard->GetPress(DIK_T))
	{
		Decrease(50, true, LIFETYPE_FAST_PLAYER);
	}

	if (pKeyboard->GetPress(DIK_Y))
	{
		Decrease(100, true, LIFETYPE_SECOND_PLAYER);
	}

	//ライフを減らす処理
	if (0 < size.x)
	{
		if (m_bLife == true)
		{
			m_nCounterLife++;

			size.x--;

			//自分のライフの色が変わったとき
			if (m_type == LIFETYPE_FAST_PLAYER)
			{
				col = D3DCOLOR_RGBA(255, 0, 0, 255);
			}
			//相手のライフの色が変わったとき
			if (m_type == LIFETYPE_SECOND_PLAYER)
			{
				col = D3DCOLOR_RGBA(0, 50, 255, 255);
			}

			if (m_nCounterLife == m_nCount)
			{
				m_bLife = false;
				m_nCounterLife = 0;

				//自分のライフの色を元に戻す
				if (m_type == LIFETYPE_FAST_PLAYER)
				{
					col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				//相手のライフの色を元に戻す
				if (m_type == LIFETYPE_SECOND_PLAYER)
				{
					col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}
		}
	}

	//ライフが半分以下になると点滅するようにする
	if (size.x < HALF_LIFE)
	{
		m_nCounter++;

		if (m_nCounter == 15)
		{
			col.a = 0.8f;
		}
		else if (m_nCounter == 30)
		{
			col.a = 1.0f;

			m_nCounter = 0;
		}
	}
	
	SetSize(size);
	SetCol(col);
}

//================================================
//描画処理
//================================================
void CLife::Draw(void)
{
	CGauge::Draw();
}

//================================================
//ライフを減らしていく処理
//================================================
void CLife::Decrease(int Count, bool Life, LIFETYPE type)
{
	m_nCount = Count;
	m_bLife = Life;
	m_typeDecrease = type;
}