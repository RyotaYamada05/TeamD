//=======================================================================================
//
// ゲージ描画処理(gauge.cpp)
// Author : 佐藤颯紀
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "keyboard.h"
#include "gauge.h"
#include "renderer.h"
#include "manager.h"

//=======================================================================================
// クリエイト処理
//=======================================================================================
CGauge* CGauge::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// オブジェクトを生成
	CGauge* pGauge = new CGauge();

	// 初期化処理
	pGauge->Init(pos, size);

	return pGauge;
}

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGauge::CGauge()
{
	m_pTextuer = NULL;
	m_pVetxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGauge::~CGauge()
{

}

//=======================================================================================
//初期化処理
//=======================================================================================
HRESULT CGauge::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVetxBuff,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点データをロックする
	m_pVetxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	// 頂点データをアンロックする
	m_pVetxBuff->Unlock();

	return S_OK;
}

//=======================================================================================
// ポリゴンの終了処理
//=======================================================================================
void CGauge::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVetxBuff != NULL)
	{
		m_pVetxBuff->Release();
		m_pVetxBuff = NULL;
	}
	CScene::Release();
}

//=======================================================================================
// ポリゴンの更新処理
//=======================================================================================
void CGauge::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点データをロックする
	m_pVetxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// 頂点データをアンロックする
	m_pVetxBuff->Unlock();
}

//=======================================================================================
// ポリゴンの描画処理
//=======================================================================================
void CGauge::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVetxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, m_pTextuer);

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}

//======================================================
//色の取得
//======================================================
void CGauge::SetCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	m_col = col;

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	m_pVetxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定(0~255の数値で設定)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,aは0~255の範囲で決めること
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);  //r:レッド g:グリーン　b:ブルー
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //aは、透明度を表している
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//頂点データをアンロック
	m_pVetxBuff->Unlock();
}
