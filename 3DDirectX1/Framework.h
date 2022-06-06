#pragma once
#include"WinApp.h"
#include"Audio.h"
#include"DXCommon.h"
#include "GameScene.h"
#include "FbxLoader.h"
#include "PostEffect.h"
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
	GameScene* gameScene = nullptr;
	PostEffect* postEffect = nullptr;
};

