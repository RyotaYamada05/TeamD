#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "model.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define THROWING_COUNTS (3)		// 投げることができる回数
#define LIFE_NUM		(2)		// 表示するライフの数

//=============================================================================
// 前方宣言
//=============================================================================
class CScore;
class CLife;
class CCharge;
//=============================================================================
// ターンクラス
//=============================================================================
class CPlayer : public CModel
{
public:
	CPlayer();							// コンストラクタ
	~CPlayer();							// デストラクタ

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// クリエイト
	static HRESULT LoadModel(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void PlayerControl(void);										// プレイヤーの制御
	void Walk(void);												// プレイヤーの歩く処理
	void Jump(void);												// ジャンプの処理
	void GroundLimit(void);											// 地面の制限
	void Fall(void);												// 急降下
	void Dush(void);												// ダッシュ
	D3DXVECTOR3 GetPos(void);


	CLife *GetLife(int nNumber);									// ライフの情報
	CCharge *GetCgarge(void);										// チャージのポインタ
private:
	CScore *pScore;							// スコアの情報
	CLife *m_pLife[LIFE_NUM];				// ライフのポインタ
	CCharge *m_pCharge;						// チャージのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_move;						// 移動
	int m_nDushFlame;						// ダッシュのフレーム
	int m_nDushInterCnt;					// ダッシュできないときのカウント
	int m_nPlayerNum;						// プレイヤーの番号
	bool m_bJump;							// ジャンプのフラグ
	bool m_bDush;							// ダッシュの処理
	bool m_bDushInter;						// ダッシュのインターバル
	static LPD3DXMESH m_pMesh;				// メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD m_nNumMat;					// マテリアル情報の数
	static int m_nPlayerAll;				// プレイヤーの数
};

#endif