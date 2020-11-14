#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//
// �G�t�F�N�g�N���X�w�b�_�[	[effect.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_SIZE_X			(70)	// �T�C�Y
#define EFFECT_SIZE_Y			(70)	// �T�C�Y
#define MAX_EFFECT_TEXTURE		(1)		// �e�N�X�`����

#define EFFECT_LASER_SIZE_X		(250)	// �T�C�Y
#define EFFECT_LASER_SIZE_Y		(250)	// �T�C�Y

#define EFFECT_LIFE				(7)		// �G�t�F�N�g�̗̑�
#define EFFECT_LASER_LIFE		(20)	// �G�t�F�N�g�̗̑�

//=============================================================================
// �O���錾
//=============================================================================
class CBillboard;

//=============================================================================
// BG�N���X
//=============================================================================
class CEffect : public CBillboard
{
public:

	CEffect();			// �R���X�g���N�^
	~CEffect();			// �f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static CEffect * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		D3DXCOLOR col, int nLife);

	void SetMove(D3DXVECTOR3 move);									// �ړ��ʐݒ�
	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	void ScaleDown(void);											// �k��
	void SetColor(D3DXCOLOR col);									// �J���[�̏�����
private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EFFECT_TEXTURE];		// �e�N�X�`�����̃|�C���^
	bool m_bScaleDown;												// �g��I���t���O
	float m_fScale;													// �X�P�[��
	float m_fScaleNum;												// �X�P�[���̒l
	int m_nLife;													// ���C�t
	D3DXCOLOR m_col;												// �J���[
};

#endif