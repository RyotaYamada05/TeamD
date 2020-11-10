#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.h]
// Author : �����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "scene3D.h"

//=====================================================
// �}�N����`
//=====================================================
#define MAX_BILLBOARD		(256)
#define BILLBOARD_SIZE_X	(25)
#define BILLBOARD_SIZE_Y	(25)

//=====================================================
// �O���錾
//=====================================================
class CScene3D;

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CBillboard : public CScene3D
{
public:
	CBillboard();
	~CBillboard();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
	void SetPos(D3DXVECTOR3 pos);										// ���W�̐ݒ�
	void SetMove(D3DXVECTOR3 move);										// �ړ��ʐݒ�
	void SetSize(D3DXVECTOR3 size);										// �T�C�Y�ݒ�
	void SetSizeBase(D3DXVECTOR3 sizeBase);								// �T�C�Y�̃x�[�X
	D3DXVECTOR3 GetPos(void);											// ���W���
	D3DXVECTOR3 GetMove(void);											// �ړ��ʏ��
	D3DXVECTOR3 GetSize(void);											// �T�C�Y���

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// �e�N�X�`���̐ݒ�
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// �A�j���[�V������񏉊���
	void UpdateAnimation(void);											// �A�j���[�V�����̍X�V

	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);								// �o�b�t�@�̏��
private:
	D3DXVECTOR3 m_Pos;									// �ʒu���
	D3DXVECTOR3 m_move;									// �ړ���
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXVECTOR3 m_Dir;									// ����7
	D3DXVECTOR3 m_sizeBase;								// �T�C�Y�̃x�[�X
	D3DXMATRIX m_mtxWorld;								// �s��v�Z�p
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;						// �|���S���̃e�N�X�`��
	int m_nLife;										// ����
	bool m_bUse;										// �g�p����

	int m_nCountAnim;									// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;							// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;									// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;									// �A�j���[�V�����̃p�^�[����
	int m_nLoop;										// ���[�v���邩
};

#endif