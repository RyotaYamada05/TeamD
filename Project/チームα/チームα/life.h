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
#define MAX_LIFE  (400)	//���C�t�̍ő吔
#define HALF_LIFE (200) //���C�t�̔���
//=============================================================================
//�N���X�錾
//=============================================================================
class CLife :public CGauge
{
public:
	//�P�o�ƂQ�o���C�t�̃^�C�v����
	typedef enum
	{
		LIFETYPE_NON = 0,
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
	void Decrease(int CounterLife,bool Life, LIFETYPE type);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_size;	//�T�C�Y
	D3DXCOLOR   m_col;	//�J���[
	LIFETYPE    m_type;	//���C�t�̎��
	LIFETYPE	m_typeDecrease;	//�_���[�W�̎󂯂����̎��

	int m_nCounter;		//�J�E���^�[
	int m_nMaxLife;		//�ő僉�C�t
	int m_nLife;		//���C�t

	int m_nCounterLife;
	int m_nCount;
	bool m_bLife;

};
#endif // ! _LIFE_H_
