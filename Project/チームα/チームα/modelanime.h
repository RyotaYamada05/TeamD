//=============================================================================
//
// �K�w�\���p�̃��f������ [modelanime.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _MODELANIME_H_
#define _MODELANIME_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�K�w���f���N���X
//=============================================================================
class CModelAnime
{
public:
	//=========================================================================
	//���f����񉹍\����
	//=========================================================================
	typedef struct
	{
		LPD3DXMESH pMesh;			//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;		//�}�e���A�����ւ̃|�C���^
		DWORD dwNumMat;				//�}�e���A�����̐�
	}MODEL;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CModelAnime();
	~CModelAnime();

	static CModelAnime *Create(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);;
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParent(CModelAnime *pParent);
	void SetPosAnime(const D3DXVECTOR3 posAnime);
	D3DXVECTOR3 GetPos(void)const;
	D3DXVECTOR3 GetPosAnime(void)const;
	void SetRotAnime(const D3DXVECTOR3 rotAnime);
	D3DXVECTOR3 GetRot(void)const;
	D3DXVECTOR3 GetRotAnime(void)const;
	D3DXMATRIX GetMtxWorld(void);
	D3DXMATRIX GetOldMtxWorld(void);

private:
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	MODEL m_model;	//���f�����
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	D3DXVECTOR3 m_posAnime;	//�A�j���[�V�����p�̈ʒu
	D3DXVECTOR3 m_rotAnime;	//�A�j���[�V�����p�̌���
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	CModelAnime *m_pParent;	//�e���̃|�C���^
	D3DXMATRIX m_OldMtxWorld;
	D3DXMATRIX m_OldMtxWorld1[5];
};

#endif 