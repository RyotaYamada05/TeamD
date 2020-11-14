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
#include "game.h"
#include "player.h"
#include "life.h"
#include "camera.h"
#include "2d_explosion.h"
#include "shock.h"
#include "model.h"
#include "bill.h"
#include "splash.h"
#include "missile.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MISSILE_XFAILE_NAME "data/Text/motionMissile.txt"	//�~�T�C���̃f�[�^�t�@�C���p�X
#define FOLLOW_TIME_MISSILE		(30)						// �~�T�C���̒Ǐ]
#define MISSILE_LIFE			(1000)						// �~�T�C���̃��C�t

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
	m_nLife = MISSILE_LIFE;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_nCounter = 0;
	m_user = MISSILE_USER_NONE;
	m_pTargetPL = NULL;
	m_nDamage = 0;
	m_fSpeed = 0.0f;
	m_fHeight = 0.0f;
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
CMissile * CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size,
	const MISSILE_USER user, float fSpeed)
{
	//�~�T�C���N���X�̃|�C���^�ϐ�
	CMissile *pMissile = NULL;

	//�C���X�^���X����
	pMissile = new CMissile;

	//���������m�ۂł��Ă�����
	if (pMissile != NULL)
	{
		pMissile->m_fSpeed = fSpeed;
		pMissile->m_user = user;

		//�����������Ăяo��
		pMissile->Init(pos, size);
		//pMissile->SetRot(rot);
		//pMissile->SetMove(move);
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
	m_size = size;

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

	switch (m_user)
	{
	case MISSILE_USER_PL1:
		//2P�̏��擾
		m_pTargetPL = CGame::GetPlayer(1);

		break;
	case MISSILE_USER_PL2:
		//1P�̏��擾
		m_pTargetPL = CGame::GetPlayer(0);

		break;
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
	//�ʒu�̎擾
	m_nCounter++;

	// �ʏ�̏ꍇ
	if (m_nCounter <= FOLLOW_TIME_MISSILE)
	{
		if (m_pTargetPL != NULL)
		{
			//�ړ��ʂ̌v�Z
			m_move = VectorMath(D3DXVECTOR3(
				m_pTargetPL->GetPos().x, m_pTargetPL->GetPos().y + 200.0f, m_pTargetPL->GetPos().z), m_fSpeed);
		}
	}


	//�ړ��ʂ��ʒu�ɗ^����
	m_pos += m_move;

	//���C�t�̐ݒ�
	m_nLife--;

	if (Collision() == true)
	{
		// �̗͂�0
		m_nLife = 0;
	}

	m_pos.y += 0.05f;

	// �G�t�F�N�g����
	CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f), EFFECT_LIFE);

	//���C�t��0�ȉ��̎�
	if (m_nLife <= 0)
	{
		// �Ռ��𐶐�
		CShock::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SHOCK_SIZE_X, SHOCK_SIZE_Y, SHOCK_SIZE_Z));

		//�I�������Ăяo��
		Uninit();
		return;
	}
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

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

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
//�o���b�g�N���X�̓����蔻��
//=============================================================================
bool CMissile::Collision(void)
{

	if (m_pTargetPL != NULL)
	{
		//�ʒu�̎擾
		D3DXVECTOR3 targetPos = m_pTargetPL->GetPos();


		// �����蔻��
		if (targetPos.x + PLAYER_COLLISION_X / 2 >= m_pos.x - 50.0f &&
			targetPos.x - PLAYER_COLLISION_X / 2 <= m_pos.x + 50.0f &&
			targetPos.y + PLAYER_COLLISION_Y >= m_pos.y - 50.0f &&
			targetPos.y - 0.0f <= m_pos.y + 50.0f &&
			targetPos.z + PLAYER_COLLISION_Z / 2 >= m_pos.z - 50.0f &&
			targetPos.z - PLAYER_COLLISION_Z / 2 <= m_pos.z + 50.0f)
		{
			for (int nCount = 0; nCount < LIFE_NUM; nCount++)
			{
				//�@�v���C���[�̃��C�t�����炷
				if (m_pTargetPL != NULL)
				{
					if (m_pTargetPL->GetArmor() == false)
					{
						m_pTargetPL->GetLife(nCount)->Decrease(m_nDamage, m_user, true);
						m_pTargetPL->GetLife(1)->Decrease(m_nDamage, m_user, true);


						m_pTargetPL->SetMotion(MOTION_DAMAGE);
					}

					// �v���C���[���̎擾
					switch (m_user)
					{
					case MISSILE_USER_PL1:
						CGame::GetCamera(1)->SetTarget(false);
						break;
					case MISSILE_USER_PL2:
						CGame::GetCamera(0)->SetTarget(false);
						break;
					}

					// ��������
					C2dExplosion::Create(D3DXVECTOR3(m_pTargetPL->GetPos().x, m_pos.y, m_pTargetPL->GetPos().z),
						D3DXVECTOR3(EXPLOSION_SIZE_X_2D, EXPLOSION_SIZE_Y_2D, EXPLOSION_SIZE_Z_2D));


				}
			}

			m_nLife = 0;
			return true;
		}
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//�擪�����擾
		CScene *pScene = CScene::GetTop(nCount);

		//NULL�ɂȂ�܂ŌJ��Ԃ�
		while (pScene)
		{
			// �I�u�W�F�N�g�^�C�v���擾
			OBJTYPE type = pScene->GetObjType();

			// ���f���Ȃ�
			if (type == OBJTYPE_MODEL)
			{
				// �L���X�g
				CModel *pModel = (CModel*)pScene;
				CModel::MODEL_TYPE type = pModel->GetType();

				// �����Ȃ�
				if (type == CModel::MODEL_TYPE_OBJECT)
				{
					//�ʒu�̎擾
					D3DXVECTOR3 targetPos = pModel->GetPos();

					// �����蔻��
					if (targetPos.x >= m_pos.x - BILL_COLLISION_SIZE_X / 2 &&
						targetPos.x <= m_pos.x + BILL_COLLISION_SIZE_X / 2 &&
						targetPos.y >= m_pos.y - BILL_COLLISION_SIZE_Y / 2 &&
						targetPos.y <= m_pos.y + BILL_COLLISION_SIZE_Y / 2 &&
						targetPos.z >= m_pos.z - BILL_COLLISION_SIZE_Z / 2 &&
						targetPos.z <= m_pos.z + BILL_COLLISION_SIZE_Z / 2)
					{
						for (int nCount = 0; nCount < LIFE_NUM; nCount++)
						{
							// ��������
							CSplash::Create(m_pos,
								D3DXVECTOR3(EXPLOSION_SIZE_X_2D, EXPLOSION_SIZE_Y_2D, EXPLOSION_SIZE_Z_2D));
						}

						m_nLife = 0;
						return true;
					}
				}
			}
			//���̏����擾
			pScene = pScene->GetNext();
		}
	}

	return false;
}

//=============================================================================
//�o���b�g�N���X�̂̃x�N�g���v�Z����
//=============================================================================
D3DXVECTOR3 CMissile::VectorMath(D3DXVECTOR3 TargetPos, float fSpeed)
{

	//2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
	D3DXVECTOR3 Vector = TargetPos - m_pos;

	//�x�N�g���̑傫�������߂�(��c^2 = a^2 * b^2)
	float fVectorSize = D3DXVec3Length(&Vector);

	//�P�ʃx�N�g���p�ϐ�
	D3DXVECTOR3 UnitVector;

	//�P�ʃx�N�g�������߂�(���̃x�N�g�� / �x�N�g���̑傫��)
	D3DXVec3Normalize(&UnitVector, &Vector);

	//�P�ʃx�N�g���𑬓x�{�ɂ��ĕԂ�(UnitVector * fSpeed)
	return	UnitVector * fSpeed;
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
