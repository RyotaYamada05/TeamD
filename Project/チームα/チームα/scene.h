//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_NUM 50	//�ő吔

//=============================================================================
//�I�u�W�F�N�g�N���X
//=============================================================================
class CScene
{
public:
	//=========================================================================
	//�񋓌^
	//=========================================================================
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,	//�v���C���[�^�C�v
		OBJTYPE_DARTS,	//�_�[�c�^�C�v
		OBJTYPE_DARTS_BOARD,	//�_�[�c�{�[�h�^�C�v
		OBJTYPE_MAX	//�I�u�W�F�N�g�^�C�v�̍ő吔
	}OBJTYPE;	//�I�u�W�F�N�g�^�C�v

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CScene();
	virtual ~CScene();
	static void ReleaseAll(void);
	static void AllUpdate(void);
	static void AllDraw(void);

	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void SetObjType(const OBJTYPE objtype);
	OBJTYPE GetObjType(void)const;
	static CScene *GetScene(int nNum);
protected:
	void Release(void);

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static CScene *m_apScene[MAX_NUM];	//�I�u�W�F�N�g�N���X�̃|�C���^�z��
	static int m_nNumAll;	//����
	int m_nID;	//�i���o�[�̕ۑ�
	OBJTYPE m_ObjType;	//�I�u�W�F�N�g�̎��
};

#endif