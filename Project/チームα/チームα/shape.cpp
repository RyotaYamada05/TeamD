//=============================================================================
//
// メッシュスフィアクラス [meshshape.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shape.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"

//=============================================================================
// static初期化
//=============================================================================
LPD3DXMESH CMeshShape::m_pMesh = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER CMeshShape::m_pBuffMat = NULL;	//マテリアル情報へのポインタ
DWORD CMeshShape::m_nNumMat = 0;				//マテリアル情報の数
LPDIRECT3DTEXTURE9 CMeshShape::m_apTexture[MAX_MESHFIELD_TEXTURE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshShape::CMeshShape()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshShape::~CMeshShape()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshShape::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//多角形メッシュの生成
	D3DXCreatePolygon(pDevice,100,6,&m_pMesh,&m_pBuffMat);
	//球メッシュの生成
	//D3DXCreateSphere(pDevice,50, 32, 32,&m_pMesh, &m_pBuffMat);
	//トーラスメッシュの生成
	//D3DXCreateTorus(pDevice, 10, 100, 32, 32, &m_pMesh, &m_pBuffMat);

	MODEL model;
	model.dwNumMat = 1;
	model.pBuffer = m_pBuffMat;
	model.pMesh = m_pMesh;

	//モデル情報を設定
	CModel::BindModel(model);

	m_pos = D3DXVECTOR3(0.0f, 200.0f, 50.0f);					// 位置
	CModel::SetPos(m_pos);
	CModel::SetRot(m_move);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshShape::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshShape::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshShape::Draw(void)
{
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	pMat->MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pMat->MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pMat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//透視変換の設定
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f), (float)rect.right / (float)rect.bottom, 100, 1000);

	// 描画処理
	CModel::Draw();
}

//=============================================================================
// ポリゴン生成
//=============================================================================
CMeshShape * CMeshShape::Create(void)
{
	CMeshShape *pMeshShape = new CMeshShape;

	if (pMeshShape != NULL)
	{
		pMeshShape->Init();
	}

	return pMeshShape;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CMeshShape::Load(void)
{
	//// レンダラーの情報を受け取る
	//CRenderer *pRenderer = NULL;
	//pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data/Texture/stone_00124.jpg",
	//	&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CMeshShape::UnLoad(void)
{
	//for (int nCount = 0; nCount < MAX_MESHFIELD_TEXTURE; nCount++)
	//{
	//	// テクスチャの開放
	//	if (m_apTexture[nCount] != NULL)
	//	{
	//		m_apTexture[nCount]->Release();
	//		m_apTexture[nCount] = NULL;
	//	}
	//}
}

D3DXVECTOR3 CMeshShape::GetPos(void)
{
	return m_pos;
}
