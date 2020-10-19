//=======================================================================================
// 
// �|���S���`�揈��(scene2d.h)
// Author : �ɓ��@�q
//
//=======================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"




//***************************************************************************************
// �N���X��`
//***************************************************************************************
class CScene2d : public CScene
{
public:

	CScene2d();
	~CScene2d();
	static CScene2d* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTextuer) { m_pTextuer = pTextuer; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void)const { return m_pos; }
	D3DXVECTOR3 GetSize(void)const { return m_PolygonSize; }
	void SetPolygonSize(const D3DXVECTOR3 nSize) { m_PolygonSize = nSize; }
	
private:

	LPDIRECT3DTEXTURE9 m_pTextuer;       // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVetxBuff; // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;                   // �|���S���̈ʒu
	D3DXVECTOR3 m_PolygonSize;           // �|���S���̃T�C�Y
};

#endif // !_SCENE2D_H_
