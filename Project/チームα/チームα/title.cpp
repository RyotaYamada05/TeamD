//=======================================================================================
//
// �w�i�`�揈�� [bg.cpp]
// Author : �ɓ��@�q
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "title.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "conection.h"
#include "tcp_client.h"
#include "fade.h"
#include "titlelogo.h"

//=======================================================================================
//�ÓI�����o�ϐ��錾
//=======================================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[1] = {};
CTitlelogo *CTitle::m_apTitlelogo[MAX_TITLE] = {};

//=======================================================================================
// �^�C�g���N���X�̃R���X�g���N�^
//=======================================================================================
CTitle::CTitle()
{
	m_pScene = NULL;
	m_bModechenge = false;
}

//=======================================================================================
// �^�C�g���N���X�̃f�X�g���N�^
//=======================================================================================
CTitle::~CTitle()
{

}

//=======================================================================================
// �^�C�g���N���X�̃N���G�C�g����
//=======================================================================================
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle();

	pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	return pTitle;
}

//=======================================================================================
// �^�C�g���N���X�̃e�N�X�`���ǂݍ��ݏ���
//=======================================================================================
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg001.png", &m_pTexture[0]);
		return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏���������
//=======================================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene == NULL)
	{
		m_pScene = CScene2d::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		//�e�N�X�`���̐ݒ�
		m_pScene->BindTexture(m_pTexture[0]);
	}

	
	if (m_apTitlelogo[0] == NULL)
	{
		m_apTitlelogo[0] = CTitlelogo::Create(D3DXVECTOR3(TITLE_UI_POS_X, TITLE_UI_POS_Y, 0.0f), D3DXVECTOR3(TITLE_UI_SIZE, TITLE_UI_SIZE, 0.0f), CTitlelogo::LOGOTIPE_UI);
	}
	if (m_apTitlelogo[1] == NULL)
	{
		m_apTitlelogo[1] = CTitlelogo::Create(D3DXVECTOR3(TITLE_PLESS_POS_X, TITLE_PLESS_POS_Y, 0.0f), D3DXVECTOR3(TITLE_PLESS_SIZE_X, TITLE_PLESS_SIZE_Y, 0.0f), CTitlelogo::LOGOTIPE_PRESS);
	}
	if (m_apTitlelogo[2] == NULL)
	{
		m_apTitlelogo[2] = CTitlelogo::Create(D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f), D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f), CTitlelogo::LOGOTIPE_TITLE);
	}
	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏I������
//=======================================================================================
void CTitle::Uninit(void)
{
	if (m_apTitlelogo[0] != NULL)
	{
		m_apTitlelogo[0]->Uninit();
		m_apTitlelogo[0] = NULL;
	}

	if (m_apTitlelogo[1] != NULL)
	{
		m_apTitlelogo[1]->Uninit();
		m_apTitlelogo[1] = NULL;
	}

	if (m_apTitlelogo[2] != NULL)
	{
		m_apTitlelogo[2]->Uninit();
		m_apTitlelogo[2] = NULL;
	}

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}

	
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=======================================================================================
// �^�C�g���N���X�̍X�V����
//=======================================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();


	if (pKey->GetTrigger(DIK_RETURN))
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}
}

//=======================================================================================
// �^�C�g���N���X�̕`�揈��
//=======================================================================================
void CTitle::Draw(void)
{

}