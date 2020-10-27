//=============================================================================
//
// メイン処理 [camera.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define DISTANCE (1000.0f)			//視点～注視点の距離

//=============================================================================
// static初期化
//=============================================================================
int CCamera::m_nCameraAll = 0;

//=============================================================================
// クリエイト
//=============================================================================
CCamera * CCamera::Create(void)
{
	// 初期化処理
	CCamera *pCamera = new CCamera;

	pCamera->Init();

	return pCamera;
}

//=============================================================================
//カメラクラスのコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	//各メンバ変数のクリア
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの座標
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// カメラの座標（目的地）
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 注視点（目的地）
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_fDistance = 0.0f;							// 視点～注視点の距離
	m_fMove = 0.0f;								// 移動量
	m_nCameraNum = m_nCameraAll++;						// カメラの番号
	m_bTarget = true; //ターゲット使用
}

//=============================================================================
//カメラクラスのデストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
//カメラクラスの初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	switch (m_nCameraNum)
	{
	case 0:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_rot.y = 0.0f;

		m_fθ = D3DXToRadian(75.0f);
		m_fφ = D3DXToRadian(0.0f);
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//注視点は全て0座標を見る
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向ベクトル
		m_posV.x = m_posR.x + m_fDistance* sinf(m_fθ) * cosf(m_fφ);
		m_posV.y = m_posR.z + m_fDistance* cosf(m_fθ);
		m_posV.z = m_posR.y + m_fDistance* sinf(m_fθ) * sinf(m_fφ);


		// ビューポートの設定
		//D3DVIEWPORT9 view_port[2];

		//if (m_nCameraNum <= 0)
		//{
		//	m_fMove = 5.0f;
		//	m_fDistance = DISTANCE;
		//	m_rot.y = 0.0f;
		//	m_posV = D3DXVECTOR3(0.0f, 0.0f, -m_fDistance);	//位置zはm_fDistance分-方向へ設定する
		//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 20.0f);	//注視点は全て0座標を見る
		//	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


		//	m_fDistance = sqrtf(
		//		powf((m_posV.x - m_posR.x), 2) +
		//		powf((m_posV.z - m_posR.z), 2));
		//}
		//else
		//{
		//	m_fMove = 5.0f;
		//	m_fDistance = DISTANCE;
		//	m_rot.y = 0.0f;
		//	m_posV = D3DXVECTOR3(0.0f, 100.0f, -m_fDistance);	//位置zはm_fDistance分-方向へ設定する
		//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 20.0f);	//注視点は全て0座標を見る
		//	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


		//	m_fDistance = sqrtf(
		//		powf((m_posV.x - m_posR.x), 2) +
		//		powf((m_posV.z - m_posR.z), 2));
		//}


		//m_fDistance = sqrtf(
		//	powf((m_posV.x - m_posR.x), 2) +
		//	powf((m_posV.z - m_posR.z), 2));


		break;

	case 1:
		m_fMove = 5.0f;
		m_fDistance = DISTANCE;
		m_fθ = D3DXToRadian(75.0f);
		m_fφ = D3DXToRadian(0.0f);
		m_rot.y = 0.0f;
		m_posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);			// 注視点は全て0座標を見る
		m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_posV.x = m_posR.x + m_fDistance* sinf(m_fθ) * cosf(m_fφ);
		m_posV.y = m_posR.z + m_fDistance* cosf(m_fθ);
		m_posV.z = m_posR.y + m_fDistance* sinf(m_fθ) * sinf(m_fφ);


		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
//カメラクラスの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
	m_nCameraAll = 0;
}

//=============================================================================
//カメラクラスの更新処理
//=============================================================================
void CCamera::Update(void)
{

	if (CGame::GetPlayer(m_nCameraNum) != NULL)
	{

		D3DXVECTOR3 pPlayerPos1 = CGame::GetPlayer(m_nCameraNum)->GetPos();
		int nCamera2p = 0;

		if (m_nCameraNum == 0)
		{
			nCamera2p = 1;
		}
		else
		{
			nCamera2p = 0;
		}

	
		D3DXVECTOR3 pPlayerPos2 = CGame::GetPlayer(nCamera2p)->GetPos();
		D3DXVECTOR3 pPlayerPos2rot;


		//キーボードクラス情報の取得
		CInputKeyboard *pKeyInput = CManager::GetKeyboard();

		// ジョイパッドの取得
		//DIJOYSTATE js = CInputJoypad::GetStick(m_nCameraNum);

		if (pKeyInput->GetTrigger(DIK_TAB))
		{
			if (m_bTarget == false)
			{
				m_fθ = D3DXToRadian(75.0f);
				m_fφ = D3DXToRadian(0.0f);
				m_bTarget = true;
			}
			else
			{
				pPlayerPos2rot = pPlayerPos2;
				m_posRRot = pPlayerPos1 - pPlayerPos2;
				m_posVRot = m_posV;
				m_bTarget = false;
			}
		}

		if (m_bTarget == true)
		{
			m_fφ = atan2f(pPlayerPos1.z - pPlayerPos2.z, pPlayerPos1.x - pPlayerPos2.x);

			m_posVDest.x = m_posR.x + m_fDistance * sinf(m_fθ) * cosf(m_fφ) + pPlayerPos1.x - pPlayerPos2.x;
			m_posVDest.y = m_posR.y + m_fDistance * cosf(m_fθ) + pPlayerPos1.y - pPlayerPos2.y;
			m_posVDest.z = m_posR.z + m_fDistance * sinf(m_fθ) * sinf(m_fφ) + pPlayerPos1.z - pPlayerPos2.z;

			m_posRDest = D3DXVECTOR3(pPlayerPos2.x, pPlayerPos2.y, pPlayerPos2.z);

			m_posV += (m_posVDest - m_posV); //カメラフロー
			m_posR += (m_posRDest - m_posR); //カメラフロー
		}
		else
		{
			// キーボード更新
			CInputKeyboard *pKeyboard = CManager::GetKeyboard();

			//視点（カメラ座標）の左旋回
			if (pKeyInput->GetPress(DIK_LEFT))
			{
				m_fφ += D3DXToRadian(1.0f);
			}
			//視点（カメラ座標）の右旋回
			if (pKeyInput->GetPress(DIK_RIGHT))
			{
				m_fφ -= D3DXToRadian(1.0f);
			}
			//視点（カメラ座標）の上旋回
			if (pKeyInput->GetPress(DIK_UP) && m_fθ >= D3DXToRadian(10.0f))
			{
				m_fθ -= D3DXToRadian(1.0f);
			}
			//視点（カメラ座標）の下旋回
			if (pKeyInput->GetPress(DIK_DOWN) && m_fθ <= D3DXToRadian(170.0f))
			{
				m_fθ += D3DXToRadian(1.0f);
			}

#ifdef CAMERA_TEST
			/*m_fφ = atan2f(m_posRRot.z , m_posRRot.x);*/

			m_posVDest.x = m_posR.x + m_fDistance * sinf(m_fθ) * cosf(m_fφ) + pPlayerPos1.x - pPlayerPos2.x;
			m_posVDest.y = m_posR.y + m_fDistance * cosf(m_fθ);
			m_posVDest.z = m_posR.z + m_fDistance * sinf(m_fθ) * sinf(m_fφ) + pPlayerPos1.z - pPlayerPos2.z;

			m_posRDest.x = m_posR.x * sinf(m_fθ) * cosf(m_fφ) + pPlayerPos1.x;
			m_posRDest.y = m_posR.y * cosf(m_fθ);
			m_posRDest.z = m_posR.z * sinf(m_fθ) * sinf(m_fφ) + pPlayerPos1.z;

			/*m_posRDest = D3DXVECTOR3(pPlayerPos2.x, pPlayerPos2.y, pPlayerPos2.z);*/

			m_posV += (m_posVDest - m_posV); //カメラフロー
			m_posR += (m_posRDest - m_posR); //カメラフロー

			////m_fφ = atan2f(m_posRRot.z, m_posRRot.x);

			//m_posVDest.x = m_posR.x + m_fDistance * sinf(m_fθ) * cosf(m_fφ) + pPlayerPos1.x - pPlayerPos2rot.x;
			//m_posVDest.y = m_posR.y + m_fDistance * cosf(m_fθ);
			//m_posVDest.z = m_posR.z + m_fDistance * sinf(m_fθ) * sinf(m_fφ) + pPlayerPos1.z - pPlayerPos2rot.z;

			////m_posRDest.x = m_posR.x + m_fDistance * sinf(m_fθ) * cosf(m_fφ) + m_posRRot.x;
			////m_posRDest.y = m_posR.y + m_fDistance * cosf(m_fθ);
			////m_posRDest.z = m_posR.z + m_fDistance * sinf(m_fθ) * sinf(m_fφ) + m_posRRot.z;

			//m_posRDest = D3DXVECTOR3(pPlayerPos2rot);

			//m_posV += (m_posVDest - m_posV);
			//m_posR += (m_posRDest - m_posR);

			//// キャラ移動時のカメラの位置
			////m_posV += (m_posVDest - m_posV) * 0.001f;

			//// キャラ移動時のカメラの向き
			////m_posR += (m_posRDest - m_posR) * 0.1f;
#endif //CAMERA_TEST

			m_posVDest.x = m_posR.x + m_fDistance * sinf(m_fθ) * cosf(m_fφ);
			m_posVDest.y = m_posR.y + m_fDistance * cosf(m_fθ);
			m_posVDest.z = m_posR.z + m_fDistance * sinf(m_fθ) * sinf(m_fφ);

			m_posRDest = D3DXVECTOR3(pPlayerPos1.x, pPlayerPos1.y + 10, pPlayerPos1.z);

			m_posV += (m_posVDest - m_posV);
			m_posR += (m_posRDest - m_posR);

		}
	}
}

//=============================================================================
//カメラクラスのセット処理
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT / 2,
		10.0f,
		100000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

D3DXVECTOR3 CCamera::GetposV(void)
{
	return m_posV;
}

D3DXVECTOR3 CCamera::GetposR(void)
{
	return m_posR;
}

D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}

bool CCamera::GetTargetBool(void)
{
	return m_bTarget;
}

float CCamera::Getθ(void)
{
	return m_fθ;
}

float CCamera::Getφ(void)
{
	return m_fφ;
}
