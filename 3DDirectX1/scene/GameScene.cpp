#include "GameScene.h"
#include <cassert>
#include<sstream>
#include<iomanip>
#include "FbxLoader.h"
#include "FbxObject.h"
#include"input.h"
#include"DebugText.h"
#include"CollisionManager.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	safe_delete(object3d);
	safe_delete(object3d2);
	safe_delete(object3d3);
	safe_delete(object3d4);
	safe_delete(model);
	safe_delete(model2);
	safe_delete(model3);
	safe_delete(model4);
	safe_delete(sprite);
	safe_delete(particleMan);
	safe_delete(lightGroup);
}

void GameScene::Initialize(DXCommon* dxCommon, Audio* audio)
{
	//u
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	FbxObject3d::SetDev(dxCommon->Getdev());
	//ライト生成
	lightGroup = LightGroup::Create();

	Object3d::SetLight(lightGroup);

	// 3Dオブエクトにライトをセット
	// 
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetDirLightDir(2, XMVECTOR{ 1,0,0,0 });
	//lightGroup->SetPointLightActive(0, true);
	//lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, true);

	FbxObject3d::SetCamera(camera);
	FbxObject3d::CreateGraphicsPipeline(L"Resources/shaders/FBXPS.hlsl", L"Resources/shaders/FBXVS.hlsl");
	colMan = CollisionManager::GetInstance();
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera);

	model3 = Model::Create("skydome", true);
	model4 = Model::Create("ground", false);
	object3d3 = Object3d::Create(model3);
	object3d4 = TouchableObject::Create(model4);
	model = Model::Create("bullet", false);
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("Player");
	object3d = Object3d::Create(model);
	object3d2 = new FbxObject3d();
	object3d2->Initialize();
	object3d2->SetModel(model2);


	//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる
	object3d->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	object3d3->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	object3d4->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

	object3d2->SetRotation({ 0,45,0 });

	//object3d->Update();

	//object3d2->Update();

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(6, L"Resources/UI/TimeUI.png");
	Sprite::LoadTexture(7, L"Resources/UI/TimeUI2.png");
	sprite = Sprite::CreateSprite(1, { 0,0 });
	timeSprite = Sprite::CreateSprite(6, { 1100,100 });
	timeSprite2 = Sprite::CreateSprite(7, { 1100,100 });
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/po.wav");
	sound2 = Audio::SoundLoadWave("Resources/World_Heritage.wav");
	//audio->SoundPlayWave(sound1);
	//audio->SoundPlayWave(sound2);
	//audio->SetBGMVolume(0.5f);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });
	player = new Player;//newすればエラー吐かない
	player->Initialize();
	gameObject = new GameObject;//newすればエラー吐かない
	gameObject->Initialize();
	stageObj = new StageObject;//newすればエラー吐かない
	stageObj->Initialize();
}

void GameScene::Init()
{
	player->Init();
	gameObject->Init();
	stageObj->Init();
	distance = 10.0f;
	for (int i = 0; i < gameObject->GetOBJNumber(); i++) {
		cData.push_back(new CollisionVariable);
	}
	colMan->SetParentFlag(false);
	colMan->SetTsize(0);
	clearFlag = false;
	overFlag = false;
	Bflag = false;
	Tsize = 1;
	Tsize2 = (int)Tsize;
	TCount = 0;
	HitCount = 0;
	TimeRot = 0;
	TimeCount = 0;
	clearTimer = 18000;//1800/60が30秒
	clearTimer2 = 0;
}

void GameScene::Update()
{
	

	//光線方向初期値                  上奥
	//static XMVECTOR lightDir = { 0, 4, 0, 0 };


	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0,0 }));
	lightGroup->SetCircleShadowCasterPos(0, player->GetPlayerPos());
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(0.5f, 0.6f, 0.0f));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(0.0f, 0.5f));

	//当たり判定
	for (int i = 0; i < gameObject->GetOBJNumber(); i++) {
		cData[i]->IsHit = false;

		if (cData[i]->Alive == true) {
			if (gameObject->GetObject(i)->GetParentFlag()==false) {
				if (Collision::CheckSphere2Sphere(player->GetSphere(), gameObject->GetCSphere(i))) {
					//if (Tsize +2>= gameObject->GetObject(i)->GetScale().x) {
					cData[i]->IsHit = true;
					HitCount++;
					cData[i]->Alive = false;
					player->SetColFlag(true, i);
					gameObject->GetObject(i)->SetParentFlag(true);
					//}

					DebugText::GetInstance()->Printf(100, 60, 3.0f, "Hit");
				}
			}
			if (cData[i]->IsHit == true) {
				gameObject->GetObject(i)->SetParent(player->GetObject());
			}
			if (HitCount == 1) {
				gameObject->GetObject(i)->transformParent();
				audio->SEPlayWave(sound1);
				HitCount = 0;
				cData[i]->IsHit = false;
				Tsize++;
			}
		}

	}
	colMan->SetTsize2(Tsize);
	//プレイヤーの大きさ
	
	Tsize2 = (int)colMan->GetTsize();
	if (Tsize2 % 10 == 0) {
		TCount++;
	}
	else {
		TCount = 0;
		Bflag = false;
	}
	if (TCount == 1) {
		distance += 5;
		Bflag = true;;
	}

	timeSprite->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetAnchorPoint({ 0.5,0.5 });
	TimeCount++;
	//TimeUI
	//5分(18000/60)は0.02
	//10分(36000/60)は0.0015
	//25分(90000/60)は0.0006(多分)

	if (Input::GetInstance()->TriggerKey(DIK_R)) {
		clearFlag = true;
		gameObject->RC();
		player->RC();
	}

	if (TimeRot < 360) {
		TimeRot += 0.02f;
	}
	if (clearTimer > 0) {
		clearTimer -= 1.0f;
	}
	else if (clearTimer <= 0) {
		if (Tsize2 < 11) {
			DebugText::GetInstance()->Printf(500, 400, 3.0f, "GameOver");
			overFlag = true;
			gameObject->RC();
			player->RC();
		}
		else if (Tsize2 >= 11) {
			DebugText::GetInstance()->Printf(500, 400, 3.0f, "Clear");
			clearFlag = true;
			gameObject->RC();
			player->RC();
		}
	}

	//else {
	clearTimer2 = (int)(clearTimer / 60.0f);
	//}
	timeSprite2->SetRotation(TimeRot);

	object3d3->SetScale({ 2.0f,2.0f,2.0f });

	//object3d->SetRotation({ a,0,b });
	//TouchableObjectのobjは	playerの前に書かないとエラー起こるよ
	stageObj->Update();

	player->Update();

	camera->FollowCamera(player->GetPlayerPos(), XMFLOAT3{ 0,2,-distance }, 0, player->GetPlayerAngle().y);

	//camera->SetEye(cameraPos);
	//camera->SetTarget(player->GetSpherePos());
	camera->Update();

	gameObject->Update();

	particleMan->Update();
;
	object3d3->Update();

	lightGroup->Update();
	colMan->ColSphere();
	if (colMan->GetAudioFlag() == true) {
		audio->SEPlayWave(sound1);
		colMan->SetAudioFlag(false);
	}
}

void GameScene::DrawBG()
{
	//背景
	Sprite::PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
	colMan->CheckAllCollisions();
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());

	object3d3->Draw();

	//object3d->Draw();
	//object3d2->Draw();
	player->Draw();
	gameObject->Draw();
	stageObj->Draw();

	Object3d::PostDraw();
	FbxObject3d::PostDraw();

}
void GameScene::DrawFront()
{
	//前景
	Sprite::PreDraw(dxCommon->GetCmdList());
	timeSprite->Draw();
	timeSprite2->Draw();
	player->DrawSprite();
	//DebugText::GetInstance()->Printf(100, 20, 3.0f, "%d", player->GetOnGround());
	//DebugText::GetInstance()->Printf(100, 40, 3.0f, "%f", Tsize);
	//DebugText::GetInstance()->Printf(100, 80, 3.0f, "%d", Alive[1]);
	DebugText::GetInstance()->Printf(100, 200, 3.0f, "WASD:MOVE");
	DebugText::GetInstance()->Printf(100, 240, 3.0f, "LRARROW:ANGLE");
	DebugText::GetInstance()->Printf(100, 280, 3.0f, "UPARROW:DASH");
	DebugText::GetInstance()->Printf(100, 320, 3.0f, "SPACE:JUMP");
	DebugText::GetInstance()->Printf(960, 150, 3.0f, "%d", cData.size());
	DebugText::GetInstance()->Printf(960, 50, 3.0f, "%d", clearTimer2);
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
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