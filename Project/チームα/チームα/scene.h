//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define MAX_NUM 2056	//最大数

//=============================================================================
//オブジェクトクラス
//=============================================================================
class CScene
{
public:
	//=========================================================================
	//列挙型
	//=========================================================================
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,	//プレイヤータイプ
		OBJTYPE_SPHERE,	//球タイプ
		OBJTYPE_BULLET,	//バレットタイプ
		OBJTYPE_MODEL,	// モデル
		OBJTYPE_PAUSE,
		OBJTYPE_MAX	//オブジェクトタイプの最大数
	}OBJTYPE;	//オブジェクトタイプ

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CScene();
	virtual ~CScene();
	static void ReleaseAll(void);
	static void AllUpdate(void);
	static void AllDraw(void);

	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void SetObjType(const OBJTYPE objtype);
	OBJTYPE GetObjType(void)const;
	static CScene *GetScene(int nNum);
	static void GetPause(bool Pause);

protected:
	void Release(void);

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static CScene *m_apScene[MAX_NUM];	//オブジェクトクラスのポインタ配列
	static int m_nNumAll;	//総数
	int m_nID;	//ナンバーの保存
	OBJTYPE m_ObjType;	//オブジェクトの種類
	static bool m_bPause;
};

#endif