//=============================================================================
// 
// �e�̃`���[�W�Q�[�W�̏���(charge.cpp)
// Author : �����D�I
//
//=============================================================================
#include "main.h"
#include "charge.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "life.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CCharge::m_pTexture = {};
float CCharge::m_fLimit[CHARGE_LIMIT] = {};

//================================================
//�N���G�C�g����
//================================================
CCharge* CCharge::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col)
{
	// �I�u�W�F�N�g�𐶐�
	CCharge* pCharge = new CCharge();

	// ����������
	pCharge->Init(pos, size, col);

	return pCharge;
}

//================================================
//�摜�̓ǂݍ���
//================================================
HRESULT CCharge::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/gage.png", //�t�@�C���̓ǂݍ���
		&m_pTexture);

	return S_OK;
}

//================================================
//�e�N�X�`���̔j��
//================================================
void CCharge::Unload(void)
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
CCharge::CCharge()
{
	m_nCounterCharge = 0;
	m_nReduce = 0;
	m_nMaxCounter = 0;
	m_bCharge = false;
	m_nBlue = 0.00f;
	m_nRed = 0.00f;
	m_nPlayerNum = 0;
}

//================================================
//�f�X�g���N�^
//================================================
CCharge::~CCharge()
{

}

//================================================
//����������
//================================================
HRESULT CCharge::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col)
{
	m_pos = pos;		//�ʒu���
	m_size = size;		//�T�C�Y
	m_col = col;		//�J���[

	for (int nCount = 0; nCount < CHARGE_LIMIT; nCount++)
	{
		m_fLimit[nCount] = m_size.x;
	}

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
void CCharge::Uninit(void)
{
	CGauge::Uninit();
}

//================================================
//�X�V����
//================================================
void CCharge::Update(void)
{
	CGauge::Update();

	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//Ready���������瓮���o��
	if (CLife::GetReadey() == false)
	{
		//�Q�[�W�����鏈��
		GaugeRedce();
		//�Q�[�W�����ɖ߂�����
		GaugeReturn();
		//�Q�[�W���ő�̎��̏���
		GaugeMax();
	}
}

//================================================
//�`�揈��
//================================================
void CCharge::Draw(void)
{
	CGauge::Draw();
}

//================================================
//�������炷���̎w��
//================================================
void CCharge::Reduce(int Counter, bool Charge,int player)
{
	m_nReduce = Counter;
	m_bCharge = Charge;
	m_nPlayerNum = player;
}

//================================================
//�Q�[�W�����炵�Ă�������
//================================================
void CCharge::GaugeRedce(void)
{
	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	//�F�̎擾
	D3DXCOLOR col = GetCol();

	//�Q�[�W�����炷����
	if (0 < size.x)
	{
		if (m_bCharge == true)
		{
			m_nCounterCharge++;
			col = D3DCOLOR_RGBA(87, 210, 128, 255);
			size.x -= 2;

			m_fLimit[m_nPlayerNum] -= 2;

		}

		//���߂�ꂽ�J�E���g������������Ƃɖ߂�
		if (m_nCounterCharge == m_nReduce)
		{
			m_bCharge = false;
			m_nCounterCharge = 0;
		}
	}
	else
	{
		m_bCharge = false;
	}

	//�T�C�Y�̐ݒ�
	SetSize(size);
	//�F�̐ݒ�
	SetCol(col);
}

//================================================
//�Q�[�W�����ɖ߂�����
//================================================
void CCharge::GaugeReturn(void)
{
	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	//�F�̎擾
	D3DXCOLOR col = GetCol();

	//�ő吔���Q�[�W�������Ă���ő吔�܂Ŗ߂�����
//	if (size.x < MAX_CHARGE && m_bCharge == false || size.x < 0)
	if (size.x < MAX_CHARGE&& m_bCharge == false && size.x > -1500.0f)
	{
		m_nBlue = size.x / 4 * 0.01f;
		m_nRed = 1.0f - m_nBlue;

		size.x +=2;

		m_fLimit[m_nPlayerNum] +=2;

		col = D3DXCOLOR(m_nRed, 0.0f, m_nBlue, 1.0f);
		m_nMaxCounter = 0;
	}

	//�T�C�Y�̐ݒ�
	SetSize(size);
	//�F�̐ݒ�
	SetCol(col);
}

//================================================
//�Q�[�W���ő�̎��̏���
//================================================
void CCharge::GaugeMax(void)
{
	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	//�F�̎擾
	D3DXCOLOR col = GetCol();

	//�ő�l�̎��̏���
	if (size.x == MAX_CHARGE)
	{
		m_nMaxCounter++;
		//�J�E���^�[����萔�����ĂȂ��Ԃ͕\��
		if (m_nMaxCounter < 100)
		{
			col = D3DCOLOR_RGBA(87, 210, 128, 255);
		}

		//�J�E���^�[����萔�ɍs���Ε\��������
		if (m_nMaxCounter == 100)
		{
			col = D3DCOLOR_RGBA(0, 0, 0, 0);
		}
	}

	//�T�C�Y�̐ݒ�
	SetSize(size);
	//�F�̐ݒ�
	SetCol(col);
}

//================================================
//�e�̐��䂷��v���C���[�̔ԍ����擾����
//================================================
float CCharge::GetCharge(int nPlayer)
{
	return m_fLimit[nPlayer];
}