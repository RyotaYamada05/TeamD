//=============================================================================
//
// ミサイル処理 [missile.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "missile.h"
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MISSILE_XFAILE_NAME "data/Text/motionMissile.txt"	//ミサイルのデータファイルパス

//=============================================================================
//グローバル変数宣言
//=============================================================================
CMissile::MODELFILLEs g_modelfile[MAX_MODEL_MISSILE_PARTS];	//モデルファイルのグローバル変数

//=============================================================================
//ミサイルクラスのコンストラクタ
//=============================================================================
CMissile::CMissile(int nPriority) : CScene(nPriority)
{
	//各メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
}

//=============================================================================
//ミサイルクラスのデストラクタ
//=============================================================================
CMissile::~CMissile()
{
}

//=============================================================================
//ミサイルクラスのクリエイト処理
//=============================================================================
CMissile * CMissile::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	//ミサイルクラスのポインタ変数
	CMissile *pMissile = NULL;

	//インスタンス生成
	pMissile = new CMissile;

	//メモリが確保できていたら
	if (pMissile != NULL)
	{
		//初期化処理呼び出し
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
//ミサイルクラスの初期化処理
//=============================================================================
HRESULT CMissile::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//位置の設定
	m_pos = pos;

	//向きの設定
	m_rot = size;

	//ファイル読み込み
	if (FAILED(ReadFile()))
	{
		return E_FAIL;
	}

	//モデルパーツ数分繰り返す
	for (int nCntModel = 0; nCntModel < MAX_MODEL_MISSILE_PARTS; nCntModel++)
	{
		//モデルの生成
		m_apModelAnime[nCntModel] = CModelAnime::Create(g_modelfile[nCntModel].xFileName,
			g_modelfile[nCntModel].offsetPos, g_modelfile[nCntModel].offsetRot);

		//親子構造の設定
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//親モデルの場合
			if (nCntModel == 0)
			{
				m_apModelAnime[nCntModel]->SetParent(NULL);
			}
			//子モデルの場合
			else
			{
				//自分の親情報を設定する
				m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[g_modelfile[nCntModel].nParent]);
			}
		}
	}
	return S_OK;
}

//=============================================================================
//ミサイルクラスの終了処理
//=============================================================================
void CMissile::Uninit(void)
{
	//モデルパーツ数分繰り返す
	for (int nCntModel = 0; nCntModel < MAX_MODEL_MISSILE_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//階層モデルクラスの終了処理
			m_apModelAnime[nCntModel]->Uninit();

			//メモリの削除
			delete m_apModelAnime[nCntModel];

			//メモリのクリア
			m_apModelAnime[nCntModel] = NULL;
		}
	}

	//オブジェクトの破棄
	SetDeathFlag();
}

//=============================================================================
//ミサイルクラスの更新処理
//=============================================================================
void CMissile::Update(void)
{
	m_pos.y += 0.05f;

	// エフェクト生成
	CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f), EFFECT_LIFE);
}

//=============================================================================
//ミサイルクラスの描画処理
//=============================================================================
void CMissile::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_MISSILE_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//階層モデルクラスの描画処理
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}
}

//=============================================================================
//ミサイルクラスの向きの設定処理
//=============================================================================
void CMissile::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//ミサイルクラスの移動量の設定処理
//=============================================================================
void CMissile::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
//ミサイルクラスのファイル読み込み処理
//=============================================================================
HRESULT CMissile::ReadFile(void)
{
	FILE *pFile = NULL;	//FILEポインタ
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;

	//ファイルオープン
	pFile = fopen(MISSILE_XFAILE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			if (strcmp(aModeName, "MODEL_FILENAME") == 0)
			{
				//Xファイルの名前
				sscanf(aHeadData, "%*s %*s %s %*s %*s", g_modelfile[nModelIndex].xFileName);

				//インデックスを１つ進める
				nModelIndex++;
			}

			if (strcmp(aModeName, "CHARACTERSET") == 0)
			{
				//インデックスを最初に戻す
				nModelIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aModeName, "END_CHARACTERSET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					if (strcmp(aModeName, "PARTSSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aModeName, "END_PARTSSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							if (strcmp(aModeName, "PARENT") == 0)
							{
								//親子情報の設定
								sscanf(aHeadData, "%*s %*s %d", &g_modelfile[nModelIndex].nParent);
							}
							if (strcmp(aModeName, "POS") == 0)
							{
								//位置の設定
								sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetPos.x,
									&g_modelfile[nModelIndex].offsetPos.y, &g_modelfile[nModelIndex].offsetPos.z);
							}
							if (strcmp(aModeName, "ROT") == 0)
							{
								//向きの設定
								sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetRot.x,
									&g_modelfile[nModelIndex].offsetRot.y, &g_modelfile[nModelIndex].offsetRot.z);
							}
						}
						//インデックスを１つ進める
						nModelIndex++;
					}
				}
			}
		} while (strcmp(aModeName, "END_SCRIPT") != 0);

		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//失敗した場合メッセージボックスを表示
		MessageBox(NULL, "モーションファイルを開くのに失敗しました", "ミサイルクラスでのエラー", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}
