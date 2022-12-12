#include "SceneManager.h"
#include"Input.h"
void SceneManager::Initialize(DXCommon* dxCommon, Audio* audio)
{
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	Sprite::LoadTexture(60, L"Resources/white.jpg");
	Change = Sprite::CreateSprite(60, { 0,0 });
	Change->SetSize({ 1280,720 });
	//Sprite::LoadTexture(61, L"Resources/UI/Load.png");
	//loadingS = Sprite::CreateSprite(61, { 0,0 });
	//loadingS->SetSize({ 1280,720 });
	titleScene = new TitleScene();
	titleScene->Initialize(dxCommon, audio);
	selectScene = new SelectScene();
	selectScene->Initialize(dxCommon, audio);
	clearScene = new ClearScene();
	clearScene->Initialize(dxCommon, audio);
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, audio);
	//gameScene->InitTH();
	loadScene = new Loading();
	loadScene->Initialize(dxCommon, audio);
	Bflag = false;
	fade = 0.0f;
	//gameScene->Init();
	//clearScene->Init();
	Load_s = NOLOAD;
	LoadFlagF = true;
	scene = LOAD;

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
	if (LoadFlagF == true) {
		switch (Load_s)
		{
		case SceneManager::NOLOAD:
			t = std::thread([&] {AsyncLoad(); });
			scene = LOAD;
			Load_s = NOWLOAD;
			break;
		case SceneManager::NOWLOAD:
			break;
		case SceneManager::ENDLOAD:
			t.join();
			scene = TITLE;
			titleScene->Init();
			Load_s = NOLOAD;
			LoadFlagF = false;
			break;
		default:
			break;
		}
	}
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
	else if (scene == LOAD) {

		loadScene->DrawBG();
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
	else if (scene == LOAD) {
		
		loadScene->DrawFront();
	}
	
	Sprite::PreDraw(dxCommon->GetCmdList());
	//if (changeFlag == true) {
	Change->Draw();
	//}
	Sprite::PostDraw();
}

void SceneManager::InitTH()
{
	gameScene->InitTH();
}

void SceneManager::SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	LoadFlag = _;
}

bool SceneManager::GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	return LoadFlag;
}

void SceneManager::AsyncLoad()
{
	InitTH();
	auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);
	Load_s = ENDLOAD;
	SetLockFlag(true);
}


