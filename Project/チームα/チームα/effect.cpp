//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCALE_DOWN_NUM		(0.003f)			// �G�t�F�N�g�̌��Z

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[MAX_EFFECT_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	// �C���X�^���X����
	CEffect *pEffect = new CEffect;

	if (pEffect != NULL)
	{
		// ����������
		pEffect->Init(pos, size);				// ���������
		pEffect->SetMove(move);					// �ړ���
		pEffect->BindTexture(m_apTexture[0]);	// �e�N�X�`���ݒ�
		pEffect->SetColor(col);					// �F�̐ݒ�
		pEffect->m_nLife = nLife;				// ���C�t
		pEffect->m_col = col;
	}

	return pEffect;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CEffect::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/effect000.jpg",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CEffect::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_EFFECT_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bScaleDown = false;
	m_pVtxBuff = NULL;
	m_fScale = 1.0f;
	m_fScaleNum = 0.0f;
	m_nLife = 0;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);
	m_Pos = pos;
	m_fScaleNum = SCALE_DOWN_NUM;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	// 2D�|���S���I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	m_nLife--;

	// 2D�|���S���X�V����
	CBillboard::Update();

	// �X�P�[��
	ScaleDown();

	// �������Ȃ肫������
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
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

	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = D3DXCOLOR(0.1f, 0.4f, 1.0f, 1.0f);
	material.Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// 2D�|���S���`�揈��
	CBillboard::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[

	// Z�o�b�t�@�߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	pDevice->SetMaterial(&OldMaterial);					// �}�e���A�������ɖ߂�
	pDevice->LightEnable(0, TRUE);
}

//=============================================================================
// �|���S���k��
//=============================================================================
void CEffect::ScaleDown()
{
	if (m_fScale >= 0.0f)
	{
		// �k���ʂ����Z
		m_fScale -= m_fScaleNum;

		// �T�C�Y�̐ݒ�
		D3DXVECTOR3 size = D3DXVECTOR3(GetSize().x * m_fScale, GetSize().y * m_fScale, 0.0f);

		// �T�C�Y
		SetSize(size);

		D3DXVECTOR3 pos = GetPos();
		SetPos(pos);
	}
	else
	{
		m_fScale = 1.0f;
	}
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CEffect::SetColor(D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pBuff = GetBuff();

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	pBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(20, 20, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(20, 20, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(20, 20, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(20, 20, 255, 255);

	//���_�o�b�t�@�̃A�����b�N
	pBuff->Unlock();
}

//=============================================
// �e�̐ݒ�
//=============================================
void CEffect::SetMove(D3DXVECTOR3 move)
{
	// �ϐ��ɑ��
	m_move = move;
}