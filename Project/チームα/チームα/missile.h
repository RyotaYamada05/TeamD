#ifndef _MISSILE_H_
#define _MISSILE_H_
//=============================================================================
//
// ビームのクラスヘッダー [missile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "bullet2.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MISSILE_SIZE_X				(1)		// ミサイルのサイズ
#define MISSILE_SIZE_Y				(1)		// ミサイルのサイズ
#define MISSILE_SIZE_Z				(1)		// ミサイルのサイズ
#define MISSILE_SPEED				(100)	// ミサイルのスピード

#define MAX_MISSILE_TEXTURE			(1)		// テクスチャの数

//=============================================================================
// 背景クラス
//=============================================================================
class CMissile : public CBullet2
{
public:
	CMissile();		// コンストラクタ
	~CMissile();		// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 size, BULLET2_USER user);							// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理

	static CMissile *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		D3DXVECTOR3 size, BULLET2_USER user);							// インスタンス生成
	static HRESULT Load(void);											// テクスチャロード
	static void UnLoad(void);											// テクスチャアンロード

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_MISSILE_TEXTURE];	// テクスチャ情報のポインタ
	static LPD3DXMESH m_pMesh;									// メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMat;								// マテリアル情報へのポインタ
	static DWORD m_nNumMat;										// マテリアル情報
};

#endif
