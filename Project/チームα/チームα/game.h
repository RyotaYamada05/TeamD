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
// �O���錾
//***************************************************************************************
class CCamera;
class CLight;
class CTurn;
class CDarts;
class CMeshField;

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
	static CMeshField *m_pMeshField;
	CDarts *m_pDarts;
	CTurn *m_pTurn;
	LPD3DXFONT m_pFont;
};

#endif // !_GAME_H_