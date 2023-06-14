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
	if (fadeIn == true) {
		//�t�F�[�h��1�����Ȃ�0.1�����Z
		if (fade < 1) {
			fade += 0.1f;
		}
		//�t�F�[�h��1�ȏ�Ȃ�
		if (fade >= 1) {
			fade = 1.0f;
			fadeIn = false;
			fadeOut = true;
		}
	}
	if (fadeOut == true) {
		if (fade >= 0) {
			fade -= 0.1f;
		}
		if (fade <= 0) {
			fade = 0.0f;
			fadeOut = false;
		}
	}
	ChangeS->SetColor({ 1, 1, 1, fade });
}

void SceneChange::DrawBG()
{
}

void SceneChange::Draw()
{
}

void SceneChange::DrawFront()
{
	if (fadeIn == true || fadeOut == true) {
		ChangeS->Draw();
	}
}
