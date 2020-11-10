//=============================================================================
//
// 軌跡の処理 [locus.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "locus.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// static初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CLocus::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CLocus::CLocus()
{
	m_nLife = 0;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CLocus::~CLocus()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CLocus * CLocus::Create(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife)
{
	//ポインタ変数
	CLocus *pLocus = NULL;

	//メモリの確保
	pLocus = new CLocus;

	//メモリが確保できていたら
	if (pLocus != NULL)
	{
		//初期化処理呼び出し
		pLocus->Init(pos, size);
		pLocus->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pLocus->SetRot(rot);
		pLocus->m_posOld = posOld;
		pLocus->m_rot = rot;
		pLocus->m_nLife = nLife;
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
HRESULT CLocus::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/board000.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CLocus::UnLoad(void)
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
HRESULT CLocus::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// 初期化処理
	CScene3D::Init(pos, size);

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;


	m_pos = pos;
	m_size = size;

	float sizeX = sqrtf((m_posOld.x - m_pos.x)*(m_posOld.x - m_pos.x));
	float sizeY = sqrtf((m_posOld.y - m_pos.y)*(m_posOld.y - m_pos.y));
	float sizeZ = sqrtf((m_posOld.z - m_pos.z)*(m_posOld.z - m_pos.z));

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(-(sizeX / 2), +(sizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(sizeX / 2), +(sizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(sizeX / 2), -(sizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(sizeX / 2), -(sizeY / 2), 0.0f);

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

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLocus::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLocus::Update(void)
{
	m_nLife--;

	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLocus::Draw(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// 加算合成を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー

	D3DXMATRIX mtxRot, mtxTrans;	//計算用のマトリクス

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	float sizeX = sqrtf((m_posOld.x - m_pos.x)*(m_posOld.x - m_pos.x));
	float sizeY = sqrtf((m_posOld.y - m_pos.y)*(m_posOld.y - m_pos.y));
	float sizeZ = sqrtf((m_posOld.z - m_pos.z)*(m_posOld.z - m_pos.z));

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, sizeX, sizeY, sizeZ);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// 描画処理
	//CScene3D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー

	// Zバッファ戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	pDevice->LightEnable(0, TRUE);

}