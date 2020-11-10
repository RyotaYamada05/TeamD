#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define THROWING_COUNTS		(3)			// �����邱�Ƃ��ł����
#define LIFE_NUM			(2)			// �\�����郉�C�t�̐�
#define MAX_PARTS			(10)		// �p�[�c�̐�
#define MOTION_KEYSET_MAX	(32)		// �L�[�Z�b�g�ő吔

#define PLAYER1_POS_X		(0.0f)		// ���W
#define PLAYER1_POS_Y		(171.0f)	// ���W
#define PLAYER1_POS_Z		(0)			// ���W

#define PLAYER2_POS_X		(0.0f)		// ���W
#define PLAYER2_POS_Y		(171.0f)	// ���W
#define PLAYER2_POS_Z		(500)		// ���W

#define PLAYER_SIZE_X		(1)			// �T�C�Y
#define PLAYER_SIZE_Y		(1)			// �T�C�Y
#define PLAYER_SIZE_Z		(1)			// �T�C�Y

#define PLAYER_COLLISION_X	(200)		// �����蔻��
#define PLAYER_COLLISION_Y	(350)		// �����蔻��
#define PLAYER_COLLISION_Z	(200)		// �����蔻��

#define PLAYER_RADIUS		(200)		// ���a

//=============================================================================
// �O���錾
//=============================================================================
class CScore;
class CLife;
class CCharge;
class CBoost;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CModel
{
public:

	typedef enum
	{
		PLAYER_STATE_NONE = 0,		// �����u
		PLAYER_STATE_NORMAL,		// �ʏ���
		PLAYER_STATE_DAMAGE,		// �_���[�W
		PLAYER_STATE_EXPLOSION,		// ����
		PLAYER_STATE_MAX
	}PLAYER_STATE;

	CPlayer();						// �R���X�g���N�^
	~CPlayer();						// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g
	static HRESULT LoadModel(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void PlayerState(void);											// �v���C���[�̏��
	void PlayerControl(void);										// �v���C���[�̐���
	void Walk(void);												// �v���C���[�̕�������
	void Jump(void);												// �W�����v�̏���
	void GroundLimit(void);											// �n�ʂ̐���
	void Fall(void);												// �}�~��
	void Dush(void);												// �_�b�V��
	void beam(void);												// �r�[��
	void bomb(void);												// �{��
	void Laser(void);												// ���[�U�[
	void BlockUp(void);												// �u���b�N�̏�ɏ�����Ƃ�
	D3DXVECTOR3 GetPos(void);										// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void);									// �Â����W���
	void SetMove(D3DXVECTOR3 move);										// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 GetMove(void);
	CLife *GetLife(int nNumber);									// ���C�t�̏��
	CCharge *GetCgarge(void);										// �`���[�W�̃|�C���^
	bool GetEnd(void);												// �G���h���
	PLAYER_STATE GetState(void);									// �v���C���[�̏��

private:
	CScore *pScore;							// �X�R�A�̏��
	CLife *m_pLife[LIFE_NUM];				// ���C�t�̃|�C���^
	CBoost *m_pBoost;						// �u�[�X�g�̃|�C���^
	CCharge *m_pCharge;						// �`���[�W�̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_OldPos;					// 1�t���[���O�̍��W
	D3DXVECTOR3 m_rot;						// ��]
	D3DXVECTOR3 m_move;						// �ړ�
	PLAYER_STATE m_state;					// �v���C���[���
	float m_fAngle;							// �p�x
	int m_nDushFlame;						// �_�b�V���̃t���[��
	int m_nDushInterCnt;					// �_�b�V���ł��Ȃ��Ƃ��̃J�E���g
	int m_nPlayerNum;						// �v���C���[�̔ԍ�
	int m_nStateCounter;					// ��ԃJ�E���^�[
	bool m_bJump;							// �W�����v�̃t���O
	bool m_bDush;							// �_�b�V���̏���
	bool m_bDushInter;						// �_�b�V���̃C���^�[�o��
	bool m_bEnd;							// �I���t���O
	bool m_bFall;							// �}�~���t���O
	static LPD3DXMESH m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;					// �}�e���A�����̐�
	static int m_nPlayerAll;				// �v���C���[�̐�
};

#endif