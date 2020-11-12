//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.cpp]
// Author : �����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CBillboard::CBillboard()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
	m_sizeBase = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �x�[�X�̃T�C�Y
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����7
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pTexture = NULL;							// �|���S���̃e�N�X�`��
	m_nLife = 0;								// ����
	m_bUse = false;								// �g�p����
	m_nCountAnim = 0;;							// �A�j���[�V�����e�N�X�`��
	m_nCountAnimPattern = 0;					// �A�j���[�V�����̃p�^�[��
	m_nCounterAnim = 0;							// �A�j���[�V�����̃J�E���^�[
	m_nPatternAnim = 0;							// �A�j���[�V�����̃p�^�[����
	m_nLoop = -1;								// ���[�v���邩
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

	m_Pos = pos;
	m_size = size;
	m_sizeBase = size;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2, - m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2, - m_size.y / 2, 0.0f);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
{	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CBillboard::Update(void)
{
	m_Pos += m_move;

	// �A�j���[�V�����̐ݒ肪���ꂽ�Ƃ�
	if (m_nPatternAnim != 0)
	{
		// �A�j���[�V�������X�V����
		UpdateAnimation();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
	//�v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	DWORD ambient;

	//���݃A���r�G���g����ۑ�
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);

	pDevice->SetRenderState(D3DRS_AMBIENT, 0xff030303);   // ������Ɣ����Ƃ炷	//���C�e�B���O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	//pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	//pDevice->LightEnable(0, TRUE);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScale,
		m_size.x / m_sizeBase.x,
		m_size.y / m_sizeBase.y,
		0.0f);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

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

//=============================================
// �A�j���[�V�������擾
//=============================================
void CBillboard::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;
	m_nLoop = nLoop;

	// ���_����ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�����X�V�֐�
//=============================================
void CBillboard::UpdateAnimation(void)
{
	// �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;

	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)	// �����̑���
	{
		// �A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnim = 0;

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_nCountAnimPattern++;
	}

	// �A�j���[�V�������I�������
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// ���l��߂��Ă���
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// �I������
			Uninit();
		}
	}
	else
	{
		// ���_����ݒ�
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

LPDIRECT3DVERTEXBUFFER9 CBillboard::GetBuff(void)
{
	return m_pVtxBuff;
}

//=====================================================
// �ʒu�̐ݒ�
//=====================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;

	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2, - m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2, - m_size.y / 2, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �ړ��ʐݒ�
//=====================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=====================================================
// �T�C�Y�ݒ�
//=====================================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CBillboard::SetSizeBase(D3DXVECTOR3 sizeBase)
{
	m_sizeBase = sizeBase;
}

//=====================================================
// �ʒu�̎擾
//=====================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_Pos;
}

//=====================================================
// �ړ��ʏ��
//=====================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return D3DXVECTOR3();
}

//=====================================================
// �T�C�Y���
//=====================================================
D3DXVECTOR3 CBillboard::GetSize(void)
{
	return m_size;
}

//=====================================================
// �e�N�X�`���̐ݒ�
//=====================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}