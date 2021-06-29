//=============================================================================
//
// ui���� [ui.h]
// Author : �����D�I
//
//=============================================================================

#ifndef  _UIPAUSE_H_
#define  _UIPAUSE_H_

#include "scene2d.h"
#include "uistart.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define UIPAUSE_SIZE_X			(300.0f)
#define UIPAUSE_SIZE_Y			(50.0f)
#define UIPAUSE_START_POS_X		(640.0f)
#define UIPAUSE_START_POS_Y		(340.0f)
#define UIPAUSE_TITLE_POS_X		(640.0f)
#define UIPAUSE_TITLE_POS_Y		(540.0f)


//=============================================================================
//�N���X�錾
//=============================================================================
class CUiPause :public CScene2d
{
public:
	typedef enum
	{
		UIPAUSETYPE_NONE = -1,
		UIPAUSETYPE_START,
		UIPAUSETYPE_TITLE,
		UIPAUSETYPE_MAX
	}UIPAUSETYPE;

	CUiPause();
	~CUiPause();

	static CUiPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, UIPAUSETYPE type);
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, UIPAUSETYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Select(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UISTART_TYPE];

	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	UIPAUSETYPE		m_type;		// �|���S���̃^�C�v
};
#endif // ! _UIPAUSE_H_
