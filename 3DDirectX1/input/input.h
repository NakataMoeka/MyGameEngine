#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#include <DirectXMath.h>

class Input
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
public: 

	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

	void Initialize(WinApp* winapp);
	void InitializeMouse(WinApp* winapp);
	
	void update();
	void updateMouse();
	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);
	bool PushMouse(int MouseNumber);
	bool TriggerMouse(int MouseNumber);
	XMFLOAT2 GetMousePos() { return MousePos; }
	MouseMove GetMouseMove();
private: // メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouse = { 0 };
	DIMOUSESTATE2 oldMouse = { 0 };
	XMFLOAT2 MousePos = { 0,0 };
	WinApp* winapp = nullptr;
};
