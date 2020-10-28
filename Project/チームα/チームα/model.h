//=============================================================================
//
// ���f������ [model.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	typedef struct
	{
		LPD3DXMESH pMesh;			//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffer;		//���_�o�b�t�@�ւ̃|�C���^
		DWORD dwNumMat;				//�}�e���A�����̐�
	}MODEL;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CModel();
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindModel(MODEL model);


	LPD3DXMESH GetMesh(void)const;
	LPD3DXBUFFER GetBuffMat(void)const;	//

	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;
	void SetRot(const D3DXVECTOR3 rot);
					// ���W�̏��
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	LPD3DXMESH m_pMesh;	//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD m_nNumMat;	//�}�e���A�����̐�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};
#endif 