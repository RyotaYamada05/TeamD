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
		LPD3DXBUFFER pBuffMat;		//�}�e���A�����ւ̃|�C���^
		DWORD dwNumMat;				//�}�e���A�����̐�
	}MODEL;

	typedef enum
	{
		MODEL_TYPE_NONE = 0,	// �����l
		MODEL_TYPE_PLAYER1,		// �v���C���[
		MODEL_TYPE_PLAYER2,		// �v���C���[
		MODEL_TYPE_BEAM,		// �r�[��
		MODEL_TYPE_OBJECT,		// ����
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CModel(int nPriority = PRIORITY_0);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, const D3DXVECTOR3 size);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindModel(MODEL model);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void BindTexturePointer(LPDIRECT3DTEXTURE9 *ppTexture);
	LPD3DXMESH GetMesh(void)const;
	LPD3DXBUFFER GetBuffMat(void)const;	//

	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;

	void SetRot(const D3DXVECTOR3 rot);		// ���W�̏��
	D3DXVECTOR3 GetRot(void);
	void SetType(MODEL_TYPE Mtype);
	void SetSize(D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void);
	LPD3DXBUFFER GetBuffMat(void);
	MODEL_TYPE GetType(void);
	D3DXMATRIX GetMtxWorld(void);
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================

	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DTEXTURE9 *m_apTexture;
	LPD3DXMESH m_pMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A�����ւ̃|�C���^
	DWORD m_nNumMat;			// �}�e���A�����̐�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_size;			// �T�C�Y
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	MODEL_TYPE m_type;			// ���
};
#endif 