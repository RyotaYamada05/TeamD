//=============================================================================
//
// 処理 [conection.h]
// Author : 伊藤　航
//
//=============================================================================

#ifndef _CONECTION_H_
#define _CONECTION_H_

//********************************************************************************
// インクルードファイル
//********************************************************************************
#include "main.h"

//********************************************************************************
// 
//********************************************************************************
#define SERVER_PORT_NUM 12345   // 接続先サーバーの接続先ポート
#define MAX_ACCEPT_CONNECTION 5 // 接続受付最大数
#define BUFFER_NUM 128          // 送受信バッファーサイズ
#define BIT_NUM 8               // ビット数

//********************************************************************************
// 
//********************************************************************************
class CTcpClient;

//********************************************************************************
// 
//********************************************************************************
class CConection
{
public:
	CConection();
	~CConection();
	static CTcpClient *GetClient(void) { return m_pClient; }
	bool GetPlayFlag(void) { return m_bPlay; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	int GetScore(void) { return m_nSore; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool CheckConect(void);
	HRESULT DoConect(void);

private:
	static CTcpClient *m_pClient;
	char m_aRecvBuffer[BUFFER_NUM]; // 返信内容の取得
	char m_aSendBuffer[BUFFER_NUM]; // 送信内容
	D3DXVECTOR3 m_pos;
	bool m_bPlay;
	int m_nSore;
};

#endif // !_CONECTION_H_
