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
	FbxObject3d::CreateGraphicsPipeline(L"Resources/shaders/FBXPS.hlsl", L"Resources/shaders/FBXVS.hlsl");
	
	//titleScene = std::unique_ptr <TitleScene>(new TitleScene());
	//titleScene->Initialize();
	//selectScene = std::unique_ptr <SelectScene>(new SelectScene());
	//selectScene->Initialize();
	//clearScene = std::unique_ptr <ClearScene>(new ClearScene());
	//clearScene->Initialize();
	//gameScene = std::unique_ptr <GameScene>(new GameScene());
	//gameScene->Initialize();
	//gameScene->InitTH();
	//loadScene = std::unique_ptr <Loading>(new Loading());
	//loadScene->Initialize();
	//change = std::unique_ptr <SceneChange>(new SceneChange());
	//change->Initialize();
	BaseScene* scene1 = new TitleScene();
	//シーンマネージャに最初のシーンセット
	SetNextScene(scene1);
	Load_s = NOLOAD;
	loadFlag = false;
	//scene = LOAD;
}

void SceneManager::Update()
{
	if (nextScene_)
	{
		//if (scene_->GetSCangeFlag() == true) {
			//change->SetChangeSFlag(true);
			if (scene_)
			{
				scene_->Finalize();
				delete scene_;
			}
			//シーン切り替え
			scene_ = nextScene_;
			nextScene_ = nullptr;
			scene_->SetSceneManager(this);
			//次のシーンを初期化する
			//if (change->GetChangeEFlag() == true) {
				scene_->Initialize();
				scene_->Init();
				//scene_->InitTH();
			//}
		//}
	}
	scene_->Update();

	//ローディング
	if (loadFlag == true) {
		switch (Load_s)
		{
		case SceneManager::NOLOAD://ロードしていないとき
			t = std::thread([&] {
				BaseScene* scene = new GameScene();
				scene->InitTH();
				Load_s = ENDLOAD; });
			Load_s = NOWLOAD;
			break;
		case SceneManager::NOWLOAD://ロードしているとき
			break;
		case SceneManager::ENDLOAD://ロード終わったら
			t.join();
			BaseScene* scene = new TitleScene();
			SetNextScene(scene);
			Load_s = NOLOAD;
			loadFlag = false;
			break;
			//default:
				//break;
		}
	}
	
	//change->Update();
}
void SceneManager::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());

	scene_->DrawBG();
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
}

void SceneManager::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());
	
	scene_->Draw();
	Object3d::PostDraw();
	FbxObject3d::PostDraw();
}

void SceneManager::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	
	scene_->DrawFront();
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}

void SceneManager::InitTH()
{

}
