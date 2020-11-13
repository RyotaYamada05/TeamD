//=============================================================================
//
// ui���� [ui.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _UISTART_H_
#define _UISTART_H_

#include "ui.h"

//=============================================================================
//�}�N����`
//=============================================================================
//ready
#define UI_READY_SIZE_X			(200.0f)	// READY��X�T�C�Y
#define UI_READY_SIZE_Y			(30.0f)		// READY��Y�T�C�Y
#define UI_READY_POS_LEFT_X		(320.0f)	// READY�̍�����X��
#define UI_READY_POS_RIGHT_X	(960.0f)	// READY�̉E����X��
#define UI_READY_POS_Y			(240.0f)	// READY��Y��
//round
#define UI_ROUND_SIZE_X			(150.0f)	// READY��X�T�C�Y
#define UI_ROUND_SIZE_Y			(20.0f)		// READY��Y�T�C�Y
#define UI_ROUND_POS_LEFT_X		(280.0f)	// READY�̍�����X��
#define UI_ROUND_POS_RIGHT_X	(920.0f)	// READY�̉E����X��
#define UI_ROUND_POS_Y			(180.0f)	// READY��Y��
//���
#define UISTART_TYPE					(6)		// UI�̎�ނ̍ő吔
//=============================================================================
//�N���X�錾
//=============================================================================
class CUiStart : public CScene2d
{
public:
	typedef enum 
	{
		UISTARTTYPE_NONE = -1,
		UISTARTTYPE_READY,
		UISTARTTYPE_ROUND_1,
		UISTARTTYPE_ROUND_2,
		UISTARTTYPE_ROUND_3,
		UISTARTTYPE_MAX
	}UISTARTTYPE;

	CUiStart();
	~CUiStart();

	static CUiStart *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UISTARTTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UISTARTTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UISTART_TYPE];

	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	UISTARTTYPE		m_type;		// �|���S���̃^�C�v
};
#endif // !_UI_H_