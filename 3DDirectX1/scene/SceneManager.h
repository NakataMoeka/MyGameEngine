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
#include"Loading.h"
#include <thread>
#include<mutex>
#include"BaseScene.h"

#include"SceneChange.h"
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
	~SceneManager();
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init();
	//繰り返し処理
	void Update();

	//背景画像描画
	void DrawBG();
	//オブジェクト描画
	void Draw();
	//前景画像描画
	void DrawFront();
	//ロード用初期化
	void InitTH();
private:
	const int debugTextTexNumber = 0;
	//最初のシーン
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Scene scene = LOAD;
	//今のシーン
	BaseScene* scene_ = nullptr;
	//次のシーン
	BaseScene* nextScene_ = nullptr;

	std::unique_ptr < TitleScene> titleScene = nullptr;
	std::unique_ptr < SelectScene> selectScene = nullptr;
	std::unique_ptr < GameScene> gameScene = nullptr;
	std::unique_ptr < ClearScene> clearScene = nullptr;
	std::unique_ptr < Loading> loadScene = nullptr;

	std::unique_ptr < SceneChange> change = nullptr;

	//ロード画面作りたい
	std::thread t = {};
	Load_Situation Load_s = NOLOAD;
};

