//================================================
//
// �T�E���h���� [sound.h]
// Author : �����D�I
//
//================================================

#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "xaudio2.h"

//================================================
//�N���X�錾
//================================================
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0
		SOUND_LABEL_BGM_GAME,			// BGM1
		SOUND_LABEL_SE_EXPLOSION_DEAH,	// ������
		SOUND_LABEL_SE_START,			// �^�C�g���̃X�^�[�g��
		SOUND_LABEL_SE_WALK,			// �����Ƃ��̉�
		SOUND_LABEL_SE_BOMB,			// �e�����������Ƃ��̉�
		SOUND_LABEL_SE_SAND,			// ���n��
		SOUND_LABEL_SE_JUMP,			// �W�����v
		SOUND_LABEL_SE_BULLET,			// �e����
		SOUND_LABEL_SE_BULLET2,			// �e����
		SOUND_LABEL_SE_TURBO,			// �^�[�{����
		SOUND_LABEL_SE_COUNTDOWN,		// �J�E���g�_�E����
		SOUND_LABEL_SE_SLASH,			// �a����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef enum
	{
		SOUND_LOOP_ON = -1,	//���[�v����
		SOUND_LOOP_OFF,		//���[�v���Ȃ�
	}SOUND_LOOP;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
private:
	typedef struct
	{
		char *m_pFilename;	// �t�@�C����
		SOUND_LOOP isLoop;		// ���[�v���邩�ǂ���
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif