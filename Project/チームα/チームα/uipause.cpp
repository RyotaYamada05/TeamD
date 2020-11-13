//================================================
//
// ui���� [ui.cpp]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h
//================================================
#include "uipause.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "life.h"
#include "joypad.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CUiPause::m_apTexture[UISTART_TYPE] = {};

//================================================
//�N���G�C�g����
//================================================
CUiPause* CUiPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, UIPAUSETYPE type)
{
	// �I�u�W�F�N�g�𐶐�
	CUiPause* pUiPause = new CUiPause;

	// ����������
	pUiPause->Init(pos, size, col,type);

	return pUiPause;

}

//================================================
//���[�h����
//================================================
HRESULT CUiPause::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//ready
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/restart.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UIPAUSETYPE_START]);

	//round1
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/titleback.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[UIPAUSETYPE_TITLE]);

	return S_OK;
}

//================================================
//���[�h�̏I��
//================================================
void CUiPause::UnLoad(void)
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
CUiPause::CUiPause()
{
	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���W
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ړ���
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �T�C�Y
	m_type = UIPAUSETYPE_NONE;						// �^�C�v
}

//================================================
//�f�X�g���N�^
//================================================
CUiPause::~CUiPause()
{

}

//================================================
//����������
//================================================
HRESULT CUiPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, UIPAUSETYPE type)
{
	m_pos = pos;	//�ʒu���
	m_size = size;	//�T�C�Y
	m_col = col;
	m_type = type;	//�^�C�v

	//CScene2d�̏�����
	CScene2d::Init(pos, size);

	CScene2d::BindTexture(m_apTexture[type]);

	//�ʒu�ݒ�
	CScene2d::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//�T�C�Y�ݒ�
	CScene2d::SetPolygonSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//�J���[�ݒ�
	CScene2d::SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CScene::OBJTYPE_PAUSE);

	return S_OK;
}

//================================================
//�I������
//================================================
void CUiPause::Uninit(void)
{
	CScene2d::Uninit();
}

//================================================
//�X�V����
//================================================
void CUiPause::Update(void)
{
	CScene2d::Update();

	Select();
}

//================================================
//�`�揈��
//================================================
void CUiPause::Draw(void)
{
	CScene2d::Draw();
}

//================================================
//Select����Ă�F�̕ω��̏���
//================================================
void CUiPause::Select(void)
{
	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	D3DXCOLOR col = GetCol();
	
	//���͂����݂���
	if (js.lX != 0.0f || js.lY != 0.0f)
	{
		if (js.lY < -5)
		{
			if (m_type == UIPAUSETYPE_START)
			{
				col.a = 1.0f;
			}

			if (m_type == UIPAUSETYPE_TITLE)
			{
				col.a = 0.5f;
			}
		}

		if (js.lY > 5)
		{
			if (m_type == UIPAUSETYPE_START)
			{
				col.a = 0.5f;
			}

			if (m_type == UIPAUSETYPE_TITLE)
			{
				col.a = 1.0f;
			}
		}
	}

	SetCol(col);
}