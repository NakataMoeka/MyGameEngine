#pragma once
#include"Sprite.h"
#include <array>
/// <summary>
/// タイマー表示(ゲームシーンからの分離)
/// </summary>
class Timer
{
public:
	void Initialize();//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void Update();//アプデ
	void Draw();//モデルの描画
	double GetDT() { return dt; }
	bool SetFlag(bool poseFlag) { return this->poseFlag = poseFlag; }
private:
	Sprite* timeSprite = nullptr;//円
	Sprite* timeSprite3 = nullptr;//円
	Sprite* timeSprite2 = nullptr;//バー
	std::array<Sprite*,2> TimeNum = {};
	//タイマー系
	float TimeRot = 0;
	int TimeCount = 0;
	float TR;
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	bool poseFlag = false;
	int tSC = 0;//1の位カウント
	int tC = 0;//10の位カウント
};

