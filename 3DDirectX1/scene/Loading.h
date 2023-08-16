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
/// <summary>
class Loading :public BaseScene
{
public:
	Loading();
	~Loading();
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize()override;
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init()override;
	void InitTH()override;
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
	Audio* audio = Audio::GetInstance();
	std::unique_ptr<Sprite> loadingS = nullptr;//ロード中の文字
	std::unique_ptr<Sprite> loadBack = nullptr;//背景
	int loadCount = 0;//文字位置
	int LoadCountCount = 0;//loadCountの数値を増やすためのやつ
};

