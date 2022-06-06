#include "GameScene.h"
#include <cassert>
#include "FbxLoader.h"
#include "FbxObject.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(object3d);
	safe_delete(object3d2);
	safe_delete(model);
	safe_delete(model2);
	safe_delete(sprite);
	safe_delete(particleMan);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	//u
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	FbxObject3d::SetDev(dxCommon->Getdev());
	FbxObject3d::SetCamera(camera);
	FbxObject3d::CreateGraphicsPipeline();

	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera);

	model = model->Create("bullet",true);
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	object3d = Object3d::Create(model);
	object3d2 = new FbxObject3d();
	object3d2->Initialize();
	object3d2->SetModel(model2);

//	object3d2->SetRotation({ 0,180,0 });
//	object3d2->SetPosition({ 0,0,0 });
	object3d->Update();
//	object3d2->Update();
	//モデル名を指定して読み込み
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	//あああああ

	//object3d2->Update();


	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/background.png");

	sprite = Sprite::CreateSprite(1, { 0,0 });

	//audio->SoundPlayWave("Resources/ショット.wav",true);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 2.5f, 0 });
	camera->SetEye({ 0, 0, -10 });
}

void GameScene::Update()
{


	if (input->PushMouse(0)) {
		debugText.Printf(100, 100, 5.0f, "www");
	}
	// パーティクル生成
	//CreateParticles();
	if (input->TriggerKey(DIK_SPACE)) {
		object3d2->PlayAnimation();
	}
	camera->Update();
	particleMan->Update();
	object3d->SetPosition(playerPosition);
	object3d2->SetRotation({ 0,90,0 });
	object3d->Update();
	object3d2->Update();

}

void GameScene::DrawBG()
{
	//背景
	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	sprite->PostDraw();
	dxCommon->ClearDepthBuffer();
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());

	//object3d->Draw();
	object3d2->Draw();
	Object3d::PostDraw();
	FbxObject3d::PostDraw();

}
void GameScene::DrawFront()
{
	//前景
	sprite->PreDraw(dxCommon->GetCmdList());
	//sprite->Draw();
	debugText.Printf(100, 20, 3.0f, "MauseLeftClick");
	debugText.Printf(600, 20, 3.0f, "%f", playerPosition.x);
	debugText.DrawAll(dxCommon->GetCmdList());
	sprite->PostDraw();
}
void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}