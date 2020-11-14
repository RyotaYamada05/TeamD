//================================================
//
// ���b�N�I������ [lockon.cpp]
// Author : �����D�I
//
//================================================

//================================================
// �C���N���[�h
//================================================
#include "lockon.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "player.h"
#include "life.h"
#include "keyboard.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CLockon::m_pTexture = 0;
int CLockon::m_nLockon = 0;

//================================================
//�N���G�C�g����
//================================================
CLockon* CLockon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOCKONTYPE type)
{
	if (m_nLockon < 2)
	{
		// �I�u�W�F�N�g�𐶐�
		CLockon* pLockon = new CLockon;

		m_nLockon++;

		// ����������
		pLockon->Init(pos, size, type);

		return pLockon;
	}
	return S_OK;
}

//================================================
//���[�h����
//================================================
HRESULT CLockon::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Lockon.png", //�t�@�C���̓ǂݍ���
		&m_pTexture);

	return S_OK;
}

//================================================
//���[�h�̏I��
//================================================
void CLockon::Unload(void)
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
CLockon::CLockon()
{
	m_nLockCounter = 0;							// �A�j���[�V�����̃J�E���^�[
	m_nLockPattern = 0;							// �A�j���[�V������
	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���W
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ړ���
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �T�C�Y
	m_type = LOCKONTYPE_NONE;
}

//================================================
//�f�X�g���N�^
//================================================
CLockon::~CLockon()
{

}

//================================================
//����������
//================================================
HRESULT CLockon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOCKONTYPE type)
{
	m_pos = pos;	// �ʒu���
	m_size = size;	// �T�C�Y
	m_type = type;	// �^�C�v

	CScene2d::Init(pos, size);	//CScene2d�̏�����

	CScene2d::BindTexture(m_pTexture);

	//�ʒu�ݒ�
	CScene2d::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//�T�C�Y�ݒ�
	CScene2d::SetPolygonSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//�J���[�ݒ�
	CScene2d::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`���[�ݒ�
	CScene2d::SetAnim(m_nLockPattern, 0.5);

	return S_OK;
}

//================================================
//�I������
//================================================
void CLockon::Uninit(void)
{
	m_nLockon--;
	CScene2d::Uninit();
}

//================================================
//�X�V����
//================================================
void CLockon::Update(void)
{
	CScene2d::Update();
	//�F�̎擾
	D3DXCOLOR col = GetCol();
	m_nLockCounter++;
	if (m_nLockCounter == 8)
	{
		m_nLockPattern++;
		CScene2d::SetAnim(m_nLockPattern, 0.5f);

		m_nLockCounter = 0;
	}

	//���b�N�I��
	if (m_type == LOCKONTYPE_FAST_PLAYER)
	{
		if ((CGame::GetCamera(0)->GetTargetBool() == true))
		{
			col.a = 1.0f;
		}
		else
		{
			col.a = 0.0f;
		}
	}

	if (m_type == LOCKONTYPE_SECOND_PLAYER)
	{
		if ((CGame::GetCamera(1)->GetTargetBool() == true))
		{
			col.a = 1.0f;
		}
		else
		{
			col.a = 0.0f;
		}
	}
	//�F�̐ݒ�
	SetCol(col);
}

//================================================
//�`�揈��
//================================================
void CLockon::Draw(void)
{
	CScene2d::Draw();
}
