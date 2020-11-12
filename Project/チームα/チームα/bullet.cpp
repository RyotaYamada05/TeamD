//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "bullet.h"
#include "player.h"
#include "game.h"
#include "life.h"
#include "2d_explosion.h"
#include "shock.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET_LIFE 100	//�o���b�g���C�t 
#define BULLET_ATK 20	//�U����
#define BULLET_SPEED 50.0f	//���x

//=============================================================================
//�o���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{
	//�e�����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�T�C�Y
	m_user = BULLET_USER_NONE;	//�g�p��
	m_nAtk = 0;	//�U����
	m_nLife = 0;	//���C�t
	m_nCounter = 0;
	m_pTargetPL = NULL;	//�G�v���C���[�̃|�C���^
}

//=============================================================================
//�o���b�g�N���X�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
//�o���b�g�N���X�̃N���G�C�g����
//=============================================================================
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET_USER user)
{
	CBullet *pBullet = NULL;

	//�������̊m��
	pBullet = new CBullet;

	//���������m�ۂł��Ă�����
	if (pBullet)
	{
		//�����������Ăяo��
		pBullet->Init(pos, size, user);
	}
	else
	{
		return NULL;
	}

	return pBullet;
}

//=============================================================================
//�o���b�g�N���X�̏���������
//=============================================================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET_USER user)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	//�T�C�Y�̐ݒ�
	m_size = size;

	//�g�p�҂̐ݒ�
	m_user = user;

	//���C�t�̐ݒ�
	m_nLife = BULLET_LIFE;

	//�U���͂̐ݒ�
	m_nAtk = BULLET_ATK;

	//�r���{�[�h�̏�����
	CBillboard::Init(m_pos, m_size);
	
	//�I�u�W�F�N�g�^�C�v��ݒ�
	//SetObjType(CScene::OBJTYPE_BULLET);

	switch (m_user)
	{
	case BULLET_USER_PL1:
		//2P�̏��擾
		m_pTargetPL = CGame::GetPlayer(1);

		break;
	case BULLET_USER_PL2:
		//1P�̏��擾
		m_pTargetPL = CGame::GetPlayer(0);

		break;
	}

	return S_OK;
}

//=============================================================================
//�o���b�g�N���X�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	//�r���{�[�h�̏I�������Ăяo��
	CBillboard::Uninit();
}

//=============================================================================
//�o���b�g�N���X�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	//�ʒu�̎擾
	m_pos = GetPos();

	if (m_nCounter <= 120)
	{
		//�ړ��ʂ̌v�Z
		m_move = VectorMath(m_pTargetPL->GetPos(), BULLET_SPEED);
	}

	m_pos += m_move;

	//�ʒu�̐ݒ�
	SetPos(m_pos);

	if (Collision() == true)
	{
		Uninit();
		return;
	}

	//���C�t��0�ȉ��̎�
	if (m_nLife <= 0)
	{
		CShock::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SHOCK_SIZE_X, SHOCK_SIZE_Y, SHOCK_SIZE_Z));
		//�I�������Ăяo��
		Uninit();
		return;
	}

	//���C�t�̌���
	m_nLife--;
	m_nCounter++;
}

//=============================================================================
//�o���b�g�N���X�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	//�r���{�[�h�̕`�揈���Ăяo��
	CBillboard::Draw();
}

//=============================================================================
//�o���b�g�N���X�̓����蔻��
//=============================================================================
bool CBullet::Collision(void)
{
	D3DXVECTOR3 targetPos = m_pTargetPL->GetPos();

	if (targetPos.x >= m_pos.x - m_size.x / 2 &&
		targetPos.x <= m_pos.x + m_size.x / 2 &&
		targetPos.y >= m_pos.y - m_size.y / 2 &&
		targetPos.y <= m_pos.y + m_size.y / 2 &&
		targetPos.z >= m_pos.z - m_size.x / 2 &&
		targetPos.z <= m_pos.z + m_size.x / 2)
	{
		for (int nCount = 0; nCount < LIFE_NUM; nCount++)
		{
			//�@�v���C���[�̃��C�t�����炷

			m_pTargetPL->GetLife(nCount)->Decrease(50, m_user, true);
		}
		C2dExplosion::Create(m_pos,
			D3DXVECTOR3(EXPLOSION_SIZE_X_2D, EXPLOSION_SIZE_Y_2D, EXPLOSION_SIZE_Z_2D));
		return true;
	}
		
	return false;
}
//=============================================================================
//�o���b�g�N���X�̂̃x�N�g���v�Z����
//=============================================================================
D3DXVECTOR3 CBullet::VectorMath(D3DXVECTOR3 TargetPos, float fSpeed)
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
