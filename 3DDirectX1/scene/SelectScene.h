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
#include<array>
/// <summary>
/// ステージセレクト　
/// </summary>
class SelectScene
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
	//パーティクル
	void CreateParticles();
	int GetStageNum() { return stageNum; }
	bool GetSCangeFlag() { return SCangeFlag; }
private:
	Audio* audio = Audio::GetInstance();
	std::unique_ptr <Camera> camera = nullptr;
	std::unique_ptr <LightGroup> lightGroup = nullptr;

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	SoundData sound4 = {};
	std::array <std::unique_ptr<Sprite>, 6> backSprite = {};
	std::unique_ptr<Sprite> SelectUI = nullptr;
	std::unique_ptr<Sprite> SelectNumber = nullptr;
	std::unique_ptr<Sprite> TutorialS = nullptr;
	float spriteCount = 0;
	int stageNum = 0;
	bool SCangeFlag = false;
	int SAFlag = 0;//アニメーション用のフラグ

};

