#pragma once
#include"Sprite.h"
#include"Audio.h"
#include<array>
#include <memory>
/// <summary>
/// スタート時の目標発表&開始カウントダウン用のクラス
/// </summary>
class start
{
public:
	void Initialize();
	void Init();
	void Update();
	void Draw(int stage);
	bool GetStartFlag() { return startFlag; }
	bool SetStartFlag(bool startFlag) { return this->startFlag=startFlag; }
private:
	Audio* audio = Audio::GetInstance();
	SoundData sound1 = {};
	std::unique_ptr<Sprite> number = nullptr;
	std::unique_ptr<Sprite> Go = nullptr;
	std::array<std::unique_ptr<Sprite>, 3> message = {};
	std::unique_ptr<Sprite> messageUI = nullptr;
	//タイマー処理
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	int tSC = 0;//カウントダウンの文字用
	bool startFlag = false;//開始カウントダウン終わったか否か
	bool GoFlag = false;
	int MCount = 0;
};

