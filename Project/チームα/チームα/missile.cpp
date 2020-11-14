//=============================================================================
//
// �~�T�C������ [missile.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "missile.h"
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MISSILE_XFAILE_NAME "data/Text/motionMissile.txt"	//�~�T�C���̃f�[�^�t�@�C���p�X

//=============================================================================
//�O���[�o���ϐ��錾
//=============================================================================
CMissile::MODELFILLEs g_modelfile[MAX_MODEL_MISSILE_PARTS];	//���f���t�@�C���̃O���[�o���ϐ�

//=============================================================================
//�~�T�C���N���X�̃R���X�g���N�^
//=============================================================================
CMissile::CMissile(int nPriority) : CScene(nPriority)
{
	//�e�����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
}

//=============================================================================
//�~�T�C���N���X�̃f�X�g���N�^
//=============================================================================
CMissile::~CMissile()
{
}

//=============================================================================
//�~�T�C���N���X�̃N���G�C�g����
//=============================================================================
CMissile * CMissile::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	//�~�T�C���N���X�̃|�C���^�ϐ�
	CMissile *pMissile = NULL;

	//�C���X�^���X����
	pMissile = new CMissile;

	//���������m�ۂł��Ă�����
	if (pMissile != NULL)
	{
		//�����������Ăяo��
		pMissile->Init(pos, size);
		pMissile->SetRot(rot);
		pMissile->SetMove(move);
	}
	else
	{
		return NULL;
	}

	return pMissile;
}

//=============================================================================
//�~�T�C���N���X�̏���������
//=============================================================================
HRESULT CMissile::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	//�����̐ݒ�
	m_rot = size;

	//�t�@�C���ǂݍ���
	if (FAILED(ReadFile()))
	{
		return E_FAIL;
	}

	//���f���p�[�c�����J��Ԃ�
	for (int nCntModel = 0; nCntModel < MAX_MODEL_MISSILE_PARTS; nCntModel++)
	{
		//���f���̐���
		m_apModelAnime[nCntModel] = CModelAnime::Create(g_modelfile[nCntModel].xFileName,
			g_modelfile[nCntModel].offsetPos, g_modelfile[nCntModel].offsetRot);

		//�e�q�\���̐ݒ�
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//�e���f���̏ꍇ
			if (nCntModel == 0)
			{
				m_apModelAnime[nCntModel]->SetParent(NULL);
			}
			//�q���f���̏ꍇ
			else
			{
				//�����̐e����ݒ肷��
				m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[g_modelfile[nCntModel].nParent]);
			}
		}
	}
	return S_OK;
}

//=============================================================================
//�~�T�C���N���X�̏I������
//=============================================================================
void CMissile::Uninit(void)
{
	//���f���p�[�c�����J��Ԃ�
	for (int nCntModel = 0; nCntModel < MAX_MODEL_MISSILE_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//�K�w���f���N���X�̏I������
			m_apModelAnime[nCntModel]->Uninit();

			//�������̍폜
			delete m_apModelAnime[nCntModel];

			//�������̃N���A
			m_apModelAnime[nCntModel] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=============================================================================
//�~�T�C���N���X�̍X�V����
//=============================================================================
void CMissile::Update(void)
{
	m_pos.y += 0.05f;

	// �G�t�F�N�g����
	CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f), EFFECT_LIFE);
}

//=============================================================================
//�~�T�C���N���X�̕`�揈��
//=============================================================================
void CMissile::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_MISSILE_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}
}

//=============================================================================
//�~�T�C���N���X�̌����̐ݒ菈��
//=============================================================================
void CMissile::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//�~�T�C���N���X�̈ړ��ʂ̐ݒ菈��
//=============================================================================
void CMissile::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
//�~�T�C���N���X�̃t�@�C���ǂݍ��ݏ���
//=============================================================================
HRESULT CMissile::ReadFile(void)
{
	FILE *pFile = NULL;	//FILE�|�C���^
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;

	//�t�@�C���I�[�v��
	pFile = fopen(MISSILE_XFAILE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			if (strcmp(aModeName, "MODEL_FILENAME") == 0)
			{
				//X�t�@�C���̖��O
				sscanf(aHeadData, "%*s %*s %s %*s %*s", g_modelfile[nModelIndex].xFileName);

				//�C���f�b�N�X���P�i�߂�
				nModelIndex++;
			}

			if (strcmp(aModeName, "CHARACTERSET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
				nModelIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aModeName, "END_CHARACTERSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					if (strcmp(aModeName, "PARTSSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aModeName, "END_PARTSSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							if (strcmp(aModeName, "PARENT") == 0)
							{
								//�e�q���̐ݒ�
								sscanf(aHeadData, "%*s %*s %d", &g_modelfile[nModelIndex].nParent);
							}
							if (strcmp(aModeName, "POS") == 0)
							{
								//�ʒu�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetPos.x,
									&g_modelfile[nModelIndex].offsetPos.y, &g_modelfile[nModelIndex].offsetPos.z);
							}
							if (strcmp(aModeName, "ROT") == 0)
							{
								//�����̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetRot.x,
									&g_modelfile[nModelIndex].offsetRot.y, &g_modelfile[nModelIndex].offsetRot.z);
							}
						}
						//�C���f�b�N�X���P�i�߂�
						nModelIndex++;
					}
				}
			}
		} while (strcmp(aModeName, "END_SCRIPT") != 0);

		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�~�T�C���N���X�ł̃G���[", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}
