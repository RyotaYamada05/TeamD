#ifndef _MISSILE_H_
#define _MISSILE_H_
//=============================================================================
//
// �r�[���̃N���X�w�b�_�[ [missile.h]
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
#define MISSILE_SIZE_X				(1)		// �~�T�C���̃T�C�Y
#define MISSILE_SIZE_Y				(1)		// �~�T�C���̃T�C�Y
#define MISSILE_SIZE_Z				(1)		// �~�T�C���̃T�C�Y
#define MISSILE_SPEED				(100)	// �~�T�C���̃X�s�[�h

#define MAX_MISSILE_TEXTURE			(1)		// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CMissile : public CBullet2
{
public:
	CMissile();		// �R���X�g���N�^
	~CMissile();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 size, BULLET2_USER user);							// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CMissile *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		D3DXVECTOR3 size, BULLET2_USER user);							// �C���X�^���X����
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_MISSILE_TEXTURE];	// �e�N�X�`�����̃|�C���^
	static LPD3DXMESH m_pMesh;									// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����
};

#endif
