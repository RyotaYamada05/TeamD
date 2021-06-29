//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : 
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CConection;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CInputJoypad;
class CSound;
class CScene;
//=============================================================================
//�}�l�[�W���[�N���X
//=============================================================================
class CManager
{
public:
	//=========================================================================
	//�񋓌^��`
	//=========================================================================
	typedef enum
	{
		MODE_TYPE_NONE = 0, 
		MODE_TYPE_TITLE,	//�^�C�g�����[�h
		MODE_TYPE_TUTORIAL,		//�`���[�g���A��
		MODE_TYPE_GAME,		//�Q�[�����[�h
		MODE_TYPE_RESULT,	//���U���g���[�h
		MODE_TYPE_MAX,
	}MODE_TYPE;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadAll(void);
	void UnLoadAll(void);

	static void SetMode(MODE_TYPE mode);
	static MODE_TYPE GetMode(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetKeyboard(void);
	static CConection *GetConection(void);
	static CFade *GetFade(void);
	static CInputJoypad *GetJoypad(void);
	static CSound *GetSound(void);
	static CScene *GetScene(void) { return m_pScene; }

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static MODE_TYPE m_mode;
	static CRenderer *m_pRenderer;	//�����_���[�N���X�̃|�C���^
	static CInputKeyboard *m_pInput;
	static CConection *m_pConection;
	static CFade *m_pFade;
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CInputJoypad *m_pJoypad;
	static CSound *m_pSound;
	static CScene *m_pScene;
};

#endif