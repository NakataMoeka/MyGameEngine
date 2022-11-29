#include "Tutorial.h"

void Tutorial::Initialize()
{
	Sprite::LoadTexture(50, L"Resources/UI/Tutorial1.png");
	Sprite::LoadTexture(51, L"Resources/UI/Tutorial2.png");
	Sprite::LoadTexture(52, L"Resources/UI/Tutorial3.png");
	Sprite::LoadTexture(53, L"Resources/UI/Tutorial4.png");
	Sprite::LoadTexture(54, L"Resources/UI/Tutorial5.png");
	Sprite::LoadTexture(55, L"Resources/UI/Tutorial6.png");
	Sprite::LoadTexture(56, L"Resources/UI/Tutorial7.png");
	TutorialSprite[0] = Sprite::CreateSprite(50, { 0,0 });
	TutorialSprite[1] = Sprite::CreateSprite(51, { 0,0 });
	TutorialSprite[2] = Sprite::CreateSprite(52, { 0,0 });
	TutorialSprite[3] = Sprite::CreateSprite(53, { 0,0 });
	TutorialSprite[4] = Sprite::CreateSprite(54, { 0,0 });
	TutorialSprite[5] = Sprite::CreateSprite(55, { 0,0 });
	TutorialSprite[6] = Sprite::CreateSprite(56, { 0,0 });
}

void Tutorial::Init()
{
}

void Tutorial::Update()
{
}

void Tutorial::Draw()
{
	for (int i = 0; i < 7; i++) {
		TutorialSprite[i]->Draw();
	}
}
