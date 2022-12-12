#pragma once
#pragma once
#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "Camera.h"
#include "FbxObject.h"
#include"LightGroup.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"ClearScene.h"
#include"SelectScene.h"
#include <thread>
#include<mutex>
class SceneManager
{
public:
	enum Scene
	{
		TITLE, SELECT, GAME, END, LOAD
	};
	enum Load_Situation
	{
		NOLOAD, NOWLOAD, ENDLOAD,
	};
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init();
	//繰り返し処理
	void Update();
	void SceneChange();
	//背景画像描画
	void DrawBG();
	//オブジェクト描画
	void Draw();
	//前景画像描画
	void DrawFront();
	void InitTH();
	void SetLockFlag(bool _);
	bool GetLockFlag();
	void AsyncLoad();

	bool GetBFlag() { return Bflag; }
private:
	//最初のシーン
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Scene scene = LOAD;

	TitleScene* titleScene = nullptr;
	SelectScene* selectScene = nullptr;
	GameScene* gameScene = nullptr;
	ClearScene* clearScene = nullptr;
	bool Bflag = false;

	Sprite* Change = nullptr;
	float fade = 0;
	bool changeSFlag = false;
	bool changeEFlag = false;
	//ロード画面作りたい
	Sprite* loadingS = nullptr;
	std::thread t = {};
	std::thread t2 = {};
	std::mutex isLoadedMutex;
	Load_Situation Load_s = NOLOAD;
	bool LoadFlag = false;
	bool LoadFlagF = false;
};

