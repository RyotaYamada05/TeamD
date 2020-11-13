//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "board.h"
#include "model.h"
#include "manager.h"
#include "conection.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "shape.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "gauge.h"
#include "life.h"
#include "ui.h"
#include "lockon.h"
#include "charge.h"
#include "uistart.h"
#include "fire.h"
#include "bill.h"
#include "continue.h"
#include "uiend.h"
#include "sound.h"
#include "missile.h"

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_apCamera[MAX_PLAYER] = {};		// �J�����N���X�̃|�C���^�ϐ�
CLight *CGame::m_pLight = NULL;						// ���C�g�N���X�̃|�C���^�ϐ�
CMeshField *CGame::m_pMeshField = NULL;				// ���b�V���t�B�[���h
CMeshShape *CGame::m_pSphere = NULL;				// ���b�V���X�t�B�A
CBg *CGame::m_pBg = NULL;							// �w�i�̃|�C���^
CPlayer *CGame::m_apPlayer[MAX_PLAYER] = {};		// �v���C���[�̃|�C���^
CTime *CGame::m_pTime = NULL;						// �^�C���̃|�C���^
CUi *CGame::m_pUi = NULL;							// ui�̃|�C���^

CUiStart *CGame::m_pUiStart = NULL;
CLockon *CGame::m_pLockon = NULL;
CBill *CGame::m_pBill = NULL;

CContinue *CGame::m_pContinue = NULL;
CUiEnd *CGame::m_pUiEnd = NULL;
int CGame::m_nRoundNum = 0;
int CGame::m_aWinNum[MAX_PLAYER] = {};

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
	m_nRoundNum = 0;
}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//�J�����N���X�̃N���G�C�g
		m_apCamera[nCount] = CCamera::Create();
	}

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	//ui
	if (m_pUi == NULL)
	{

		//UI���C�t�Q�[�W(�O�g)�̐���
		m_pUi = CUi::Create(D3DXVECTOR3(330.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);
		m_pUi = CUi::Create(D3DXVECTOR3(1060.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_PLAYERY, 0.0f), CUi::UITTYPE_LIFE);

		m_pUi = CUi::Create(D3DXVECTOR3(330.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);
		m_pUi = CUi::Create(D3DXVECTOR3(1060.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_LIFE_SIZE_X / 2, UI_LIFE_SIZE_ENEMYY, 0.0f), CUi::UITTYPE_LIFE);
		//UI�̃^�C������
		m_pUi = CUi::Create(D3DXVECTOR3(640.0f, 50.0f, 0.0f), D3DXVECTOR3(UI_TIME_SIZE_X, UI_TIME_SIZE_Y, 0.0f), CUi::UITYPE_TIME);

		//UI�̃v���C���[�E�G�l�~�[�����̐���
		m_pUi = CUi::Create(D3DXVECTOR3(70.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
		m_pUi = CUi::Create(D3DXVECTOR3(75.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

		m_pUi = CUi::Create(D3DXVECTOR3(800.0f, 30.0f, 0.0f), D3DXVECTOR3(UI_PLAYER_SIZE_X, UI_PLAYER_SIZE_Y, 0.0f), CUi::UITYPE_PLAYER);
		m_pUi = CUi::Create(D3DXVECTOR3(805.0f, 65.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_SIZE_X, UI_ENEMY_SIZE_Y, 0.0f), CUi::UITYPE_ENEMY);

		//�W������
		m_pUi = CUi::Create(D3DXVECTOR3(UI_LOCKON_POS_LEFT_X, UI_LOCKON_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_SMALL_X, UI_LOCKON_SIZE_SMALL_Y, 0.0f), CUi::UITYPE_STANDARD);
		m_pUi = CUi::Create(D3DXVECTOR3(UI_LOCKON_POS_RIGHT_X, UI_LOCKON_POS_Y, 0.0f), D3DXVECTOR3(UI_LOCKON_SIZE_SMALL_X, UI_LOCKON_SIZE_SMALL_Y, 0.0f), CUi::UITYPE_STANDARD);
	}

	//start��UI
	if (m_pUiStart == NULL)
	{
		//ready����
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_LEFT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_RIGHT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
		//round����
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_LEFT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_1);
		m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_RIGHT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_1);
	}

	//�Ō�ɏo��UI
	/*if (m_pUiEnd == NULL)
	{
		m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, UI_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_CONTINUE_SIZE_X, UI_CONTINUE_SIZE_Y, 0.0f), CUiEnd::UIENDTYPE_CONTINUE);
		m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, 500.0f, 0.0f), D3DXVECTOR3(400, 40, 0.0f), CUiEnd::UIENDTYPE_THANKS);
	}*/

	// �v���C���[�̐���
	if (m_apPlayer[0] == NULL)
	{

		m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, -1000.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));	}
	if (m_apPlayer[1] == NULL)
	{
		m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 1000.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	}

	//�r��
	if (m_pBill == NULL)
	{
		m_pBill = CBill::Create(D3DXVECTOR3(3000.0f, 0.0f, -4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(-3000.0f, 0.0f, -4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(3000.0f, 0.0f, 4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(-3000.0f, 0.0f, 4000.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
		m_pBill = CBill::Create(D3DXVECTOR3(-2000.0f, 0.0f, .0f), D3DXVECTOR3(BILL_SIZE_X, BILL_SIZE_Y, BILL_SIZE_Z));
	}
	CMissile::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// ���b�V���t�B�[���h
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}
	CMeshShape::Load();

	//// ���b�V���X�t�B�A
	//if (m_pSphere == NULL)
	//{
	//	m_pSphere = CMeshShape::Create();
	//}

	// �w�i
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	//�^�C��
	if (m_pTime == NULL)
	{
		m_pTime = CTime::Create(D3DXVECTOR3(TIME_POS_X, TIME_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//�R���e�j���[�̃^�C��
	/*if (m_pContinue == NULL)
	{
		CContinue::Create(D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}*/

	//BGM
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�t�H���g�̐���
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);


	
	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//�J�����N���X�̏I�������Ăяo
			m_apCamera[nCount]->Uninit();

			//�������̔j��
			delete[] * m_apCamera;

			//�������̃N���A
			m_apCamera[nCount] = NULL;
		}
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
	}


	//CMeshShape::UnLoad();
	//// ���b�V���X�t�B�A
	//if (m_pSphere != NULL)
	//{
	//	m_pSphere->Uninit();
	//}

	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
	}

	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	//�Q�[��BGM��~
	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);

	CManager::GetConection()->Uninit();

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apCamera[nCount] != NULL)
		{
			//�J�����N���X�̍X�V����
			m_apCamera[nCount]->Update();
		}
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Update();
	}

	// ���b�V���X�t�B�A
	if (m_pSphere != NULL)
	{
		m_pSphere->Update();
	}

	for (int nCount = 0; nCount < FIRE_NUM; nCount++)
	{
		// ���̐���
		CFire::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f),
			D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
		CFire::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f),
			D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
		CFire::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f),
			D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
		CFire::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f),
			D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
	}

	// �Q�[���̐ݒ�
	SetGame();

	CManager::GetConection()->Update();
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Draw();
	}

	//// ���b�V���X�t�B�A
	//if (m_pSphere != NULL)
	//{
	//	m_pSphere->Draw();
	//}

	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}
}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{

		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			// �v���C���[�̏��擾
			CPlayer *pPlayer = GetPlayer(nCount);
			bool bEnd = pPlayer->GetEnd();

			// �ǂ��炩���I����Ă�����
			if (bEnd == true)
			{
				switch (nCount)
				{
				case 0:
					m_aWinNum[1]++;
					break;
				case 1:
					m_aWinNum[0]++;
					break;
				default:
					break;
				}

				if (m_aWinNum[0] < 2 && m_aWinNum[1] < 2)
				{
					// ���E���h��i�߂�
					m_nRoundNum++;

					// ����������
					ResetGame();

				}
				else
				{
					//�Ō�ɏo��UI
					if (m_pUiEnd == NULL)
					{
						m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, UI_CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(UI_CONTINUE_SIZE_X, UI_CONTINUE_SIZE_Y, 0.0f), CUiEnd::UIENDTYPE_CONTINUE);
						m_pUiEnd = CUiEnd::Create(D3DXVECTOR3(UI_CONTINUE_POS_X, 500.0f, 0.0f), D3DXVECTOR3(400, 40, 0.0f), CUiEnd::UIENDTYPE_THANKS);
					}

					//�R���e�j���[�̃^�C��
					if (m_pContinue == NULL)
					{
						m_pContinue = CContinue::Create(D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					}
				}
				break;
			}
		}
	}
}

//=======================================================================================
// �Q�[���̃��Z�b�g�֐�
//=======================================================================================
void CGame::ResetGame(void)
{
	if (m_apPlayer[0] != NULL)
	{
		m_apPlayer[0]->Init(D3DXVECTOR3(0.0f, 50.0f, -500.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));

		// ���S�̏I��
		m_apPlayer[0]->SetWinToLose(false);
	}
	if (m_apPlayer[1] != NULL)
	{
		m_apPlayer[1]->Init(D3DXVECTOR3(PLAYER2_POS_X, PLAYER2_POS_Y, PLAYER2_POS_Z), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
		m_apPlayer[1]->SetWinToLose(false);
	}

	//�^�C��
	if (m_pTime != NULL)
	{
		m_pTime->Init(D3DXVECTOR3(TIME_POS_X, TIME_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

		switch (m_nRoundNum)
		{
		case 1:
			//ready����
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_LEFT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_RIGHT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			//round����
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_LEFT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_2);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_RIGHT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_2);

			break;
		case 2:
			//ready����
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_LEFT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_READY_POS_RIGHT_X, UI_READY_POS_Y, 0.0f), D3DXVECTOR3(UI_READY_SIZE_X, UI_READY_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_READY);
			//round����
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_LEFT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_3);
			m_pUiStart = CUiStart::Create(D3DXVECTOR3(UI_ROUND_POS_RIGHT_X, UI_ROUND_POS_Y, 0.0f), D3DXVECTOR3(UI_ROUND_SIZE_X, UI_ROUND_SIZE_Y, 0.0f), CUiStart::UISTARTTYPE_ROUND_3);

			break;
		default:
			break;
		
	}
}

//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera * CGame::GetCamera(int nCount)
{
	return m_apCamera[nCount];
}

//=======================================================================================
// ���C�g�̏��
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// �v���C���[�̏��
//=======================================================================================
CPlayer * CGame::GetPlayer(int nCount)
{
	return m_apPlayer[nCount];
}

//=======================================================================================
// �^�C���̏��
//=======================================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

//=======================================================================================
// ui�̏��
//=======================================================================================
CUi * CGame::GetUi(void)
{
	return m_pUi;
}


//=======================================================================================
// uistart�̏��
//=======================================================================================
CUiStart * CGame::GetUiStart(void)
{
	return m_pUiStart;
}

//=======================================================================================
// uiend�̏��
//=======================================================================================
CUiEnd *CGame::GetUiEnd(void)
{
	return m_pUiEnd;
}

CMeshShape * CGame::GetSphere()
{
	return m_pSphere;
}

//=======================================================================================
// ���b�N�I���̏��
//=======================================================================================
CLockon * CGame::GetLockon(void)
{
	return m_pLockon;}

//=======================================================================================
// �r���̏��
//=======================================================================================
CBill * CGame::GetBill(void)
{
	return m_pBill;
}

//=======================================================================================
// �R���e�j���[�̏��
//=======================================================================================
CContinue * CGame::GetContinue(void)
{
	return m_pContinue;
}

