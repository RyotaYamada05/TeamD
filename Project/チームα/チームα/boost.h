#ifndef _BOOST_H_
#define _BOOST_H_

//=============================================================================
//
// �u�[�X�^�[�̏��� [boost.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene3D.h"

//=========================================================================
// �}�N����`
//=========================================================================
#define BOOST_SIZE_X	(30.0f)
#define BOOST_SIZE_Y	(300.0f)
#define BOOST_SIZE_Z	(50.0f)
#define BOOST_LIFE		(15)

//=========================================================================
// �u�[�X�^�[�N���X
//=========================================================================
class CBoost :public CScene3D
{
public:
	CBoost();
	~CBoost();

	static CBoost *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nNumber);
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// ������
	void Uninit(void);													// �I��
	void Update(void);													// �X�V
	void Draw(void);													// �`��
	void BoostMove(void);												// �u�[�X�g�̍X�V����
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���|�C���^
	int m_nNum;									// �i���o�[
};
#endif