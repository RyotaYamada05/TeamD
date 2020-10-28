//================================================
//
// ui処理 [ui.h]
// Author : 佐藤颯紀
//
//================================================

#ifndef _UI_H_
#define _UI_H_

#include "scene2d.h"

//================================================
//マクロ定義
//================================================
#define UI_LIFE_SIZE_X			(405.0f)	//ライフUIのXサイズ
#define UI_LIFE_SIZE_PLAYERY	(22)	//プレイヤーライフUIのYサイズ
#define UI_LIFE_SIZE_ENEMYY		(11.2f)	//エネミーライフUIのYサイズ
#define UI_TIME_SIZE_X			(85)	//タイムUIのXサイズ
#define UI_TIME_SIZE_Y			(40)	//タイムUIのYサイズ
#define UI_PLAYER_SIZE_X		(50)	//プレイヤーUIのXサイズ
#define UI_PLAYER_SIZE_Y		(15)	//プレイヤーUIのYサイズ
#define UI_ENEMY_SIZE_X			(45)	//エネミーUIのXサイズ
#define UI_ENEMY_SIZE_Y			(10)	//エネミーUIのYサイズ
#define UI_HIT_SIZE_X			(100)	//ヒットUIのXサイズ
#define UI_HIT_SIZE_Y			(50)	//ヒットUIのYサイズ
#define UI_TYPE					(9)		//UIの種類の最大数

//================================================
//クラス宣言
//================================================
class CUi :public CScene2d
{
public:
	typedef enum
	{
		UITYPE_NONE=0,
		UITTYPE_LIFE,	//ライフバー
		UITYPE_TIME,	//タイムバー
		UITYPE_PLAYER,	//プレイヤー文字
		UITYPE_ENEMY,	//エネミー文字
		UITYPE_HIT,		//ヒット文字
		UITYPE_WIN,		//WIN文字
		UITYPE_LOSE,	//LOSE文字
		UITYPE_MAX
	}UITYPE;
	CUi();
	~CUi();

	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UiHit(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UI_TYPE];

	D3DXVECTOR3	m_pos;	// ポリゴンの位置
	D3DXVECTOR3 m_move;	// ポリゴンの移動量
	D3DXVECTOR3 m_size;	// ポリゴンのサイズ
	D3DXCOLOR   m_col;	// カラー
	UITYPE		m_type;	// ポリゴンのタイプ
	int m_nCounter;		// カウンター
	int m_nPattern;		// 使用しているかどうか
};

#endif // !_UI_H_
