//=====================================================
//
// ビルボードクラスヘッダー [billboard.h]
// Author : 小西優斗
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

CBillboard *CBillboard::m_apBillboard[MAX_BILLBOARD] = {};	// 出現させるビルボード

//=====================================================
// コンストラクタ
//=====================================================
CBillboard::CBillboard()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置情報
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 方向7
	m_pVtxBuff = NULL;									// 頂点バッファへのポインタ
	m_pTexture = NULL;									// ポリゴンのテクスチャ
	m_nLife = 0;										// 寿命
	m_bUse = false;										// 使用判定
}

//=====================================================
// デストラクタ
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBillboard::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBillboard::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CBillboard::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CBillboard::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans;
	DWORD ambient;

	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転の逆行列の生成
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL,
		&mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// アルファテストの比較方法の設定(GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリクスの設定 初期化、向き、位置
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	pDevice->LightEnable(0, TRUE);
}

//=====================================================
// テクスチャの設定
//=====================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}