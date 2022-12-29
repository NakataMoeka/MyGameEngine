#include "start.h"
#include <time.h>
#include"DebugText.h"
void start::Initialize(Audio* audio)
{
	Sprite::LoadTexture(65, L"Resources/UI/number/number2.png");
	Sprite::LoadTexture(66, L"Resources/UI/number/Go.png");
	number = Sprite::CreateSprite(65, { 500,300 });
	Go = Sprite::CreateSprite(66, { 400,300 });
}

void start::Init()
{
	start = (double)time(NULL);
	total = 0.0;
	SetTime = 8;
	start = clock() / CLOCKS_PER_SEC;
	dt = SetTime;
	tSC = 0;
	startFlag = false;
}

void start::Update()
{
	if (dt > 0) {
		end = clock() / CLOCKS_PER_SEC;
		total = end - start;
		dt = SetTime - total;
	}
	if (dt == 0) {
		startFlag = true;
	}
	number->SetSize({ 120,120 });
	Go->SetSize({ 360,120 });
	tSC = ((int)dt % 10)-2;
	number->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,45 });
}

void start::Draw()
{
	if (startFlag == false) {
		if (dt > 1 && dt < 5) {
			number->Draw();
		}
		if (dt == 1) {
			Go->Draw();
		}
	}
	//DebugText::GetInstance()->Printf(300, 300, 3.0f, { 1,1,1,1 }, "%d", (int)dt);
}
