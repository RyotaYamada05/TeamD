//=============================================================================
//
// モデル処理 [model.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
//モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	typedef struct
	{
		LPD3DXMESH pMesh;			//メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffer;		//頂点バッファへのポインタ
		DWORD dwNumMat;				//マテリアル情報の数
	}MODEL;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CModel();
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindModel(MODEL model);


	LPD3DXMESH GetMesh(void)const;
	LPD3DXBUFFER GetBuffMat(void)const;	//

	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;
	void SetRot(const D3DXVECTOR3 rot);
					// 座標の情報
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	LPD3DXMESH m_pMesh;	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報へのポインタ
	DWORD m_nNumMat;	//マテリアル情報の数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
};
#endif 