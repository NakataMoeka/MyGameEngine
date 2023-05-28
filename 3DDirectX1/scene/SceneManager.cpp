#include "SceneManager.h"
#include"Input.h"
SceneManager::~SceneManager()
{
	//#if _DEBUG
	if (scene == LOAD) {
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
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(debugTextTexNumber);

	FbxObject3d::SetDev(dxCommon->Getdev());

	titleScene = std::unique_ptr <TitleScene>(new TitleScene());
	titleScene->Initialize();
	selectScene = std::unique_ptr <SelectScene>(new SelectScene());
	selectScene->Initialize();
	clearScene = std::unique_ptr <ClearScene>(new ClearScene());
	clearScene->Initialize();
	gameScene = std::unique_ptr <GameScene>(new GameScene());
	gameScene->Initialize();
	//gameScene->InitTH();
	loadScene = std::unique_ptr <Loading>(new Loading());
	loadScene->Initialize();
	change = std::unique_ptr <SceneChange>(new SceneChange());
	change->Initialize();

	Load_s = NOLOAD;
	scene = LOAD;
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{

	//if (nextScene_)
	//{
	//	if (scene_->GetSCangeFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (scene_)
	//		{
	//			scene_->Finalize();
	//			delete scene_;
	//		}
	//		//シーン切り替え
	//		scene_ = nextScene_;
	//		nextScene_ = nullptr;
	//		scene_->SetSceneManager(this);
	//		//次のシーンを初期化する
	//		if (change->GetChangeEFlag() == true) {
	//			scene_->Initialize();
	//			scene_->Init();
	//			scene_->InitStageNum(num);
	//		}
	//	}
	//}
	//scene_->Update();
	if (scene == TITLE) {
		if (titleScene->GetSCangeFlag() == true) {
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
				selectScene->Init();
				scene = SELECT;
			}
		}
		titleScene->Update();
	}
	//セレクト
	else if (scene == SELECT) {
		if (selectScene->GetSCangeFlag() == true) {
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
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
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
				clearScene->SetClearFlag(true);
				clearScene->Init();
				scene = END;
			}
		}
		if (gameScene->GetOverFlag() == true) {
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
				clearScene->SetOverFlag(true);
				clearScene->Init();
				scene = END;
			}
		}
		if (gameScene->GetTitleFlag() == true) {
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
				titleScene->Init();
				scene = TITLE;
			}
		}
		if (gameScene->GetTSFlag() == true) {
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
				selectScene->Init();
				scene = SELECT;
			}
		}
		gameScene->Update();
	}
	//エンド
	else if (scene == END) {
		if (clearScene->GetSCangeFlag() == true) {
			change->SetChangeSFlag(true);
			if (change->GetChangeEFlag() == true) {
				titleScene->Init();
				scene = TITLE;
			}
		}
		clearScene->Update();
	}
	//ローディング
	else if (scene == LOAD) {
		switch (Load_s)
		{
		case SceneManager::NOLOAD://ロードしていないとき
			t = std::thread([&] {InitTH(); });
			Load_s = NOWLOAD;
			break;
		case SceneManager::NOWLOAD://ロードしているとき
			break;
		case SceneManager::ENDLOAD://ロード終わったら
			t.join();
			scene = TITLE;
			titleScene->Init();
			Load_s = NOLOAD;
			break;
		default:
			break;
		}
		loadScene->Update();
	}
	change->Update();
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
	change->DrawFront();
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}

void SceneManager::InitTH()
{
	gameScene->InitTH();
	Load_s = ENDLOAD;
}