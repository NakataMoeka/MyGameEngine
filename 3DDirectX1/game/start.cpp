#include "start.h"
#include <time.h>
#include"DebugText.h"
#include"Input.h"
void start::Initialize()
{

	Sprite::LoadTexture(65, L"Resources/UI/number/number2.png");
	Sprite::LoadTexture(66, L"Resources/UI/number/Go.png");
	Sprite::LoadTexture(67, L"Resources/UI/message.png");
	Sprite::LoadTexture(68, L"Resources/UI/oshioki.png");
	Sprite::LoadTexture(69, L"Resources/UI/message2.png");
	Sprite::LoadTexture(70, L"Resources/UI/tutorialUI.png");
	number = std::unique_ptr<Sprite>(Sprite::CreateSprite(65, { 550,300 }));
	Go = std::unique_ptr<Sprite>(Sprite::CreateSprite(66, { 450,300 }));
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/カウントダウン電子音.wav");
	message[0] = std::unique_ptr<Sprite>(Sprite::CreateSprite(67, { 150,400 }));
	message[1] = std::unique_ptr<Sprite>(Sprite::CreateSprite(68, { 300,400 }));
	message[2] = std::unique_ptr<Sprite>(Sprite::CreateSprite(69, { 150,400 }));
	messageUI = std::unique_ptr<Sprite>(Sprite::CreateSprite(70, { 700,550 }));
}

void start::Init()
{
	start = (double)time(NULL);
	total = 0.0;
	SetTime = 5;

	dt = SetTime;
	tSC = 0;
	startFlag = false;
	GoFlag = false;
	MCount = 0;
}

void start::Update()
{	
	if (GoFlag == false) {
		//目標発表
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			if (MCount < 2) {
				MCount++;
			}
		}
		if (MCount == 2) {
			GoFlag = true;
			start = clock() / CLOCKS_PER_SEC;
			audio->SEPlayWave(sound1);
		}
	}
	else if (GoFlag == true) {
		//開始カウントダウンの処理
		if (dt > 0) {
			end = clock() / CLOCKS_PER_SEC;
			total = end - start;
			dt = SetTime - total;
		}
		if (dt == 0) {
			startFlag = true;
		}
	}
	number->SetSize({ 120,130 });
	Go->SetSize({ 360,120 });
	tSC = ((int)dt % 10) - 2;
	number->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,48 });
}

void start::Draw(int stage)
{
	if (GoFlag == true) {
		if (startFlag == false) {
			if (dt > 1 && dt < 5) {
				number->Draw();
			}
			if (dt == 1) {
				Go->Draw();
			}
		}
	}
	else if (GoFlag == false) {
		if (MCount == 0) {
			if (stage == 1) {
				message[0]->Draw();
			} 
			else if (stage == 2) {
				message[2]->Draw();
			}
		}
		else if (MCount == 1) {
			message[1]->Draw();
		}
		messageUI->Draw();
	}
	//DebugText::GetInstance()->Printf(300, 300, 3.0f, { 1,1,1,1 }, "%d", (int)dt);
}
