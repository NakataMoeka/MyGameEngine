#include "SceneManager.h"
#include"Input.h"
void SceneManager::Initialize(DXCommon* dxCommon, Audio* audio)
{
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;

	Sprite::LoadTexture(60, L"Resources/white.jpg");
	Change = Sprite::CreateSprite(60, { 0,0 });
	Change->SetSize({ 1280,720 });
	titleScene = new TitleScene();
	titleScene->Initialize(dxCommon, audio);
	selectScene = new SelectScene();
	selectScene->Initialize(dxCommon, audio);
	clearScene = new ClearScene();
	clearScene->Initialize(dxCommon, audio);
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, audio);
	gameScene->InitTH();
	titleScene->Init();
	Bflag = false;
	fade = 0.0f;
	//gameScene->Init();
	//clearScene->Init();
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (scene == TITLE) {
		if (titleScene->GetSCangeFlag() == true) {
			changeSFlag = true;
			if (changeEFlag == true) {
				selectScene->Init();
				scene = SELECT;
			}
		}
		titleScene->Update();
	}
	else if (scene == SELECT) {
		if (selectScene->GetSCangeFlag() == true) {

			changeSFlag = true;
			if (changeEFlag == true) {
				gameScene->InitStageNum(selectScene->GetStageNum());
				gameScene->Init();
				scene = GAME;
			}
		}
		selectScene->Update();
	}
	else if (scene == GAME) {
		if (gameScene->GetClearFlag() == true) {
			changeSFlag = true;
			if (changeEFlag == true) {
				clearScene->SetClearFlag(true);
				clearScene->Init();
				scene = END;
			}

		}
		if (gameScene->GetOverFlag() == true) {
			changeSFlag = true;
			if (changeEFlag == true) {
				clearScene->SetOverFlag(true);
				clearScene->Init();
				scene = END;
			}
		}
		if (gameScene->GetTitleFlag() == true) {
			changeSFlag = true;
			if (changeEFlag == true) {
				titleScene->Init();
				scene = TITLE;
			}
		}
		if (gameScene->GetTSFlag() == true) {
			changeSFlag = true;
			if (changeEFlag == true) {
				selectScene->Init();
				scene = SELECT;
			}
		}
		gameScene->Update();
	}
	else if (scene == END) {

		if (clearScene->GetSCangeFlag() == true) {
			changeSFlag = true;
			if (changeEFlag == true) {
				titleScene->Init();
				scene = TITLE;
			}
		}
		clearScene->Update();
	}

if (gameScene->GetBFlag() == true) {
	Bflag = true;
}
else if (gameScene->GetBFlag() == false) {
	Bflag = false;
}
SceneChange();
}

void SceneManager::SceneChange()
{
	Change->SetColor({ 1, 1, 1, fade });
	if (changeSFlag == true) {
		if (fade < 1) {
			fade += 0.1f;
		}
		if (fade >= 1) {
			fade = 1.0f;
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

void SceneManager::DrawBG()
{
	if (scene == TITLE) {
		titleScene->DrawBG();
	}
	else if (scene == SELECT) {
		selectScene->DrawBG();
	}
	else if (scene == GAME) {
		gameScene->DrawBG();
	}
	else if (scene == END) {
		clearScene->DrawBG();
	}
}

void SceneManager::Draw()
{
	if (scene == TITLE) {
		titleScene->Draw();
	}
	else if (scene == GAME) {
		gameScene->Draw();
	}
	else if (scene == END) {
		clearScene->Draw();
	}
}

void SceneManager::DrawFront()
{
	if (scene == TITLE) {
		titleScene->DrawFront();
	}
	else if (scene == SELECT) {
		selectScene->DrawFront();
	}
	else if (scene == GAME) {
		gameScene->DrawFront();
	}
	else if (scene == END) {
		clearScene->DrawFront();
	}
	Sprite::PreDraw(dxCommon->GetCmdList());
	//if (changeFlag == true) {
	Change->Draw();
	//}
	Sprite::PostDraw();
}


