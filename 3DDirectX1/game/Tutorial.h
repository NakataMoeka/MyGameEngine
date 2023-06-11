#pragma once
#include"Sprite.h"
#include<array>
#include <memory>
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
	bool GetColFlag() { return colFlag; }
	bool SetColFlag( bool col) { return colFlag=col; }
	int SetWalkCount(int wcount) { return walkCount = wcount; }
private:
	std::array < std::unique_ptr<Sprite>, 7> TutorialSprite = {};
	std::unique_ptr<Sprite> TutorialUI = nullptr;
	int TutorialCount = 0;//説明文の表示カウント
	bool countFlag = false;//説明文を進めることができるのかのフラグ
	bool colFlag = false;//くっつけるか否か
	bool endFlag = false;//チュートリアル終了フラグ
	bool moveFlag = false;//動けるかのフラグ
	int walkCount = 0;//動いた量
};

