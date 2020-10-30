//=============================================================================
//
// 弾の処理(モデル派生) [bullet2.h]
// Author : Konishi Yuuto
//
//=============================================================================
#ifndef _BULLET2_H_
#define _BULLET2_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;

//=============================================================================
//バレットクラス
//=============================================================================
class CBullet2 :public CModel
{
public:
	//=========================================================================
	//弾の使用者判別用の列挙型
	//=========================================================================
	typedef enum
	{
		BULLET2_USER_NONE = -1,
		BULLET2_USER_PL1,	//PL1
		BULLET2_USER_PL2,	//PL2
		BULLET2_USER_MAX		//最大数
	}BULLET2_USER;

	CBullet2();		// コンストラクタ
	~CBullet2();	// デストラクタ

	static CBullet2 * Create(const D3DXVECTOR3 pos,			// ポリゴン生成
		const D3DXVECTOR3 size, const BULLET2_USER user);

	HRESULT Init(const D3DXVECTOR3 pos,						// 初期化処理
		const D3DXVECTOR3 size, const BULLET2_USER user);
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	bool Collision(void);									// 当たり判定
	D3DXVECTOR3 VectorMath(D3DXVECTOR3 TargetPos,			// 追従
		float fSpeed);
	void SetLife(int nLife);								// 体力の設定
	void SetMove(D3DXVECTOR3 move);							// 移動量加算

	D3DXVECTOR3 GetMove(void);								// 移動量の更新
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_size;		// 大きさ
	int m_nAtk;				// 攻撃力
	int m_nLife;			// ライフ
	BULLET2_USER m_user;	// 使用者
	CPlayer *m_pTargetPL;	//敵プレイヤーのポインタ
	int m_nCounter;
	float m_fSpeed;			// 速さ
};

#endif 