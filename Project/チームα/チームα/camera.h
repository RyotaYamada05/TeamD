//=============================================================================
//
// ���C������ [camera.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CLockon;

//===========================================================
//�J�����N���X
//=============================================================================
class CCamera
{
public:
	typedef enum
	{
		CAMERASTATE_NONE = 0,
		CAMERASTATE_NORMAL,	//�ʏ�
		CAMERASTATE_END,	//�I��
		CAMERASTATE_MAX	//STATE�̍ő吔
	}CAMERASTATE;
	//=========================================================================
	//�p�u���b�N�����o�֐��錾
	//=========================================================================
	CCamera();
	~CCamera();
	static CCamera*Create(void);// �N���G�C�g
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	bool GetTargetBool(void);
	float Get��(void);
	float Get��(void);
	D3DXVECTOR3 GetposV(void);
	D3DXVECTOR3 GetposR(void);
	D3DXMATRIX GetMtxView(void);
	void SetTarget(bool Target);
private:
	//=========================================================================
	//�v���C�x�[�g�����o�֐��錾
	//=========================================================================
	void EndUpdate(D3DXVECTOR3 PlayerPos[], D3DXVECTOR3 PlayerRot[], int nWinPlayer);
	void NomalUpdate(D3DXVECTOR3 PlayerPos[], D3DXVECTOR3 PlayerRot[]);
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	D3DXVECTOR3 m_posV;						//�J�����̍��W
	D3DXVECTOR3 m_posVDest;					//�J�����̍��W�i�ړI�n�j
	D3DXVECTOR3 m_posVRot;					//�J�����̍��W�i�j
	D3DXVECTOR3 m_posR;						//�����_
	D3DXVECTOR3 m_posRDest;					//�����_�i�ړI�n�j
	D3DXVECTOR3 m_posRRot;					//�����_�i�j
	D3DXVECTOR3 m_posU;						//������x�N�g��
	D3DXMATRIX m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;						//����
	bool m_bTarget;							//�^�[�Q�b�g�g�p�t���O
	float m_f��;							//�c��]�p�x
	float m_f��;							//����]�p
	int m_nCameraNum;						//�v���C���[�̔ԍ�
	float m_fDistance;						//���_�`�����_�̋���
	float m_fMove;							//�ړ���
	CAMERASTATE m_state;					//�X�e�[�^�X
	static int m_nCameraAll;				//�J�����̐�
	CLockon *m_pLockon[2];
	int m_nWinPlayer;						//Win�v���C���[�ԍ�
	float m_fDifference;					//�����J������]�J�n�p����I���p�̍�
	float m_fEndVertical;					//�����J�����I���p�x
};
#endif 