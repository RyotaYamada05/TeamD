//=============================================================================
//
// �K�w�\���p�̃��f������ [modelanime.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�K�w���f���N���X�̃R���X�g���N�^
//=============================================================================
CModelAnime::CModelAnime()
{
	//�e�����o�ϐ��̃N���A
	memset(&m_model, 0, sizeof(m_model));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
}

//=============================================================================
//�K�w���f���N���X�̃f�X�g���N�^
//=============================================================================
CModelAnime::~CModelAnime()
{
}

//=============================================================================
//�K�w���f���N���X�̃N���G�C�g����
//=============================================================================
CModelAnime * CModelAnime::Create(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�K�w���f���N���X�̃|�C���^�ϐ�
	CModelAnime *pModelAnime = NULL;

	//�C���X�^���X����
	pModelAnime = new CModelAnime;

	//���������m�ۂł��Ă�����
	if (pModelAnime != NULL)
	{
		//�����������Ăяo��
		pModelAnime->Init(xfilename, pos, rot);
	}
	//���s���Ă����ꍇ
	else
	{
		return NULL;
	}

	return pModelAnime;
}

//=============================================================================
//�K�w���f���N���X�̏���������
//=============================================================================
HRESULT CModelAnime::Init(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���f���̓ǂݍ���
	D3DXLoadMeshFromX(xfilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model.pBuffMat,
		NULL,
		&m_model.dwNumMat,
		&m_model.pMesh);

	//�ʒu�̐ݒ�
	m_pos = pos;

	//�����̐ݒ�
	m_rot = rot;

	return S_OK;
}

//=============================================================================
//�K�w���f���N���X�̏I������
//=============================================================================
void CModelAnime::Uninit(void)
{
	//�}�e���A�����̔j��
	if (m_model.pBuffMat != NULL)
	{
		m_model.pBuffMat->Release();
		m_model.pBuffMat = NULL;
	}

	//���b�V�����̔j��
	if (m_model.pMesh != NULL)
	{
		m_model.pMesh->Release();
		m_model.pMesh = NULL;
	}
}

//=============================================================================
//�K�w���f���N���X�̍X�V����
//=============================================================================
void CModelAnime::Update(void)
{
}

//=============================================================================
//�K�w���f���N���X�̕`�揈��
//=============================================================================
void CModelAnime::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;
	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�A�j���[�V�����̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�A�j���[�V�����̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�����݂���ꍇ
	if (m_pParent != NULL)
	{
		//�e����ݒ�
		mtxParent = m_pParent->GetMtxWorld();
	}
	//�e�����݂��Ȃ��ꍇ
	else
	{
		//�f�o�C�X����ݒ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�e�̃}�g���N�X�Ɗ|�����킹��
	m_mtxWorld *= mtxParent;

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_model.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model.dwNumMat; nCntMat++)
	{
		//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		m_model.pMesh->DrawSubset(nCntMat);

		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//�K�w���f���N���X�̐e���̐ݒ菈��
//=============================================================================
void CModelAnime::SetParent(CModelAnime * pParent)
{
	m_pParent = pParent;
}

//=============================================================================
//�K�w���f���N���X�̈ʒu�ݒ菈��
//=============================================================================
void CModelAnime::SetPosAnime(const D3DXVECTOR3 posAnime)
{
	m_posAnime = posAnime;
}

//=============================================================================
//�K�w���f���N���X�̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//�K�w���f���N���X�̃A�j���[�V�����ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPosAnime(void) const
{
	return m_posAnime;
}

//=============================================================================
//�K�w���f���N���X�̌����̐ݒ菈��
//=============================================================================
void CModelAnime::SetRotAnime(const D3DXVECTOR3 rotAnime)
{
	m_rotAnime = rotAnime;
}

//=============================================================================
//�K�w���f���N���X�̌����̎擾����
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRot(void) const
{
	return m_rot;
}

//=============================================================================
//�K�w���f���N���X�̃A�j���[�V���������̎擾
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRotAnime(void) const
{
	return m_rotAnime;
}

//=============================================================================
//�K�w���f���N���X�̃}�g���N�X���̎擾����
//=============================================================================
D3DXMATRIX CModelAnime::GetMtxWorld(void)
{
	return m_mtxWorld;
}
