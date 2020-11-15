//=============================================================================
// 
// ���C�t�Q�[�W����(life.h)
// Author : �����D�I
//
//=============================================================================

#ifndef  _LIFE_H_
#define  _LIFE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gauge.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_LIFE			(400)		// ���C�t�̍ő吔(���C�t��X�T�C�Y)
#define HALF_LIFE			(200)		// ���C�t�̔���
#define LIFE_SIZE_PLAYER_Y	(20)		// �v���C���[���C�t��Y�T�C�Y
#define LIFE_SIZE_ENEMY_Y	(10)		// �G�l�~�[���C�t��Y�T�C�Y
#define LIFE_POS_LEFT_X		(130.0f)	// ������ʂ̃��C�t��X���W
#define LIFE_POS_RIGHT_X	(860.0f)	// �E����ʂ̃��C�t��X���W
#define LIFE_POS_UP_Y		(30.0f)		// �㑤���C�t��Y���W
#define LIFE_POS_DOWN_Y		(65.0f)		// �������C�t��Y���W
#define LIFE_TYPE			(2)			// ���C�t�̎��

//=============================================================================
//�N���X�錾
//=============================================================================
class CLife :public CGauge
{
public:
	//�P�o�ƂQ�o���C�t�̃^�C�v����
	typedef enum
	{
		LIFETYPE_NONE = -1,
		LIFETYPE_FAST_PLAYER,		//�P�o���\��
		LIFETYPE_SECOND_PLAYER,		//�Q�o���葤�\��
		LIFETYPE_PLAYER_MAX
	}LIFETYPE;

	CLife();
	~CLife();
	static CLife* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const LIFETYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Decrease(int Reduce,int PlayerNamber,bool Life);
	void Lifereduce(void);
	void LifeFlashing(void);
	void LifeStart(void);
	static void SetReady(bool bReady);
	static bool GetReadey(void);
	float GetLife(void);
	bool GetbLife(void);
	//bool GetLife(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[LIFE_TYPE];	// �e�N�X�`���[�̃|�C���^
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXCOLOR   m_col;									// �J���[
	LIFETYPE    m_type;									// ���C�t�̎��
	LIFETYPE	m_typeDecrease;							// �_���[�W�̎󂯂����̎��
	int m_nCounter;										// �J�E���^�[
	int m_nCounterLife;									// ���炷���̃J�E���^�[
	int m_nReduce;										// �������炷��
	int m_nPlayerNum;									// �P�o���Q�o��
	bool m_bLife;										// ���炷�������g�p���邩���Ȃ���
	static bool m_bStart;								// �X�^�[�g�̏������g�p���邩���Ȃ���
	bool m_bEnd;
	float m_fLife;										// ���C�t
	bool m_bArmor;
};
#endif // ! _LIFE_H_
