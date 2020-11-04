//=============================================================================
//
//  [title.h]
// Author : �ɓ��@�q
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_
//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

class CScene2d;
class CTitlelogo;

//***************************************************************************************
// �}�N����`
//***************************************************************************************
#define MAX_TITLE (3)

//***************************************************************************************
// �^�C�g���N���X
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
	
	static CTitlelogo *GetLogo(int nCount) { return m_apTitlelogo[nCount]; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[1];	//�e�N�X�`���ւ̃|�C���^
	CScene2d* m_pScene;	//�|�C���^
	bool m_bModechenge;
	static CTitlelogo *m_apTitlelogo[MAX_TITLE];			//�^�C�g�����S�̃|�C���^
};

#endif // !_TITEL_H_