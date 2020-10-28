#ifndef _SHOCK_H_
#define _SHOCK_H_
//=============================================================================
//
// �Ռ����f���̃N���X�w�b�_�[ [shock.h]
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
#define SHOCK_SIZE_X			(3)			// �����̃T�C�Y
#define SHOCK_SIZE_Y			(2)			// �����̃T�C�Y
#define SHOCK_SIZE_Z			(3)			// �����̃T�C�Y

#define SHOCK_SPEED				(70)		// �r�[���̃X�s�[�h
#define MAX_SHOCK_TEXTURE		(1)			// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CShock : public CModel
{
public:
	CShock();		// �R���X�g���N�^
	~CShock();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);	// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CShock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
		D3DXVECTOR3 size);												// �C���X�^���X����
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h

	void ScaleUp(void);													// �g��
	void AddRot(void);													// �p�x�����Z
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SHOCK_TEXTURE];	// �e�N�X�`�����̃|�C���^
	static LPD3DXMESH m_pMesh;									// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����
	D3DXVECTOR3 m_FirstSize;									// �ŏ��̃T�C�Y
	float m_fScale;												// �g�k�p
	float m_fScaleNum;											// �g�k�p�̒l
	float m_fAddRotNum;											// �p�x�̉��Z
};

#endif
