#include "Timer.h"
#include<time.h>
#include"input.h"
#include"DebugText.h"
void Timer::Initialize()
{
	Sprite::LoadTexture(6, L"Resources/UI/TimeUI.png");
	Sprite::LoadTexture(7, L"Resources/UI/TimeUI2.png");
	Sprite::LoadTexture(28, L"Resources/UI/TimeUI_2.png");
	timeSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(6, { 1100,100 }));
	timeSprite2 = std::unique_ptr<Sprite>(Sprite::CreateSprite(7, { 1100,100 }));
	timeSprite3 = std::unique_ptr<Sprite>(Sprite::CreateSprite(28, { 1100,100 }));
	for (int i = 0; i < 2; i++) {
		TimeNum[i] = std::unique_ptr<Sprite>(Sprite::CreateSprite(25, { 1000,50 }));
	}
}

void Timer::Init()
{
	TimeRot = 0;
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 0.0;
	SetTime = 180;
	dt = SetTime;
	TR = (float)dt;
	tSC = (int)(dt / 60) + 1;
	timeSprite->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetAnchorPoint({ 0.5,0.5 });
	timeSprite3->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetRotation(-TimeRot);
	TimeNum[0]->SetColor({ 1,1,1,1 });
}
void Timer::Update()
{
	if (startFlag == true) {
		if (poseFlag == true) {
			//ポーズ中はタイマー動かない
			start = clock() / CLOCKS_PER_SEC;
		}
		if (poseFlag == false) {
			//ポーズ画面じゃないときタイマーの処理をする
			if (dt > 60) {
				TR = (float)dt;
			}
			else if (dt == 60) {
				TimeRot = 180;
			}
			else if (dt <= 60) {
				TR = (float)dt * 3;
			}
			TimeRot = TR * 2;

			if (dt > 0) {
				end = clock() / CLOCKS_PER_SEC;
				total = end - start;
				dt = SetTime - total;
			}
		}
	}
	else {
		start = clock() / CLOCKS_PER_SEC;
	}
	timeSprite->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetAnchorPoint({ 0.5,0.5 });
	timeSprite3->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetRotation(-TimeRot);
	TimeNum[0]->SetSize({ 32,50 });
	TimeNum[1]->SetSize({ 32,50 });
	TimeNum[1]->SetPosition({ 960,50 });

	if (((int)dt / 60 != 0)) {
		tSC = (int)(dt / 60) + 1;
		TimeNum[0]->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,48 });
		TimeNum[0]->SetColor({ 1,1,1,1 });
	}
	else {
		tC = (int)dt / 10;
		tSC = (int)dt % 10;
		TimeNum[0]->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,48 });
		TimeNum[1]->SetTextureRect({ 0 + 32 * (float)tC,0 }, { 32,48 });
		TimeNum[0]->SetColor({ 1.0f,0.5f,0,1 });
		TimeNum[1]->SetColor({ 1.0f,0.5f,0,1 });
	}


}

void Timer::Draw()
{
	if (((int)dt / 60 == 0)) {
		timeSprite3->Draw();
		//DebugText::GetInstance()->Printf(1000, 50, 3.0f, { 1.0f,0.5f,0,1 }, "%d", (int)dt);
		TimeNum[0]->Draw();
		TimeNum[1]->Draw();
	}
	else
	{
		timeSprite->Draw();

		TimeNum[0]->Draw();
	}
	//DebugText::GetInstance()->Printf(1000, 50, 3.0f, { 1,1,1,1 }, "%d", (int)dt);
	timeSprite2->Draw();
}
