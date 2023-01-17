#pragma once
#include"Sprite.h"
#include"Audio.h"
#include<array>
/// <summary>
/// スタート時の目標発表&開始カウントダウン用のクラス
/// </summary>
class start
{
public:
	void Initialize(Audio* audio);
	void Init();
	void Update();
	void Draw();
	bool GetStartFlag() { return startFlag; }
	bool SetStartFlag(bool startFlag) { return this->startFlag=startFlag; }
private:
	Audio* audio = nullptr;
	SoundData sound1 = {};
	Sprite* number = nullptr;
	Sprite* Go = nullptr;
	std::array<Sprite*, 3> message = {};
	Sprite* messageUI = nullptr;
	//タイマー処理
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	int tSC = 0;
	bool startFlag = false;//開始カウントダウン終わったか否か
	bool GoFlag = false;
	int MCount = 0;
};

