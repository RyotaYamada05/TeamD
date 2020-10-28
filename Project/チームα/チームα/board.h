#ifndef _ITEM_H_
#define _ITEM_H_

//===================================================
//
// �A�C�e���N���X�w�b�_�[	[item.h]
// Author : Konishi Yuuto
//
//===================================================

//===================================================
// �C���N���[�h
//===================================================
#include "billboard.h"

//===================================================
// �}�N����`
//===================================================
#define MAX_BOARD_TEXTURE (1)

//===================================================
// �A�C�e���N���X
//===================================================
class CBoard : public CBillboard
{
public:
	CBoard();									// �R���X�g���N�^
	~CBoard();									// �f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	static CBoard*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �|���S������

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
private:
	D3DXVECTOR3 m_Pos;											// �ʒu���
	D3DXVECTOR3 m_Dir;											// ����7
	D3DXMATRIX m_mtxWorld;										// �s��v�Z�p
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOARD_TEXTURE];	// �e�N�X�`�����̃|�C���^
};

#endif