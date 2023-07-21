#include "Pose.h"
#include"input.h"
#include<cassert>

void Pose::Initialize()
{
	Sprite::LoadTexture(20, L"Resources/UI/title/pose.png");
	Sprite::LoadTexture(21, L"Resources/UI/title/TitleBack.png");
	Sprite::LoadTexture(22, L"Resources/UI/title/Back.png");
	Sprite::LoadTexture(23, L"Resources/UI/Info.png");
	Sprite::LoadTexture(24, L"Resources/UI/PoseBack.png");
	PoseSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(20, { 450,0 }));
	TitleBackSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(21, { 0,0 }));
	BackSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(22, { 0,0 }));
	InfoSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(23, { 0,0 }));
	PBSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(24, { 0,0 }));
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/決定ボタンを押す26.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/SE/cursor.wav");
}

void Pose::Init()
{
	PoseFlag = false;//ゲーム中断フラグ
	TitleFlag = false;//タイトルに戻るフラグ
	PS = 0;
	jFlag = false;
}

void Pose::Update()
{
	if (PoseFlag == false) {
		//Rを押すとpose画面に行く
		if (Input::GetInstance()->TriggerKey(DIK_R)) {
			PoseFlag = true;
			audio->SEPlayWave(sound1);
		}
		jFlag = false;
	}
	else if (PoseFlag == true) {
		//ゲームに戻るかタイトルに戻るか
		if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW)) {
			PS = 1;
			audio->SEPlayWave(sound2);
		}
		else if (Input::GetInstance()->TriggerKey(DIK_UPARROW)) {
			PS = 0;
			audio->SEPlayWave(sound2);
		}
		if (PS == 0) {
			//ゲームに戻る
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				PoseFlag = false;
				jFlag = true;
				audio->SEPlayWave(sound1);
			}
			BackSprite->SetSize({ 500,110 });
			TitleBackSprite->SetSize({ 350,55 });
			BackSprite->SetPosition({ 400,500 });
			TitleBackSprite->SetPosition({ 490,600 });
		}
		else if (PS == 1) {
			//タイトルに戻る
			if (TitleFlag == false) {
				if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
					TitleFlag = true;
					audio->StopWave();
					audio->SEPlayWave(sound1);
				}
			}
			BackSprite->SetSize({ 260,55 });
			TitleBackSprite->SetSize({ 500,110 });
			BackSprite->SetPosition({ 500,550 });
			TitleBackSprite->SetPosition({ 400,600 });
		}
	}

}

void Pose::Draw()
{
		PBSprite->Draw();
		PoseSprite->Draw();
		TitleBackSprite->Draw();
		BackSprite->Draw();
		InfoSprite->Draw();
}
