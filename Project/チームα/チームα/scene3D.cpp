//=============================================================================
//
// ���C������ [scene3D.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CScene3D::m_pTexture = NULL;

//=============================================================================
//3D�|���S���N���X�̃R���X�g���N�^
//=============================================================================
CScene3D::CScene3D()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//3D�|���S���N���X�̃f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
//3D�|���S���N���X�̃N���G�C�g����
//=============================================================================
CScene3D * CScene3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//3D�|���S���N���X�̃|�C���^�ϐ�
	CScene3D *pScene3D = NULL;

	//�������̊m��
	pScene3D = new CScene3D;

	//���������m�ۂł��Ă�����
	if (pScene3D != NULL)
	{
		//�����������Ăяo��
		pScene3D->Init(pos, size);
	}
	else
	{
		return NULL;
	}

	return pScene3D;
}
//=============================================================================
//3D�|���S���N���X�̃e�N�X�`�����[�h����
//=============================================================================
HRESULT CScene3D::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/board000.png", &m_pTexture);
	
	return S_OK;
}

//=============================================================================
//3D�|���S���N���X�̃e�N�X�`���j������
//=============================================================================
void CScene3D::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}



//=============================================================================
//3D�|���S���N���X�̏���������
//=============================================================================
HRESULT CScene3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	m_pos = pos;
	m_size = size;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (size.x / 2), m_pos.y + (size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (size.x / 2), m_pos.y + (size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (size.x / 2), m_pos.y - (size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (size.x / 2), m_pos.y - (size.y / 2), 0.0f);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//3D�|���S���N���X�̏I������
//=============================================================================
void CScene3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
//3D�|���S���N���X�̍X�V����
//=============================================================================
void CScene3D::Update(void)
{

}

//=============================================================================
//3D�|���S���N���X�̕`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�̃}�g���N�X

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);


}

void CScene3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CScene3D::SetPosision(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}