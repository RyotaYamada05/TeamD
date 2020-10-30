//=================================================================================
//
// ボムクラス [bomb.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// インクルード
//=================================================================================
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "shock.h"

//=================================================================================
// マクロ定義
//=================================================================================
#define BOMB_LIFE			(60)			// ボムのライフ
#define BOMB_GRAVITY_POWAR	(0.2f)			// ボムの重力

//=================================================================================
// static初期化
//=================================================================================
LPDIRECT3DTEXTURE9 CBomb::m_apTexture[MAX_BOMB_TEXTURE] = {};
LPD3DXMESH CBomb::m_pMesh = NULL;
LPD3DXBUFFER CBomb::m_pBuffMat = NULL;		//マテリアル情報へのポインタ
DWORD CBomb::m_nNumMat = 0;					//マテリアル情報の数

//=================================================================================
// インスタンス生成
//=================================================================================
CBomb * CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, BULLET2_USER user)
{
	// メモリ確保
	CBomb *pBomb = new CBomb;

	if (pBomb != NULL)
	{
		// 初期化処理
		pBomb->Init(pos, size, user);		// 初期化情報
		pBomb->SetMove(move);					// 移動量
		pBomb->SetLife(BOMB_LIFE);				// ライフの情報
	}

	return pBomb;
}

//=================================================================================
// コンストラクタ
//=================================================================================
CBomb::CBomb()
{
	m_fAddRotNum = 0.0f;
}

//=================================================================================
// デストラクタ
//=================================================================================
CBomb::~CBomb()
{
}

//=================================================================================
// 初期化処理
//=================================================================================
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BULLET2_USER user)
{
	MODEL model;

	model.dwNumMat = m_nNumMat;
	model.pBuffer = m_pBuffMat;
	model.pMesh = m_pMesh;

	//モデル情報を設定
	BindModel(model);
	BindTexture(m_apTexture[0]);

	// 初期化処理
	CBullet2::Init(pos, size, user);		// 初期化情報
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 向き

	return S_OK;
}

//=================================================================================
// 終了処理
//=================================================================================
void CBomb::Uninit(void)
{
	// 終了処理
	CBullet2::Uninit();
}

//=================================================================================
// 更新処理
//=================================================================================
void CBomb::Update(void)
{
	// 更新処理
	CBullet2::Update();

	// 回転
	AddRot();

	// 座標を受け取る
	D3DXVECTOR3 pos = GetPos();

	// エフェクト生成
	//CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f));

	// 移動量を受け取る
	D3DXVECTOR3 move = GetMove();

	// 座標が地面より上なら
	if (pos.y > 20.0f)
	{

		// 重力を加算
		SetMove(D3DXVECTOR3(move.x, move.y - BOMB_GRAVITY_POWAR, move.z));
	}
	else
	{
		SetMove(D3DXVECTOR3(move.x, 0.0f, move.z));
	}


}

//=================================================================================
// 描画処理
//=================================================================================
void CBomb::Draw(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL*pMat;

	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	// モデルの描画
	CBullet2::Draw();
}

//=================================================================================
// 角度を加算
//=================================================================================
void CBomb::AddRot(void)
{
	m_fAddRotNum += 1.0f;

	// 角度の変化
	D3DXVECTOR3 rot = D3DXVECTOR3(GetRot().x, GetRot().y + D3DXToRadian(m_fAddRotNum), GetRot().z);

	// 角度を渡す
	SetRot(rot);
}


//=================================================================================
// テクスチャロード
//=================================================================================
HRESULT CBomb::Load(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Explosion004.jpg",
		&m_apTexture[0]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/bomb.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=================================================================================
// テクスチャアンロード
//=================================================================================
void CBomb::UnLoad(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	for (int nCount = 0; nCount < MAX_BOMB_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}