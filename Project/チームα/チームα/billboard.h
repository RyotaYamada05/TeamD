#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.h]
// Author : �����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "scene3D.h"

//=====================================================
// �}�N����`
//=====================================================
#define MAX_BILLBOARD		(256)
#define BILLBOARD_SIZE_X	(25)
#define BILLBOARD_SIZE_Y	(25)

//=====================================================
// �O���錾
//=====================================================
class CScene3D;

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CBillboard : public CScene3D
{
public:
	CBillboard();									// �R���X�g���N�^
	~CBillboard();									// �f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	void SetPos(D3DXVECTOR3 pos);					// ���W�̐ݒ�
	D3DXVECTOR3 GetPos(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// �e�N�X�`���̐ݒ�

private:
	D3DXVECTOR3 m_Pos;									// �ʒu���
	D3DXVECTOR3 m_size;									//�T�C�Y
	D3DXVECTOR3 m_Dir;									// ����7
	D3DXMATRIX m_mtxWorld;								// �s��v�Z�p
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;						// �|���S���̃e�N�X�`��
	int m_nLife;										// ����
	bool m_bUse;										// �g�p����
	static CBillboard *m_apBillboard[MAX_BILLBOARD];	// �o��������r���{�[�h
};

#endif