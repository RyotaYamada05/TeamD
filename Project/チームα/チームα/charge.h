//=============================================================================
// 
// �e�̃`���[�W�Q�[�W�̏���(charge.h)
// Author : �����D�I
//
//=============================================================================

#ifndef _CHARGE_H_
#define _CHARGE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gauge.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_CHARGE			(400)		// �Q�[�W�̍ő吔(�Q�[�W��X�T�C�Y)
#define HALF_CHARGE			(200)		// �Q�[�W�̔���
#define CHARGE_POS_LEFT_X	(120.0f)	// �����̃Q�[�W��X���W
#define CHARGE_POS_RIGHT_X	(760.0f)	// �E���̃Q�[�W��X���W
#define CHARGE_POS_Y		(680.0f)	// �Q�[�W��Y���W
#define CHARGE_SIZE_Y		(15)		// �Q�[�W��Y�T�C�Y

//=============================================================================
//�N���X�錾
//=============================================================================
class CCharge :public CGauge
{
public:
	CCharge();
	~CCharge();

	static CCharge* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Reduce(int Counter, bool Charge);
	void GaugeRedce(void);
	void GaugeReturn(void);
	void GaugeMax(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR   m_col;						// �J���[
	int m_nCounterCharge;					// ���炷���̃J�E���^�[
	int m_nReduce;							// �������炷��
	int m_nMaxCounter;						// �Q�[�W�ő�̂Ƃ��̃J�E���^�[
	bool m_bCharge;							// ���炷�������g�p���邩���Ȃ���
	float m_nBlue;							// �F�̐ݒ�
	float m_nRed;							// �ԐF�̐ݒ�
};

#endif // !_CHARGE_H_
