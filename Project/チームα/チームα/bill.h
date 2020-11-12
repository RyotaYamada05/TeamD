//=============================================================================
//
// ビル処理 [bill.h]
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef  _BILL_H_
#define  _BILL_H_

//=============================================================================
// インクルード
//=============================================================================
#include "model.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BILL_SIZE_X				(12)			// サイズ
#define BILL_SIZE_Y				(12)			// サイズ
#define BILL_SIZE_Z				(12)			// サイズ

#define BILL_COLLISION_SIZE_X	(780)			// サイズ
#define BILL_COLLISION_SIZE_Y	(480)			// サイズ
#define BILL_COLLISION_SIZE_Z	(780)			// サイズ

//=============================================================================
// クラス宣言
//=============================================================================
class CBill : public CModel
{
public:
	CBill();
	~CBill();

	static CBill*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// クリエイト
	static HRESULT LoadModel(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	bool Collision(void);											// 当たり判定

private:
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_rot;						// 回転
	D3DXVECTOR3 m_move;						// 移動
	float m_fAngle;							// 角度
	static LPD3DXMESH m_pMesh;				// メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD m_nNumMat;					// マテリアル情報の数

};
#endif // ! _BILL_H_