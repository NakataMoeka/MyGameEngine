#include "SceneManager.h"
#include"Input.h"
void SceneManager::Initialize(DXCommon* dxCommon, Audio* audio)
{
	titleScene = new TitleScene();
	titleScene->Initialize(dxCommon, audio);
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, audio);
	titleScene->Init();
	gameScene->Init();
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (scene == TITLE) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			gameScene->Init();
			scene = GAME;
		}
		titleScene->Update();
	}
	else if (scene == GAME) {
		gameScene->Update();
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
}

void SceneManager::Draw()
{
	if (scene == TITLE) {
		titleScene->Draw();
	}
	else if (scene == GAME) {
		gameScene->Draw();
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
}
