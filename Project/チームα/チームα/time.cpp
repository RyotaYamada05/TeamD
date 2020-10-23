//=============================================================================
//
// �^�C������ [time.cpp]
// Author : �����D�I
//
//=============================================================================
#include "main.h"
#include "time.h"
#include "number.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CTime *pTime = new CTime;

	pTime->Init(pos, D3DXVECTOR3(0.0f,0.0f,0.0f));

	return pTime;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTime::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �i���o�[�e�N�X�`�������[�h
	CNumber::Load();

	m_nTimeCount = 0;

	m_nTime = TIME_LIMIT;

	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		if (nCount < 2)
		{
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount*50.0f, pos.y, 0.0f), D3DXVECTOR3(TIME_S_SIZE_X, TIME_S_SIZE_Y, 0.0f));
		}
		else if (nCount < 3)
		{
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount*45.0f, pos.y+10, 0.0f), D3DXVECTOR3(TIME_MS_SIZE_X, TIME_MS_SIZE_Y, 0.0f));
		}
		else
		{
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount*40.0f, pos.y + 10, 0.0f), D3DXVECTOR3(TIME_MS_SIZE_X, TIME_MS_SIZE_Y, 0.0f));
		}
		
	}

	AddTime(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
			m_apNumber[nCount] = NULL;
		}
	}

	// �����[�X
	Release();

	// �i���o�[�e�N�X�`�����A�����[�h
	CNumber::Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTime::Update(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_apNumber[nCount]->Update();
	}

	m_nTimeCount++;

	if (m_nTimeCount % 1 == 0)
	{
		if (m_nTime > 0)
		{
			AddTime(1);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
// �X�R�A���Z
//=============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime -= nValue;

	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_nTime % (int)powf(10, MAX_TIME - nCount) / powf(10, MAX_TIME - nCount - 1));
	}
}
