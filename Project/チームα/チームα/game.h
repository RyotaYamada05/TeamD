#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// �}�N����`
//***************************************************************************************
#ifdef VIIEW_PORT_TEST
#endif // VIIEW_PORT_TEST
#define MAX_PLAYER (2)			// �v���C���[�̐�

//***************************************************************************************
// �O���錾
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CMeshShape;
class CBg;
class CPlayer;
class CTime;
class CUi;
class CUiStart;
class CLockon;
class CBill;
class CContinue;
class CUiEnd;
//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	static CGame* Create();
	static CCamera *GetCamera(int nCount);
	static CLight *GetLight(void);
	static CPlayer *GetPlayer(int nCount);
	static CTime *GetTime(void);
	static CMeshShape*GetSphere();
	static CUi *GetUi(void);
	static CUiStart *GetUiStart(void);
	static CUiEnd *GetUiEnd(void);
	static CLockon *GetLockon(void);
	static CBill *GetBill(void);
	static CContinue *GetContinue(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	
	static CCamera *m_apCamera[MAX_PLAYER];		// �J�����̃|�C���^	
	static CLight *m_pLight;					// ���C�g�̃|�C���^
	static CMeshField *m_pMeshField;			// ���b�V���t�B�[���h�̃|�C���^
	static CMeshShape * m_pSphere;					// ���b�V���X�t�B�A�̃|�C���^
	static CBg *m_pBg;							// �w�i�̃|�C���^
	static CPlayer *m_apPlayer[MAX_PLAYER];		// �v���C���[�̃|�C���^
	static CTime *m_pTime;						// �^�C���̃|�C���^
	static CUi *m_pUi;							// ui�̃|�C���^
	static CUiStart *m_pUiStart;				// uistart�̃|�C���^
	static CUiEnd *m_pUiEnd;					// uiend�̃|�C���^
	static CLockon *m_pLockon;					// ���b�N�I���̃|�C���^
	static CBill *m_pBill;						// �r���̃|�C���^
	static CContinue *m_pContinue;
	LPD3DXFONT m_pFont;
};
#endif