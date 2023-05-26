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
#include"BaseScene.h"
class SceneChange
{
public:
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize();
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

	bool SetChangeSFlag(bool fadeIn) { return this->fadeIn = fadeIn; }
	bool GetChangeEFlag() { return fadeOut; }
private:
	std::unique_ptr<Sprite>ChangeS = nullptr;
	float fade = 0;
	bool fadeIn = false;//フェードイン
	bool fadeOut = false;//フェードアウト
};

