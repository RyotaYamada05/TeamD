#ifndef _BOOST_H_
#define _BOOST_H_

//=============================================================================
//
// ブースターの処理 [boost.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene3D.h"

//=========================================================================
// マクロ定義
//=========================================================================
#define BOOST_SIZE_X	(30.0f)
#define BOOST_SIZE_Y	(300.0f)
#define BOOST_SIZE_Z	(50.0f)
#define BOOST_LIFE		(15)

//=========================================================================
// ブースタークラス
//=========================================================================
class CBoost :public CScene3D
{
public:
	CBoost();
	~CBoost();

	static CBoost *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nNumber);
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// 初期化
	void Uninit(void);													// 終了
	void Update(void);													// 更新
	void Draw(void);													// 描画
	void BoostMove(void);												// ブーストの更新処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャポインタ
	int m_nNum;									// ナンバー
};
#endif