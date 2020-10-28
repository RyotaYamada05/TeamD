//================================================
//
// 数字表示処理 [number.h]
// Author : 佐藤颯紀
//
//================================================

#ifndef  _NUMBER_H_
#define  _NUMBER_H_

#include "main.h"
//================================================
//マクロ定義
//================================================

//================================================
//クラス宣言
//================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;

	D3DXVECTOR3	m_pos;	//ポリゴンの位置
	D3DXVECTOR3 m_size;	//ポリゴンのサイズ

	int m_nNumber;		//ナンバー

};

#endif // ! _NUMBER_H_
