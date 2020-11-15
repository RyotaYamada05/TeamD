
//=============================================================================
//
// �^�C������ [time.h]
// Author : �����D�I
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CNumber;

//=============================================================================
// �}�N����`
//=============================================================================
#define TIME_LIMIT		(8000.0f)	// ��������	8000
#define MAX_TIME		(4)			// ����
#define TIME_S_SIZE_X	(50.0f)		// �����̂w�T�C�Y
#define TIME_S_SIZE_Y	(50.0f)		// �����̂x�T�C�Y
#define TIME_MS_SIZE_X	(35.0f)		// �~���b�����̂w�T�C�Y
#define TIME_MS_SIZE_Y	(35.0f)		// �~���b�����̂x�T�C�Y
#define TIME_POS_X		(585.0f)	// �^�C����X���W
#define TIME_POS_Y		(55.0f)		// �^�C����Y���W
#define TIME_INTERVAL	(50.0f)		// �ŏ���2���̐����̒u���Ԋu
#define TIME_INTERVAL2	(45.0f)		// �����_�̐����̒u���Ԋu
#define TIME_INTERVAL3	(40.0f)		// �����_�̐����̒u���Ԋu
#define TIME_INTERVAL_Y	(10.0f)		// Y���̐����̒u���Ԋu

//================================================
//�N���X�錾
//================================================
class CTime : public CScene
{
public:
	CTime(int nPriority = PRIORITY_0);
	~CTime();
	static CTime *Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(int nValue);
	void SetTime(int nTime) { m_nTime = nTime; }
	int GetTime(void) { return m_nTime; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;					// �|���S���̈ʒu
	CNumber	*m_apNumber[MAX_TIME];		// �����̔z�u
	int m_nTime;						// �^�C��
	int m_nTimeCount;					// �^�C���̃J�E���^�[


};
#endif