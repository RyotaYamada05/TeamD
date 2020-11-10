#ifndef _SPLASH_H_
#define _SPLASH_H_

//=====================================================
//
// �X�v���b�V���N���X�w�b�_�[ [splash.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"

//=====================================================
// �}�N����`
//=====================================================
#define SPLASH_SIZE_X_2D	(300)
#define SPLASH_SIZE_Y_2D	(300)
#define SPLASH_SIZE_Z_2D	(300)

//=====================================================
// �O���錾
//=====================================================
class CBillboard;

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CSplash : public CBillboard
{
public:
	CSplash();									// �R���X�g���N�^
	~CSplash();								// �f�X�g���N�^

	static CSplash *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;						// �|���S���̃e�N�X�`��
};

#endif