//=============================================================================
//
// �r������ [bill.cpp]
// Author : �����D�I
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bill.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_VERTEX		(8)		// ���_��

//=============================================================================
// static������
//=============================================================================
LPD3DXMESH CBill::m_pMesh = NULL;			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER CBill::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CBill::m_nNumMat = 0;				// �}�e���A�����̐�

//=============================================================================
// �N���G�C�g
//=============================================================================
CBill * CBill::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBill *pBill= new CBill;

	// ����������
	pBill->Init(pos, size);

	return pBill;
}

//=============================================================================
// ���f�����[�h
//=============================================================================
HRESULT CBill::LoadModel(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���f���̐���
	D3DXLoadMeshFromX("data/model/bill.x", D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// ����I��
	return S_OK;
}

//=============================================================================
// ���f���A�����[�h
//=============================================================================
void CBill::Unload(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBill::CBill()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBill::~CBill()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBill::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���f���̏���ݒ�
	MODEL model;
	model.dwNumMat = m_nNumMat;
	model.pBuffMat = m_pBuffMat;
	model.pMesh = m_pMesh;

	//���f������ݒ�
	CModel::BindModel(model);

	//�ʒu�̐ݒ�
	m_pos = pos;

	// ������	
	CModel::Init(m_pos, size);

	//rot������
	CModel::SetRot(m_rot);

	SetObjType(OBJTYPE_MODEL);

	// ���f���̎�ނ�ݒ�
	SetType(MODEL_TYPE_OBJECT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBill::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBill::Update(void)
{
	// �����蔻��
	Collision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBill::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CBill::Collision(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[���
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{


			//�ʒu�̎擾
			D3DXVECTOR3 targetPos = pPlayer->GetPos();

			// �����蔻��
			if (targetPos.x - PLAYER_COLLISION_X / 2 <= m_pos.x + BILL_COLLISION_SIZE_X / 2 &&
				targetPos.x + PLAYER_COLLISION_X / 2 >= m_pos.x - BILL_COLLISION_SIZE_X / 2 &&
				targetPos.y - PLAYER_COLLISION_Y / 2 <= m_pos.y + BILL_COLLISION_SIZE_Y / 2 &&
				targetPos.y + PLAYER_COLLISION_Y / 2 >= m_pos.y - BILL_COLLISION_SIZE_Y / 2 &&
				targetPos.z - PLAYER_COLLISION_Z / 2 <= m_pos.z + BILL_COLLISION_SIZE_Z / 2 &&
				targetPos.z + PLAYER_COLLISION_Z / 2 >= m_pos.z - BILL_COLLISION_SIZE_Z / 2)
			{
				D3DXVECTOR3 OldTarget = pPlayer->GetOldPos();
				D3DXVECTOR3 move = pPlayer->GetMove();

				if (targetPos.x - PLAYER_COLLISION_X / 2 <= m_pos.x + BILL_COLLISION_SIZE_X / 2 &&
					OldTarget.x + PLAYER_COLLISION_X / 2 >= m_pos.x + BILL_COLLISION_SIZE_X / 2)
				{
					// �u���b�N�ɉE���瓖�������Ƃ�
					pPlayer->SetPos(D3DXVECTOR3(PLAYER_COLLISION_X / 2 + m_pos.x + BILL_COLLISION_SIZE_X / 2, targetPos.y, targetPos.z));	// �v���C���[�������߂�
				}
				else if (targetPos.x + PLAYER_COLLISION_X / 2 >= m_pos.x - BILL_COLLISION_SIZE_X / 2 &&
					OldTarget.x - (PLAYER_COLLISION_X / 2) <= m_pos.x - BILL_COLLISION_SIZE_X / 2)
				{
					// �u���b�N�ɍ����瓖��������
					pPlayer->SetPos(D3DXVECTOR3(m_pos.x - BILL_COLLISION_SIZE_X / 2 - PLAYER_COLLISION_X / 2, targetPos.y, targetPos.z));	// �v���C���[�������߂�
				}
				else if ((targetPos.y - PLAYER_COLLISION_Y / 2) < m_pos.y + BILL_COLLISION_SIZE_Y / 2 &&
					OldTarget.y - PLAYER_COLLISION_Y / 2 >= m_pos.y)
				{
					// �u���b�N�ɏォ�瓖��������
					pPlayer->SetPos(D3DXVECTOR3(targetPos.x, PLAYER_COLLISION_Y / 2 + m_pos.y + BILL_COLLISION_SIZE_Y / 2, targetPos.z));
					pPlayer->BlockUp();
				}
				else if (targetPos.z - PLAYER_COLLISION_Z / 2 < m_pos.z + BILL_COLLISION_SIZE_Z / 2 &&
					OldTarget.z + PLAYER_COLLISION_Z / 2 >= m_pos.z)
				{
					// �u���b�N�Ɏ�O���瓖��������
					pPlayer->SetPos(D3DXVECTOR3(targetPos.x, targetPos.y, PLAYER_COLLISION_Z / 2 + m_pos.z + BILL_COLLISION_SIZE_Z / 2));

				}
				else if (targetPos.z + PLAYER_COLLISION_Z / 2 > m_pos.z - BILL_COLLISION_SIZE_Z / 2 &&
					OldTarget.z - PLAYER_COLLISION_Z / 2 <= m_pos.z - BILL_COLLISION_SIZE_Z / 2)
				{
					// �u���b�N�ɉ����瓖��������
					pPlayer->SetPos(D3DXVECTOR3(targetPos.x, targetPos.y, m_pos.z - BILL_COLLISION_SIZE_Z / 2 - PLAYER_COLLISION_Z / 2));
				}
				else if (targetPos.y + PLAYER_COLLISION_Y / 2 > m_pos.y - BILL_COLLISION_SIZE_Y / 2 &&
					OldTarget.y + PLAYER_COLLISION_Y / 2 <= m_pos.y)
				{
					// �u���b�N�ɉ����瓖��������
					pPlayer->SetPos(D3DXVECTOR3(targetPos.x, m_pos.y - BILL_COLLISION_SIZE_Y / 2, targetPos.z));		// �v���C���[���u���b�N�ɂ߂荞�܂Ȃ��悤�ɂ���
					pPlayer->SetMove(D3DXVECTOR3(move.x, 0.0f, move.z));
				}


			}
		}
	}
	//for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	//{

	//	// �v���C���[���
	//	CPlayer *pPlayer = CGame::GetPlayer(nCount);

	//	//�ʒu�̎擾
	//	D3DXVECTOR3 targetPos = pPlayer->GetPos();

	//// ���_�̈ʒu
	//D3DXVECTOR3 VertexPos[8] =
	//{
	//	D3DXVECTOR3(m_pos.x - BILL_COLLISION_SIZE_X / 2, m_pos.y + BILL_COLLISION_SIZE_Y / 2, m_pos.z - BILL_COLLISION_SIZE_Z / 2),	// 0
	//	D3DXVECTOR3(m_pos.x - BILL_COLLISION_SIZE_X / 2, m_pos.y + BILL_COLLISION_SIZE_Y / 2, m_pos.z + BILL_COLLISION_SIZE_Z / 2),	// 1
	//	D3DXVECTOR3(m_pos.x + BILL_COLLISION_SIZE_X / 2, m_pos.y + BILL_COLLISION_SIZE_Y / 2, m_pos.z - BILL_COLLISION_SIZE_Z / 2),	// 2
	//	D3DXVECTOR3(m_pos.x + BILL_COLLISION_SIZE_X / 2, m_pos.y + BILL_COLLISION_SIZE_Y / 2, m_pos.z + BILL_COLLISION_SIZE_Z / 2),	// 3
	//	D3DXVECTOR3(m_pos.x - BILL_COLLISION_SIZE_X / 2, m_pos.y - BILL_COLLISION_SIZE_Y / 2, m_pos.z - BILL_COLLISION_SIZE_Z / 2),	// 4
	//	D3DXVECTOR3(m_pos.x - BILL_COLLISION_SIZE_X / 2, m_pos.y - BILL_COLLISION_SIZE_Y / 2, m_pos.z + BILL_COLLISION_SIZE_Z / 2),	// 5
	//	D3DXVECTOR3(m_pos.x + BILL_COLLISION_SIZE_X / 2, m_pos.y - BILL_COLLISION_SIZE_Y / 2, m_pos.z - BILL_COLLISION_SIZE_Z / 2),	// 6
	//	D3DXVECTOR3(m_pos.x + BILL_COLLISION_SIZE_X / 2, m_pos.y - BILL_COLLISION_SIZE_Y / 2, m_pos.z + BILL_COLLISION_SIZE_Z / 2),	// 7
	//};

	//// 2�_�Ԃ̋���
	//float Distance[8] = 
	//{
	//	sqrtf((targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y + BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y + BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y + BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y + BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y - BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y - BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y - BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z - BILL_COLLISION_SIZE_Z / 2)),

	//	sqrtf((targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2)*(targetPos.x - m_pos.x + BILL_COLLISION_SIZE_X / 2) +
	//	(targetPos.y - m_pos.y - BILL_COLLISION_SIZE_Y / 2)*(targetPos.x - m_pos.x - BILL_COLLISION_SIZE_Y / 2) +
	//		(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2)*(targetPos.z - m_pos.z + BILL_COLLISION_SIZE_Z / 2))
	//};

	//for (int nCntVex = 0; nCntVex < MAX_VERTEX; nCntVex++)
	//{
	//	// �����蔻��
	//	if (Distance[nCntVex] <= PLAYER_RADIUS)
	//	{
	//		D3DXVec3Normalize(&VertexPos[nCntVex], &targetPos);

	//		VertexPos[nCntVex] *= PLAYER_RADIUS;
	//	}
	//}

	//	if (targetPos.x < (m_pos.x - BILL_COLLISION_SIZE_X / 2) - PLAYER_COLLISION_X / 2 ||
	//		targetPos.x > (m_pos.x + BILL_COLLISION_SIZE_X / 2) + PLAYER_COLLISION_X / 2 ||
	//		targetPos.y < (m_pos.x - BILL_COLLISION_SIZE_Y / 2) - PLAYER_COLLISION_Y / 2 ||
	//		targetPos.y > (m_pos.x + BILL_COLLISION_SIZE_Y / 2) + PLAYER_COLLISION_Y / 2 ||
	//		targetPos.z < (m_pos.x - BILL_COLLISION_SIZE_Z / 2) - PLAYER_COLLISION_Z / 2 ||
	//		targetPos.z > (m_pos.x + BILL_COLLISION_SIZE_Z / 2) + PLAYER_COLLISION_Z / 2)
	//	{

	//		return false;
	//	}





	//}

	return false;
}
