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
	//changeSFlag��true�ɂȂ�����
	if (changeSFlag == true) {
		//�t�F�[�h��1�����Ȃ�0.1�����Z
		if (fade < 1) {
			fade += 0.1f;
		}
		//�t�F�[�h��1�ȏ�Ȃ�
		if (fade >= 1) {
			fade = 1.0f;
			//changeSFlag��false�ɂ���
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
