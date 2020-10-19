//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//モデルクラスのコンストラクタ
//=============================================================================
CModel::CModel()
{
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_nNumMat = 0;
	m_pos = D3DXVECTOR3();
	m_rot = D3DXVECTOR3();
}

//=============================================================================
//モデルクラスのデストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//モデルクラスのポインタ変数
	CModel *pModel = NULL;

	//メモリ確保
	pModel = new CModel;

	//メモリが確保できていたら
	if (pModel != NULL)
	{
		//初期化処理呼び出し
		pModel->Init(pos, size);
	}
	//メモリ確保に失敗したとき
	else
	{
		return NULL;
	}

	return pModel;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CModel::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//位置の初期化
	m_pos = pos;

	//向きの初期化
	m_rot = rot;

	return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CModel::Uninit(void)
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

	//オブジェクトの破棄
	Release();
}

//=============================================================================
//モデルクラスの更新処理
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
//モデルクラスの描画処理
//=============================================================================
void CModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

void CModel::BindModel(MODEL model)
{
	m_pMesh = model.pMesh;
	m_pBuffMat = model.pBuffer;
	m_nNumMat = model.dwNumMat;
}

//=============================================================================
//モデルクラスのメッシュ情報の取得
//=============================================================================
LPD3DXMESH CModel::GetMesh(void) const
{
	return m_pMesh;
}

//=============================================================================
//モデルクラスの位置情報の設定
//=============================================================================
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//モデルクラスの位置情報の取得
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//モデルクラスの向きの設定
//=============================================================================
void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}
