#ifndef _BOMB_H_
#define _BOMB_H_
//=============================================================================
//
// �{���̃N���X�w�b�_�[ [bomb.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bullet2.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOMB_SIZE_X				(3)		// �{���̃T�C�Y
#define BOMB_SIZE_Y				(3)		// �{���̃T�C�Y
#define BOMB_SIZE_Z				(3)		// �{���̃T�C�Y
#define BOMB_SPEED				(30)	// �{���̃X�s�[�h
#define BOMB_MOVE_Y				(4.0f)	// �{���̃X�s�[�h
#define MAX_BOMB_TEXTURE		(1)		// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CBomb : public CBullet2
{
public:
	CBomb();		// �R���X�g���N�^
	~CBomb();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, BULLET2_USER user);							// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		D3DXVECTOR3 size, BULLET2_USER user);							// �C���X�^���X����

	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h
	void AddRot(void);													// �p�x�����Z

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOMB_TEXTURE];	// �e�N�X�`�����̃|�C���^
	static LPD3DXMESH m_pMesh;									// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����
	int m_fAddRotNum;
};

#endif
