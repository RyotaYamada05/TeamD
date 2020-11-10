#ifndef _SAND_H_
#define _SAND_H_
//=============================================================================
//
// ���̃N���X�w�b�_�[ [sand.h]
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
#define SAND_SIZE_X			(3)			// ���̃T�C�Y
#define SAND_SIZE_Z			(3)			// ���̃T�C�Y
#define SAND_SIZE_Y			(3)			// ���̃T�C�Y

#define MAX_SAND_TEXTURE	(1)			// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CSand : public CModel
{
public:
	CSand();		// �R���X�g���N�^
	~CSand();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);	// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CSand *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		 D3DXVECTOR3 rot, D3DXVECTOR3 size);												// �C���X�^���X����
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h

	void ScaleUp(void);													// �g��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SAND_TEXTURE];	// �e�N�X�`�����̃|�C���^
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
