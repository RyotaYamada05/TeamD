//=============================================================================
//
// ���� [bullet.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "bullet.h"
#include "player.h"
#include "game.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET_LIFE 60	//�o���b�g���C�t 
#define BULLET_ATK 20	//�U����

//=============================================================================
//�o���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{
	//�e�����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�T�C�Y
	m_user = BULLET_USER_NONE;	//�g�p��
	m_nAtk = 0;	//�U����
	m_nLife = 0;	//���C�t
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
	CBillboard::Init(pos, m_size);

	SetObjType(CScene::OBJTYPE_PLAYER);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 10.0f);

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

	//�ړ��ʂ��ʒu�ɗ^����
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
		//�I�������Ăяo��
		Uninit();
		return;
	}

	//���C�t�̌���
	m_nLife--;
}

//=============================================================================
//�o���b�g�N���X�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	//�r���{�[�h�̕`�揈���Ăяo��
	CBillboard::Draw();
}

bool CBullet::Collision(void)
{
	CPlayer * pPlayer = NULL;
	switch (m_user)
	{
	case BULLET_USER_PL1:

		//�v���C���[�N���X�փL���X�g
		pPlayer = CGame::GetPlayer(1);

		break;
	case BULLET_USER_PL2:
		//�v���C���[�N���X�փL���X�g
		pPlayer = CGame::GetPlayer(0);

		break;
	}

	//�ʒu�̎擾
	D3DXVECTOR3 targetPos = pPlayer->GetPos();

	if (targetPos.x >= m_pos.x - m_size.x / 2 &&
		targetPos.x <= m_pos.x + m_size.x / 2 &&
		targetPos.y >= m_pos.y - m_size.y / 2 &&
		targetPos.y <= m_pos.y + m_size.y / 2 &&
		targetPos.z >= m_pos.z - m_size.x / 2 &&
		targetPos.z <= m_pos.z + m_size.x / 2)
	{
		return true;
	}

	return false;
}
