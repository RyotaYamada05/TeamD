//=============================================================================
//
// �R���e�B�j���[���� [continue.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _CONTINUE_H_
#define _CONTINUE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CNumber;
class CUi;
class CUiEnd;

//=============================================================================
// �}�N����`
//=============================================================================
#define CONTINUE_LIMIT		(15)		// ��������
#define MAX_CONTINUE		(2)			// ����
#define CONTINUE_SIZE_X		(50)		// �����̂w�T�C�Y
#define CONTINUE_SIZE_Y		(50)		// �����̂x�T�C�Y
#define CONTINUE_POS_X		(640.0f)	// �^�C����X���W
#define CONTINUE_POS_Y		(300.0f)		// �^�C����Y���W
#define CONTINUE_INTERVAL	(50)		// �����̒u���Ԋu

//================================================
//�N���X�錾
//================================================
class CContinue :public CScene
{
public:
	CContinue(int nPriority = PRIORITY_0);
	~CContinue();
	static CContinue *Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(int nValue);
	void SetTime(int nTime) { m_nContinue = nTime; }
	int GetTime(void) { return m_nContinue; }
	static CUi *GetUi(void) { return m_pUi; }
	bool GetEnd(void);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;						// �|���S���̈ʒu
	CNumber	*m_apContinue[MAX_CONTINUE];	// �����̔z�u
	int m_nContinue;						// �^�C��
	int m_nContinueCount;					// �^�C���̃J�E���^�[
	static CUi *m_pUi;							// ui�̃|�C���^
	CUiEnd *m_pUiEnd;			// �R���e�B�j���[
	bool m_bEnd;
	bool m_bTimeUp;
};
#endif // !_CONTINUE_H_

