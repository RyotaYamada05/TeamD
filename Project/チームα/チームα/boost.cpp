//=============================================================================
//
// ブースターの処理 [boost.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "boost.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"

//=============================================================================
// static初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CBoost::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBoost::CBoost()
{
	m_nNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBoost::~CBoost()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CBoost * CBoost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nNumber)
{
	//3Dポリゴンクラスのポインタ変数
	CBoost *pLocus = NULL;

	//メモリの確保
	pLocus = new CBoost;

	//メモリが確保できていたら
	if (pLocus != NULL)
	{
		//初期化処理呼び出し
		pLocus->Init(pos, size);
		pLocus->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pLocus->SetRot(D3DXVECTOR3(rot.x, rot.y+ D3DXToRadian(180), rot.z));
		pLocus->BindTexture(m_pTexture);
	}
	else
	{
		return NULL;
	}

	return pLocus;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CBoost::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/boost.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CBoost::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBoost::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// 初期化処理
	CScene3D::Init(pos, size);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBoost::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBoost::Update(void)
{
	// 3Dポリゴン更新処理
	CScene3D::Update();

	// レーザーを動かす処理
	BoostMove();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBoost::Draw(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// かぶさらないようにする　(Zバッファ)
//	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// 裏面を（左回り）をカリング

	// アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	// 描画処理
	CScene3D::Draw();

	// アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Zバッファ戻す
//	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

//=============================================================================
// ブーストの更新処理
//=============================================================================
void CBoost::BoostMove(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer(m_nNum);
	D3DXVECTOR3 rot = pPlayer->GetRot();
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x - sinf(rot.y) * 70.0f, pos.y - 50.0f, pos.z - cosf(rot.y) * 70.0f);

	// 角度
	SetRot(rot);

	// 座標
	SetPos(TargetPos + move);
}