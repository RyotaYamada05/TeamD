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
#define LIFE_NUM			(2)			// �\�����郉�C�t�̐�
#define MAX_PARTS			(10)		// �p�[�c�̐�
#define MOTION_KEYSET_MAX	(32)		// �L�[�Z�b�g�ő吔
#define PLAYER2_POS_X		(0.0f)		// ���W
#define PLAYER2_POS_Y		(171.0f)	// ���W
#define PLAYER2_POS_Z		(500)		// ���W

#define PLAYER_SIZE_X		(1)			// �T�C�Y
#define PLAYER_SIZE_Y		(1)			// �T�C�Y
#define PLAYER_SIZE_Z		(1)			// �T�C�Y
#define MAX_MODEL_PARTS			(21)		//���f���̃p�[�c�̍ő吔

#define PLAYER_COLLISION_X	(200)		// �����蔻��
#define PLAYER_COLLISION_Y	(175)		// �����蔻��
#define PLAYER_COLLISION_Z	(200)		// �����蔻��

#define PLAYER_RADIUS		(150)		// ���a

//=============================================================================
// �O���錾
//=============================================================================
class CScore;
class CLife;
class CCharge;
class CBoost;

//=============================================================================
//�@���[�V������Ԃ̗񋓌^
//=============================================================================

typedef enum
{
	MOTION_NONE = -1,
	MOTION_IDOL,	//�A�C�h�����[�V����
	MOTION_WALK,	//���s���[�V����
	MOTION_ATTACK,	//�U�����[�V����
	MOTION_JUMP,	//�W�����v���[�V����
	MOTION_LANDING,	//���n���[�V����
	MOTION_WIN,		//�������[�V����
	MOTION_RIGHTBOOST,	//�E�u�[�X�g
	MOTION_LEFTBOOST,	//���u�[�X�g
	MOTION_DAMAGE,	//����
	MOTION_MAX,		//���[�V�����ő吔
}MOTION_STATE;

//=============================================================================
//�@���f���t�@�C�����̍\����
//=============================================================================
typedef struct
{
	char xFileName[1024];	//�t�@�C���l�[��
	D3DXVECTOR3 offsetPos;	//�ʒu�̃I�t�Z�b�g���
	D3DXVECTOR3 offsetRot;	//�����̃I�t�Z�b�g���
	int nParent;	//�e���
}MODELFILLE;

//=============================================================================
//�@�e�v�f�̃L�[���
//=============================================================================
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//=============================================================================
//	�L�[���̍\����
//=============================================================================
typedef struct
{
	int nFrame;	//�t���[����
	KEY aKey[MAX_MODEL_PARTS];	//�e�p�[�c�̃L�[���
}KEY_INFO;

//=============================================================================
//�@���[�V�������̍\����
//=============================================================================
typedef struct
{
	bool bLoop;	//���[�v���邩�ǂ���
	int nNumKey;	//�L�[��
	KEY_INFO aKeyInfo[20];	//�L�[���
}Motion_Info;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CScene
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

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void UpdateMotion(void);										//���[�V�����X�V����
	void Draw(void);												// �`�揈��
	void SetMotion(MOTION_STATE motion);

	void PlayerState(void);											// �v���C���[�̏��
	void PlayerControl(void);										// �v���C���[�̐���
	void Walk(void);												// �v���C���[�̕�������
	void Jump(void);												// �W�����v�̏���
	void GroundLimit(void);											// �n�ʂ̐���
	void Fall(void);												// �}�~��
	void Dush(void);												// �_�b�V��
	void beam(void);												// �r�[��
	D3DXVECTOR3 GetRot(void);										// �p�x���
	void bomb(void);												// �{��
	void Laser(void);												// ���[�U�[
	void BlockUp(void);												// �u���b�N�̏�ɏ�����Ƃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetWinToLose(bool bFlag);									// �����������S�̐ݒ�
	bool GetSetWinLose(void);
	D3DXVECTOR3 GetPos(void);										// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void);									// �Â����W���
	void SetMove(D3DXVECTOR3 move);										// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 GetMove(void);

	CLife *GetLife(int nNumber);									// ���C�t�̏��
	CCharge *GetCgarge(void);										// �`���[�W�̃|�C���^
	HRESULT ReadFile(void);
	bool GetEnd(void);												// �G���h���
	PLAYER_STATE GetState(void);									// �v���C���[�̏��
private:

	CScore *pScore;								// �X�R�A�̏��
	CLife *m_pLife[LIFE_NUM];					// ���C�t�̃|�C���^
	CBoost *m_pBoost;							// �u�[�X�g�̃|�C���^
	CCharge *m_pCharge;							// �`���[�W�̃|�C���^
	D3DXVECTOR3 m_pos;							// ���W
	D3DXVECTOR3 m_OldPos;						// 1�t���[���O�̍��W
	D3DXVECTOR3 m_rot;							// ��]
	D3DXVECTOR3 m_move;							// �ړ�
	PLAYER_STATE m_state;						// �v���C���[���
	float m_fAngle;								// �p�x
	int m_nDushFlame;							// �_�b�V���̃t���[��
	int m_nDushInterCnt;						// �_�b�V���ł��Ȃ��Ƃ��̃J�E���g
	int m_nPlayerNum;							// �v���C���[�̔ԍ�
	int m_nStateCounter;						// ��ԃJ�E���^�[
	bool m_bJump;								// �W�����v�̃t���O
	bool m_bDush;								// �_�b�V���̏���
	bool m_bDushInter;							// �_�b�V���̃C���^�[�o��
	bool m_bEnd;								// �I���t���O
	bool m_bFall;								// �}�~���t���O
	bool m_bWalk;								//�ړ��t���O
	static int m_nPlayerAll;					// �v���C���[�̐�
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	//���f���p�[�c�p�̃|�C���^
	int m_nNumKey;								//�L�[�̑���
	int m_nKey;									//���݃L�[��No
	int m_nCountMotion;							//���[�V�����J�E���^�[
	int m_nMotionInterval;						//���[�V�����̃C���^�[�o��
	KEY_INFO *m_apKeyInfo;						//�L�[���̃|�C���^
	MOTION_STATE m_MotionState;					//���[�V�����̏��
	Motion_Info m_Motion[MOTION_MAX];			//���[�V�������
	bool m_bWinLose;							// ���������̃��S�t���O
	bool m_bEntered;							//�ړ����͂����邩�ǂ���
	bool m_bMotionPlaing;

};
#endif