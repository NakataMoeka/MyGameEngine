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
class SceneManager
{
public:
	enum Scene
	{
		TITLE, GAME, END,
	};
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
	bool GetBFlag() { return Bflag; }
private:
	//最初のシーン
	Scene scene = TITLE;
	TitleScene* titleScene;
	GameScene* gameScene;
	ClearScene* clearScene;
	bool Bflag = false;
};

