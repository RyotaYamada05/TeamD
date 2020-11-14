//=======================================================================================
//
// �Q�[�W�`�揈��(gauge.cpp)
// Author : �����D�I
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "keyboard.h"
#include "gauge.h"
#include "renderer.h"
#include "manager.h"

//=======================================================================================
// �N���G�C�g����
//=======================================================================================
CGauge* CGauge::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �I�u�W�F�N�g�𐶐�
	CGauge* pGauge = new CGauge();

	// ����������
	pGauge->Init(pos, size);

	return pGauge;
}

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGauge::CGauge(int nPriority) : CScene(nPriority)
{
	m_pTextuer = NULL;
	m_pVetxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGauge::~CGauge()
{

}

//=======================================================================================
//����������
//=======================================================================================
HRESULT CGauge::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVetxBuff,
		NULL);

	m_pos = pos;
	m_size = size;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�����b�N����
	m_pVetxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	// ���_�f�[�^���A�����b�N����
	m_pVetxBuff->Unlock();

	return S_OK;
}

//=======================================================================================
// �|���S���̏I������
//=======================================================================================
void CGauge::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVetxBuff != NULL)
	{
		m_pVetxBuff->Release();
		m_pVetxBuff = NULL;
	}
	CScene::SetDeathFlag();
}

//=======================================================================================
// �|���S���̍X�V����
//=======================================================================================
void CGauge::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�����b�N����
	m_pVetxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVetxBuff->Unlock();
}

//=======================================================================================
// �|���S���̕`�揈��
//=======================================================================================
void CGauge::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g��l�̐ݒ�
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVetxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, m_pTextuer);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, NULL);
}

//======================================================
//�F�̎擾
//======================================================
void CGauge::SetCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	m_col = col;

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	m_pVetxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�(0~255�̐��l�Őݒ�)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,a��0~255�͈̔͂Ō��߂邱��
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);  //r:���b�h g:�O���[���@b:�u���[
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //a�́A�����x��\���Ă���
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�f�[�^���A�����b�N
	m_pVetxBuff->Unlock();
}
