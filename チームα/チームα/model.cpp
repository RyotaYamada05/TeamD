//=============================================================================
//
// ���f������ [model.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"
#include "life.h"
#include "2d_explosion.h"

//=============================================================================
//���f���N���X�̃R���X�g���N�^
//=============================================================================
CModel::CModel(int nPriority) : CScene(nPriority)
{
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_nNumMat = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_type = MODEL_TYPE_NONE;
	m_pTexture = NULL;
	//memset(m_apTexture, 0, sizeof(m_apTexture));
	m_apTexture = NULL;
}

//=============================================================================
//���f���N���X�̃f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
//���f���N���X�̃N���G�C�g����
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//���f���N���X�̃|�C���^�ϐ�
	CModel *pModel = NULL;

	//�������m��
	pModel = new CModel;

	//���������m�ۂł��Ă�����
	if (pModel != NULL)
	{
		//�����������Ăяo��
		pModel->Init(pos, size);
	}
	//�������m�ۂɎ��s�����Ƃ�
	else
	{
		return NULL;
	}

	return pModel;
}

//=============================================================================
//���f���N���X�̏���������
//=============================================================================
HRESULT CModel::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�̏�����
	m_pos = pos;

	// �T�C�Y������
	m_size = size;

	return S_OK;
}

//=============================================================================
//���f���N���X�̏I������
//=============================================================================
void CModel::Uninit(void)
{
	////���b�V���̔j��
	//if (m_pMesh != NULL)
	//{
	//	m_pMesh->Release();
	//	m_pMesh = NULL;
	//}
	////�}�e���A���̔j��
	//if (m_pBuffMat != NULL)
	//{
	//	m_pBuffMat->Release();
	//	m_pBuffMat = NULL;
	//}

	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=============================================================================
// ���f���N���X�̍X�V����
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// ���f���N���X�̕`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�����I�u�W�F�N�g�̏ꍇ
		if (m_type == MODEL_TYPE_OBJECT)
		{
			pDevice->SetTexture(0, m_apTexture[nCntMat]);
		}
		else
		{
			pDevice->SetTexture(0, m_pTexture);
		}
		

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		if (m_type == MODEL_TYPE_OBJECT)
		{
			pDevice->SetTexture(0, NULL);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

void CModel::BindModel(MODEL model)
{
	m_pMesh = model.pMesh;
	m_pBuffMat = model.pBuffMat;
	m_nNumMat = model.dwNumMat;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CModel::BindTexturePointer(LPDIRECT3DTEXTURE9 *ppTexture)
{
	m_apTexture = ppTexture;
}

//=============================================================================
//���f���N���X�̃��b�V�����̎擾
//=============================================================================
LPD3DXMESH CModel::GetMesh(void) const
{
	return m_pMesh;
}

LPD3DXBUFFER CModel::GetBuffMat(void) const
{
	return m_pBuffMat;
}

//=============================================================================
//���f���N���X�̈ʒu���̐ݒ�
//=============================================================================
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//���f���N���X�̈ʒu���̎擾
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//���f���N���X�̌����̐ݒ�
//=============================================================================
void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �p�x�̏��
//=============================================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//=============================================================================
//���f���̎��
//=============================================================================
void CModel::SetType(MODEL_TYPE Mtype)
{
	m_type = Mtype;
}

//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CModel::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �T�C�Y�̏��
//=============================================================================
D3DXVECTOR3 CModel::GetSize(void)
{
	return m_size;
}

LPD3DXBUFFER CModel::GetBuffMat(void)
{
	return m_pBuffMat;
}

CModel::MODEL_TYPE CModel::GetType(void)
{
	return m_type;
}

D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}
