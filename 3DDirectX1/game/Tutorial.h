#pragma once
#include"Sprite.h"
#include<array>
/// <summary>
/// チュートリアルクラス
/// </summary>
class Tutorial
{
public:
	//1回限りの初期化初期化(オブジェクトの読込など)
	void Initialize();
	//繰り返し行う初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	int GetTCount() { return TutorialCount; }
	int SetTCount(int TutorialCount) { return this->TutorialCount=TutorialCount; }
	bool SetCountFlag(bool countFlag) { return this->countFlag = countFlag; }
	bool GetEndFlag() { return endFlag; }
	bool GetMoveFlag() { return moveFlag; }
private:
	std::array < Sprite*, 7> TutorialSprite = {};
	Sprite* TutorialUI = nullptr;
	int TutorialCount = 0;//説明文の表示カウント
	bool countFlag = false;//説明文を進めることができるのかのフラグ
	bool endFlag = false;//チュートリアル終了フラグ
	bool moveFlag = false;//動けるかのフラグ
};

