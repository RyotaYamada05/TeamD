//================================================
//
// �I������ui���� [uiend.cpp]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h
//================================================
#include "uiend.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "life.h"
#include "fade.h"

//================================================
// �}�N����`
//================================================
#define END_TIME	(200)

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CUiEnd::m_apTexture[UIEND_TYPE] = {};

//================================================
//�N���G�C�g����
//================================================
CUiEnd* CUiEnd::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UIENDTYPE type)
{
	// �I�u�W�F�N�g�𐶐�
	CUiEnd* pUiStart = new CUiEnd;

	// ����������
	pUiStart->Init(pos, size, type);

	return pUiStart;

}

//================================================
//���[�h����
//================================================
HRESULT CUiEnd::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/continue000.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UIENDTYPE_CONTINUE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Thanks.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UIENDTYPE_THANKS]);

	return S_OK;
}

//================================================
//���[�h�̏I��
//================================================
void CUiEnd::Unload(void)
{
	for (int nCount = 0; nCount < UIEND_TYPE; nCount++)
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
CUiEnd::CUiEnd()
{
	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���W
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ړ���
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �T�C�Y
	m_type = UIENDTYPE_NONE;						// �^�C�v
	m_nCount = 0;
}

//================================================
//�f�X�g���N�^
//================================================
CUiEnd::~CUiEnd()
{

}

//================================================
//����������
//================================================
HRESULT CUiEnd::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UIENDTYPE type)
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
void CUiEnd::Uninit(void)
{
	CScene2d::Uninit();
}

//================================================
//�X�V����
//================================================
void CUiEnd::Update(void)
{
	CScene2d::Update();

	// �Ō�̃��S�̎�
	if (m_type == UIENDTYPE_THANKS)
	{
		m_nCount++;

		if (m_nCount >= END_TIME)
		{
			// �I������
			Uninit();

			CManager::GetFade()->SetFade(CManager::MODE_TYPE_TITLE);
			return;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CUiEnd::Draw(void)
{
	CScene2d::Draw();
}