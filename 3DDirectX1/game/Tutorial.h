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
	bool SetTCount(int TutorialCount) { return this->TutorialCount=TutorialCount; }
private:
	std::array < Sprite*, 7> TutorialSprite = {};
	int TutorialCount = 0;
	bool countFlag = false;
};

