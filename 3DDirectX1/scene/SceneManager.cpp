#include "SceneManager.h"
#include"Input.h"
void SceneManager::Initialize(DXCommon* dxCommon, Audio* audio)
{
	titleScene = new TitleScene();
	titleScene->Initialize(dxCommon, audio);
	clearScene = new ClearScene();
	clearScene->Initialize(dxCommon, audio);
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, audio);

	titleScene->Init();
	Bflag = false;
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
			gameScene->Init();
			scene = GAME;
		}
		titleScene->Update();
	}
	else if (scene == GAME) {
		if (gameScene->GetClearFlag() == true) {
			clearScene->Init();
			clearScene->SetClearFlag(true);
			scene = END;
		}
		if (gameScene->GetOverFlag() == true) {
			clearScene->Init();
			clearScene->SetOverFlag(true);
			scene = END;
		}
		if (gameScene->GetTitleFlag() == true) {
			titleScene->Init();
			scene = TITLE;
		}
		gameScene->Update();
	}
	else if (scene == END) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			clearScene->SetClearFlag(false);
			clearScene->SetOverFlag(false);
			titleScene->Init();
			scene = TITLE;
		}
		clearScene->Update();
	}
	if (gameScene->GetBFlag() == true) {
		Bflag = true;
	}
	else if (gameScene->GetBFlag() == false) {
		Bflag = false;
	}
}

void SceneManager::DrawBG()
{
	if (scene == TITLE) {
		titleScene->DrawBG();
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
	else if (scene == GAME) {
		gameScene->DrawFront();
	}
	else if (scene == END) {
		clearScene->DrawFront();
	}
}
