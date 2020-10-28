//================================================
//
// ui���� [ui.h]
// Author : �����D�I
//
//================================================

#ifndef _UI_H_
#define _UI_H_

#include "scene2d.h"

//================================================
//�}�N����`
//================================================
#define UI_LIFE_SIZE_X			(405.0f)	//���C�tUI��X�T�C�Y
#define UI_LIFE_SIZE_PLAYERY	(22)	//�v���C���[���C�tUI��Y�T�C�Y
#define UI_LIFE_SIZE_ENEMYY		(11.2f)	//�G�l�~�[���C�tUI��Y�T�C�Y
#define UI_TIME_SIZE_X			(85)	//�^�C��UI��X�T�C�Y
#define UI_TIME_SIZE_Y			(40)	//�^�C��UI��Y�T�C�Y
#define UI_PLAYER_SIZE_X		(50)	//�v���C���[UI��X�T�C�Y
#define UI_PLAYER_SIZE_Y		(15)	//�v���C���[UI��Y�T�C�Y
#define UI_ENEMY_SIZE_X			(45)	//�G�l�~�[UI��X�T�C�Y
#define UI_ENEMY_SIZE_Y			(10)	//�G�l�~�[UI��Y�T�C�Y
#define UI_HIT_SIZE_X			(100)	//�q�b�gUI��X�T�C�Y
#define UI_HIT_SIZE_Y			(50)	//�q�b�gUI��Y�T�C�Y
#define UI_TYPE					(9)		//UI�̎�ނ̍ő吔

//================================================
//�N���X�錾
//================================================
class CUi :public CScene2d
{
public:
	typedef enum
	{
		UITYPE_NONE=0,
		UITTYPE_LIFE,	//���C�t�o�[
		UITYPE_TIME,	//�^�C���o�[
		UITYPE_PLAYER,	//�v���C���[����
		UITYPE_ENEMY,	//�G�l�~�[����
		UITYPE_HIT,		//�q�b�g����
		UITYPE_WIN,		//WIN����
		UITYPE_LOSE,	//LOSE����
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

	D3DXVECTOR3	m_pos;	// �|���S���̈ʒu
	D3DXVECTOR3 m_move;	// �|���S���̈ړ���
	D3DXVECTOR3 m_size;	// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;	// �J���[
	UITYPE		m_type;	// �|���S���̃^�C�v
	int m_nCounter;		// �J�E���^�[
	int m_nPattern;		// �g�p���Ă��邩�ǂ���
};

#endif // !_UI_H_
