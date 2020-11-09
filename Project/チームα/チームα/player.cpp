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
#include <stdio.h>
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "joypad.h"
#include "charge.h"
#include "camera.h"
#include "life.h"
#include "game.h"
#include "beam.h"
#include "particle.h"
#include "bomb.h"

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
#define LBX_XFAILE_NAME "data/Text/motion_LBX.txt"	//LBXのXファイルパス

//モデルパーツ情報
MODELFILLE g_modelfile[MODEL_PARTS];

//=============================================================================
// static初期化
//=============================================================================
int CPlayer::m_nPlayerAll = 0;				// プレイヤーの総数

//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// プレイヤーの番号を代入
	pPlayer->m_nPlayerNum = m_nPlayerAll++;

	// 初期化処理
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	pScore = NULL;
	memset(m_pLife, 0, sizeof(m_pLife));
	m_pCharge = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nDushFlame = 0;
	m_nDushInterCnt = 0;
	m_bJump = false;
	m_bDush = false;
	m_bDushInter = false;
	m_nPlayerNum = 0;						// プレイヤーの番号
	m_fAngle = 0.0f;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_nNumKey = 0;
	m_apKeyInfo = NULL;
	m_nKey = 0;;
	m_nCountMotion = 0;
	memset(&m_Motion, 0, sizeof(m_Motion));
	m_MotionState = M_MOTION_STATE_IDOL;
	m_nFlame = 0;
		 
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
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//位置の設定
	m_pos = pos;

	switch (m_nPlayerNum)
	{
	//1Pだった場合
	case 0:
		//1Pのライフゲージ		
		if (m_pLife[0] == NULL)
		{
			//1P側に体力ゲージを生成
			m_pLife[0] = CLife::Create(D3DXVECTOR3(LIFE_POS_LEFT_X, LIFE_POS_UP_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//1Pのライフゲージ
		if (m_pLife[1] == NULL)
		{
			//2P側に体力ゲージを生成
			m_pLife[1] = CLife::Create(D3DXVECTOR3(LIFE_POS_RIGHT_X, LIFE_POS_DOWN_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}


		//１Ｐの弾のチャージゲージ
		if (m_pCharge == NULL)
		{
			//2P側に体力ゲージを生成
			m_pCharge = CCharge::Create(D3DXVECTOR3(CHARGE_POS_LEFT_X, CHARGE_POS_Y, 0.0f),
				D3DXVECTOR3(MAX_CHARGE, CHARGE_SIZE_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
		}

		m_rot = D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f);

		break;

	//2Pだった場合
	case 1:
		//２Ｐのライフゲージ
		if (m_pLife[0] == NULL)
		{
			m_pLife[0] = CLife::Create(D3DXVECTOR3(LIFE_POS_RIGHT_X, LIFE_POS_UP_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_PLAYER_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_FAST_PLAYER);
		}

		//１Ｐのライフゲージ		
		if (m_pLife[1] == NULL)
		{
			m_pLife[1] = CLife::Create(D3DXVECTOR3(LIFE_POS_LEFT_X, LIFE_POS_DOWN_Y, 0.0f),
				D3DXVECTOR3(MAX_LIFE, LIFE_SIZE_ENEMY_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255),
				CLife::LIFETYPE_SECOND_PLAYER);
		}

		//２Ｐの弾のチャージゲージ
		if (m_pCharge == NULL)
		{
			m_pCharge = CCharge::Create(D3DXVECTOR3(CHARGE_POS_RIGHT_X, CHARGE_POS_Y, 0.0f),
				D3DXVECTOR3(MAX_CHARGE, CHARGE_SIZE_Y, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		m_rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);

		break;

	default:
		break;
	}
	//ファイル読み込み
	if (FAILED(ReadFile()))
	{
		return E_FAIL;
	}

	//モデルパーツ数分繰り返す
	for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
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
	
	//アニメーションの設定
	SetMotion(M_MOTION_STATE_IDOL);
	SetMotion(M_MOTION_STATE_DUSH);
	//SetMotion(M_MOTION_STATE_JUMP);

	//オブジェクトタイプの設定
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModelNum = 0; nCntModelNum < MODEL_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//終了処理
			m_apModelAnime[nCntModelNum]->Uninit();

			//メモリの削除
			delete m_apModelAnime[nCntModelNum];

			//メモリのクリア
			m_apModelAnime[nCntModelNum] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	
	// プレイヤーの制御
	PlayerControl();

	// ダッシュしていないとき
	if (m_bDush == false)
	{
		// 重力をかける
		m_move.y -= GRAVITY_POWAR;
		m_pos.y += m_move.y;		// 落下
	}

	D3DXVECTOR3 size = m_pLife[0]->GetSize();

	if (size.x <= 0)
	{
		//Uninit();
		return;
	}
	//位置へ移動量を加算
	m_pos += m_move;

	// 地面の制限
	GroundLimit();

	switch (m_nPlayerNum)
	{
	case 0:
		if (CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
		{
			m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Getφ() + D3DXToRadian(90.0f));
		}

		break;

	case 1:
		if (CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
		{
			m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Getφ() + D3DXToRadian(90.0f));
		}

		break;
	}

	//アニメーションの更新処理
	UpdateMotion();

}

//=============================================================================
// アニメーションの更新処理
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey[MODEL_PARTS];	//現在キーと次のキー情報
	KEY *pKeyNext[MODEL_PARTS];
	D3DXVECTOR3 diffPos, diffRot, startPos, startRot, setPos, setRot;
	float fRateMotion;	//現在キーから次キーの相対値

	//現在キーが最大キー数未満の場合
	if (m_nKey < m_Motion[m_MotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
		{
			m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey];

			//現在キーの取得
			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];

			if (m_nKey + 1 == m_Motion[m_MotionState].nNumKey)
			{
				m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[0];
			}
			else
			{
				m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey + 1];
			}

			//次キーの取得
			pKeyNext[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		//相対値の算出
		fRateMotion = (float)m_nCountMotion / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

		for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//1フレーム当たりの更新値 = (終点位置-開始位置) / フレーム数
				diffPos.x = (pKeyNext[nCntModel]->fPosX - startPos.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.y = (pKeyNext[nCntModel]->fPosY - startPos.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.z = (pKeyNext[nCntModel]->fPosZ - startPos.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

				//1フレーム当たりの更新値 = (終点向き-開始向き) / フレーム数
				diffRot.x = (pKeyNext[nCntModel]->fRotX - startRot.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.y = (pKeyNext[nCntModel]->fRotY - startRot.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.z = (pKeyNext[nCntModel]->fRotZ - startRot.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
		
				setPos.x = diffPos.x * m_nCountMotion + startPos.x;
				setPos.y = diffPos.y * m_nCountMotion + startPos.y;
				setPos.z = diffPos.z * m_nCountMotion + startPos.z;
						
				setRot.x = diffRot.x * m_nCountMotion + startRot.x;
				setRot.y = diffRot.y * m_nCountMotion + startRot.y;
				setRot.z = diffRot.z * m_nCountMotion + startRot.z;

				D3DXVECTOR3 pos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 rot = m_apModelAnime[nCntModel]->GetRotAnime();

				//位置に更新用の位置を加算
				pos += setPos;

				//向きに更新用の向きを加算
				rot += setRot;
				
				//位置の設定
				m_apModelAnime[nCntModel]->SetPosAnime(setPos);

				//向きの設定
				m_apModelAnime[nCntModel]->SetRotAnime(setRot);
			}
		}
	
		//モーションカウンターの加算
		m_nCountMotion++;

		//現在キーの再生フレームに達したら
		if (m_nCountMotion == m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame)
		{
			//キーを１つ進める
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//ループするなら
		if (m_Motion[m_MotionState].bLoop == true)
		{
			m_nKey = 0;
		}
		else
		{
			return;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画処理
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

	for (int nCntModelNum = 0; nCntModelNum < MODEL_PARTS; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//階層モデルクラスの描画処理
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}
}

//=============================================================================
// モーションセット処理
//=============================================================================
void CPlayer::SetMotion(MOTION_STATE motion)
{
	m_MotionState = motion;
	m_nKey = 0;
	D3DXVECTOR3 pos, rot;

	for (int nCntModel = 0; nCntModel < MODEL_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//開始位置
			pos.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			pos.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			pos.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

			//開始向き
			rot.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			rot.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			rot.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//位置の設定
			m_apModelAnime[nCntModel]->SetPosAnime(pos);

			//向きの設定
			m_apModelAnime[nCntModel]->SetRotAnime(rot);
		}
	}
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

	// ビームの処理
	beam();

	// ボムの処理
	bomb();
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
		m_fAngle = CGame::GetCamera(m_nPlayerNum)->Getφ();

		if (js.lX < -50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Getφ() - D3DXToRadian(180.0f));
			}

			// ジョイパッド操作

			m_pos.x += sinf(m_fAngle)* PLAYER_SPEED;
			m_pos.z -= cosf(m_fAngle)* PLAYER_SPEED;
		}
		else if (js.lX > 50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Getφ());
			}

			// ジョイパッド操作
			m_pos.x -= sinf(m_fAngle)* PLAYER_SPEED;
			m_pos.z += cosf(m_fAngle)* PLAYER_SPEED;
		}
		else
		{

		}

		if (js.lY < -50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Getφ() + D3DXToRadian(90.0f));
			}

			// ジョイパッド操作
			m_pos.x -= cosf(m_fAngle)* PLAYER_SPEED;
			m_pos.z -= sinf(m_fAngle)* PLAYER_SPEED;
		}
		else if (js.lY > 50.0f)
		{
			if (!CGame::GetCamera(m_nPlayerNum)->GetTargetBool())
			{
				m_rot.y = -(CGame::GetCamera(m_nPlayerNum)->Getφ() + D3DXToRadian(-90.0f));
			}
			// ジョイパッド操作

			m_pos.x += cosf(m_fAngle)* PLAYER_SPEED;
			m_pos.z += sinf(m_fAngle)* PLAYER_SPEED;
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
			SetMotion(M_MOTION_STATE_JUMP);
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
				m_fAngle = CGame::GetCamera(m_nPlayerNum)->Getφ();

				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				// ジョイパッド操作				
				m_move.x += sinf(m_fAngle)* PLAYER_DUSH;
				m_move.z -= cosf(m_fAngle)* PLAYER_DUSH;

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
				m_fAngle = CGame::GetCamera(m_nPlayerNum)->Getφ();

				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				m_move.x -= sinf(m_fAngle)* PLAYER_DUSH;
				m_move.z += cosf(m_fAngle)* PLAYER_DUSH;

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

		int nNum = rand() % 3;

		if (nNum % 3 == 0)
		{
			// 火花の生成
			for (int nCount = 0; nCount < 2; nCount++)
			{
				CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 25.0f, m_pos.z), D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE, SPARK_SPPED);
			}
		}
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

//=============================================================================
// ビーム
//=============================================================================
void CPlayer::beam(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// Lキーを押したとき・コントローラのR1を押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nPlayerNum) && m_bJump == false
		|| pKeyboard->GetTrigger(DIK_L) && m_bJump == false)
	{
		switch (m_nPlayerNum)
		{
		case 0:
			//バレットの生成
			CBeam::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, -BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL1);
			//弾うったらゲージを減らす
			m_pCharge->Reduce(50, true);
			break;

		case 1:
			//バレットの生成
			CBeam::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, BEAM_SPEED), D3DXVECTOR3(BEAM_SIZE_X, BEAM_SIZE_Y, BEAM_SIZE_Z), CBullet2::BULLET2_USER_PL2);
			//弾うったらゲージを減らす
			m_pCharge->Reduce(50, true);
			break;
		}
	}
}

//=============================================================================
// ボム
//=============================================================================
void CPlayer::bomb(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// Lキーを押したとき・コントローラのR1を押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nPlayerNum) && m_bJump == false
		|| pKeyboard->GetTrigger(DIK_V) && m_bJump == false)
	{
		switch (m_nPlayerNum)
		{
		case 0:
			//バレットの生成
			CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z),
				D3DXVECTOR3(0.0f, BOMB_MOVE_Y, -BOMB_SPEED),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL1);
			//弾うったらゲージを減らす
			m_pCharge->Reduce(50, true);
			break;

		case 1:
			//バレットの生成
			CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y +50.0f, m_pos.z), 
				D3DXVECTOR3(0.0f, BOMB_MOVE_Y, BOMB_SPEED),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, BOMB_SIZE_Z), CBullet2::BULLET2_USER_PL2);
			//弾うったらゲージを減らす
			m_pCharge->Reduce(50, true);
			break;
		}
	}

}

CLife * CPlayer::GetLife(int nNumber)
{
	return m_pLife[nNumber];
}

D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

CCharge * CPlayer::GetCgarge(void)
{
	return m_pCharge;
}

//=============================================================================
// ファイル読み込み処理
//=============================================================================
HRESULT CPlayer::ReadFile(void)
{
	FILE *pFile = NULL;	//FILEポインタ
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	//モデルのインデックス
	int nMotionType = 0;	//モーションのタイプ
	int nKeyNum = 0;//キー番号
	int nMotionNum = 0;	//モーション番号

	//ファイルオープン
	pFile = fopen(LBX_XFAILE_NAME, "r");

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
				nModelIndex++;
			}

			if (strcmp(aModeName, "CHARACTERSET") == 0)
			{
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
						nModelIndex++;
					}
				}
			}

			//モーションセット
			if (strcmp(aModeName, "MOTIONSET") == 0)
			{
				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aModeName, "END_MOTIONSET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					//ループ情報の取得
					if (strcmp(aModeName, "LOOP") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
					}

					//キー情報の取得
					if (strcmp(aModeName, "NUM_KEY") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
					}

					if (strcmp(aModeName, "KEYSET") == 0)
					{
						//END_KEYSETになるまで繰り返す
						while (strcmp(aModeName, "END_KEYSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							//フレーム数の取得
							if (strcmp(aModeName, "FRAME") == 0)
							{
								sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
							}

							//各キーのオフセット情報の取得
							if (strcmp(aModeName, "KEY") == 0)
							{
								//END_KEYになるまで繰り返す
								while (strcmp(aModeName, "END_KEY") != 0)
								{
									//一列読み込んでモード情報を抽出
									fgets(aHeadData, sizeof(aHeadData), pFile);
									sscanf(aHeadData, "%s", aModeName);

									//位置の取得
									if (strcmp(aModeName, "POS") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
									}

									//向きの取得
									if (strcmp(aModeName, "ROT") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
									}
								}
								//読み終わったらカウントを1つ進める
								nKeyNum++;
							}
						}
						nKeyNum = 0;
						nMotionNum++;
					}
				}
				nMotionNum = 0;
				nMotionType++;
			}

		} while (strcmp(aModeName, "END_SCRIPT") != 0);


		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK);

		return	E_FAIL;
	}
}
