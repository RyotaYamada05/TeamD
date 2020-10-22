//=============================================================================
// 
// ライフゲージ処理(life.h)
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef  _LIFE_H_
#define  _LIFE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gauge.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_LIFE  (400)	//ライフの最大数
#define HALF_LIFE (200) //ライフの半分
//=============================================================================
//クラス宣言
//=============================================================================
class CLife :public CGauge
{
public:
	//１Ｐと２Ｐライフのタイプ分け
	typedef enum
	{
		LIFETYPE_NON = 0,
		LIFETYPE_FAST_PLAYER,		//１Ｐ側表示
		LIFETYPE_SECOND_PLAYER,		//２Ｐ相手側表示
		LIFETYPE_PLAYER_MAX
	}LIFETYPE;

	CLife();
	~CLife();
	static CLife* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Decrease(int CounterLife,bool Life, LIFETYPE type);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_size;	//サイズ
	D3DXCOLOR   m_col;	//カラー
	LIFETYPE    m_type;	//ライフの種類
	LIFETYPE	m_typeDecrease;	//ダメージの受けた方の種類

	int m_nCounter;		//カウンター
	int m_nMaxLife;		//最大ライフ
	int m_nLife;		//ライフ

	int m_nCounterLife;
	int m_nCount;
	bool m_bLife;

};
#endif // ! _LIFE_H_
