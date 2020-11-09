//=============================================================================
//
// 階層構造用のモデル処理 [modelanime.cpp]
// Author : 山田陵太
//
//=============================================================================
#ifndef _MODELANIME_H_
#define _MODELANIME_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

class CModelAnime
{
public:
	typedef struct
	{
		LPD3DXMESH pMesh;			//メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
		DWORD dwNumMat;				//マテリアル情報の数
	}MODEL;

	CModelAnime();
	~CModelAnime();

	static CModelAnime *Create(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);;
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParent(CModelAnime *pParent);
	void SetPosAnime(const D3DXVECTOR3 posAnime);
	D3DXVECTOR3 GetPos(void)const;
	D3DXVECTOR3 GetPosAnime(void)const;
	void SetRotAnime(const D3DXVECTOR3 rotAnime);
	D3DXVECTOR3 GetRot(void)const;
	D3DXVECTOR3 GetRotAnime(void)const;
	D3DXMATRIX GetMtxWorld(void);
private:
	MODEL m_model;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_posAnime;
	D3DXVECTOR3 m_rotAnime;
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	CModelAnime *m_pParent;
};

#endif 