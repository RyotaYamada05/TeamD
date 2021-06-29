//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture[2] = {};

//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CResult::CResult(int nPriority) : CScene(nPriority)
{
	//�����o�ϐ��̃N���A
	m_pScene2D = NULL;
}

//=============================================================================
//���U���g�N���X�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
//���U���g�N���X�̃N���G�C�g����
//=============================================================================
CResult * CResult::Create(void)
{
	//���U���g�N���X�̃|�C���^�ϐ�
	CResult *pResult = NULL;

	//�������̊m��
	pResult = new CResult;

	//���������m�ۂł��Ă�����
	if (pResult != NULL)
	{
		//�����������Ăяo��
		pResult->Init(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
	}

	return pResult;
}

//=============================================================================
//���U���g�N���X�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CResult::Load(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Result.png", &m_pTexture[0]);

	return S_OK;
}

//=============================================================================
//���U���g�N���X�̏���������
//=============================================================================
HRESULT CResult::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//2D�I�u�W�F�N�g�̐���
	m_pScene2D = CScene2d::Create(pos, size);
	if (m_pScene2D != NULL)
	{
		m_pScene2D->BindTexture(m_pTexture[0]);
	}
	

	return E_NOTIMPL;
}

//=============================================================================
//���U���g�N���X�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
	}

	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=============================================================================
//���U���g�N���X�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard *pKey = CManager::GetKeyboard();
	CFade *pFade = CManager::GetFade();

	if (pKey->GetTrigger(DIK_RETURN))
	{
		if (pFade != NULL)
		{
			pFade->SetFade(CManager::MODE_TYPE_TITLE);
		}
		Uninit();
	}
}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
}
