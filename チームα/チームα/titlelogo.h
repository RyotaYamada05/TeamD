//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.h]
// Author : �����D�I
//
//=============================================================================
#ifndef  _TITLELOGO_H_
#define  _TITLELOGO_H_

#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
//�^�C�g�����S
#define TITLE_SIZE_X			(400.0f)	// �^�C�g����X�T�C�Y
#define TITLE_SIZE_Y			(200.0f)		// �^�C�g����Y�T�C�Y
#define TITLE_POS_X				(640.0f)	// �^�C�g����X���W
#define TITLE_POS_Y				(350.0f)	// �^�C�g����Y���W
//UI
#define TITLE_UI_SIZE			(700.0f)	// UI�T�C�Y
#define TITLE_UI_POS_X			(640.0f)	// UI��X���W
#define TITLE_UI_POS_Y			(360.0f)	// UI��Y���W
//PLESS
#define TITLE_PLESS_SIZE_X		(400.0f)	// PLESS��X�T�C�Y
#define TITLE_PLESS_SIZE_Y		(30.0f)		// PLESS��Y�T�C�Y
#define TITLE_PLESS_POS_X		(640.0f)	// PLESS��X���W
#define TITLE_PLESS_POS_Y		(650.0f)	// PLESS��Y���W
//���
#define TITLELOGO_TYPE			(3)			// ���S�̎�ނ̍ő吔

//=============================================================================
//�N���X�錾
//=============================================================================
class CTitlelogo :public CScene2d
{
public:
	typedef enum
	{
		LOGOTYPE_NONE = -1,
		LOGOTIPE_TITLE,			// �^�C�g��
		LOGOTIPE_PRESS,			// �v���X����
		LOGOTIPE_UI,			// UI
		LOGOTYPE_MAX
	}LOGOTYPE;

	CTitlelogo();
	~CTitlelogo();

	static CTitlelogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Flashing(void);
	void Rotation(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TITLELOGO_TYPE];

	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	LOGOTYPE	m_type;		// �|���S���̃^�C�v
	int m_nCounter;			// �J�E���^�[
	int m_nPattern;			// �g�p���Ă��邩�ǂ���

	float m_fRotasion; //��]���x
};
#endif // ! _TITLELOGO_H_
