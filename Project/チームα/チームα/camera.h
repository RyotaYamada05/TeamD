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

//===========================================================
//�J�����N���X
//=============================================================================
class CCamera
{
public:
	//=========================================================================
	//�����o�֐��錾
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
private:
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
	bool m_bTarget;
	float m_f��;
	float m_f��;
	int m_nCameraNum;						//�v���C���[�̔ԍ�
	float m_fDistance;						//���_�`�����_�̋���
	float m_fMove;							//�ړ���
	static int m_nCameraAll;				//�J�����̐�
};
#endif 