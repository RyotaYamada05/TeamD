//=============================================================================
//
// �O�Ղ̏��� [locus.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "locus.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CLocus::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLocus::CLocus()
{
	m_nLife = 0;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLocus::~CLocus()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CLocus * CLocus::Create(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife)
{
	//�|�C���^�ϐ�
	CLocus *pLocus = NULL;

	//�������̊m��
	pLocus = new CLocus;

	//���������m�ۂł��Ă�����
	if (pLocus != NULL)
	{
		//�����������Ăяo��
		pLocus->Init(pos, size);
		pLocus->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pLocus->SetRot(rot);
		pLocus->m_posOld = posOld;
		pLocus->m_rot = rot;
		pLocus->m_nLife = nLife;
	}
	else
	{
		return NULL;
	}

	return pLocus;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CLocus::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/board000.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CLocus::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLocus::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

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

	float sizeX = sqrtf((m_posOld.x - m_pos.x)*(m_posOld.x - m_pos.x));
	float sizeY = sqrtf((m_posOld.y - m_pos.y)*(m_posOld.y - m_pos.y));
	float sizeZ = sqrtf((m_posOld.z - m_pos.z)*(m_posOld.z - m_pos.z));

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(sizeX / 2), +(sizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(sizeX / 2), +(sizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(sizeX / 2), -(sizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(sizeX / 2), -(sizeY / 2), 0.0f);

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

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLocus::Uninit(void)
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
// �X�V����
//=============================================================================
void CLocus::Update(void)
{
	m_nLife--;

	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLocus::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�̃}�g���N�X

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	float sizeX = sqrtf((m_posOld.x - m_pos.x)*(m_posOld.x - m_pos.x));
	float sizeY = sqrtf((m_posOld.y - m_pos.y)*(m_posOld.y - m_pos.y));
	float sizeZ = sqrtf((m_posOld.z - m_pos.z)*(m_posOld.z - m_pos.z));

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, sizeX, sizeY, sizeZ);
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

	// �`�揈��
	//CScene3D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[

	// Z�o�b�t�@�߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	pDevice->LightEnable(0, TRUE);

}