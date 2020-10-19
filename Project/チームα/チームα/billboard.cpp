//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.h]
// Author : �����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

CBillboard *CBillboard::m_apBillboard[MAX_BILLBOARD] = {};	// �o��������r���{�[�h

//=====================================================
// �R���X�g���N�^
//=====================================================
CBillboard::CBillboard()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu���
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����7
	m_pVtxBuff = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
	m_pTexture = NULL;									// �|���S���̃e�N�X�`��
	m_nLife = 0;										// ����
	m_bUse = false;										// �g�p����
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CBillboard::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBillboard::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CBillboard::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans;
	DWORD ambient;

	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�̋t�s��̐���
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL,
		&mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// �A���t�@�e�X�g��L�͉�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// �A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �ʒu�𔽉f�A���[���h�}�g���N�X�ݒ�A�|���S���`��
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���N�X�̐ݒ� �������A�����A�ʒu
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	pDevice->LightEnable(0, TRUE);
}

//=====================================================
// �e�N�X�`���̐ݒ�
//=====================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}