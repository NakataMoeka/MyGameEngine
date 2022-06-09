#pragma once
#include"WinApp.h"
#include"Audio.h"
#include"DXCommon.h"
#include "input.h"
#include "Object3d.h"
#include "FbxLoader.h"
#include "PostEffect.h"
#include"Light.h"
class Framework
{
public:
	//‰Šú‰»
	void Run();
	virtual void Initialize();
	//I—¹
	virtual void Finalize();
	// –ˆƒtƒŒ[ƒ€ˆ—
	virtual void Update();
	// •`‰æ
	virtual void Draw() = 0;
	bool eR() { return endRequst; }
protected:
	bool endRequst = false;
	WinApp* winapp = nullptr;
	DirectXCommon* dxcommon = nullptr;
	Audio* audio = nullptr;
	Input* input = nullptr;

	PostEffect* postEffect = nullptr;
};

