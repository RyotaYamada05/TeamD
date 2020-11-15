#ifndef _SEA_H_
#define _SEA_H_

//=====================================================
//
// �C�i���b�V���t�B�[���h�j�̃N���X [sea.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SEA_WIDTH					(4)
#define SEA_HEIGHT				(4)
#define SEA_WIDTH_SIZE			(50000.0f)
#define SEA_HEIGHT_SIZE			(50000.0f)
#define SEA_HEIGHT_POS_Y		(-500.0f)

#define MAX_SEA_TEXTURE		(1)				// �e�N�X�`���̐�

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CSea
{
public:
	CSea();			// �R���X�g���N�^
	~CSea();			// �f�X�g���N�^

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static CSea*Create(void);		// ���b�V���t�B�[���h
	static HRESULT Load(void);			// �e�N�X�`�����[�h
	static void UnLoad(void);			// �e�N�X�`���A�����[�h
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SEA_TEXTURE];	// �e�N�X�`�����̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR3 m_rot;												// �����i��]�j
	D3DXMATRIX m_mtxWorld;											// ���[���h�}�g���b�N�X
	int m_nNumVertex;												// �����_��
	int m_nNumIndex;												// ���C���f�b�N�X��
	int m_nNumPolygon;												// ���|���S����
	float m_fOne_SizeW;
	float m_fOne_SizeH;
};


#endif
