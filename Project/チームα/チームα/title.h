//=============================================================================
//
//  [title.h]
// Author : 伊藤　航
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_
//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

class CScene2d;

//***************************************************************************************
// タイトルクラス
//***************************************************************************************
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	static CTitle* Create(void);
	static HRESULT Load(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[1];	//テクスチャへのポインタ
	CScene2d* m_pScene;	//ポインタ
	bool m_bModechenge;
};

#endif // !_TITEL_H_