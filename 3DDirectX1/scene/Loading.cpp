#include "Loading.h"

void Loading::Initialize(DXCommon* dxCommon, Audio* audio)
{
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
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
	//LoadCountCount‚ª10–¢–ž‚È‚ç‚Î‰ÁŽZ
	if (LoadCountCount < 10) {
		LoadCountCount++;
	}
	//10‚É‚È‚Á‚½‚ç
	else if (LoadCountCount == 10) {
		//0‚É–ß‚·
		LoadCountCount = 0;
		//loadCount‚ª4–¢–ž‚È‚ç‰ÁŽZ
		if (loadCount < 4) {
			loadCount++;
		}
		//4‚É‚È‚Á‚½‚ç0‚É–ß‚·
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
