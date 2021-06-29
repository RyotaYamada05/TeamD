//=============================================================================
//
// �r������ [bill.h]
// Author : �����D�I
//
//=============================================================================

#ifndef  _BILL_H_
#define  _BILL_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================

#define BILL_SIZE_X				(12)			// �T�C�Y
#define BILL_SIZE_Y				(12)			// �T�C�Y
#define BILL_SIZE_Z				(12)			// �T�C�Y
#define BILL_POS_X_1	(3000.0f)		// X���W(��)
#define BILL_POS_X_2	(2000.0f)		// X���W(��O)
#define BILL_POS_Z		(4000.0f)		// Z���W

#define BILL_COLLISION_SIZE_X	(780)			// �T�C�Y
#define BILL_COLLISION_SIZE_Y	(400)			// �T�C�Y
#define BILL_COLLISION_SIZE_Z	(1000)			// �T�C�Y

//=============================================================================
// �N���X�錾
//=============================================================================
class CBill : public CModel
{
public:
	CBill();
	~CBill();

	static CBill*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g
	static HRESULT LoadModel(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	bool Collision(void);											// �����蔻��

private:
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_rot;						// ��]
	D3DXVECTOR3 m_move;						// �ړ�
	float m_fAngle;							// �p�x
	static LPD3DXMESH m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;					// �}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture[10];	//�e�N�X�`���ւ̃|�C���^

};
#endif // ! _BILL_H_