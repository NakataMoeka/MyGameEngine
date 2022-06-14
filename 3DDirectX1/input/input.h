#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#include <DirectXMath.h>
enum ButtonKind
{
	LButtonUp,
	LButtonDown,
	LButtonLeft,
	LButtonRight,
	RButtonUp,
	RButtonDown,
	RButtonLeft,
	RButtonRight,
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	ButtonRB,
	ButtonLB,
	Select,
	Start,
	ButtonRT,
	ButtonLT,
	ButtonKindMax,
};
enum ButtonState
{
	ButtonStateNone,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
};


class Input
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: 

	static Input* GetInstance();

	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

	/// <summary>
	/// キーボードの初期化
	/// </summary>
	void Initialize(WinApp* winapp);
	/// <summary>
	/// マウスの初期化
	/// </summary>
	void InitializeMouse(WinApp* winapp);

	/// <summary>
	/// ゲームパッドの初期化
	/// </summary>
	bool InitializePad();

	void ReleaseInput();
	/// <summary>
	/// キーボードの更新
	/// </summary>
	void update();
	/// <summary>
	/// マウスの更新
	/// </summary>
	void updateMouse();
	/// <summary>
	/// ゲームパッドの更新
	/// </summary>
	void updatePud();
	//キーボード押す
	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);
	//マウス押す
	bool PushMouse(int MouseNumber);
	bool TriggerMouse(int MouseNumber);
	//マウスの移動量
	MouseMove GetMouseMove();
	//ボタン押す
	bool IsButtonPush(ButtonKind button);
	bool IsButtonUp(ButtonKind button);
	bool IsButtonDown(ButtonKind button);
	//スティック入力してるか
	bool ConRightInput();
	bool ConLeftInput();


private: // メンバ変数
	Input() = default;
	Input(const Input&) = delete;
	~Input() = default;
	Input& operator=(const Input&) = delete;

	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouse = { 0 };
	DIMOUSESTATE2 oldMouse = { 0 };

	// ゲームパッドの入力情報取得
	ComPtr<IDirectInputDevice8> devGamePad;
	DIJOYSTATE pad_data;
	DIJOYSTATE oldpad_data;
	LPDIRECTINPUTDEVICE8 g_GamePadDevice = nullptr;
	LPDIRECTINPUT8 g_InputInterface = nullptr;

	WinApp* winapp = nullptr;
};
