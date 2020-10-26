//=============================================================================
// 
// ���C�t�Q�[�W����(life.h)
// Author : �����D�I
//
//=============================================================================

#include "Life.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "main.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CLife::m_apTexture[LIFETYPE_PLAYER_MAX] = {};

//================================================
//�N���G�C�g����
//================================================
CLife* CLife::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type)
{
	// �I�u�W�F�N�g�𐶐�
	CLife* pLife = new CLife;

	// ����������
	pLife->Init(pos, size, col, type);

	return pLife;
}

//================================================
//�摜�̓ǂݍ���
//================================================
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Life001.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[LIFETYPE_FAST_PLAYER]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Life002.png", //�t�@�C���̓ǂݍ���
		&m_apTexture[LIFETYPE_SECOND_PLAYER]);

	return S_OK;
}

//================================================
//�e�N�X�`���̔j��
//================================================
void CLife::Unload(void)
{
	for (int nCount = 0; nCount < LIFETYPE_PLAYER_MAX; nCount++)
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
CLife::CLife()
{
	m_nCounter = 0;
	m_nCounterLife = 0;
	m_bLife = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�J���[
	m_type = LIFETYPE_NONE;		//�^�C�v

}

//================================================
//�f�X�g���N�^
//================================================
CLife::~CLife()
{

}

//================================================
//����������
//================================================
HRESULT CLife::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type)
{
	m_pos = pos;		//�ʒu���
	m_size = size;		//�T�C�Y
	m_col = col;		//�J���[
	m_type = type;		//�^�C�v

	CGauge::Init(pos, size);	//CGauge�̏�����

	CGauge::BindTexture(m_apTexture[type]); //�e�N�X�`���[�̎擾

	//�ʒu�ݒ�
	CGauge::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//�T�C�Y�ݒ�
	CGauge::SetSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//�J���[�ݒ�
	CGauge::SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));

	return S_OK;
}

//================================================
//�I������
//================================================
void CLife::Uninit(void)
{
	CGauge::Uninit();
}

//================================================
//�X�V����
//================================================
void CLife::Update(void)
{
	CGauge::Update();

	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//�ʒu�̎擾
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR col = GetCol();

	
	//T�L�[��������
	if (pKeyboard->GetPress(DIK_T))
	{
		Decrease(50, true, LIFETYPE_FAST_PLAYER);
	}

	if (pKeyboard->GetPress(DIK_Y))
	{
		Decrease(100, true, LIFETYPE_SECOND_PLAYER);
	}

	//���C�t�����炷����
	if (0 < size.x)
	{
		if (m_bLife == true)
		{
			m_nCounterLife++;

			size.x--;

			//�����̃��C�t�̐F���ς�����Ƃ�
			if (m_type == LIFETYPE_FAST_PLAYER)
			{
				col = D3DCOLOR_RGBA(255, 0, 0, 255);
			}
			//����̃��C�t�̐F���ς�����Ƃ�
			if (m_type == LIFETYPE_SECOND_PLAYER)
			{
				col = D3DCOLOR_RGBA(0, 50, 255, 255);
			}

			if (m_nCounterLife == m_nCount)
			{
				m_bLife = false;
				m_nCounterLife = 0;

				//�����̃��C�t�̐F�����ɖ߂�
				if (m_type == LIFETYPE_FAST_PLAYER)
				{
					col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				//����̃��C�t�̐F�����ɖ߂�
				if (m_type == LIFETYPE_SECOND_PLAYER)
				{
					col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}
		}
	}

	//���C�t�������ȉ��ɂȂ�Ɠ_�ł���悤�ɂ���
	if (size.x < HALF_LIFE)
	{
		m_nCounter++;

		if (m_nCounter == 15)
		{
			col.a = 0.8f;
		}
		else if (m_nCounter == 30)
		{
			col.a = 1.0f;

			m_nCounter = 0;
		}
	}
	
	SetSize(size);
	SetCol(col);
}

//================================================
//�`�揈��
//================================================
void CLife::Draw(void)
{
	CGauge::Draw();
}

//================================================
//���C�t�����炵�Ă�������
//================================================
void CLife::Decrease(int Count, bool Life, LIFETYPE type)
{
	m_nCount = Count;
	m_bLife = Life;
	m_typeDecrease = type;
}