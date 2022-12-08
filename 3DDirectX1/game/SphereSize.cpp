#include "SphereSize.h"
#include"DebugText.h"
void SphereSize::Initialize()
{
	Sprite::LoadTexture(25, L"Resources/UI/number/Number.png");
	Sprite::LoadTexture(26, L"Resources/UI/number/m.png");
	Sprite::LoadTexture(27, L"Resources/UI/number/c.png");

	for (int i = 0; i < 10; i++) {
		Number[i] = Sprite::CreateSprite(25, { 180,50 });
	}
	for (int i = 0; i < 4; i++) {
		Meters[i] = Sprite::CreateSprite(26, { 0,0 });
	}
	for (int i = 0; i < 2; i++) {
		Centimeter[i] = Sprite::CreateSprite(27, { 0,0 });
	}

}

void SphereSize::Init()
{
	Tsize = 1;
	TCount = 0;
	tSC = 0;
	tC = 0;
	tM = 0;
	tSM = 0;
	tMM = 0;
}

void SphereSize::InitStage(int maxNum)
{
	Number[5]->SetTextureRect({ 0 + 16 * (float)tSC,0 }, { 16,45 });
	Number[6]->SetTextureRect({ 0 + 16 * (float)tC,0 }, { 16,45 });
	Number[7]->SetTextureRect({ 0 + 16 * (float)tSM,0 }, { 16,45 });
	Number[8]->SetTextureRect({ 0 + 16 * (float)tM,0 }, { 16,45 });
	Number[9]->SetTextureRect({ 0 + 16 * (float)tMM,0 }, { 16,45 });
	tSC = maxNum % 10;
	tC = maxNum / 10;
	tSM = maxNum / 100;
	tM = maxNum / 1000;
	tMM = maxNum / 10000;
}

void SphereSize::Update()
{
	if (Tsize % 10 == 0) {
		TCount++;
	}
	else {
		TCount = 0;
	}
	for (int i = 0; i < 5; i++) {
		Number[i]->SetSize({ 32,32 });
	}
	for (int i = 5; i < 10; i++) {
		Number[i]->SetSize({ 16,16 });
	}
	for (int i = 0; i < 2; i++) {
		Meters[i]->SetSize({ 32,32 });
	}
	Meters[2]->SetSize({ 16,16 });
	Meters[3]->SetSize({ 16,16 });
	Centimeter[0]->SetSize({ 32,32 });
	Centimeter[1]->SetSize({ 16,16 });


	tSC = Tsize % 10;
	tC = Tsize / 10;
	tSM = Tsize / 100;
	tM = Tsize / 1000;
	tMM = Tsize / 10000;
	Number[0]->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,45 });
	Number[1]->SetTextureRect({ 0 + 32 * (float)tC,0 }, { 32,45 });
	Number[2]->SetTextureRect({ 0 + 32 * (float)tSM,0 }, { 32,45 });
	Number[3]->SetTextureRect({ 0 + 32 * (float)tM,0 }, { 32,45 });
	Number[4]->SetTextureRect({ 0 + 32 * (float)tMM,0 }, { 32,45 });



	Number[1]->SetPosition({ 150,50 });
	Number[2]->SetPosition({ 90,50 });
	Number[3]->SetPosition({ 60,50 });
	Number[4]->SetPosition({ 30,50 });
	Centimeter[0]->SetPosition({ 210,50 });
	Meters[0]->SetPosition({ 120,50 });
	Meters[1]->SetPosition({ 240,50 });
}

void SphereSize::Draw()
{
	for (int i = 0; i < 5; i++) {
		Number[i]->Draw();
	}
	Meters[0]->Draw();
	Meters[1]->Draw();
	Centimeter[0]->Draw();
	//DebugText::GetInstance()->Printf(100, 40, 3.0f, { 1,1,1,1 }, "%dcm", Tsize);
}
