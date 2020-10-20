#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=====================================================
//
// ビルボードクラスヘッダー [billboard.h]
// Author : 小西優斗
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "scene3D.h"

//=====================================================
// マクロ定義
//=====================================================
#define MAX_BILLBOARD		(256)
#define BILLBOARD_SIZE_X	(25)
#define BILLBOARD_SIZE_Y	(25)

//=====================================================
// 前方宣言
//=====================================================
class CScene3D;

//=====================================================
// ビルボードクラス
//=====================================================
class CBillboard : public CScene3D
{
public:
	CBillboard();									// コンストラクタ
	~CBillboard();									// デストラクタ

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	void SetPos(D3DXVECTOR3 pos);					// 座標の設定
	D3DXVECTOR3 GetPos(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// テクスチャの設定

private:
	D3DXVECTOR3 m_Pos;									// 位置情報
	D3DXVECTOR3 m_size;									//サイズ
	D3DXVECTOR3 m_Dir;									// 方向7
	D3DXMATRIX m_mtxWorld;								// 行列計算用
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;						// ポリゴンのテクスチャ
	int m_nLife;										// 寿命
	bool m_bUse;										// 使用判定
	static CBillboard *m_apBillboard[MAX_BILLBOARD];	// 出現させるビルボード
};

#endif