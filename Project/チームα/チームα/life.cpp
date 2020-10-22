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
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//================================================
//�N���G�C�g����
//================================================
CLife* CLife::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type)
{
	// �I�u�W�F�N�g�𐶐�
	CLife* pLife = new CLife();

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
		"Data/TEXTURE/siro.png", //�t�@�C���̓ǂݍ���
		&m_pTexture);

	return S_OK;
}

//================================================
//�e�N�X�`���̔j��
//================================================
void CLife::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
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

	CGauge::BindTexture(m_pTexture); //�e�N�X�`���[�̎擾

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
	//	if (m_type == m_typeDecrease)
		{
			if (m_bLife == true)
			{
				m_nCounterLife++;
				//m_col = D3DCOLOR_RGBA(0.0f,0.0f,0.0f,0.0f);
				size.x--;
				if (m_nCounterLife == m_nCount)
				{
					m_bLife = false;
					m_nCounterLife = 0;
				}
			}
		}
	}

	//���C�t�������ȉ��ɂȂ�Ɠ_�ł���悤�ɂ���
	if (size.x < 200)
	{
		m_nCounter++;

		if (m_nCounter == 10)
		{
			col.a = 0.5f;
		}
		else if (m_nCounter == 20)
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