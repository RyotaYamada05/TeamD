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
#include "camera.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED			(5.0f)				// プレイヤーの移動量
#define PLAYER_DUSH				(10.0f)				// プレイヤーのダッシュ
#define PLAYER_DUSH_INTER		(80)				// ダッシュができる長さ
#define DUSH_NONE_TIME			(100)				// ダッシュできない時間
#define PLAYER_JUMP				(5.0f)				// ジャンプの処理
#define GRAVITY_POWAR			(0.05f)				// 重力の強さ
#define PLAYER_FALL				(-8.0f)				// 急降下の処理

//=============================================================================
// static初期化
//=============================================================================
LPD3DXMESH CPlayer::m_pMesh = NULL;
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
	pPlayer->Init(pos, size);

	// プレイヤーの番号を代入
	pPlayer->m_nPlayerNum = m_nPlayerAll++;

	return pPlayer;
}

//=============================================================================
// モデルロード
//=============================================================================
HRESULT CPlayer::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// モデルの生成
	D3DXLoadMeshFromX("data/model/box.x",
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

	// 初期化
	CModel::Init(pos, rot);
	m_pos = pos;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
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

	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_V))
	{
		CBullet::Create(m_pos, D3DXVECTOR3(200.0f, 200.0f, 0.0f), CBullet::BULLET_USER_PL1);
	}
	// プレイヤーの制御
	PlayerControl();

	// ダッシュしていないとき
	if (m_bDush == false)
	{
		// 重力をかける
		m_move.y -= GRAVITY_POWAR;
		m_pos.y += m_move.y;		// 落下
	}

	// 地面の制限
	GroundLimit();

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
		float fAngle = CGame::GetCamera(m_nPlayerNum)->Getφ();

		if (js.lX < -50.0f)
		{
			// ジョイパッド操作
			m_pos.x += sinf(fAngle)* PLAYER_SPEED;
			m_pos.z -= cosf(fAngle)* PLAYER_SPEED;
		}
		else if (js.lX > 50.0f)
		{
			// ジョイパッド操作
			m_pos.x -= sinf(fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(fAngle)* PLAYER_SPEED;
		}
		else
		{

		}

		if (js.lY < -50.0f)
		{
			// ジョイパッド操作
			m_pos.x -= cosf(fAngle)* PLAYER_SPEED;
			m_pos.z -= sinf(fAngle)* PLAYER_SPEED;
		}
		else if (js.lY > 50.0f)
		{
			// ジョイパッド操作
			m_pos.x += cosf(fAngle)* PLAYER_SPEED;
			m_pos.z += sinf(fAngle)* PLAYER_SPEED;
		}
		else
		{

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
		m_pos.x -= sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}
	// Dキーを押したとき
	if (pKeyboard->GetPress(DIK_D))
	{
		m_pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}

	// 移動量加算
	m_pos += m_move;
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき・コントローラのYを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(1, m_nPlayerNum) && m_bJump == false 
		|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false )
	{
		// ジャンプの処理
		m_move.y = 0.0f;
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
	}

	// 移動量加算
	m_pos += m_move;
}

//=============================================================================
// 地面の制限
//=============================================================================
void CPlayer::GroundLimit(void)
{
	// 着地の処理
	if (m_pos.y <= 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = 0.0f;
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
		CManager::GetJoypad()->GetJoystickTrigger(2, m_nPlayerNum) && m_bJump == true)
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
		if (CManager::GetJoypad()->GetJoystickTrigger(0, m_nPlayerNum))
		{
			// ジョイパッドの取得
			DIJOYSTATE js = CInputJoypad::GetStick(m_nPlayerNum);

			if (js.lX != 0.0f || js.lY != 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fAngle = atan2f((float)js.lX, (float)js.lY);

				// ジョイパッド操作
				m_move.x += sinf(-D3DX_PI /2)* PLAYER_DUSH;
				m_move.z -= cosf(-D3DX_PI /2)* PLAYER_DUSH;
				m_bDush = true;

			}
		}

		// Bボタンの時
		if (CManager::GetJoypad()->GetJoystickTrigger(3, m_nPlayerNum))
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

D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
