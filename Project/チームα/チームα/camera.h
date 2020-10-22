//=============================================================================
//
// メイン処理 [camera.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//===========================================================
//カメラクラス
//=============================================================================
class CCamera
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetposV(void);
	D3DXVECTOR3 GetposR(void);
	D3DXMATRIX GetMtxView(void);
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	D3DXVECTOR3 m_posV;				// カメラの座標
	D3DXVECTOR3 m_posVDest;			// カメラの座標（目的地）
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_posRDest;			// 注視点（目的地）
	D3DXVECTOR3 m_posU;				// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス
	D3DXVECTOR3 m_rot;				// 向き
	float m_fDistance;				// 視点〜注視点の距離
	float m_fMove;					// 移動量
	static int m_nCountAll;			// カメラの数
	int m_nNum;						// カメラの番号
	
};
#endif 