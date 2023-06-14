#include "Loading.h"

void Loading::Initialize()
{
	Sprite::LoadTexture(61, L"Resources/UI/Load.png");
	loadingS = std::unique_ptr<Sprite>(Sprite::CreateSprite(61, { 600,500 }));
	//loadingS->SetSize({ 1280,720 });
	Sprite::LoadTexture(62, L"Resources/UI/Select0.png");
	loadBack = std::unique_ptr<Sprite>(Sprite::CreateSprite(62, { 0,0 }));
	//loadBack->SetSize({ 1280,720 });
	loadCount = 0;
	LoadCountCount = 0;
}

void Loading::Init()
{
}

void Loading::Update()
{
	//LoadCountCountが10未満ならば加算
	if (LoadCountCount < 10) {
		LoadCountCount++;
	}
	//10になったら
	else if (LoadCountCount == 10) {
		//0に戻す
		LoadCountCount = 0;
		//loadCountが4未満なら加算
		if (loadCount < 4) {
			loadCount++;
		}
		//4になったら0に戻す
		else if (loadCount == 4) {
			loadCount = 0;
		}
	}	
	loadingS->SetSize({ 640,360 });
	loadingS->SetTextureRect({ 0 + 1280 * (float)loadCount,0 }, {1280,720 });
}

void Loading::DrawBG()
{
	loadBack->Draw();
}

void Loading::Draw()
{
}

void Loading::DrawFront()
{
	loadingS->Draw();
}
