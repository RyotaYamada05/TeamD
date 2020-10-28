#ifndef _ITEM_H_
#define _ITEM_H_

//===================================================
//
// アイテムクラスヘッダー	[item.h]
// Author : Konishi Yuuto
//
//===================================================

//===================================================
// インクルード
//===================================================
#include "billboard.h"

//===================================================
// マクロ定義
//===================================================
#define MAX_BOARD_TEXTURE (1)

//===================================================
// アイテムクラス
//===================================================
class CBoard : public CBillboard
{
public:
	CBoard();									// コンストラクタ
	~CBoard();									// デストラクタ

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void SetPos(D3DXVECTOR3 pos);									// 座標の設定
	static CBoard*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ポリゴン生成

	static HRESULT Load(void);										// テクスチャロード
	static void UnLoad(void);										// テクスチャアンロード
private:
	D3DXVECTOR3 m_Pos;											// 位置情報
	D3DXVECTOR3 m_Dir;											// 方向7
	D3DXMATRIX m_mtxWorld;										// 行列計算用
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOARD_TEXTURE];	// テクスチャ情報のポインタ
};

#endif