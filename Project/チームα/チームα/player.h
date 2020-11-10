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
#define THROWING_COUNTS		(3)			// 投げることができる回数
#define LIFE_NUM			(2)			// 表示するライフの数
#define MAX_PARTS			(10)		// パーツの数
#define MOTION_KEYSET_MAX	(32)		// キーセット最大数

#define PLAYER1_POS_X		(0.0f)		// 座標
#define PLAYER1_POS_Y		(171.0f)	// 座標
#define PLAYER1_POS_Z		(0)			// 座標

#define PLAYER2_POS_X		(0.0f)		// 座標
#define PLAYER2_POS_Y		(171.0f)	// 座標
#define PLAYER2_POS_Z		(500)		// 座標

#define PLAYER_SIZE_X		(1)			// サイズ
#define PLAYER_SIZE_Y		(1)			// サイズ
#define PLAYER_SIZE_Z		(1)			// サイズ

#define PLAYER_COLLISION_X	(200)		// 当たり判定
#define PLAYER_COLLISION_Y	(350)		// 当たり判定
#define PLAYER_COLLISION_Z	(200)		// 当たり判定

#define PLAYER_RADIUS		(200)		// 半径

//=============================================================================
// 前方宣言
//=============================================================================
class CScore;
class CLife;
class CCharge;
class CBoost;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CModel
{
public:

	typedef enum
	{
		PLAYER_STATE_NONE = 0,		// 初期置
		PLAYER_STATE_NORMAL,		// 通常状態
		PLAYER_STATE_DAMAGE,		// ダメージ
		PLAYER_STATE_EXPLOSION,		// 爆発
		PLAYER_STATE_MAX
	}PLAYER_STATE;

	CPlayer();						// コンストラクタ
	~CPlayer();						// デストラクタ

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// クリエイト
	static HRESULT LoadModel(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void PlayerState(void);											// プレイヤーの状態
	void PlayerControl(void);										// プレイヤーの制御
	void Walk(void);												// プレイヤーの歩く処理
	void Jump(void);												// ジャンプの処理
	void GroundLimit(void);											// 地面の制限
	void Fall(void);												// 急降下
	void Dush(void);												// ダッシュ
	void beam(void);												// ビーム
	void bomb(void);												// ボム
	void Laser(void);												// レーザー
	void BlockUp(void);												// ブロックの上に乗ったとき
	D3DXVECTOR3 GetPos(void);										// 現在の座標情報
	D3DXVECTOR3 GetOldPos(void);									// 古い座標情報
	void SetMove(D3DXVECTOR3 move);										// 移動量の設定
	D3DXVECTOR3 GetMove(void);
	CLife *GetLife(int nNumber);									// ライフの情報
	CCharge *GetCgarge(void);										// チャージのポインタ
	bool GetEnd(void);												// エンド情報
	PLAYER_STATE GetState(void);									// プレイヤーの状態

private:
	CScore *pScore;							// スコアの情報
	CLife *m_pLife[LIFE_NUM];				// ライフのポインタ
	CBoost *m_pBoost;						// ブーストのポインタ
	CCharge *m_pCharge;						// チャージのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_OldPos;					// 1フレーム前の座標
	D3DXVECTOR3 m_rot;						// 回転
	D3DXVECTOR3 m_move;						// 移動
	PLAYER_STATE m_state;					// プレイヤー状態
	float m_fAngle;							// 角度
	int m_nDushFlame;						// ダッシュのフレーム
	int m_nDushInterCnt;					// ダッシュできないときのカウント
	int m_nPlayerNum;						// プレイヤーの番号
	int m_nStateCounter;					// 状態カウンター
	bool m_bJump;							// ジャンプのフラグ
	bool m_bDush;							// ダッシュの処理
	bool m_bDushInter;						// ダッシュのインターバル
	bool m_bEnd;							// 終了フラグ
	bool m_bFall;							// 急降下フラグ
	static LPD3DXMESH m_pMesh;				// メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD m_nNumMat;					// マテリアル情報の数
	static int m_nPlayerAll;				// プレイヤーの数
};

#endif