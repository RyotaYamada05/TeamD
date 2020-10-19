//=============================================================================
//
// メイン処理 [scene3D.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=========================================================================
//インクルードファイル
//=========================================================================
#include "scene.h"

#define SIZE_X (300.0f)
#define SIZE_Z (300.0f)

//=========================================================================
//3Dポリゴンクラス
//=========================================================================
class CScene3D :public CScene
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CScene3D();
	virtual ~CScene3D();

	static CScene3D*Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void UnLoad(void);
	
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// 初期化
	virtual void Uninit(void);													// 終了
	virtual void Update(void);													// 更新
	virtual void Draw(void);													// 描画

	void SetPos(D3DXVECTOR3 pos);												// 座標の設定
	void SetPosision(D3DXVECTOR3 pos);											// 座標の更新
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファポインタ
	D3DXMATRIX	m_mtxWorld;						// ワールドマトリクス
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_size;							// サイズ
	D3DXVECTOR3 m_rot;							// 向き
};
#endif