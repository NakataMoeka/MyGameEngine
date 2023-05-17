#include "SceneManager.h"
#include"Input.h"
SceneManager::~SceneManager()
{
	//#if _DEBUG
	if (LoadFlagF == true) {
		t.detach();
	}
	t.~thread();
	//#endif
}
void SceneManager::Initialize(DXCommon* dxCommon, Audio* audio)
{
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	Sprite::LoadTexture(60, L"Resources/white.jpg");
	Change = std::unique_ptr<Sprite>(Sprite::CreateSprite(60, { 0,0 }));
	Change->SetSize({ 1280,720 });

	titleScene = std::unique_ptr <TitleScene>(new TitleScene());
	titleScene->Initialize(dxCommon, audio);
	selectScene = std::unique_ptr <SelectScene>(new SelectScene());
	selectScene->Initialize(dxCommon, audio);
	clearScene = std::unique_ptr <ClearScene>(new ClearScene());
	clearScene->Initialize(dxCommon, audio);
	gameScene = std::unique_ptr <GameScene>(new GameScene());
	gameScene->Initialize(dxCommon, audio);
	//gameScene->InitTH();
	loadScene = std::unique_ptr <Loading>(new Loading());
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
	//タイトル
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
	//セレクト
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
	//ゲームシーン
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
	//エンド
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
	else if (scene == LOAD) {
		loadScene->Update();
	}
	if (gameScene->GetBFlag() == true) {
		Bflag = true;
	}
	else if (gameScene->GetBFlag() == false) {
		Bflag = false;
	}
	SceneChange();
	//ローディング
	if (LoadFlagF == true) {
		switch (Load_s)
		{
		case SceneManager::NOLOAD://ロードしていないとき
			t = std::thread([&] {InitTH(); });
			scene = LOAD;
			Load_s = NOWLOAD;
			break;
		case SceneManager::NOWLOAD://ロードしているとき
			break;
		case SceneManager::ENDLOAD://ロード終わったら
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

void SceneManager::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
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
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
}

void SceneManager::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());
	if (scene == TITLE) {
		titleScene->Draw();
	}
	else if (scene == GAME) {
		gameScene->Draw();
	}
	else if (scene == END) {
		clearScene->Draw();
	}
	Object3d::PostDraw();
	FbxObject3d::PostDraw();
}

void SceneManager::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
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

	if (changeSFlag == true || changeEFlag == true) {
		Change->Draw();
	}
	Sprite::PostDraw();
}

void SceneManager::InitTH()
{
	gameScene->InitTH();
	Load_s = ENDLOAD;
}