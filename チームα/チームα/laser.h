#ifndef _LASER_H_
#define _LASER_H_
//=============================================================================
//
// ���[�U�[�̃N���X�w�b�_�[ [beam.h]
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
#define LASER_SIZE_X			(6)		// �r�[���̃T�C�Y
#define LASER_SIZE_Y			(5)		// �r�[���̃T�C�Y
#define LASER_SIZE_Z			(6)		// �r�[���̃T�C�Y
#define LASER_SPEED				(200)	// �r�[���̃X�s�[�h

#define MAX_LASER_TEXTURE		(1)		// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CLaser : public CBullet2
{
public:
	CLaser();		// �R���X�g���N�^
	~CLaser();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 size, BULLET2_USER user);							// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	void Scale(void);													// �g�k
	static CLaser *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
	D3DXVECTOR3 rot, D3DXVECTOR3 size, BULLET2_USER user);				// �C���X�^���X����
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LASER_TEXTURE];	// �e�N�X�`�����̃|�C���^
	static LPD3DXMESH m_pMesh;									// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����
	float m_fFlash;												// �_�ŗp
	float m_fFlashNum;											// �_�ŗp�̒l
	float m_fScale;												// �g��p
	float m_fScaleNum;											// �g��p�̒l
	float m_fSizeZ;												// ���[�U�[�̒���
};

#endif
