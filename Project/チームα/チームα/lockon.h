//=============================================================================
//
// ���b�N�I������ [lockon.h]
// Author : �����D�I
//
//=============================================================================

#ifndef  _LOCKON_H_
#define  _LOCKON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define UI_LOCKON_SIZE_X		(70.0f)		// ���b�N�I����X�T�C�Y
#define UI_LOCKON_SIZE_Y		(70.0f)		// ���b�N�I����Y�T�C�Y

//=============================================================================
//�N���X�錾
//=============================================================================
class CLockon :public CScene2d
{
public:
	//�P�o�ƂQ�o�̃^�C�v����
	typedef enum
	{
		LOCKONTYPE_NONE = -1,
		LOCKONTYPE_FAST_PLAYER,		//�P�o���\��
		LOCKONTYPE_SECOND_PLAYER,	//�Q�o���葤�\��
		LOCKONTYPE_PLAYER_MAX
	}LOCKONTYPE;

	CLockon();
	~CLockon();

	static CLockon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOCKONTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOCKONTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3 m_move;		// �|���S���̈ړ���
	D3DXVECTOR3 m_size;		// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;		// �J���[
	LOCKONTYPE m_type;
	int m_nLockCounter;		// ���b�N�I���J�E���^�[
	int m_nLockPattern;		// ���b�N�I���̃p�^�[��
	static int m_nLockon;

};
#endif // ! _LOCKON_H_

