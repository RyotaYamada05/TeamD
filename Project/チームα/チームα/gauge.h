//=============================================================================
// 
// �Q�[�W�`�揈��(gauge.h)
// Author : �����D�I
//
//=============================================================================

#ifndef  _GAUGE_H_
#define  _GAUGE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�N���X�錾
//=============================================================================
class CGauge : public CScene
{
public:
	CGauge(int nPriority = PRIORITY_0);
	~CGauge();
	static CGauge* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTextuer) { m_pTextuer = pTextuer; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize( D3DXVECTOR3 nSize) { m_size = nSize; }
	void SetCol(D3DXCOLOR col);

	D3DXVECTOR3 GetPos(void)const { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR   GetCol(void) { return m_col; }
private:

	LPDIRECT3DTEXTURE9 m_pTextuer;       // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVetxBuff; // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;                   // �|���S���̈ʒu
	D3DXVECTOR3 m_size;					 // �|���S���̃T�C�Y
	D3DXCOLOR   m_col;
};

#endif // ! _GAUGE_H_
