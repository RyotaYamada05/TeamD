//=============================================================================
//
// タイム処理 [time.h]
// Author : 佐藤颯紀
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;

//=============================================================================
// マクロ定義
//=============================================================================
#define TIME_LIMIT		(8000)	//制限時間
#define MAX_TIME		(4)		//桁数
#define TIME_S_SIZE_X	(50)	//数字のＸサイズ
#define TIME_S_SIZE_Y	(50)	//数字のＹサイズ
#define TIME_MS_SIZE_X	(30)	//ミリ秒数字のＸサイズ
#define TIME_MS_SIZE_Y	(30)	//ミリ秒数字のＹサイズ
#define TIME_INTERVAL	(50)	//数字の置く間隔

//================================================
//クラス宣言
//================================================
class CTime : public CScene
{
public:
	CTime();
	~CTime();
	static CTime *Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(int nValue);
	void SetTime(int nTime) { m_nTime = nTime; }
	int GetTime(void) { return m_nTime; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;					//ポリゴンの位置
	CNumber	*m_apNumber[MAX_TIME];		//数字の配置
	int m_nTime;						//タイム
	int m_nTimeCount;					//タイムのカウンター


};
#endif