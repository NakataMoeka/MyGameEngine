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
	TutorialSprite[0] = Sprite::CreateSprite(50, { 200,500 });
	TutorialSprite[1] = Sprite::CreateSprite(51, { 200,500 });
	TutorialSprite[2] = Sprite::CreateSprite(52, { 200,500 });
	TutorialSprite[3] = Sprite::CreateSprite(53, { 200,500 });
	TutorialSprite[4] = Sprite::CreateSprite(54, { 200,500 });
	TutorialSprite[5] = Sprite::CreateSprite(55, { 200,500 });
	TutorialSprite[6] = Sprite::CreateSprite(56, { 200,500 });
}

void Tutorial::Init()
{
	countFlag = false;
	endFlag = false;
	moveFlag = false;
}

void Tutorial::Update()
{
	if (countFlag == false) {
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			if (TutorialCount < 6) {
				TutorialCount++;
			}
		}
	}
	if (TutorialCount == 6) {
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {

			endFlag = true;
		}
	}
	if (TutorialCount == 1 || TutorialCount >= 3) {
		moveFlag = true;
	}
	else {
		moveFlag = false;
	}
	//else if (Input::GetInstance()->TriggerKey(DIK_LEFTARROW)) {
	//	if (TutorialCount > 0) {
	//		TutorialCount--;
	//	}
	//}
}

void Tutorial::Draw()
{
	//for (int i = 0; i < 7; i++) {
	TutorialSprite[TutorialCount]->Draw();
	//}
}
