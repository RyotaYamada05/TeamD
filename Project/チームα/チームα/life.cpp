//=============================================================================
// 
// ���C�t�Q�[�W����(life.h)
// Author : �����D�I
//
//=============================================================================
#include "main.h"
#include "Life.h"
#include "manager.h"
#include "renderer.h"
#include "ui.h"
#include "sound.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CLife::m_apTexture[LIFETYPE_PLAYER_MAX] = {};
bool CLife::m_bStart = true;

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
	m_nReduce = 0;
	m_nPlayerNum = 0;
	m_bLife = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�J���[
	m_type = LIFETYPE_NONE;		//�^�C�v
	m_bEnd= false;
	m_bStart = true;
	m_fLife = MAX_LIFE;
	m_bArmor = false;
}

//================================================
//�f�X�g���N�^
//================================================
CLife::~CLife()
{
	m_bStart = false;
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
	m_fLife = MAX_LIFE;
	m_bArmor = false;

	CGauge::Init(pos, size);	//CGauge�̏�����

	CGauge::BindTexture(m_apTexture[type]); //�e�N�X�`���[�̎擾

	//�ʒu�ݒ�
	CGauge::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//�T�C�Y�ݒ�
	CGauge::SetSize(D3DXVECTOR3(size.x, size.y, size.z));

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

	if (m_bStart == true)
	{
		//���C�t�̍ŏ��̓���
		LifeStart();
	}
	else
	{
		//���C�t�����炷
		Lifereduce();

		//���C�t�������ɂȂ�Ɠ_�ł�����
		LifeFlashing();
	}
}

//================================================
//�`�揈��
//================================================
void CLife::Draw(void)
{
	CGauge::Draw();
}

//================================================
//���C�t���������炷���̎擾�E�q�b�g�I���o��
//================================================
void CLife::Decrease(int Reduce, int PlayerNamber, bool Life)
{
	if (m_bArmor == false)
	{
		m_fLife -= (float)Reduce;
		m_bArmor = true;
	}
	m_nReduce = Reduce;
	m_bLife = Life;
	m_nPlayerNum = PlayerNamber;

	//�Q�o�ɒe������������P�o�̏ꏊ�ɂg�h�s�̕������o��
	if (m_nPlayerNum == 0)
	{
		CUi::Create(D3DXVECTOR3(UI_HIT_POS_LEFT_X, 600.0f, 0.0f), D3DXVECTOR3(UI_HIT_SIZE_X, UI_HIT_SIZE_Y, 0.0f), CUi::UITYPE_HIT);
	}
	//�P�o�ɒe������������Q�o�̏ꏊ�ɂg�h�s�̕������o��
	if (m_nPlayerNum == 1)
	{
		CUi::Create(D3DXVECTOR3(UI_HIT_POS_RIGHT_X, 600.0f, 0.0f), D3DXVECTOR3(UI_HIT_SIZE_X, UI_HIT_SIZE_Y, 0.0f), CUi::UITYPE_HIT);
	}
}

//================================================
//���C�t�����炷����
//================================================
void CLife::Lifereduce(void)
{
	CSound *pSound = CManager::GetSound();

	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	//�F�̎擾
	D3DXCOLOR col = GetCol();

	//���C�t�����炷����
	if (0 < size.x)
	{

		if (m_bLife == true)
		{
			pSound->Play(CSound::SOUND_LABEL_SE_BOMB);

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

			//���߂�ꂽ�J�E���g������������Ƃɖ߂�
			if (m_nCounterLife == m_nReduce)
			{
				m_bLife = false;
				m_nCounterLife = 0;

				m_bArmor = false;

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
	else
	{
		m_bStart = true;
		size.x = 0.0f;
	}


	//�T�C�Y�̐ݒ�
	SetSize(size);
	//�F�̐ݒ�
	SetCol(col);
}

//================================================
//���C�t�������ɂȂ�Ɠ_�ł�����
//================================================
void CLife::LifeFlashing(void)
{
	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	//�F�̎擾
	D3DXCOLOR col = GetCol();

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

	//�T�C�Y�̐ݒ�
	SetSize(size);
	//�F�̐ݒ�
	SetCol(col);
}

//================================================
//�Q�[���X�^�[�g���̃��C�t�̓���
//================================================
void CLife::LifeStart(void)
{
	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();

	if (m_size.x < MAX_LIFE)
	{
		if (m_bStart == true)
		{
			m_size.x += 2;
		}
	}
	else
	{
		m_bStart = false;
	}
	//�T�C�Y�̐ݒ�
	SetSize(m_size);
}

//================================================
// READY�̐ݒ�
//================================================
void CLife::SetReady(bool bReady)
{
	m_bStart = bReady;
}

//================================================
//READY�̎g�p���Ă邩���ĂȂ����̎擾
//================================================
bool CLife::GetReadey(void)
{
	return m_bStart;
}


float CLife::GetLife(void)
{
	return m_fLife;
}

bool CLife::GetbLife(void)
{
	return m_bLife;
}
