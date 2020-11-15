//=============================================================================
//
//  [pause.h]
// Author : ���� �D�I
//
//=============================================================================

#ifndef  _PAUSE_H_
#define  _PAUSE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CScene2d;
class CUiPause;

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PAUSE			(3)		//�|�[�YUI�̍ő吔

//=============================================================================
// �N���X�錾
//=============================================================================
class CPause :public CScene
{
public:
	CPause(int nPriority = PRIORITY_1);
	~CPause();
	static CPause* Create(void);
	static HRESULT Load(void);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Select(void);

	static CUiPause *GetPause(int nCount) { return m_apPauselogo[nCount]; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[1];	//�e�N�X�`���ւ̃|�C���^
	CScene2d* m_pScene;	//�|�C���^
	static CUiPause *m_apPauselogo[MAX_PAUSE];			//�^�C�g�����S�̃|�C���^
	D3DXVECTOR3 m_SelectPos;					//���S�̂�����W
};

#endif // ! _PAUSE_H_