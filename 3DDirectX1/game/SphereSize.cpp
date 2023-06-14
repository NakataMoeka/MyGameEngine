#include "SphereSize.h"
#include"DebugText.h"
void SphereSize::Initialize()
{
	Sprite::LoadTexture(25, L"Resources/UI/number/Number.png");
	Sprite::LoadTexture(26, L"Resources/UI/number/m.png");
	Sprite::LoadTexture(27, L"Resources/UI/number/c.png");
	Sprite::LoadTexture(29, L"Resources/UI/number/target.png");
	for (int i = 0; i < 10; i++) {
		Number[i] = std::unique_ptr<Sprite>(Sprite::CreateSprite(25, { 180,50 }));
	}
	for (int i = 0; i < 4; i++) {
		Meters[i] = std::unique_ptr<Sprite>(Sprite::CreateSprite(26, { 0,0 }));
	}
	for (int i = 0; i < 2; i++) {
		Centimeter[i] = std::unique_ptr<Sprite>(Sprite::CreateSprite(27, { 0, 0 }));
	}
	TargetSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(29, { 0,0 }));

}

void SphereSize::Init(int stageNum)
{
	this->stageNum = stageNum;
	//if (stageNum == 1||stageNum==0) {
		Tsize = 1;
//	}
	//else if (stageNum == 2) {
		Tsize = 10;
	//}
	TCount = 0;
	tSC = 0;
	tC = 0;
	tM = 0;
	tSM = 0;
	tMM = 0;
}

void SphereSize::InitStage(int maxNum)
{
	tSC = maxNum % 10;
	tC = (maxNum / 10) % 10;
	tSM = (maxNum / 100) % 10;
	tM = (maxNum / 1000) % 10;
	tMM = (maxNum / 10000) % 10;
	Number[5]->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,48 });
	Number[6]->SetTextureRect({ 0 + 32 * (float)tC,0 }, { 32,48 });
	Number[7]->SetTextureRect({ 0 + 32 * (float)tSM,0 }, { 32,48 });
	Number[8]->SetTextureRect({ 0 + 32 * (float)tM,0 }, { 32,48 });
	Number[9]->SetTextureRect({ 0 + 32 * (float)tMM,0 }, { 32,48 });
}

void SphereSize::Update()
{
	if (stageNum == 1) {
		if (Tsize % 10 == 0) {
			TCount++;
		}
		else {
			TCount = 0;
		}
	}
	else if (stageNum == 2) {
		
		if (Tsize % 100 == 0) {
			TCount++;
		}
		else {
			TCount = 0;
		}
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
	Meters[2]->SetSize({ 18,18 });
	Meters[3]->SetSize({ 18,18 });
	Centimeter[0]->SetSize({ 32,32 });
	Centimeter[1]->SetSize({ 18,18 });

	tSC = Tsize % 10;
	tC = (Tsize / 10) % 10;
	tSM = (Tsize / 100) % 10;
	tM = (Tsize / 1000) % 10;
	tMM = (Tsize / 10000) % 10;

	Number[0]->SetTextureRect({ 0 + 32 * (float)tSC,0 }, { 32,48 });
	Number[1]->SetTextureRect({ 0 + 32 * (float)tC,0 }, { 32,48 });
	Number[2]->SetTextureRect({ 0 + 32 * (float)tSM,0 }, { 32,48 });
	Number[3]->SetTextureRect({ 0 + 32 * (float)tM,0 }, { 32,48 });
	Number[4]->SetTextureRect({ 0 + 32 * (float)tMM,0 }, { 32,48 });
	Number[1]->SetPosition({ 150,50 });
	
	Number[2]->SetPosition({ 90,50 });
	Number[3]->SetPosition({ 60,50 });
	Number[4]->SetPosition({ 30,50 });
	Number[5]->SetPosition({ 210,90 });
	Number[6]->SetPosition({ 190,90 });
	Number[7]->SetPosition({ 150,90 });
	Number[8]->SetPosition({ 130,90 });
	Number[9]->SetPosition({ 110,90 });
	Centimeter[0]->SetPosition({ 210,50 });
	Centimeter[1]->SetPosition({ 230,90 });
	Meters[0]->SetPosition({ 120,50 });
	Meters[1]->SetPosition({ 240,50 });
	Meters[2]->SetPosition({ 170,90 });
	Meters[3]->SetPosition({ 250,90 });
	TargetSprite->SetPosition({ 60,82 });
	TargetSprite->SetSize({ 32,32 });
}

void SphereSize::Draw()
{
	for (int i = 0; i < 10; i++) {
		Number[i]->Draw();
	}
	for (int i = 0; i < 4; i++) {
		Meters[i]->Draw();
	}
	for (int i = 0; i < 2; i++) {
		Centimeter[i]->Draw();
	}
	TargetSprite->Draw();
	//DebugText::GetInstance()->Printf(100, 40, 3.0f, { 1,1,1,1 }, "%dcm", Tsize);
}
