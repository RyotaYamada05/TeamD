//=============================================================================
//
// ���U���g���� [result.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CScene2d;

//=============================================================================
//���U���g�N���X
//=============================================================================
class CResult : public CScene
{
public:
	CResult(int nPriority = PRIORITY_0);
	~CResult();

	static CResult* Create(void);
	static HRESULT Load(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
	CScene2d* m_pScene2D;
};
#endif