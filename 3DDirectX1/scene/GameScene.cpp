#include "GameScene.h"
#include <cassert>
//#include "FbxLoader.h"
#include<time.h>
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
	model2 = model2->Create("bullet");
	object3d = Object3d::Create(model);
	object3d2 = Object3d::Create(model2);
	

	object3d->Update();
	object3d2->Update();
	//モデル名を指定して読み込み
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	//あああああ




	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);
	
	Sprite::LoadTexture(1, L"Resources/jimenParticle.png");
	Sprite::LoadTexture(2, L"Resources/white1x1.png");

	sprite = Sprite::CreateSprite(1, playerPos2d);
	sprite2 = Sprite::CreateSprite(2, playerPos2d2);
	sprite->SetSize({ 100,100 });
	sprite2->SetSize({ 100, 1 });
	//audio->SoundPlayWave("Resources/ショット.wav",true);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetEye({ 0, 0, -100 });
	//camera->SetDistance(20.0f);
			//v2.x = v * cos(60 * PI / 180.0);
			//v2.y = v * sin(60 * PI / 180.0);
		
	//vu = v;
	//vBu = vB;
	srand(time(NULL));
	radius = 2.0f;
}

void GameScene::Update()
{

#pragma region MT4_課題1コメントアウト	

	//if (input->TriggerKey(DIK_SPACE)) {

	//	Mflag = true;
	//}
	//

	//if (Mflag == true) {
	//	playerPosition2.y = playerPosition2.y + v;
	//	v = -g + v;
	//	g = k*v / m;
	/*	if (playerPosition2.y >= 1000) {
			playerPosition2.y = 30;
			v = 0.0f;
			g = 9.8f / 60.0f;
			fx1 = 1.0f;
			m = 5.0f;
			Mflag = false;
		}*/
	//}
#pragma endregion

#pragma region MT4_課題2_1
	//if (input->TriggerKey(DIK_SPACE)) {

	//	Mflag = true;
	//}
	//if (Mflag == true) {
	//	if (v <= 0) {
	//		v = 0;
	//	}
	//	playerPosition2.x = playerPosition2.x + v;
	//
	//		v = v - a;

	//	fx = 100 * cos(60 * PI / 180.0);
	//	fy = 100 * sin(60 * PI / 180.0);

	//	N = m * g - fy;
	//	fx = fx - (uk * N);
	//
	//	a = fx / m;
	//	a = a / 300;

	//}
#pragma endregion
	
#pragma region MT4_課題2_2

	//if (input->TriggerKey(DIK_SPACE)) {

	//	Mflag = true;
	//}
	//
	//	if (Mflag == true) {
	//		
	//		if (playerPosition2.y<= 500) {
	//			playerPosition2.x += v2.x;
	//			playerPosition2.y -= v2.y;


	//			v2.y = -g + v2.y;
	//			g = k * v / m;

	//		}
	//	}
	//
	//sprite->SetPosition(playerPosition2);
#pragma endregion
#pragma region MT4_課題3

	/*sphereA.center = XMVectorSet(playerPosition.x, playerPosition.y, playerPosition.z, 1);
	sphereB.center = XMVectorSet(playerPositionB.x, playerPositionB.y, playerPositionB.z, 1);
	sphereA.radius = 2.0f;
	sphereB.radius = 2.0f;

	if (input->TriggerKey(DIK_SPACE)) {

		Mflag = true;
	}
	
	if (Mflag == true) {

		playerPosition.x += v;
		playerPositionB.x -= vB;
	}
	if (Collision::CheckSphere2Sphere(sphereA, sphereB)) {
		debugText.Printf(0, 500, 3.0f, "Hit");

		v = (vBu * m2 - vu * m) / m;
		vB = (v * m - vBu * m2) / m2;
		v *= e;
		vB *= e;
	}*/


#pragma endregion
#pragma region MT4_課題4



//if (input->TriggerKey(DIK_SPACE)) {
//
//	Mflag = true;
//}
//
//if (Mflag == true) 
//{
//	Length += 0.5f;
//	if (Length >= 50)
//	{
//		Length = 50;
//	}
//		radius = angle * 3.14f / 180.0f;
//		add_x = cos(radius) * Length;
//		add_y = sin(radius) * Length;
//		playerPosition.x = playerPositionB.x + add_x;
//		playerPosition.y = playerPositionB.y + add_y;
//		angle += va;
//}
//if (input->TriggerKey(DIK_R)) {
//	Mflag = false;
//	Length = 0;
//	playerPosition = { 0.0f,0.0f,0.0f };
//}

#pragma endregion
#pragma region MT4_課題5
if (input->TriggerKey(DIK_SPACE)) {

	Mflag = true;
}
playerEndPos2d2 = { playerPos2d2.x+cosf(XMConvertToRadians(angle))*100,playerPos2d2.y + sinf(XMConvertToRadians(angle))*100 };

sprite->SetAnchorPoint({ 0.5,0.5 });
playerPos2d = { 100,100};

//if (Mflag == true) {
	
	//if (playerPos2d2.x >= 0 && playerPos2d2.x < 1280) {
		if (input->PushKey(DIK_D)) {
			playerPos2d2.x += 1;
		}
		if (input->PushKey(DIK_A)) {
			playerPos2d2.x -= 1;
		}
	//}
	//if (playerPos2d2.y >= 0 && playerPos2d2.y <720) {
		if (input->PushKey(DIK_W)) {
			playerPos2d2.y -= 1;
		}
		if (input->PushKey(DIK_S)) {
			playerPos2d2.y += 1;
		}
	//}
	if (input->PushKey(DIK_Q)) {
		angle -=1 ;
	}
	if (input->PushKey(DIK_E)) {
		angle += 1;
	}
	sprite->SetColor({ 1,1,1,1 });
	//avec
	XMFLOAT2 a = { playerPos2d2.x - playerEndPos2d2.x,playerPos2d2.y - playerEndPos2d2.y };
	//bvec
	XMFLOAT2 b = { playerPos2d2.x - playerPos2d.x,playerPos2d2.y - playerPos2d.y };
	//cvec
	XMFLOAT2 c = { playerEndPos2d2.x - playerPos2d.x,playerEndPos2d2.y - playerPos2d.y };

	//|a|算出
	float alength = sqrtf(pow(a.x, 2) + pow(a.y, 2));
	//|b|算出
	float blength = sqrtf(pow(b.x, 2) + pow(b.y, 2));
	//|c|算出
	float clength = sqrtf(pow(c.x, 2) + pow(c.y, 2));
	float noma =0;
	float noma2 = 0;
	if (alength > 0)
	{
		noma = a.x / alength;
		noma2 = a.y / alength;
	}
	bool flag = true;
	
		//外積	
		float distance = abs(b.x * noma2 - b.y * noma);

		

		if (distance <= radius) {
			float dot1 = b.x * a.x + b.x * a.y;
			float dot2 = c.x * a.x + c.x * a.y;
			if (dot1*dot2 <= 0.0f) {
				sprite->SetColor({ 1,0,0,1 });
			}
			if (blength < radius || clength < radius) {
				sprite->SetColor({ 1,0,0,1 });
			}
		}
		
	


		
		
	
//}

sprite->SetPosition(playerPos2d);
sprite2->SetPosition(playerPos2d2);
sprite2->SetRotation(angle);
#pragma endregion
	if (input->PushMouse(0)) {
		debugText.Printf(100, 100, 5.0f, "www");
	}
	// パーティクル生成
	//CreateParticles();
	camera->Update();
	particleMan->Update();
	object3d->SetPosition(playerPosition);
	object3d2->SetPosition(playerPositionB);
	object3d2->SetScale({ 2.0f,2.0f,2.0f });
	object3d->Update();
	object3d2->Update();
	
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	//object3d->Draw();
	//object3d2->Draw();
	Object3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	sprite2->Draw();
	//char str[256];

	//debugText.Printf(0, 80, 3.0f, "%f,%f",playerEndPos2d2.x,playerEndPos2d2.y);
	//debugText.Printf(0, 140, 3.0f, "%d",circleFlag);

	//debugText.Printf(0, 80, 3.0f, "SPACE:free fall");

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

