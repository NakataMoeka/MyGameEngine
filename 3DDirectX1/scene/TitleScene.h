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
#include "BaseScene.h"
/// <summary>
/// タイトル表示
/// </summary>
class TitleScene :public BaseScene
{
public:
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize()override;
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init()override;
	void InitTH()override;
	void InitStageNum(int stageNum)override;
	//繰り返し処理
	void Update()override;
	//背景画像描画
	void DrawBG()override;
	//オブジェクト描画
	void Draw()override;
	//前景画像描画
	void DrawFront()override;

	void Finalize()override;

	bool GetSCangeFlag()override;
private:


	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	Audio* audio = Audio::GetInstance();
	std::unique_ptr < Camera> camera = nullptr;
	std::unique_ptr < LightGroup> lightGroup = nullptr;

	std::unique_ptr < Sprite> TSprite;
	std::unique_ptr < Sprite> TBSprite;
	std::unique_ptr < Sprite> TB2Sprite;
	std::unique_ptr<Sprite> TSSprite;
	std::unique_ptr<Sprite> TS2Sprite;

	bool SCangeFlag = false;
	int SceneNum = 0;
	int Scene = 0;
	float TaCount = 0;
	int testCount = 0;
};

