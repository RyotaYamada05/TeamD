#ifndef _BEAM_H_
#define _BEAM_H_
//=============================================================================
//
// �r�[���̃N���X�w�b�_�[ [beam.h]
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
#define BEAM_SIZE_X				(1)		// �r�[���̃T�C�Y
#define BEAM_SIZE_Y				(1)		// �r�[���̃T�C�Y
#define BEAM_SIZE_Z				(1)		// �r�[���̃T�C�Y
#define BEAM_SPEED				(70)	// �r�[���̃X�s�[�h

#define MAX_BEAM_TEXTURE		(1)		// �e�N�X�`���̐�

//=============================================================================
// �w�i�N���X
//=============================================================================
class CBeam : public CBullet2
{
public:
	CBeam();		// �R���X�g���N�^
	~CBeam();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, 
		D3DXVECTOR3 size, BULLET2_USER user);							// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CBeam *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
		D3DXVECTOR3 size, BULLET2_USER user);							// �C���X�^���X����
	static HRESULT Load(void);											// �e�N�X�`�����[�h
	static void UnLoad(void);											// �e�N�X�`���A�����[�h

private:
	D3DXVECTOR3 m_move;											// �ړ���
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BEAM_TEXTURE];	// �e�N�X�`�����̃|�C���^
	static LPD3DXMESH m_pMesh;									// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;								// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;										// �}�e���A�����
};

#endif
