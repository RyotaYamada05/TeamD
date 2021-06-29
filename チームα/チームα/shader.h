#ifndef _SHADER_H_
#define _SHADER_H_

//====================================================================
//
// �V�F�[�_�̏����w�b�_�[	[shader.h]
// Author : Konishi Yuuto
//
//====================================================================

//====================================================================
// �C���N���[�h
//====================================================================
#include "main.h"

//====================================================================
// �V�F�[�_�N���X
//====================================================================
class CShader
{
public:
	CShader();							// �R���X�g���N�^
	~CShader();							// �f�X�g���N�^

	BOOL Init();					// ����������
	void Draw(D3DXMATRIX Matrix);		// �`�揈��
	void Delete(void);					// ����

private:
	// �\���̐錾
	typedef struct _VERTEX
	{
		D3DXVECTOR3 m_Pos;
	}VERTEX;	

	LPDIRECT3DVERTEXBUFFER9 m_pBuffer;			// ���_�p�o�b�t�@
	LPD3DXEFFECT m_pShader;						// �V�F�[�_�f�[�^
	D3DXHANDLE m_Tech;							// �e�N�j�b�N�ւ̃n���h��
	D3DXHANDLE m_Matrix;						// �V�F�[�_�̃O���[�o���ϐ��p�n���h��(�}�g���N�X)
	D3DXHANDLE m_Color;							// �V�F�[�_�̃O���[�o���ϐ��p�n���h��(�J���[)
	LPDIRECT3DVERTEXDECLARATION9 m_pDecl;		// ���_�f�N�����[�V�����ւ̃|�C���^

};

#endif