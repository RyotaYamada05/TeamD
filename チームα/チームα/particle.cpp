//=============================================================================
//
// �X�p�[�N�N���X [particle.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "particle.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CParticle::m_apTexture[MAX_SPARK_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col,
	int nAngle, int nBaseAngle, int nDistance, int nLife, int nSpeed)
{
	// �C���X�^���X����
	CParticle *pParticle = new CParticle;

	if (pParticle != NULL)
	{
		// �����̐ݒ�
		int nDis = rand() % nDistance + rand() % nDistance - rand() % nDistance - rand() % nDistance;

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDis * cosf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))),
			pos.y + nDis * sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))), pos.z + nDis * sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))));

		// ����������
		pParticle->Init(TargetPos, size);

		// �ړ���
		D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * nSpeed,
			sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * +nSpeed,
			sinf(D3DXToRadian(nBaseAngle + (rand() % nAngle - rand() % nAngle))) * nSpeed);

		// �ړ���
		pParticle->SetMove(move);

		// �e�N�X�`���̂̐ݒ�
		pParticle->BindTexture(m_apTexture[0]);

		// ���C�t�̐ݒ�
		pParticle->SetLife(nLife);
	}

	return pParticle;
}


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticle::CParticle()
{
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CParticle::Uninit(void)
{
	// 2D�|���S���I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticle::Update(void)
{
	// ���C�t���Z
	m_nLife--;

	// 2D�|���S���X�V����
	CBillboard::Update();

	// ���C�t��0�ɂȂ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();

		return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CParticle::Draw(void)
{
	// �`�揈��
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[

	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 0.5f;
	material.Ambient.b = 0.0f;
	material.Ambient.a = 1.0f;
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// �`�揈��
	CBillboard::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[

	// Z�o�b�t�@�߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CParticle::SetColor(D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 100, 0, 255);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// ���C�t�̐ݒ�
//=============================================================================
void CParticle::SetLife(int nLife)
{
	m_nLife = nLife - rand() % 30;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CParticle::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/spark.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CParticle::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_SPARK_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}