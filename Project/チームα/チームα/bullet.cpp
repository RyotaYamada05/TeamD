//=============================================================================
//
// 処理 [bullet.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "bullet.h"
#include "player.h"
#include "game.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define BULLET_LIFE 60	//バレットライフ 
#define BULLET_ATK 20	//攻撃力

//=============================================================================
//バレットクラスのコンストラクタ
//=============================================================================
CBullet::CBullet()
{
	//各メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//サイズ
	m_user = BULLET_USER_NONE;	//使用者
	m_nAtk = 0;	//攻撃力
	m_nLife = 0;	//ライフ
}

//=============================================================================
//バレットクラスのデストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
//バレットクラスのクリエイト処理
//=============================================================================
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET_USER user)
{
	CBullet *pBullet = NULL;

	//メモリの確保
	pBullet = new CBullet;

	//メモリが確保できていたら
	if (pBullet)
	{
		//初期化処理呼び出し
		pBullet->Init(pos, size, user);
	}
	else
	{
		return NULL;
	}

	return pBullet;
}

//=============================================================================
//バレットクラスの初期化処理
//=============================================================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const BULLET_USER user)
{
	//位置の設定
	m_pos = pos;

	//サイズの設定
	m_size = size;

	//使用者の設定
	m_user = user;

	//ライフの設定
	m_nLife = BULLET_LIFE;

	//攻撃力の設定
	m_nAtk = BULLET_ATK;

	//ビルボードの初期化
	CBillboard::Init(pos, m_size);

	SetObjType(CScene::OBJTYPE_PLAYER);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 10.0f);

	return S_OK;
}

//=============================================================================
//バレットクラスの終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	//ビルボードの終了処理呼び出し
	CBillboard::Uninit();
}

//=============================================================================
//バレットクラスの更新処理
//=============================================================================
void CBullet::Update(void)
{
	//位置の取得
	m_pos = GetPos();

	//移動量を位置に与える
	m_pos += m_move;

	//位置の設定
	SetPos(m_pos);

	if (Collision() == true)
	{
		Uninit();
		return;
	}

	//ライフが0以下の時
	if (m_nLife <= 0)
	{
		//終了処理呼び出し
		Uninit();
		return;
	}

	//ライフの減少
	m_nLife--;
}

//=============================================================================
//バレットクラスの描画処理
//=============================================================================
void CBullet::Draw(void)
{
	//ビルボードの描画処理呼び出し
	CBillboard::Draw();
}

bool CBullet::Collision(void)
{
	CPlayer * pPlayer = NULL;
	switch (m_user)
	{
	case BULLET_USER_PL1:

		//プレイヤークラスへキャスト
		pPlayer = CGame::GetPlayer(1);

		break;
	case BULLET_USER_PL2:
		//プレイヤークラスへキャスト
		pPlayer = CGame::GetPlayer(0);

		break;
	}

	//位置の取得
	D3DXVECTOR3 targetPos = pPlayer->GetPos();

	if (targetPos.x >= m_pos.x - m_size.x / 2 &&
		targetPos.x <= m_pos.x + m_size.x / 2 &&
		targetPos.y >= m_pos.y - m_size.y / 2 &&
		targetPos.y <= m_pos.y + m_size.y / 2 &&
		targetPos.z >= m_pos.z - m_size.x / 2 &&
		targetPos.z <= m_pos.z + m_size.x / 2)
	{
		return true;
	}

	return false;
}
