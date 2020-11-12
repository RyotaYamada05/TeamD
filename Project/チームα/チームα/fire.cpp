//=============================================================================
//
// ���N���X [fire.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "fire.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCALE_DOWN		(0.1f)		// �k���̒l
#define ALPHA_NUM		(0.05f)		// �����x�̒l

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CFire::m_apTexture[MAX_FIRE_TEXTURE] = {};

//=============================================================================
// �C���X�^���X����
//=============================================================================
CFire * CFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
	 int nLife)
{
	// �C���X�^���X����
	CFire *pFire = new CFire;

	if (pFire != NULL)
	{
		// �����̐ݒ�
		int nDis = 
			rand() % FIRE_DISTANCE + rand() % FIRE_DISTANCE - rand() % FIRE_DISTANCE - rand() % FIRE_DISTANCE;

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDis ,
			pos.y + nDis, pos.z + nDis);

		// ����������
		pFire->Init(TargetPos, size);

		// ���x�̐ݒ�
		int nSpeed = 0;
		nSpeed += rand() % 4 + rand() % 4 + rand() % 4;

		// �ړ���
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, nSpeed, 0.0f);

		// �ړ���
		pFire->SetMove(move);

		// �e�N�X�`���̂̐ݒ�
		pFire->BindTexture(m_apTexture[0]);

		// ���C�t�̐ݒ�
		pFire->SetLife(nLife);
	}

	return pFire;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFire::CFire()
{
	m_nLife = 0;
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_fAlpha = 0.0f;
	m_fAlphaNum = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFire::~CFire()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// �k��
	m_fScaleNum = SCALE_DOWN;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFire::Uninit(void)
{
	// 2D�|���S���I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFire::Update(void)
{
	// ���C�t���Z
	m_nLife--;

	// 2D�|���S���X�V����
	CBillboard::Update();

	// �k���̏���
	ScaleDown();

	// �����x
	//Alpha();

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
void CFire::Draw(void)
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
	material.Ambient = D3DXCOLOR(1.0f, 0.4f, 0.05f, 1.0f);
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

	pDevice->SetRenderState(D3DRS_ZENABLE, true);		// Z�o�b�t�@�߂�
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);	// �A���r�G���g�����ɖ߂�
	pDevice->SetMaterial(&OldMaterial);					// �}�e���A�������ɖ߂�
	pDevice->LightEnable(0, TRUE);						// ���C�g��߂�
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CFire::SetColor(D3DXCOLOR col)
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
void CFire::SetLife(int nLife)
{
	m_nLife = nLife - rand() % 30;
}

//=============================================================================
// �k��
//=============================================================================
void CFire::ScaleDown(void)
{
	// �T�C�Y�󂯎��
	D3DXVECTOR3 size = GetSize();

	size.x -= m_fScaleNum;
	size.y -= m_fScaleNum;

	// �T�C�Y�󂯓n��
	SetSize(size);
}

//=============================================================================
// �����x
//=============================================================================
void CFire::Alpha(void)
{

}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CFire::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/fire111.jpg",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CFire::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_FIRE_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}