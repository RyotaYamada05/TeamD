//================================================================================
//
//	
//	Author : 伊藤　航
//
//================================================================================

#ifndef _TCP_CLIANT_H_
#define _TCP_CLIANT_H_

//********************************************************************************
// インクルードファイル
//********************************************************************************
#include "main.h"

//********************************************************************************
// 通信処理クラス
//********************************************************************************
class CTcpClient
{
public:

	CTcpClient();
	~CTcpClient();
	static CTcpClient* Create(const char *pHostName, int nPortNum);
	static CTcpClient* Create(SOCKET sock);
	bool Init(const char *pHostName, int nPortNum);
	bool Init(SOCKET sock);
	int Send(char *pSendData, int nSendDataSize);
	int Recv(char *pRecvBuff, int nRecvDataSize);
	void Close(void);
	void Release(void);

private:

	SOCKET m_sock;
};

#endif // !_TCP_CLIANT_H_
