//================================================
//
// ui���� [ui.cpp]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h
//================================================
#include "uistart.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "life.h"
#include "player.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CUiStart::m_apTexture[UISTART_TYPE] = {};

//================================================
//�N���G�C�g����
//================================================
CUiStart* CUiStart::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UISTARTTYPE type)
{
	// �I�u�W�F�N�g�𐶐�
	CUiStart* pUiStart = new CUiStart;

	// ����������
	pUiStart->Init(pos, size, type);

	return pUiStart;

}

//================================================
//���[�h����
//================================================
HRESULT CUiStart::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//ready
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/READY.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UISTARTTYPE_READY]);

	//round1
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/ROUND1.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UISTARTTYPE_ROUND_1]);
	//round2
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/ROUND2.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UISTARTTYPE_ROUND_2]);


	//round3
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/ROUND3.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UISTARTTYPE_ROUND_3]);


	return S_OK;
}

//================================================
//���[�h�̏I��
//================================================
void CUiStart::Unload(void)
{
	for (int nCount = 0; nCount < UISTART_TYPE; nCount++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//================================================
//�R���X�g���N�^
//================================================
CUiStart::CUiStart()
{
	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���W
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ړ���
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �T�C�Y
	m_type = UISTARTTYPE_NONE;						// �^�C�v
}

//================================================
//�f�X�g���N�^
//================================================
CUiStart::~CUiStart()
{

}

//================================================
//����������
//================================================
HRESULT CUiStart::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UISTARTTYPE type)
{
	m_pos = pos;	//�ʒu���
	m_size = size;	//�T�C�Y
	m_type = type;	//�^�C�v

	//CScene2d�̏�����
	CScene2d::Init(pos, size);

	CScene2d::BindTexture(m_apTexture[type]);

	//�ʒu�ݒ�
	CScene2d::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//�T�C�Y�ݒ�
	CScene2d::SetPolygonSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//�J���[�ݒ�
	CScene2d::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//================================================
//�I������
//================================================
void CUiStart::Uninit(void)
{
	CScene2d::Uninit();
}

//================================================
//�X�V����
//================================================
void CUiStart::Update(void)
{
	CScene2d::Update();

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (CGame::GetPlayer(nCount)->GetLife(nCount)->GetReadey() == false)
		{
			Uninit();
			return;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CUiStart::Draw(void)
{
	CScene2d::Draw();
}