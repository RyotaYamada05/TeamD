//=============================================================================
//
// �e�̏���(���f��) [bullet2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================
#include "bullet2.h"
#include "player.h"
#include "game.h"
#include "life.h"
#include "2d_explosion.h"
#include "shock.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET2_ATK	(20)	//�U����

//=============================================================================
//�o���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CBullet2::CBullet2()
{
	// �e�����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
	m_user = BULLET2_USER_NONE;					// �g�p��
	m_nAtk = 0;									// �U����
	m_nLife = 0;								// ���C�t
	m_nCounter = 0;
	m_pTargetPL = NULL;	//�G�v���C���[�̃|�C���^
	m_fSpeed = 0.0f;
}

//=============================================================================
//�o���b�g�N���X�̃f�X�g���N�^
//=============================================================================
CBullet2::~CBullet2()
{
}

//=============================================================================
//�o���b�g�N���X�̃N���G�C�g����
//=============================================================================
CBullet2 * CBullet2::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET2_USER user)
{
	CBullet2 *pBullet2 = NULL;

	//�������̊m��
	pBullet2 = new CBullet2;

	//���������m�ۂł��Ă�����
	if (pBullet2)
	{
		//�����������Ăяo��
		pBullet2->Init(pos, size, user);
	}
	else
	{
		return NULL;
	}

	return pBullet2;
}

//=============================================================================
//�o���b�g�N���X�̏���������
//=============================================================================
HRESULT CBullet2::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET2_USER user)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	//�T�C�Y�̐ݒ�
	m_size = size;

	SetSize(size);

	//�g�p�҂̐ݒ�
	m_user = user;

	//�U���͂̐ݒ�
	m_nAtk = BULLET2_ATK;

	//����������������
	CModel::Init(pos, m_size);

	switch (m_user)
	{
	case BULLET2_USER_PL1:
		//2P�̏��擾
		m_pTargetPL = CGame::GetPlayer(1);

		break;
	case BULLET2_USER_PL2:
		//1P�̏��擾
		m_pTargetPL = CGame::GetPlayer(0);

		break;
	}

	return S_OK;
}

//=============================================================================
//�o���b�g�N���X�̏I������
//=============================================================================
void CBullet2::Uninit(void)
{
	//�I������
	CModel::Uninit();
}

//=============================================================================
//�o���b�g�N���X�̍X�V����
//=============================================================================
void CBullet2::Update(void)
{
	//�ʒu�̎擾
	m_pos = GetPos();

	if (m_nCounter <= 10)
	{
		//�ړ��ʂ̌v�Z
		m_move = VectorMath(m_pTargetPL->GetPos(), 70.0f);
	}

	//�ړ��ʂ��ʒu�ɗ^����
	m_pos += m_move;

	//���C�t�̐ݒ�
	m_nLife--;

	//�ʒu�̐ݒ�
	SetPos(m_pos);

	if (Collision() == true)
	{
		// �̗͂�0
		m_nLife = 0;
	}

	//���C�t��0�ȉ��̎�
	if (m_nLife <= 0)
	{
		// �Ռ��𐶐�
		CShock::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SHOCK_SIZE_X, SHOCK_SIZE_Y, SHOCK_SIZE_Z));

		//�I�������Ăяo��
		Uninit();
		return;
	}
}

//=============================================================================
//�o���b�g�N���X�̕`�揈��
//=============================================================================
void CBullet2::Draw(void)
{
	//�`�揈��
	CModel::Draw();
}

//=============================================================================
//�o���b�g�N���X�̓����蔻��
//=============================================================================
bool CBullet2::Collision(void)
{
	CPlayer * pPlayer = NULL;

	switch (m_user)
	{
	case BULLET2_USER_PL1:

		//�v���C���[�N���X�փL���X�g
		pPlayer = CGame::GetPlayer(1);
		break;

	case BULLET2_USER_PL2:

		//�v���C���[�N���X�փL���X�g
		pPlayer = CGame::GetPlayer(0);
		break;
	}

	//�ʒu�̎擾
	D3DXVECTOR3 targetPos = pPlayer->GetPos();

	if (targetPos.x >= m_pos.x - 50.0f / 2 &&
		targetPos.x <= m_pos.x + 50.0f / 2 &&
		targetPos.y >= m_pos.y - 50.0f / 2 &&
		targetPos.y <= m_pos.y + 50.0f / 2 &&
		targetPos.z >= m_pos.z - 50.0f / 2 &&
		targetPos.z <= m_pos.z + 50.0f / 2)
	{
		for (int nCount = 0; nCount < LIFE_NUM; nCount++)
		{
			//�@�v���C���[�̃��C�t�����炷
			m_pTargetPL->GetLife(nCount)->Decrease(50, m_user, true);

			// ��������
			C2dExplosion::Create(m_pos,
				D3DXVECTOR3(EXPLOSION_SIZE_X_2D, EXPLOSION_SIZE_Y_2D, EXPLOSION_SIZE_Z_2D));
		}

		m_nLife = 0;
		return true;
	}

	return false;
}

//=============================================================================
//�o���b�g�N���X�̂̃x�N�g���v�Z����
//=============================================================================
D3DXVECTOR3 CBullet2::VectorMath(D3DXVECTOR3 TargetPos, float fSpeed)
{
	//2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
	D3DXVECTOR3 Vector = TargetPos - m_pos;

	//�x�N�g���̑傫�������߂�(��c^2 = a^2 * b^2)
	float fVectorSize = D3DXVec3Length(&Vector);

	//�P�ʃx�N�g���p�ϐ�
	D3DXVECTOR3 UnitVector;

	//�P�ʃx�N�g�������߂�(���̃x�N�g�� / �x�N�g���̑傫��)
	D3DXVec3Normalize(&UnitVector, &Vector);


	//�P�ʃx�N�g���𑬓x�{�ɂ��ĕԂ�(UnitVector * fSpeed)
	return	UnitVector * fSpeed;
}


//=============================================================================
// �̗͂̐ݒ�
//=============================================================================
void CBullet2::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void CBullet2::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �ړ��ʏ��
//=============================================================================
D3DXVECTOR3 CBullet2::GetMove(void)
{
	return m_move;
}
