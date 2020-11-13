#ifndef _FIRE_H_
#define _FIRE_H_

//=============================================================================
//
// ���N���X�w�b�_�[ [fire.h]
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
#define FIRE_SIZE_X			(40)	// ���T�C�Y
#define FIRE_SIZE_Y			(40)	// �c�T�C�Y
#define MAX_FIRE_TEXTURE	(1)		// �e�N�X�`����
#define FIRE_LIFE			(12)	// �X�p�[�N�̗̑�
#define FIRE_NUM			(30)	// �X�p�[�N�̐�
#define FIRE_SPPED			(1)		// �X�s�[�h
#define FIRE_DISTANCE		(10)	// ��������

//=============================================================================
// �O���錾
//=============================================================================
class CBillboard;

//=============================================================================
// BG�N���X
//=============================================================================
class CFire : public CBillboard
{
public:
	CFire();			// �R���X�g���N�^
	~CFire();			// �f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static CFire * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nLife);

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h

	void SetColor(D3DXCOLOR col);									// �p�[�e�B�N���̃J���[��ݒ�
	void SetLife(int nLife);										// ���C�t�̐ݒ�
	void ScaleDown(void);											// �k��
	void Alpha(void);												// �����x
private:
	int m_nLife;												// �̗�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_FIRE_TEXTURE];	// �e�N�X�`�����̃|�C���^
	float m_fScale;												// �g�k�p
	float m_fScaleNum;											// �g�k�̒l
	float m_fAlpha;												// �����p
	float m_fAlphaNum;											// �����̒l
};

#endif