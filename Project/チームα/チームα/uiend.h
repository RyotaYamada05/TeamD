//=============================================================================
//
// �I������ui���� [uiend.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _UIEND_H_
#define _UIEND_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
//continue
#define UI_CONTINUE_SIZE_X			(200.0f)	// CONTINUE��X�T�C�Y
#define UI_CONTINUE_SIZE_Y			(30.0f)		// CONTINUE��Y�T�C�Y
#define UI_CONTINUE_POS_X			(640.0f)	// CONTINUE�̉E����X��
#define UI_CONTINUE_POS_Y			(240.0f)	// CONTINUE��Y��
//���
#define UIEND_TYPE					(2)		// UI�̎�ނ̍ő吔
//=============================================================================
//�N���X�錾
//=============================================================================
class CUiEnd : public CScene2d
{
public:
	typedef enum
	{
		UIENDTYPE_NONE = -1,
		UIENDTYPE_CONTINUE,
		UIENDTYPE_THANKS,
		UIENDTYPE_MAX
	}UIENDTYPE;

	CUiEnd();
	~CUiEnd();

	static CUiEnd *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UIENDTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UIENDTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UIEND_TYPE];

	D3DXVECTOR3		m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3		m_move;		// �|���S���̈ړ���
	D3DXVECTOR3		m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR		m_col;		// �J���[
	UIENDTYPE		m_type;		// �|���S���̃^�C�v
	int m_nCount;				// �t���[���J�E���g

};
#endif // !_UI_H_