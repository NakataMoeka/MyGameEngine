#include "Tutorial.h"
#include"Input.h"
void Tutorial::Initialize()
{
	Sprite::LoadTexture(50, L"Resources/UI/Tutorial1.png");
	Sprite::LoadTexture(51, L"Resources/UI/Tutorial2.png");
	Sprite::LoadTexture(52, L"Resources/UI/Tutorial3.png");
	Sprite::LoadTexture(53, L"Resources/UI/Tutorial4.png");
	Sprite::LoadTexture(54, L"Resources/UI/Tutorial5.png");
	Sprite::LoadTexture(55, L"Resources/UI/Tutorial6.png");
	Sprite::LoadTexture(56, L"Resources/UI/Tutorial7.png");
	Sprite::LoadTexture(57, L"Resources/UI/TutorialUI.png");
	TutorialSprite[0] = std::unique_ptr<Sprite>(Sprite::CreateSprite(50, { 200,400 }));
	TutorialSprite[1] = std::unique_ptr<Sprite>(Sprite::CreateSprite(51, { 200,400 }));
	TutorialSprite[2] = std::unique_ptr<Sprite>(Sprite::CreateSprite(52, { 200,400 }));
	TutorialSprite[3] = std::unique_ptr<Sprite>(Sprite::CreateSprite(53, { 200,400 }));
	TutorialSprite[4] = std::unique_ptr<Sprite>(Sprite::CreateSprite(54, { 200,400 }));
	TutorialSprite[5] = std::unique_ptr<Sprite>(Sprite::CreateSprite(55, { 200,400 }));
	TutorialSprite[6] = std::unique_ptr<Sprite>(Sprite::CreateSprite(56, { 200,400 }));
	TutorialUI = std::unique_ptr<Sprite>(Sprite::CreateSprite(57, { 700,550 }));
}

void Tutorial::Init()
{
	TutorialCount = 0;
	countFlag = false;
	endFlag = false;
	moveFlag = false;
	colFlag = false;
}

void Tutorial::Update()
{
	if (countFlag == false) {
		//説明文を進める
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			if (TutorialCount < 6) {
				TutorialCount++;
			}
			else if (TutorialCount == 6) {
				endFlag = true;
			}
		}
	}
	//1になったら
	if (TutorialCount == 1) {
		//プレイヤーのZ座標位置が0以上になったら
		if (walkCount == 100) {
			//2にする
			TutorialCount = 2;
		}
		countFlag = true;
	}
	else if (TutorialCount==3) {
		//当たり判定がonになる
		colFlag = true;
		countFlag = true;
	}
	else{
		countFlag = false;
	}
	if (TutorialCount == 1 || TutorialCount >= 3) {
		//動ける
		moveFlag = true;
	}
	else {
		//動けない
		moveFlag = false;
	}
}

void Tutorial::Draw()
{
	TutorialSprite[TutorialCount]->Draw();
	if (TutorialCount != 1 && TutorialCount != 3) {
		TutorialUI->Draw();
	}
}
