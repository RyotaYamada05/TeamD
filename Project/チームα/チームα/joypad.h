#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//===============================
//
// �W���C�p�b�h�w�b�_ [joypad.h]
// Author : Konishi Yuuto
//
//===============================

//===============================
// �C���N���[�h�t�@�C��
//===============================
#include "main.h"
#include "input.h"

//===============================
//�}�N����`
//===============================
#define MAX_JOYSTICK_NUM 4// JOYPAD�ڑ����
#define	NUM_JOY_MAX 256   // �{�^���̍ő吔

//===============================
//�W���C�p�b�h�N���X
//===============================
class CInputJoypad : public CInput
{
public:
	//=============================================================================
	//�W���C�X�e�B�b�N�̃{�^���p�̗񋓌^��`
	//=============================================================================
	typedef enum
	{
		JOY_BUTTON_X = 0,		//X�{�^��
		JOY_BUTTON_Y,			//Y�{�^��
		JOY_BUTTON_A,			//A�{�^��
		JOY_BUTTON_B,			//B�{�^��
		JOY_BUTTON_L_TRIGGER,	//L�g���K�[�{�^��
		JOY_BUTTON_R_TRIGGER,	//R�g���K�[�{�^��
		JOY_BUTTON_L2_TRIGGER,	//L�g���K�[�{�^��2
		JOY_BUTTON_R2_TRIGGER,	//R�g���K�[�{�^��2
		JOY_BUTTON_L3,			//L�{�^��
		JOY_BUTTON_R3,			//R�{�^��
		JOY_BUTTON_SELECT,		//SELECT�{�^��
		JOY_BUTTON_START,		//START�{�^��
		JOY_BUTTON_HOME,		//HOME�{�^��
		JOY_BUTTON_MAX,			//�ő�{�^����
	}JOY_BUTTON;

	//�����o�֐�
	CInputJoypad();
	virtual ~CInputJoypad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey, int nId);
	bool GetJoystickTrigger(int nKey, int nId);
	bool GetJoystickRelease(int nKey, int nId);
	static LPDIRECTINPUTDEVICE8 GetController(int nNumber);

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);

	// �����o�ϐ�
	BYTE m_aJoyState[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};          // �W���C�p�b�h�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // �W���C�p�b�h�̃g���K�[���
	BYTE m_aJoyStateRelease[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // �W���C�p�b�h�̃����[�X���
	static DIJOYSTATE CInputJoypad::GetStick(const int nID);

private:
	static LPDIRECTINPUTDEVICE8 m_apDevice[MAX_JOYSTICK_NUM];
	DIDEVCAPS   m_diDevCaps;
	static int m_nJoyStickCont;
};

#endif