//=============================================================================
//
// 処理 [bullet.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "billboard.h"

//=============================================================================
//前方宣言
//=============================================================================
class CPlayer;

//=============================================================================
//バレットクラス
//=============================================================================
class CBullet :public CBillboard
{
public:
	//=========================================================================
	//弾の使用者判別用の列挙型
	//=========================================================================
	typedef enum
	{
		BULLET_USER_NONE = -1,
		BULLET_USER_PL1,	//PL1
		BULLET_USER_PL2,	//PL2
		BULLET_USER_MAX		//最大数
	}BULLET_USER;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CBullet();
	~CBullet();

	static CBullet * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET_USER user);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET_USER user);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(void);
	D3DXVECTOR3 VectorMath(D3DXVECTOR3 TargetPos, float fSpeed);
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR3 m_size;	//大きさ
	int m_nAtk;	//攻撃力
	int m_nLife;	//ライフ
	BULLET_USER m_user;	//使用者
	CPlayer * m_pTargetPL;	//敵プレイヤーのポインタ
};

#endif