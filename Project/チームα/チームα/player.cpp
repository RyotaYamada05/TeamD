//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "joypad.h"
#include "life.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED			(10.0f)				// プレイヤーの移動量
#define PLAYER_DUSH				(15.0f)				// プレイヤーのダッシュ
#define PLAYER_DUSH_INTER		(80)				// ダッシュができる長さ
#define DUSH_NONE_TIME			(100)				// ダッシュできない時間
#define PLAYER_JUMP				(5.0f)				// ジャンプの処理
#define GRAVITY_POWAR			(0.05f)				// 重力の強さ
#define PLAYER_FALL				(-8.0f)				// 急降下の処理
#define GROUND_RIMIT			(0.0f)				// 地面の制限

//=============================================================================
// static初期化
//=============================================================================
LPD3DXMESH CPlayer::m_pMesh = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;	//マテリアル情報へのポインタ
DWORD CPlayer::m_nNumMat = 0;				//マテリアル情報の数
int CPlayer::m_nPlayerAll = 0;

//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// プレイヤーの番号を代入
	pPlayer->m_nPlayerNum = m_nPlayerAll++;

	pPlayer->Init(pos, size);


	return pPlayer;
}

//=============================================================================
// モデルロード
//=============================================================================
HRESULT CPlayer::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// モデルの生成
	D3DXLoadMeshFromX("data/model/TestBox1.x",
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// 正常終了
	return S_OK;
}

void CPlayer::Unload(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	pScore = NULL;
	memset(m_pLife, 0, sizeof(m_pLife));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nDushFlame = 0;
	m_nDushInterCnt = 0;
	m_bJump = false;
	m_bDush = false;
	m_bDushInter = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
	m_nPlayerAll = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	MODEL model;
	model.dwNumMat = m_nNumMat;
	model.pBuffer = m_pBuffMat;
	model.pMesh = m_pMesh;

	//モデル情報を設定
	CModel::BindModel(model);

	m_pos = pos;

	//ライフのロード
	CLife::Load();

	switch (m_nPlayerNum)
	{
	case 0:
		//１Ｐのライフゲージ
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(130.0f,30.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//１Ｐのライフゲージ
		if (m_pLife[1] == NULL)
		{
			m_pLife[1] = CLife::Create(D3DXVECTOR3(860.0f, 65.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}
		break;

	case 1:
		//２Ｐのライフゲージ
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(130.0f, 65.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}

		//２Ｐのライフゲージ
		if (m_pLife[1] == NULL)
		{
			m_pLife[1] = CLife::Create(D3DXVECTOR3(860.0f, 30.0f, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}
		break;

			
	default:
		break;
	}


//	CLife::Create(D3DXVECTOR3(300, 200.0f, 0.0f), D3DXVECTOR3(MAX_LIFE, 20.0f, 0.0f), D3DCOLOR_RGBA(60, 179, 113, 255), CLife::LIFETYPE_FAST_PLAYER);


	// 初期化
	CModel::Init(m_pos, rot);

	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	//ライフのアンロード
	CLife::Unload();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	//位置の取得
	m_pos = CModel::GetPos();
	
	// プレイヤーの制御
	PlayerControl();

	// ダッシュしていないとき
	if (m_bDush == false)
	{
		// 重力をかける
		m_move.y -= GRAVITY_POWAR;
		m_pos.y += m_move.y;		// 落下
	}

	//位置へ移動量を加算
	m_pos += m_move;

	// 地面の制限
	GroundLimit();

	switch (m_nPlayerNum)
	{
	case 0:
		//R2トリガーまたはVキーを押したら
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) ||
			pKeyboard->GetTrigger(DIK_V))
		{
			//バレットの生成
			CBullet::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CBullet::BULLET_USER_PL1);
		}
		break;

	case 1:
		//R2トリガーまたはVキーを押したら
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) ||
			pKeyboard->GetTrigger(DIK_V))
		{
			//バレットの生成
			CBullet::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CBullet::BULLET_USER_PL2);
		}
		break;
	}

	// 座標情報を与える
	CModel::SetPos(m_pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	// ダッシュしていないとき
	if (m_bDush == false)
	{
		// プレイヤーの移動処理
		Walk();
	}

	// ジャンプの処理
	Jump();

	// 急降下の処理
	Fall();

	// 回避の処理
	Dush();
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ジョイパッドの取得
	DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

	if (js.lX != 0.0f || js.lY != 0)
	{
		float fAngle = atan2f((float)js.lX, (float)js.lY);

		if (m_nPlayerNum == 0)
		{
			// ジョイパッド操作
			m_pos.x += sinf(-fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(-fAngle)* PLAYER_SPEED;
		}
		else
		{
			// ジョイパッド操作
			m_pos.x += sinf(+fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(+fAngle)* -PLAYER_SPEED;

		}
	}

	// Wキーを押したとき
	if (pKeyboard->GetPress(DIK_W))
	{
		m_pos.z += cosf(0)*PLAYER_SPEED;
	}
	// Sキーを押したとき
	if (pKeyboard->GetPress(DIK_S))
	{
		m_pos.z += cosf(D3DX_PI)*PLAYER_SPEED;
	}
	// Aキーを押したとき
	if (pKeyboard->GetPress(DIK_A))
	{
		m_pos.x += sinf(-D3DX_PI / 2)*PLAYER_SPEED;
	}
	// Dキーを押したとき
	if (pKeyboard->GetPress(DIK_D))
	{
		m_pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき・コントローラのYを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, m_nPlayerNum) && m_bJump == false
		|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false )
	{
			// ジャンプの処理
			m_move.y = 0.0f;
			m_move.y = PLAYER_JUMP;
			m_bJump = true;
	}
}

//=============================================================================
// 地面の制限
//=============================================================================
void CPlayer::GroundLimit(void)
{
	// 着地の処理
	if (m_pos.y <= GROUND_RIMIT)
	{
		m_move.y = GROUND_RIMIT;
		m_pos.y = GROUND_RIMIT;
		m_bJump = false;
	}
}

//=============================================================================
// 急降下
//=============================================================================
void CPlayer::Fall(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき
	if (pKeyboard->GetTrigger(DIK_B) && m_bJump == true ||
		CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nPlayerNum) && m_bJump == true)
	{
		// ジャンプの処理
		m_move.y = 0.0f;
		m_move.y = PLAYER_FALL;
	}
}

//=============================================================================
// ダッシュ
//=============================================================================
void CPlayer::Dush(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ジャンプが使えるとき
	if (m_bDushInter == false)
	{
		// Xボタンの時
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, m_nPlayerNum))
		{
			// ジョイパッドの取得
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fAngle = atan2f((float)js.lX, (float)js.lY);

				// ジョイパッド操作
				m_move.x += sinf(-D3DX_PI / 2)* PLAYER_DUSH;
				m_move.z -= cosf(-D3DX_PI / 2)* PLAYER_DUSH;
				m_bDush = true;

			}
		}

		// Bボタンの時
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, m_nPlayerNum))
		{
			// ジョイパッドの取得
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fAngle = atan2f((float)js.lX, (float)js.lY);

				// ジョイパッド操作
				m_move.x += sinf(D3DX_PI / 2)* PLAYER_DUSH;
				m_move.z -= cosf(D3DX_PI / 2)* PLAYER_DUSH;
				m_bDush = true;

			}
		}


		// Wキーを押したとき
		if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.z += cosf(0)*PLAYER_DUSH;
			m_bDush = true;
		}
		// Sキーを押したとき
		if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.z += cosf(D3DX_PI)*PLAYER_DUSH;
			m_bDush = true;
		}
		// Aキーを押したとき
		if (pKeyboard->GetPress(DIK_A) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.x -= sinf(D3DX_PI / 2)*PLAYER_DUSH;
			m_bDush = true;
		}
		// Dキーを押したとき
		if (pKeyboard->GetPress(DIK_D) && pKeyboard->GetTrigger(DIK_RSHIFT))
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move.x += sinf(D3DX_PI / 2)*PLAYER_DUSH;
			m_bDush = true;
		}
	}
	else
	{
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		m_nDushInterCnt++;
	}

	// ダッシュしているとき
	if (m_bDush == true)
	{
		// ダッシュが終わるまでをカウント
		m_nDushFlame++;
	}

	// ダッシュが終わるフレーム
	if (m_nDushFlame >= PLAYER_DUSH_INTER)
	{
		m_nDushFlame = 0;
		m_bDush = false;
		m_bDushInter = true;
	}

	// ダッシュができるようになるフレーム
	if (m_nDushInterCnt >= DUSH_NONE_TIME)
	{
		m_nDushInterCnt = 0;
		m_bDushInter = false;
	}
}

CLife * CPlayer::GetLife(int nNumber)
{
	return m_pLife[nNumber];
}
