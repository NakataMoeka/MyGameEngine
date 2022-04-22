#include "GameScene.h"
#include <cassert>
//#include "FbxLoader.h"
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
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera);

	model = model->Create("bullet");
	model2 = model2->Create("Player");
	object3d = Object3d::Create(model);
	object3d2 = Object3d::Create(model2);
	
	object3d2->SetRotation({ 0,180,0 });
	object3d2->SetPosition({ 0,0,0 });
	object3d->Update();
	object3d2->Update();
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

	Sprite::LoadTexture(1, L"Resources/Arrow.png");

	sprite = Sprite::CreateSprite(1, { 10,10 });

	//audio->SoundPlayWave("Resources/ショット.wav",true);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	//camera->SetDistance(20.0f);
}

void GameScene::Update()
{

#pragma region MT4_課題1コメントアウト	

	/*if (input->TriggerKey(DIK_SPACE)) {

		Mflag = true;
	}
	

	if (Mflag == true) {
		playerPosition.y = playerPosition.y + vx;
		vx = -g + vx;
	
		if (playerPosition.y <= -1000) {
			playerPosition.y = 30;
			vx = 0.0f;
			g = 9.8f / 60.0f;
			fx1 = 1.0f;
			m = 5.0f;
			Mflag = false;
		}
	}*/
#pragma endregion

#pragma region MT4_課題2
	if (input->TriggerKey(DIK_SPACE)) {

		Mflag = true;
	}
	if (Mflag == true) {
		if (vx <= 0) {
			vx = 0;
		}
		playerPosition.x = playerPosition.x + vx;
		if (vx < 0.5f) {
			vx = vx + a;
		}
		else if(vx>=0.5f) {
			vx = vx - a;
		}

		fx = 100 * cos(60 * PI / 180.0);
		fy = 100 * sin(60 * PI / 180.0);

		N = m * g - fy;
		fx = fx - (uk * N);
	
		a = fx / m;
		a = a / 300;

	}
#pragma endregion
	
	

	if (input->PushMouse(0)) {
		debugText.Printf(100, 100, 5.0f, "www");
	}
	// パーティクル生成
	//CreateParticles();
	camera->Update();
	particleMan->Update();
	object3d->SetPosition(playerPosition);
	object3d->Update();
	object3d2->Update();
	
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	object3d->Draw();
	//object3d2->Draw();
	Object3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	char str[256];


	debugText.Printf(0, 140, 3.0f, "%f,%f,%f",fx,fy,vx);
	debugText.Printf(0, 80, 3.0f, "SPACE:free fall");

	debugText.DrawAll(dxCommon->GetCmdList( ));
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

