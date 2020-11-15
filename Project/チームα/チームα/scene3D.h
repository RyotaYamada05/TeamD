//=============================================================================
//
// ���C������ [scene3D.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=========================================================================
//�C���N���[�h�t�@�C��
//=========================================================================
#include "scene.h"

#define SIZE_X (300.0f)
#define SIZE_Z (300.0f)

//=========================================================================
//3D�|���S���N���X
//=========================================================================
class CScene3D :public CScene
{
public:
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CScene3D(int nPriority = PRIORITY_0);
	virtual ~CScene3D();

	static CScene3D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ������
	virtual void Uninit(void);												// �I��
	virtual void Update(void);												// �X�V
	virtual void Draw(void);												// �`��

	void SetPos(D3DXVECTOR3 pos);											// ���W�̐ݒ�
	void SetPosision(D3DXVECTOR3 pos);										// ���W�̍X�V
	void SetColor(D3DXCOLOR col);											// �J���[�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);											// �p�x�̐ݒ�
	void Alpha(void);														// �����x
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);							// �e�N�X�`���̐ݒ�

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);								// �o�b�t�@���
	D3DXVECTOR3 GetPos(void);												// ���W
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�|�C���^
	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���N�X
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_size;							// �T�C�Y
	D3DXVECTOR3 m_rot;							// ����
};
#endif