#pragma once
#include"Sprite.h"
#include<array>
/// <summary>
/// サイズ表示用のクラス
/// </summary>
class SphereSize
{
public:
	void Initialize();//1回のみの初期化
	void Init();//シーン開始時にする初期化
	void InitStage(int maxNum);
	void Update();
	void Draw();
	int SetTsize(int Tsize) { return this->Tsize = Tsize; }
	int GetTsize() { return Tsize; }
	int GetTcount() { return TCount; }
private:
	std::array < Sprite*, 10>Number = {};//数字。8つなのはcmとmの一の位と十の位があるため&目標サイズ用
	std::array < Sprite*, 4> Meters = {};//目標サイズと現在のサイズ用で2つ
	std::array < Sprite*, 2> Centimeter = {};//上記と同じ
	int Tsize = 1;
	int TCount = 0;
	int tSC = 0;//cmの1の位カウント
	int tC = 0;//cmの10の位カウント
	int tSM = 0;//mの1の位
	int tM = 0;//mの10の位
	int tMM = 0;//mの100の位

};

