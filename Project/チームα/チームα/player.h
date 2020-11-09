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
#include "scene.h"
#include "modelanime.h"

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
#define MODEL_PARTS 20	//���f���̃p�[�c��

//=============================================================================
// �O���錾
//=============================================================================
class CScore;
class CLife;
class CCharge;

typedef enum
{
	M_MOTION_STATE =-1,
	M_MOTION_STATE_IDOL,	//�A�C�h�����[�V����
	M_MOTION_STATE_WALK,	//���s���[�V����
	M_MOTION_STATE_DUSH,	
	M_MOTION_STATE_JUMP,
	M_MOTION_STATE_MAX,	//���[�V�����ő吔
}MOTION_STATE;

typedef struct
{
	char xFileName[1024];
	D3DXVECTOR3 offsetPos;
	D3DXVECTOR3 offsetRot;
	int nParent;
}MODELFILLE;

typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

typedef struct
{
	int nFrame;
	KEY aKey[MODEL_PARTS];
}KEY_INFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[20];
}Motion_Info;

//=============================================================================
// �^�[���N���X
//=============================================================================
class CPlayer : public CScene
{
public:
	CPlayer();							// �R���X�g���N�^
	~CPlayer();							// �f�X�g���N�^


	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void UpdateMotion(void);										//���[�V�����X�V����
	void Draw(void);												// �`�揈��
	void SetMotion(MOTION_STATE motion);

	void PlayerControl(void);										// �v���C���[�̐���
	void Walk(void);												// �v���C���[�̕�������
	void Jump(void);												// �W�����v�̏���
	void GroundLimit(void);											// �n�ʂ̐���
	void Fall(void);												// �}�~��
	void Dush(void);												// �_�b�V��
	void beam(void);												// �r�[��
	D3DXVECTOR3 GetPos(void);
	void bomb(void);												// �{��
	CLife *GetLife(int nNumber);									// ���C�t�̏��
	CCharge *GetCgarge(void);										// �`���[�W�̃|�C���^
	HRESULT ReadFile(void);
private:
	CScore *pScore;								// �X�R�A�̏��
	CLife *m_pLife[LIFE_NUM];					// ���C�t�̃|�C���^
	CCharge *m_pCharge;							// �`���[�W�̃|�C���^
	D3DXVECTOR3 m_pos;							// ���W
	D3DXVECTOR3 m_rot;							// ��]
	D3DXVECTOR3 m_move;							// �ړ�
	float m_fAngle;								// �p�x
	int m_nDushFlame;							// �_�b�V���̃t���[��
	int m_nDushInterCnt;						// �_�b�V���ł��Ȃ��Ƃ��̃J�E���g
	int m_nPlayerNum;							// �v���C���[�̔ԍ�
	bool m_bJump;								// �W�����v�̃t���O
	bool m_bDush;								// �_�b�V���̏���
	bool m_bDushInter;							// �_�b�V���̃C���^�[�o��
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	static int m_nPlayerAll;					// �v���C���[�̐�
	CModelAnime *m_apModelAnime[MODEL_PARTS];	//���f���p�[�c�p�̃|�C���^
	int m_nNumKey;								//�L�[�̑���
	int m_nKey;									//���݃L�[��No
	int m_nCountMotion;							//���[�V�����J�E���^�[
	KEY_INFO *m_apKeyInfo;						//�L�[���̃|�C���^
	MOTION_STATE m_MotionState;
	Motion_Info m_Motion[M_MOTION_STATE_MAX];
	int m_nFlame;
};

#endif