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

//=============================================================================
//マクロ定義
//=============================================================================
#define DISTANCE (300.0f)	//視点～注視点の距離

//=============================================================================
//カメラクラスのコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	//各メンバ変数のクリア
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//カメラの座標
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//カメラの座標（目的地）
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//注視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//注視点（目的地）
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_fDistance = 0.0f;	//視点～注視点の距離
	m_fMove = 0.0f;	//移動量
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
	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_rot.y = 0.0f;
	m_posV = D3DXVECTOR3(0.0f, 150.0f, -m_fDistance);	//位置zはm_fDistance分-方向へ設定する
	m_posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//注視点は全て0座標を見る
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fDistance = sqrtf(
		powf((m_posV.x - m_posR.x), 2) +
		powf((m_posV.z - m_posR.z), 2));

	return S_OK;
}

//=============================================================================
//カメラクラスの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
//カメラクラスの更新処理
//=============================================================================
void CCamera::Update(void)
{
	//キーボードクラス情報の取得
	CInput *pInput = CManager::GetKeyboard();

	//注視点の左旋回
	if (pInput->GetPress(DIK_Q))
	{
		m_rot.y += 5.0f;
		m_posR.x = m_posV.x + sinf(D3DXToRadian(m_rot.y))*m_fDistance;
		m_posR.z = m_posV.z + cosf(D3DXToRadian(m_rot.y))*m_fDistance;
	}
	//注視点の右旋回
	if (pInput->GetPress(DIK_E))
	{
		m_rot.y -= 5.0f;
		m_posR.x = m_posV.x + sinf(D3DXToRadian(m_rot.y))*m_fDistance;
		m_posR.z = m_posV.z + cosf(D3DXToRadian(m_rot.y))*m_fDistance;
	}


	//視点（カメラ座標）の左旋回
	if (pInput->GetPress(DIK_RIGHT))
	{
		m_rot.y -= 5;
		m_posV.x = m_posR.x - sinf(D3DXToRadian(m_rot.y)) * m_fDistance;
		m_posV.z = m_posR.z - cosf(D3DXToRadian(m_rot.y)) * m_fDistance;
	}
	//視点（カメラ座標）の右旋回
	if (pInput->GetPress(DIK_LEFT))
	{
		m_rot.y += 5;
		m_posV.x = m_posR.x - sinf(D3DXToRadian(m_rot.y)) * m_fDistance;
		m_posV.z = m_posR.z - cosf(D3DXToRadian(m_rot.y)) * m_fDistance;
	}

	// キャラ移動時のカメラの位置
	//m_posV += (m_posVDest - m_posV) * 0.001f;

	// キャラ移動時のカメラの向き
	//m_posR += (m_posRDest - m_posR) * 0.1f;

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
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}
