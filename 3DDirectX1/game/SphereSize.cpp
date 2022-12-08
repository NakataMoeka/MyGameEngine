#include "SphereSize.h"
#include"DebugText.h"
void SphereSize::Initialize()
{
	Sprite::LoadTexture(25, L"Resources/UI/number/Number.png");
	Sprite::LoadTexture(26, L"Resources/UI/number/m.png");
	Sprite::LoadTexture(27, L"Resources/UI/number/cm.png");

	for (int i = 0; i < 8; i++) {
		Number[i] = Sprite::CreateSprite(25, { 0,0 });
	}
	for (int i = 0; i < 2; i++) {
		Meters[i] = Sprite::CreateSprite(26, {0,0});
		Centimeter[i] = Sprite::CreateSprite(27, {0,0});
	}
}

void SphereSize::Init()
{
	Tsize = 1;
	TCount = 0;
}

void SphereSize::Update()
{
	if (Tsize % 10 == 0) {
		TCount++;
	}
	else {
		TCount = 0;
	}
}

void SphereSize::Draw()
{
	DebugText::GetInstance()->Printf(100, 40, 3.0f, { 1,1,1,1 }, "%dcm", Tsize);
}
