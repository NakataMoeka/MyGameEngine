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
	
	Sprite::LoadTexture(1, L"Resources/Circle.png");
	Sprite::LoadTexture(2, L"Resources/white1x1.png");

	sprite = Sprite::CreateSprite(1, playerPos2d2);
	sprite2 = Sprite::CreateSprite(2,playerPos2d);
	sprite->SetSize({ 100, 100 });
	sprite2->SetSize(playerSize2d);

	//audio->SoundPlayWave("Resources/ショット.wav",true);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetEye({ 0, 0, -50 });
	//camera->SetDistance(20.0f);
			//v2.x = v * cos(60 * PI / 180.0);
			//v2.y = v * sin(60 * PI / 180.0);
		
	//vu = v;
	//vBu = vB;
	//srand(time(NULL));
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
//if (input->TriggerKey(DIK_SPACE)) {
//
//	Mflag = true;
//}
//playerEndPos2d2 = { playerPos2d2.x+cosf(XMConvertToRadians(angle))*100,playerPos2d2.y + sinf(XMConvertToRadians(angle))*100 };
//
//circle.center = { playerPos2d.x + 100, playerPos2d.y + 100, 0 };
//circle.radius = 100;
//line.center = { playerPos2d2.x + 100, playerPos2d2.y + 0.5f, 0 };
//line.scale= { 1,150,1 };
//
////if (Mflag == true) {
//	
//	//if (playerPos2d2.x >= 0 && playerPos2d2.x < 1280) {
//		if (input->PushKey(DIK_D)) {
//			playerPos2d2.x += 1;
//		}
//		if (input->PushKey(DIK_A)) {
//			playerPos2d2.x -= 1;
//		}
//	//}
//	//if (playerPos2d2.y >= 0 && playerPos2d2.y <720) {
//		if (input->PushKey(DIK_W)) {
//			playerPos2d2.y -= 1;
//		}
//		if (input->PushKey(DIK_S)) {
//			playerPos2d2.y += 1;
//		}
//	//}
//	if (input->PushKey(DIK_Q)) {
//		angle -=1 ;
//	}
//	if (input->PushKey(DIK_E)) {
//		angle += 1;
//	}
//	if (Collision::CheckSphere2Box(circle, line))
//	{
//		sprite->SetColor({ 1,0,0,1 });
//	}
//	else
//	{
//		sprite->SetColor({ 1,1,1,1 });
//	}
//	
//		
//	
//
//
//		
//		
	
//}

//sprite->SetPosition(playerPos2d);
//sprite2->SetPosition(playerPos2d2);
//sprite2->SetRotation(angle);
#pragma endregion
#pragma region MT4_課題6

	//if (input->TriggerKey(DIK_1)) {
	//	playerPos2d = { 300,300 };
	//	playerSize2d = { 100, 100 };
	//	easeTimer = 0;
	//	EaseFlag = 1;
	//}
	//if (input->TriggerKey(DIK_2)) {
	//	playerPos2d = { 300,300 };
	//	playerSize2d = { 100, 100 };
	//	easeTimer = 0;
	//	EaseFlag = 2;
	//}
	//if (input->TriggerKey(DIK_3)) {
	//	playerPos2d = { 300,300 };
	//	playerSize2d = { 100, 100 };
	//	easeTimer = 0;
	//	EaseFlag = 3;
	//}
	//if (input->TriggerKey(DIK_4)) {
	//	playerPos2d = { 300,300 };
	//	playerSize2d = { 100, 100 };
	//	easeTimer = 0;
	//	EaseFlag = 4;
	//}
	//if (EaseFlag== 1) {
	//	if (easeTimer < 0.2) {
	//		easeTimer += 0.1 / 60;
	//	}
	//	playerPos2d = Eas::easeInQuad(playerPos2d, playerEndPos2d, easeTimer,0.2);
	//}
	//if (EaseFlag == 2) {
	//	if (easeTimer < 0.2) {
	//		easeTimer += 0.1 / 60;
	//	}
	//	playerPos2d = Eas::easeOutQuad(playerPos2d, playerEndPos2d, easeTimer,0.2);
	//}
	//if (EaseFlag == 3) {
	//	if (easeTimer < 0.2) {
	//		easeTimer += 0.1 / 60;
	//	}
	//	playerPos2d = Eas::easeInCubic(playerPos2d, playerEndPos2d, easeTimer,0.2);
	//}
	//if (EaseFlag == 4) {
	//	if (easeTimer < 0.2) {
	//		easeTimer += 0.1 / 60;
	//	}
	//	playerPos2d = Eas::easeOutCubic(playerPos2d, playerEndPos2d, easeTimer,0.2);
	//}
	//if (input->TriggerKey(DIK_R)) {
	//	playerPos2d = { 300,300 };
	//	playerSize2d = { 100, 100 };
	//	easeTimer = 0;
	//	EaseFlag = 0;
	//}
#pragma endregion
#pragma region MT4_課題8
//
circle.center = { playerPos2d2.x+10, playerPos2d2.y+10, 0 };
circle.radius = 100;
ray.start = { input->GetMousePos().x,input->GetMousePos().y,0 };
ray.dir = { 1,0,0,0 };
//sprite->SetParent(sprite);
if (input->PushMouse(0)) {

	if (Collision::CheackRay2Sphere(ray, circle)) {
		playerPos2d2 = { input->GetMousePos().x/*playerPos2d.x*/,input->GetMousePos().y };
	/*	acc.y = gacc;
		acc.y += dist * k / m;
		vel.y += acc.y;
		vel.y -= vel.y * kv;*/
		//playerSize2d.x += vel.x;
		//playerSize2d.y += vel.y;
		playerSize2d.y++;
	}
	if (playerPos2d2.x > 300) {
		playerAngle--;
	}
	
}
else if(!input->PushMouse(0)&&playerPos2d2.y>150) {
	playerPos2d2.y-=2;
	//if (playerPos2d2.x > 300) {
		if (playerAngle < 0) {
			playerAngle++;
		}
	//}
}

XMFLOAT2 V0 = { 0,0 };
//2
XMMATRIX  rotM = XMMatrixIdentity();
rotM *= XMMatrixRotationZ(XMConvertToRadians(playerAngle));
//3
XMVECTOR v2 = { V0.x,V0.y };
XMVECTOR v = XMVector3TransformNormal(v2, rotM);

//4
XMFLOAT2 f3 = { v.m128_f32[0],v.m128_f32[1] };
playerPos2d.x = playerPos2d2.x + f3.x;
playerPos2d.y = playerPos2d2.y + f3.y;

playerSize2d.y = playerPos2d2.y;
#pragma endregion
	// パーティクル生成
	//CreateParticles();
	camera->Update();
	particleMan->Update();
	sprite2->SetSize(playerSize2d);
	sprite->SetPosition(playerPos2d2);
	sprite->SetAnchorPoint({ 0.5,0.5 });
	sprite2->SetRotation(playerAngle);
	object3d->SetPosition(playerPosition);
	//object3d2->SetPosition(playerPositionB);
	object3d2->SetScale({ 2.0f,2.0f,2.0f });
	object3d->Update();
	object3d2->Update();
	
}

void GameScene::Draw()
{	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	Object3d::PreDraw(dxCommon->GetCmdList());
	//object3d->Draw();
	//object3d2->Draw();
	Object3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	sprite2->Draw();
	//char str[256];

//	debugText.Printf(0, 80, 3.0f, "%f",playerPos2d.x);
	debugText.Printf(0, 140, 3.0f, "%f",playerAngle);

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

