#ifndef _BG_H_
#define _BG_H_
//=============================================================================
//
// �Q�[���w�i�̏��� [bg.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BG_SIZE_X				(1000)
#define BG_SIZE_Y				(500)
#define BG_SIZE_Z				(1000)
#define MAX_BG_TEXTURE			(1)

//=============================================================================
// �w�i�N���X
//=============================================================================
class CBg : public CModel
{
public:
	CBg();		// �R���X�g���N�^
	~CBg();		// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CBg *Create(void);		// �C���X�^���X����
	static HRESULT Load(void);		// �e�N�X�`�����[�h
	static void UnLoad(void);		// �e�N�X�`���A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE];	// �e�N�X�`�����̃|�C���^
	D3DXVECTOR3 m_pos;										// ���݂̈ʒu
	D3DXVECTOR3 m_rot;										// ���݂̊p�x
	D3DXVECTOR3 m_size;										// �傫��
	D3DXMATRIX m_mtxWorld;									// �s��v�Z�p
	static LPD3DXMESH m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;					// �}�e���A�����̐�
};

#endif
