//=============================================================================
//
// ���� [game.h]
// Author : �ɓ��@�q
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// 
//***************************************************************************************
class CCamera;
class CLight;
class CTurn;
class CDarts;
class CLife;
//***************************************************************************************
// �C���N���[�h�t�@�C��
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
	CDarts *m_pDarts;
	CTurn *m_pTurn;
	LPD3DXFONT m_pFont;
};

#endif // !_GAME_H_