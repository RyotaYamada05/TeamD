//=============================================================================
//
// �A�N�V�����@�u���b�N���� [main.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <thread>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//�x���Ώ��p�i"dinput.h"�̒��O�ɒ�`�j
#include <dinput.h>
#include "d3dx9math.h"


//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
//#pragma comment(lib, "dxguid.lib")
#pragma comment (lib,"ws2_32.lib")

//=============================================================================
// �}�N����`
//=============================================================================
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)	//���W�E�@���E�J���[
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_�t�H�[�}�b�g
#define NUM_VERTEX (4)	//���_��
#define NUM_POLYGON (2)	//�|���S����

//=============================================================================
//�\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos; // ���_���W
	float rhw;		 //	���W�ϊ��p�W���i1.0f�ŌŒ�j
	D3DCOLOR  col;	 // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
}VERTEX_2D;
#endif