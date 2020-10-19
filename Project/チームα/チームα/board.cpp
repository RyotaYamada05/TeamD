//===================================================
//
// �A�C�e���N���X�w�b�_�[	[item.cpp]
// Author : Konishi Yuuto
//
//===================================================

//===================================================
// �C���N���[�h
//===================================================
#include "board.h"
#include "manager.h"
#include "renderer.h"

//===================================================
// static����������
//===================================================
LPDIRECT3DTEXTURE9 CBoard::m_apTexture[MAX_BOARD_TEXTURE] = {};

//===================================================
// �|���S������
//===================================================
CBoard * CBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBoard *pItem = new CBoard;
	pItem->Init(pos, size);

	// �e�N�X�`���̐ݒ�
	pItem->BindTexture(m_apTexture[0]);

	return pItem;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBoard::Load(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/board000.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBoard::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BOARD_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//===================================================
// �R���X�g���N�^
//===================================================
CBoard::CBoard()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu���
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����7
}

//===================================================
// �f�X�g���N�^
//===================================================
CBoard::~CBoard()
{

}

//===================================================
// ����������
//===================================================
HRESULT CBoard::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CBoard::Uninit(void)
{
	CBillboard::Uninit();
}

//===================================================
// �X�V����
//===================================================
void CBoard::Update(void)
{

}

//===================================================
// �`�揈��
//===================================================
void CBoard::Draw(void)
{
	CBillboard::Draw();
}