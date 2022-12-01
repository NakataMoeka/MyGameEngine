#pragma once
#include"Sprite.h"
#include<array>
/// <summary>
/// チュートリアルクラス
/// </summary>
class Tutorial
{
public:
	void Initialize();
	void Init();
	void Update();
	void Draw();
	int GetTCount() { return TutorialCount; }
	int SetTCount(int TutorialCount) { return this->TutorialCount=TutorialCount; }
	bool SetCountFlag(bool countFlag) { return this->countFlag = countFlag; }
	bool GetEndFlag() { return endFlag; }
private:
	std::array < Sprite*, 7> TutorialSprite = {};
	int TutorialCount = 0;
	bool countFlag = false;
	bool endFlag = false;//チュートリアル終了フラグ
};

