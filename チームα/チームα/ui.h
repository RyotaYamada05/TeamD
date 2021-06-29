//=============================================================================
//
// ui���� [ui.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
//���C�t
#define UI_LIFE_SIZE_X				(405.0f)	// ���C�tUI��X�T�C�Y
#define UI_LIFE_SIZE_PLAYERY		(22.0f)		// �v���C���[���C�tUI��Y�T�C�Y
#define UI_LIFE_SIZE_ENEMYY			(11.2)		// �G�l�~�[���C�tUI��Y�T�C�Y
//�^�C��
#define UI_TIME_SIZE_X				(85.0f)		// �^�C��UI��X�T�C�Y
#define UI_TIME_SIZE_Y				(40.0f)		// �^�C��UI��Y�T�C�Y
//�v���C���[�E�G�l�~�[�̕���
#define UI_PLAYER_SIZE_X			(50.0f)		// �v���C���[UI��X�T�C�Y
#define UI_PLAYER_SIZE_Y			(15.0f)		// �v���C���[UI��Y�T�C�Y
#define UI_ENEMY_SIZE_X				(45.0f)		// �G�l�~�[UI��X�T�C�Y
#define UI_ENEMY_SIZE_Y				(10.0f)		// �G�l�~�[UI��Y�T�C�Y
//HIT
#define UI_HIT_SIZE_X				(100.0f)	// �q�b�gUI��X�T�C�Y
#define UI_HIT_SIZE_Y				(50.0f)		// �q�b�gUI��Y�T�C�Y
#define UI_HIT_POS_LEFT_X			(320.0f)	// �q�b�gUI�̍�����X��
#define UI_HIT_POS_RIGHT_X			(960.0f)	// �q�b�gUI�̉E����X��
#define UI_HIT_POS_Y				(600.0f)	// �q�b�gUI��Y�T�C�Y
//WIN��LOSE
#define UI_RESULT_SIZE_X			(200.0f)	// ���s������X�T�C�Y
#define UI_RESULT_SIZE_Y			(30.0f)		// ���s������Y�T�C�Y
#define UI_RESULT_POS_LEFT_X		(320.0f)	// ���s�����o��X���i�����j
#define UI_RESULT_POS_RIGHT_X		(960.0f)	// ���s�����o��X���i�E���j
#define UI_RESULT_POS_Y				(360.0f)	// ���s�����o���ꏊ��Y��
//�W��
#define UI_LOCKON_SIZE_SMALL_X		(40.0f)		// ���b�N�I����X�T�C�Y
#define UI_LOCKON_SIZE_SMALL_Y		(40.0f)		// ���b�N�I����Y�T�C�Y
#define UI_LOCKON_POS_LEFT_X		(320.0f)	// ���b�N�I���̍�����X��
#define UI_LOCKON_POS_RIGHT_X		(960.0f)	// ���b�N�I���̉E����X��
#define UI_LOCKON_POS_Y				(360.0f)	// ���b�N�I����Y��

//WINMark
#define UI_WINMARK_SIZE_X			(15.0f)		// WINMark��X�T�C�Y
#define UI_WINMARK_SIZE_Y			(15.0f)		// WINMark��X�T�C�Y
#define UI_WINMARK_POS_LEFT1_X		(50.0f)
#define UI_WINMARK_POS_LEFT2_X		(85.0f)
#define UI_WINMARK_POS_RIGHT1_X		(790.0f)
#define UI_WINMARK_POS_RIGHT2_X		(825.0f)
#define UI_WINMARK_POS_Y			(100.0f)

//���
#define UI_TYPE					(12)		// UI�̎�ނ̍ő吔

//=============================================================================
//�N���X�錾
//=============================================================================
class CUi :public CScene2d
{
public:
	typedef enum
	{
		UITYPE_NONE = -1,
		UITTYPE_LIFE,			// ���C�t�o�[
		UITYPE_TIME,			// �^�C���o�[
		UITYPE_PLAYER,			// �v���C���[����
		UITYPE_ENEMY,			// �G�l�~�[����
		UITYPE_HIT,				// �q�b�g����
		UITYPE_WIN,				// WIN����
		UITYPE_LOSE,			// LOSE����
		UITYPE_STANDARD,		// �W���\��
		UYTYPE_WINMARKFRAME,	// �����̘g
		UYTYPE_WINMARK,			// �������}�[�N
		UYTYPE_CONTINUE,	// CONTINUE����
		UITYPE_DRAW,		// ��������
		UITYPE_MAX
	}UITYPE;

	CUi();
	~CUi();

	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UiHit(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UI_TYPE];
	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	UITYPE		m_type;		// �|���S���̃^�C�v
	int m_nCounter;			// �J�E���^�[
	int m_nPattern;			// �g�p���Ă��邩�ǂ���
	static int m_nUi;
	
};

#endif // !_UI_H_
