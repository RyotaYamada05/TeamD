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
#define PLAYER_SIZE_X		(1)			// �T�C�Y
#define PLAYER_SIZE_Y		(1)			// �T�C�Y
#define PLAYER_SIZE_Z		(1)			// �T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CScore;
class CLife;
class CCharge;
//=============================================================================
// �^�[���N���X
//=============================================================================
class CPlayer : public CModel
{
public:
	CPlayer();							// �R���X�g���N�^
	~CPlayer();							// �f�X�g���N�^


	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g
	static HRESULT LoadModel(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void PlayerControl(void);										// �v���C���[�̐���
	void Walk(void);												// �v���C���[�̕�������
	void Jump(void);												// �W�����v�̏���
	void GroundLimit(void);											// �n�ʂ̐���
	void Fall(void);												// �}�~��
	void Dush(void);												// �_�b�V��
	void beam(void);												// �r�[��
	D3DXVECTOR3 GetPos(void);										// �ʒu�擾
	D3DXVECTOR3 GetRot(void);										// �p�x�X�V
	void bomb(void);												// �{��
	CLife *GetLife(int nNumber);									// ���C�t�̏��
	CCharge *GetCgarge(void);										// �`���[�W�̃|�C���^
private:
	CScore *pScore;							// �X�R�A�̏��
	CLife *m_pLife[LIFE_NUM];				// ���C�t�̃|�C���^
	CCharge *m_pCharge;						// �`���[�W�̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_rot;						// ��]
	D3DXVECTOR3 m_move;						// �ړ�
	float m_fAngle;							// �p�x
	int m_nDushFlame;						// �_�b�V���̃t���[��
	int m_nDushInterCnt;					// �_�b�V���ł��Ȃ��Ƃ��̃J�E���g
	int m_nPlayerNum;						// �v���C���[�̔ԍ�
	bool m_bJump;							// �W�����v�̃t���O
	bool m_bDush;							// �_�b�V���̏���
	bool m_bDushInter;						// �_�b�V���̃C���^�[�o��
	static LPD3DXMESH m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat;					// �}�e���A�����̐�
	static int m_nPlayerAll;				// �v���C���[�̐�

};

#endif