#include "Timer.h"
#include<time.h>
#include"input.h"
#include"DebugText.h"
void Timer::Initialize()
{
	Sprite::LoadTexture(6, L"Resources/UI/TimeUI.png");
	Sprite::LoadTexture(7, L"Resources/UI/TimeUI2.png");
	Sprite::LoadTexture(28, L"Resources/UI/TimeUI_2.png");
	timeSprite = Sprite::CreateSprite(6, { 1100,100 });
	timeSprite2 = Sprite::CreateSprite(7, { 1100,100 });
	timeSprite3 = Sprite::CreateSprite(28, { 1100,100 });
}

void Timer::Init()
{
	TimeRot = 0;
	TimeCount = 0;
	start = (double)time(NULL);
	total = 0.0;
	SetTime = 180;
	start = clock() / CLOCKS_PER_SEC;
	dt = SetTime;
	TR = (float)dt;
	poseFlag = false;
}
void Timer::Update()
{
	
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
	
	timeSprite->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetAnchorPoint({ 0.5,0.5 });
	timeSprite3->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetRotation(-TimeRot);
}

void Timer::Draw()
{
	if (((int)dt / 60 == 0)) {
		timeSprite3->Draw();
		DebugText::GetInstance()->Printf(1000, 50, 3.0f, { 1.0f,0.5f,0,1 }, "%d", (int)dt);
	}
	else
	{
		timeSprite->Draw();
		DebugText::GetInstance()->Printf(1000, 50, 3.0f, { 1,1,1,1 }, "%d", (int)(dt / 60) + 1);
	}
	timeSprite2->Draw();
}
