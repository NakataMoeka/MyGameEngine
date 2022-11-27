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
	//パーティクル
	void CreateParticles();
	int GetStageNum() { return stageNum; }
	bool GetSCangeFlag() { return SCangeFlag; }
private:
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	const int debugTextTexNumber = 0;
	Camera* camera = nullptr;
	LightGroup* lightGroup = nullptr;

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};

	std::array < Sprite*, 6> backSprite = {};
	Sprite* SelectUI = nullptr;
	float spriteCount = 0;
	int stageNum = 0;
	bool SCangeFlag = false;
	int SAFlag = 0;//アニメーション用のフラグ
};

