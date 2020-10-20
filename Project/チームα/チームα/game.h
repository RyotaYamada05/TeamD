#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// ゲームの処理 [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// マクロ定義
//***************************************************************************************
#define MAX_PLAYER (2)			// プレイヤーの数

//***************************************************************************************
// 前方宣言
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	static CGame* Create();
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CPlayer *GetPlayer(int nCount);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CCamera *m_pCamera;					// カメラのポインタ
	static CLight *m_pLight;					// ライトのポインタ
	static CMeshField *m_pMeshField;			// メッシュフィールドのポインタ
	static CBg *m_pBg;							// 背景のポインタ
	static CPlayer *m_apPlayer[MAX_PLAYER];		// プレイヤーのポインタ
	LPD3DXFONT m_pFont;
};

#endif // !_GAME_H_