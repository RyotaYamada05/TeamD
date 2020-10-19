//=============================================================================
//
// ���� [conection.h]
// Author : �ɓ��@�q
//
//=============================================================================

#ifndef _CONECTION_H_
#define _CONECTION_H_

//********************************************************************************
// �C���N���[�h�t�@�C��
//********************************************************************************
#include "main.h"

//********************************************************************************
// 
//********************************************************************************
#define SERVER_PORT_NUM 12345   // �ڑ���T�[�o�[�̐ڑ���|�[�g
#define MAX_ACCEPT_CONNECTION 5 // �ڑ���t�ő吔
#define BUFFER_NUM 128          // ����M�o�b�t�@�[�T�C�Y
#define BIT_NUM 8               // �r�b�g��

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
	char m_aRecvBuffer[BUFFER_NUM]; // �ԐM���e�̎擾
	char m_aSendBuffer[BUFFER_NUM]; // ���M���e
	D3DXVECTOR3 m_pos;
	bool m_bPlay;
	int m_nSore;
};

#endif // !_CONECTION_H_
