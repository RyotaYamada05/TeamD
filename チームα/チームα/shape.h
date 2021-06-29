#ifndef _SHAPE_H_
#define _SHAPE_H_

//=====================================================
//
// �����b�V���̃N���X [shape.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
//#define FIELD_WIDTH					(4)
//#define FIELD_HEIGHT				(4)
//#define FIELD_WIDTH_SIZE			(10000.0f)
//#define FIELD_HEIGHT_SIZE			(10000.0f)
//
//#define FIELD_WIDTH_SIZE_TUTORIAL	(300.0f)
//#define FIELD_HEIGHT_SIZE_TUTORIAL	(300.0f)
//
//#define MAX_MESHFIELD_TEXTURE		(1)				// �e�N�X�`���̐�

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMeshShape : public CModel
{
public:
	CMeshShape();			// �R���X�g���N�^
	~CMeshShape();			// �f�X�g���N�^

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static CMeshShape*Create(void);		// ���b�V���t�B�[���h
	static HRESULT Load(void);			// �e�N�X�`�����[�h
	static void UnLoad(void);			// �e�N�X�`���A�����[�h
	D3DXVECTOR3 GetPos(void);
private:
	static LPD3DXMESH m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;					// �}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_MESHFIELD_TEXTURE];	// �e�N�X�`�����̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_move;						// �ړ�
};


#endif
