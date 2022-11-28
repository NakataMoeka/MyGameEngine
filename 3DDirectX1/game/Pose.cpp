#include "Pose.h"
#include"input.h"
#include<cassert>

void Pose::Initialize(Audio* audio)
{

	assert(audio);

	this->audio = audio;
	Sprite::LoadTexture(20, L"Resources/UI/Pose.png");
	Sprite::LoadTexture(21, L"Resources/UI/TitleBack.png");
	Sprite::LoadTexture(22, L"Resources/UI/Back.png");
	Sprite::LoadTexture(23, L"Resources/UI/Info.png");
	Sprite::LoadTexture(24, L"Resources/UI/PoseBack.png");
	PoseSprite = Sprite::CreateSprite(20, { 0,0 });
	TitleBackSprite = Sprite::CreateSprite(21, { 0,0 });
	BackSprite = Sprite::CreateSprite(22, { 0,0 });
	InfoSprite = Sprite::CreateSprite(23, { 0,0 });
	PBSprite = Sprite::CreateSprite(24, { 0,0 });
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
		if (Input::GetInstance()->TriggerKey(DIK_R)) {
			PoseFlag = true;
			audio->SEPlayWave(sound1);
		}
		jFlag = false;
	}
	else if (PoseFlag == true) {

		if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW)) {
			PS = 1;
			audio->SEPlayWave(sound2);
		}
		else if (Input::GetInstance()->TriggerKey(DIK_UPARROW)) {
			PS = 0;
			audio->SEPlayWave(sound2);
		}

		if (PS == 0) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				PoseFlag = false;
				jFlag = true;
				audio->SEPlayWave(sound1);
			}
			BackSprite->SetSize({ 500,110 });
			TitleBackSprite->SetSize({ 350,55 });
			BackSprite->SetPosition({ 400,500 });
			TitleBackSprite->SetPosition({ 500,600 });
		}
		else if (PS == 1) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				TitleFlag = true;
				audio->StopWave();
				audio->SEPlayWave(sound1);
			}
			BackSprite->SetSize({ 250,55 });
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
