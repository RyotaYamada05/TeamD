//=============================================================================
//
// ���C������ [life.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[CPolygon::TEX_TYPE_MAX] = {};

//=============================================================================
//�|���S���N���X�̃R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	//�e�����o�ϐ��̃N���A
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = TEX_TYPE_NORE;
}

//=============================================================================
//�|���S���N���X�̃f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
//�|���S���N���X�̃N���G�C�g����
//=============================================================================
CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX_TYPE type )
{
	//�|���S���N���X�̃|�C���^�ϐ�
	CPolygon *pPolygon = NULL;

	//�������̊m��
	pPolygon = new CPolygon;

	//���������m�ۂł��Ă�����
	if (pPolygon != NULL)
	{
		//�����������Ăяo��
		pPolygon->Init(pos, size, type);
	}
	else
	{
		return NULL;
	}

	return pPolygon;
}

//=============================================================================
//�|���S���N���X�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CPolygon::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	m_pTexture[TEX_TYPE_NORE] = NULL;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/Title.png", &m_pTexture[TEX_TYPE_TITLE]);	//�^�C�g��
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/Result.png", &m_pTexture[TEX_TYPE_RESULET]);	//���U���g
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/gaugebar.png", &m_pTexture[TEX_TYPE_LIFE_GAUGE]);	//���C�t
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/UnderUI.png", &m_pTexture[TEX_TYPE_UNDERUI]);	//UnderUI

	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/�`�[�^�[.png", &m_pTexture[TEX_TYPE_CHEETAH]);	//�`�[�^�[
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/�S����.png", &m_pTexture[TEX_TYPE_GORILLA]);	//�S����
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/�T.png", &m_pTexture[TEX_TYPE_TURTLE]);	//�J��
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/PRESS  ENTER.png", &m_pTexture[TEX_TYPE_PRESSENTER]);	//PRESS ENTER�e�N�X�`��

	return S_OK;
}

//=============================================================================
//�|���S���N���X�̃e�N�X�`���j������
//=============================================================================
void CPolygon::UnLoad(void)
{
	for (int nCount = 0; nCount < TEX_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//�|���S���N���X�̏���������
//=============================================================================
HRESULT CPolygon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX_TYPE type)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//�����ʒu�̐ݒ�
	m_pos = pos;

	//�傫���̐ݒ�
	m_Size = size;

	//�e�N�X�`���̐ݒ�
	m_Type = type;

	//���_�o�b�t�@�̍쐬
	pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,	//�i�Œ�j
		FVF_VERTEX_2D,	//�t�H�[�}�b�g
		D3DPOOL_MANAGED,	//(�Œ�)
		&m_pVtxBuff,
		NULL
	);

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_Size.x / 2), m_pos.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_Size.x / 2), m_pos.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_Size.x / 2), m_pos.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_Size.x / 2), m_pos.y + (m_Size.y / 2), 0.0f);

	//rhw�̐ݒ�i�l��1.0�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//�|���S���N���X�̏I������
//=============================================================================
void CPolygon::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//�|���S���N���X�̍X�V����
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
//�|���S���N���X�̕`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, m_pTexture[m_Type]);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		NUM_POLYGON);	//�|���S����

	//�e�N�X�`���̐ݒ�����ɖ߂�
	pD3DDevice->SetTexture(0, NULL);
}

void CPolygon::SetType(const TEX_TYPE type)
{
	m_Type = type;
}

void CPolygon::SetColor(const D3DXCOLOR color)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
