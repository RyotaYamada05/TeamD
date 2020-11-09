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
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define THROWING_COUNTS		(3)			// 投げることができる回数
#define LIFE_NUM			(2)			// 表示するライフの数
#define MAX_PARTS			(10)		// パーツの数
#define MOTION_KEYSET_MAX	(32)		// キーセット最大数
#define PLAYER_SIZE_X		(1)			// サイズ
#define PLAYER_SIZE_Y		(1)			// サイズ
#define PLAYER_SIZE_Z		(1)			// サイズ
#define MODEL_PARTS 20	//モデルのパーツ数

//=============================================================================
// 前方宣言
//=============================================================================
class CScore;
class CLife;
class CCharge;

typedef enum
{
	M_MOTION_STATE =-1,
	M_MOTION_STATE_IDOL,	//アイドルモーション
	M_MOTION_STATE_WALK,	//歩行モーション
	M_MOTION_STATE_DUSH,	
	M_MOTION_STATE_JUMP,
	M_MOTION_STATE_MAX,	//モーション最大数
}MOTION_STATE;

typedef struct
{
	char xFileName[1024];
	D3DXVECTOR3 offsetPos;
	D3DXVECTOR3 offsetRot;
	int nParent;
}MODELFILLE;

typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

typedef struct
{
	int nFrame;
	KEY aKey[MODEL_PARTS];
}KEY_INFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[20];
}Motion_Info;

//=============================================================================
// ターンクラス
//=============================================================================
class CPlayer : public CScene
{
public:
	CPlayer();							// コンストラクタ
	~CPlayer();							// デストラクタ


	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// クリエイト

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void UpdateMotion(void);										//モーション更新処理
	void Draw(void);												// 描画処理
	void SetMotion(MOTION_STATE motion);

	void PlayerControl(void);										// プレイヤーの制御
	void Walk(void);												// プレイヤーの歩く処理
	void Jump(void);												// ジャンプの処理
	void GroundLimit(void);											// 地面の制限
	void Fall(void);												// 急降下
	void Dush(void);												// ダッシュ
	void beam(void);												// ビーム
	D3DXVECTOR3 GetPos(void);
	void bomb(void);												// ボム
	CLife *GetLife(int nNumber);									// ライフの情報
	CCharge *GetCgarge(void);										// チャージのポインタ
	HRESULT ReadFile(void);
private:
	CScore *pScore;								// スコアの情報
	CLife *m_pLife[LIFE_NUM];					// ライフのポインタ
	CCharge *m_pCharge;							// チャージのポインタ
	D3DXVECTOR3 m_pos;							// 座標
	D3DXVECTOR3 m_rot;							// 回転
	D3DXVECTOR3 m_move;							// 移動
	float m_fAngle;								// 角度
	int m_nDushFlame;							// ダッシュのフレーム
	int m_nDushInterCnt;						// ダッシュできないときのカウント
	int m_nPlayerNum;							// プレイヤーの番号
	bool m_bJump;								// ジャンプのフラグ
	bool m_bDush;								// ダッシュの処理
	bool m_bDushInter;							// ダッシュのインターバル
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	static int m_nPlayerAll;					// プレイヤーの数
	CModelAnime *m_apModelAnime[MODEL_PARTS];	//モデルパーツ用のポインタ
	int m_nNumKey;								//キーの総数
	int m_nKey;									//現在キーのNo
	int m_nCountMotion;							//モーションカウンター
	KEY_INFO *m_apKeyInfo;						//キー情報のポインタ
	MOTION_STATE m_MotionState;
	Motion_Info m_Motion[M_MOTION_STATE_MAX];
	int m_nFlame;
};

#endif