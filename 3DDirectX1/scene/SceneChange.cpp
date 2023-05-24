#include "SceneChange.h"

void SceneChange::Initialize()
{
	Sprite::LoadTexture(60, L"Resources/white.jpg");
	ChangeS = std::unique_ptr<Sprite>(Sprite::CreateSprite(60, { 0,0 }));
	ChangeS->SetSize({ 1280,720 });
	fade = 0.0f;

}

void SceneChange::Init()
{
}

void SceneChange::Update()
{
	ChangeS->SetColor({ 1, 1, 1, fade });
	//changeSFlagがtrueになったら
	if (changeSFlag == true) {
		//フェードが1未満なら0.1ずつ加算
		if (fade < 1) {
			fade += 0.1f;
		}
		//フェードが1以上なら
		if (fade >= 1) {
			fade = 1.0f;
			//changeSFlagをfalseにする
			changeSFlag = false;
			changeEFlag = true;
		}
	}
	if (changeEFlag == true) {
		if (fade >= 0) {
			fade -= 0.1f;
		}
		if (fade <= 0) {
			changeEFlag = false;
			fade = 0.0f;
		}
	}
}

void SceneChange::DrawBG()
{
}

void SceneChange::Draw()
{
}

void SceneChange::DrawFront()
{
	if (changeSFlag == true || changeEFlag == true) {
		ChangeS->Draw();
	}
}
