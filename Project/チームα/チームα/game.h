//=============================================================================
//
// 処理 [game.h]
// Author : 伊藤　航
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// 前方宣言
//***************************************************************************************
class CCamera;
class CLight;
class CTurn;
class CDarts;
class CMeshField;

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
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CMeshField *m_pMeshField;
	CDarts *m_pDarts;
	CTurn *m_pTurn;
	LPD3DXFONT m_pFont;
};

#endif // !_GAME_H_