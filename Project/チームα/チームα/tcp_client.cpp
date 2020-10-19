//================================================================================
//
//	
//	Author : �ɓ��@�q
//
//================================================================================

#include "tcp_client.h"

//-------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------
CTcpClient::CTcpClient()
{
	m_sock = -1;
}

//-------------------------------------------------
// �f�X�X�g���N�^
//-------------------------------------------------
CTcpClient::~CTcpClient()
{

}
//-------------------------------------------------
// ����
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
// ����
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
// �ڑ�
//-------------------------------------------------
bool CTcpClient::Init(const char *pHostName, int nPortNum)
{
	// �ڑ���t�p�\�P�b�g�̍쐬
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		return false;
	}

	struct sockaddr_in addr;
	// �ڑ���t���̐ݒ�
	addr.sin_family = AF_INET;                          // IPv4���g���Ƃ���AF_INET���g��
	addr.sin_port = htons(nPortNum);             //�T�[�o�[�̃|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName); // �T�[�o�[�̐ڑ����󂯕t����

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
// ���M
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
// ��M
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
// �ؒf
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
// �J��
//-------------------------------------------------
void CTcpClient::Release(void)
{
	Close();
	delete this;
}