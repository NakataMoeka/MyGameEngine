#include "Loading.h"

void Loading::Initialize(DXCommon* dxCommon, Audio* audio)
{
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
	Sprite::LoadTexture(61, L"Resources/UI/Load.png");
	loadingS = Sprite::CreateSprite(61, { 600,500 });
	//loadingS->SetSize({ 1280,720 });
	Sprite::LoadTexture(62, L"Resources/UI/Select0.png");
	loadBack = Sprite::CreateSprite(62, { 0,0 });
	//loadBack->SetSize({ 1280,720 });
	loadCount = 0;
	LoadCountCount = 0;
}

void Loading::Init()
{
}

void Loading::Update()
{
	if (LoadCountCount < 10) {
		LoadCountCount++;
	}
	else if (LoadCountCount == 10) {
		LoadCountCount = 0;
	}
	if (LoadCountCount == 10) {
		if (loadCount < 4) {
			loadCount++;
		}
		else if (loadCount == 4) {
			loadCount = 0;
		}
	}
	loadingS->SetSize({ 640,360 });
	loadingS->SetTextureRect({ 0 + 1280 * (float)loadCount,0 }, {1280,720 });
}

void Loading::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	dxCommon->ClearDepthBuffer();
	loadBack->Draw();
	Sprite::PostDraw();
}

void Loading::Draw()
{
}

void Loading::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	loadingS->Draw();
	Sprite::PostDraw();
}
