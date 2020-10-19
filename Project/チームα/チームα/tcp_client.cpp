//================================================================================
//
//	
//	Author : 伊藤　航
//
//================================================================================

#include "tcp_client.h"

//-------------------------------------------------
// コンストラクタ
//-------------------------------------------------
CTcpClient::CTcpClient()
{
	m_sock = -1;
}

//-------------------------------------------------
// デスストラクタ
//-------------------------------------------------
CTcpClient::~CTcpClient()
{

}
//-------------------------------------------------
// 生成
//-------------------------------------------------
CTcpClient* CTcpClient::Create(const char *pHostName, int nPortNum)
{
	CTcpClient *pTcpClient = new CTcpClient;
	if (pTcpClient->Init(pHostName, nPortNum) == false)
	{
		delete pTcpClient;
		pTcpClient = NULL;
	}
	return pTcpClient;
}

//-------------------------------------------------
// 生成
//-------------------------------------------------
CTcpClient* CTcpClient::Create(SOCKET sock)
{
	CTcpClient *pTcpClient = new CTcpClient;
	if (pTcpClient->Init(sock) == false)
	{
		delete pTcpClient;
		pTcpClient = NULL;
	}
	return pTcpClient;
}

//-------------------------------------------------
// 接続
//-------------------------------------------------
bool CTcpClient::Init(const char *pHostName, int nPortNum)
{
	// 接続受付用ソケットの作成
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		return false;
	}

	struct sockaddr_in addr;
	// 接続受付情報の設定
	addr.sin_family = AF_INET;                          // IPv4を使うときはAF_INETを使う
	addr.sin_port = htons(nPortNum);             //サーバーのポート番号
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName); // サーバーの接続を受け付ける

	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		return false;
	}
	return true;
}

bool CTcpClient::Init(SOCKET sock)
{
	m_sock = sock;
	return true;
}

//-------------------------------------------------
// 送信
//-------------------------------------------------
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	if (m_sock < 0)
	{
		return 0;
	}
	int nSendSize = send(m_sock, pSendData, nSendDataSize, 0);
	return nSendSize;
}

//-------------------------------------------------
// 受信
//-------------------------------------------------
int CTcpClient::Recv(char *pRecvBuff, int nRecvDataSize)
{
	if (m_sock < 0)
	{
		Close();
	}
	int nRecvSize = recv(m_sock, pRecvBuff, nRecvDataSize, 0);
	return nRecvSize;
}

//-------------------------------------------------
// 切断
//-------------------------------------------------
void CTcpClient::Close()
{
	if (m_sock < 0)
	{
		return;
	}
	closesocket(m_sock);
	m_sock = -1;
}

//-------------------------------------------------
// 開放
//-------------------------------------------------
void CTcpClient::Release(void)
{
	Close();
	delete this;
}