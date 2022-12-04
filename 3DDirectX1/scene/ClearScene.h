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
#include"Ease.h"
/// <summary>
/// タイトル表示
/// </summary>
class ClearScene
{
public:
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
	bool GetClearFlag() { return clearFlag; }
	bool GetOverFlag() { return overFlag; }
	bool SetClearFlag(bool clearFlag) { return this->clearFlag = clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
	bool GetSCangeFlag() { return SCangeFlag; }

private:
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	const int debugTextTexNumber = 0;
	Camera* camera = nullptr;
	LightGroup* lightGroup = nullptr;

	SoundData sound1 = {};

	Sprite* overTextSprite = nullptr;
	Sprite* clearTextSprite = nullptr;
	Sprite* overSprite = nullptr;
	Sprite* clearSprite = nullptr;
	Sprite* motherASprite = nullptr;
	Sprite* motherSSprite = nullptr;
	Sprite* Space = nullptr;
	Sprite* back = nullptr;

	bool clearFlag = false;
	bool overFlag = false;
	XMFLOAT2 pos = { 300,800 };
	Eas* eas;
	float easeTimer = 0;//イージングのタイマー
	bool pushFlag = false;//ボタンを押せるようにする
	bool SCangeFlag = false;
};

