#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=====================================================
//
// ���b�V���t�B�[���h�̃N���X [meshfield.h]
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
#define FIELD_WIDTH					(4)
#define FIELD_HEIGHT				(4)
#define FIELD_WIDTH_SIZE			(10000.0f)
#define FIELD_HEIGHT_SIZE			(10000.0f)

#define FIELD_WIDTH_SIZE_TUTORIAL	(300.0f)
#define FIELD_HEIGHT_SIZE_TUTORIAL	(300.0f)

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMeshField
{
public:
	CMeshField();			// �R���X�g���N�^
	~CMeshField();			// �f�X�g���N�^

	void Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// �����i��]�j
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nNumVertex;							// �����_��
	int m_nNumIndex;					// ���C���f�b�N�X��
	int m_nNumPolygon;					// ���|���S����
	float m_fOne_SizeW;
	float m_fOne_SizeH;
};


#endif
