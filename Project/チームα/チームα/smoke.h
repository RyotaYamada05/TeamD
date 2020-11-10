#ifndef _SMOKE_H_
#define _SMOKE_H_
//=============================================================================
//
// ���̃N���X�w�b�_�[ [smoke.h]
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
#define SMOKE_SIZE_X			(20)			// ���̃T�C�Y
#define SMOKE_SIZE_Z			(20)			// ���̃T�C�Y
#define SMOKE_SIZE_Y			(4)			// ���̃T�C�Y

#define MAX_SMOKE_TEXTURE		(1)			// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CSmoke : public CModel
{
public:
	CSmoke();		// �R���X�g���N�^
	~CSmoke();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);	// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CSmoke *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		D3DXVECTOR3 size);												// �C���X�^���X����
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h

	void ScaleUp(void);													// �g��
	void AddRot(void);													// �p�x�����Z
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SMOKE_TEXTURE];	// �e�N�X�`�����̃|�C���^
	static LPD3DXMESH m_pMesh;									// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����
	D3DXVECTOR3 m_FirstSize;									// �ŏ��̃T�C�Y
	float m_fScale;												// �g�k�p
	float m_fScaleNum;											// �g�k�p�̒l
	float m_fAddRotNum;											// �p�x�̉��Z
	float m_fAlphaNum;											// �����x
};

#endif
