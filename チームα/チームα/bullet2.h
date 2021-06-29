//=============================================================================
//
// �e�̏���(���f���h��) [bullet2.h]
// Author : Konishi Yuuto
//
//=============================================================================
#ifndef _BULLET2_H_
#define _BULLET2_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;

//=============================================================================
//�o���b�g�N���X
//=============================================================================
class CBullet2 :public CModel
{
public:
	//=========================================================================
	//�e�̎g�p�Ҕ��ʗp�̗񋓌^
	//=========================================================================
	typedef enum
	{
		BULLET2_USER_NONE = -1,
		BULLET2_USER_PL1,	//PL1
		BULLET2_USER_PL2,	//PL2
		BULLET2_USER_MAX		//�ő吔
	}BULLET2_USER;

	typedef enum
	{
		BULLET2_TYPE_NONE = 0,	// �����l
		BULLET2_TYPE_NORMAL,	// �ʏ�e
		BULLET2_TYPE_BOMB,		// �{��
		BULLET2_TYPE_LASER,		// ���[�U�[
		BULLET2_TYPE_MAX
	}BULLET2_TYPE;

	CBullet2();		// �R���X�g���N�^
	~CBullet2();	// �f�X�g���N�^

	static CBullet2 * Create(const D3DXVECTOR3 pos,			// �|���S������
		const D3DXVECTOR3 size, const BULLET2_USER user,
		float fSpeed);

	HRESULT Init(const D3DXVECTOR3 pos,						// ����������
		const D3DXVECTOR3 size, const BULLET2_USER user,
		float fSpeed);

	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	bool Collision(void);									// �����蔻��
	D3DXVECTOR3 VectorMath(D3DXVECTOR3 TargetPos,float fSpeed);		// �Ǐ]
		

	void SetLife(int nLife);								// �̗͂̐ݒ�
	void SetMove(D3DXVECTOR3 move);							// �ړ��ʉ��Z
	void SetType(BULLET2_TYPE type);						// �^�C�v�̐ݒ�
	void SetHeight(float fHeight);							// �����̐ݒ�
	D3DXVECTOR3 GetMove(void);							// �ړ��ʂ̍X�V
	float GetHeight(void);									// �����̏��

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_size;		// �傫��
	int m_nAtk;				// �U����
	int m_nLife;			// ���C�t
	BULLET2_USER m_user;	// �g�p��
	BULLET2_TYPE m_type;	// �^�C�v
	CPlayer *m_pTargetPL;	//�G�v���C���[�̃|�C���^
	int m_nCounter;
	int m_nDamage;			//�_���[�W��
	float m_fSpeed;			// ����
	float m_fHeight;		// ����
};

#endif 