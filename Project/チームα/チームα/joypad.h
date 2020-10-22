#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//===============================
//
// ジョイパッドヘッダ [joypad.h]
// Author : Konishi Yuuto
//
//===============================

//===============================
// インクルードファイル
//===============================
#include "main.h"
#include "input.h"

//===============================
//マクロ定義
//===============================
#define MAX_JOYSTICK_NUM 4// JOYPAD接続上限
#define	NUM_JOY_MAX 256   // ボタンの最大数

//===============================
//ジョイパッドクラス
//===============================
class CInputJoypad : public CInput
{
public:
	//=============================================================================
	//ジョイスティックのボタン用の列挙型定義
	//=============================================================================
	typedef enum
	{
		JOY_BUTTON_X = 0,		//Xボタン
		JOY_BUTTON_Y,			//Yボタン
		JOY_BUTTON_A,			//Aボタン
		JOY_BUTTON_B,			//Bボタン
		JOY_BUTTON_L_TRIGGER,	//Lトリガーボタン
		JOY_BUTTON_R_TRIGGER,	//Rトリガーボタン
		JOY_BUTTON_L2_TRIGGER,	//Lトリガーボタン2
		JOY_BUTTON_R2_TRIGGER,	//Rトリガーボタン2
		JOY_BUTTON_L3,			//Lボタン
		JOY_BUTTON_R3,			//Rボタン
		JOY_BUTTON_SELECT,		//SELECTボタン
		JOY_BUTTON_START,		//STARTボタン
		JOY_BUTTON_HOME,		//HOMEボタン
		JOY_BUTTON_MAX,			//最大ボタン数
	}JOY_BUTTON;

	//メンバ関数
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

	// メンバ変数
	BYTE m_aJoyState[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};          // ジョイパッドの入力情報ワーク
	BYTE m_aJoyStateTrigger[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // ジョイパッドのトリガー情報
	BYTE m_aJoyStateRelease[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // ジョイパッドのリリース情報
	static DIJOYSTATE CInputJoypad::GetStick(const int nID);

private:
	static LPDIRECTINPUTDEVICE8 m_apDevice[MAX_JOYSTICK_NUM];
	DIDEVCAPS   m_diDevCaps;
	static int m_nJoyStickCont;
};

#endif