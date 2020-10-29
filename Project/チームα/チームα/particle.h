#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================================================================
//
// �ΉԃN���X�w�b�_�[ [particl.h]
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
#define SPARK_SIZE_X			(20)		// ���T�C�Y
#define SPARK_SIZE_Y			(5)			// �c�T�C�Y
#define MAX_SPARK_TEXTURE		(1)			// �e�N�X�`����
#define SPARK_LIFE				(14)		// �X�p�[�N�̗̑�
#define SPARK_BASE_ANGLE		(90)		// �ΉԂ̌���
#define SPARK_NUM				(50)		// �X�p�[�N�̐�
#define SPARK_SPPED				(1)			// �X�s�[�h
#define SPARK_DISTANCE			(20)		// ��������
#define SPARK_ANGLE				(30)		// �p�x

//=============================================================================
// �O���錾
//=============================================================================
class CBillboard;

//=============================================================================
// BG�N���X
//=============================================================================
class CParticle : public CBillboard
{
public:
	CParticle();			// �R���X�g���N�^
	~CParticle();			// �f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static CParticle * Create(										// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col,
		int nAngle, int nBaseAngle, 
		int nDistance, int nLife, int nSpeed);

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h

	void SetColor(D3DXCOLOR col);									// �p�[�e�B�N���̃J���[��ݒ�
	void SetLife(int nLife);										// ���C�t�̐ݒ�
private:
	int m_nLife;												// �̗�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SPARK_TEXTURE];	// �e�N�X�`�����̃|�C���^
};

#endif