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
#include<time.h>
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
	FbxObject3d::SetCamera(camera);
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
	Sprite::LoadTexture(20, L"Resources/UI/Pose.png");
	Sprite::LoadTexture(21, L"Resources/UI/TitleBack.png");
	Sprite::LoadTexture(22, L"Resources/UI/Back.png");
	Sprite::LoadTexture(23, L"Resources/UI/Info.png");
	Sprite::LoadTexture(24, L"Resources/UI/PoseBack.png");
	Sprite::LoadTexture(25, L"Resources/UI/number/Number.png");
	Sprite::LoadTexture(26, L"Resources/UI/number/m.png");
	Sprite::LoadTexture(27, L"Resources/UI/number/cm.png");
	Sprite::LoadTexture(28, L"Resources/UI/TimeUI_2.png");
	sprite = Sprite::CreateSprite(1, { 0,0 });
	timeSprite = Sprite::CreateSprite(6, { 1100,100 });
	timeSprite2 = Sprite::CreateSprite(7, { 1100,100 });
	timeSprite3 = Sprite::CreateSprite(28, { 1100,100 });
	PoseSprite = Sprite::CreateSprite(20, { 0,0 });
	TitleBackSprite = Sprite::CreateSprite(21, { 0,0 });
	BackSprite = Sprite::CreateSprite(22, { 0,0 });
	InfoSprite = Sprite::CreateSprite(23, { 0,0 });
	PBSprite = Sprite::CreateSprite(24, { 0,0 });
	for (int i = 0; i < 4; i++) {
		Number[i] = Sprite::CreateSprite(25, { 0,0 });
	}
	Meters = Sprite::CreateSprite(26, { 0,0 });
	Centimeter = Sprite::CreateSprite(27, { 0,0 });
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/po.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/BGM/oo39_ys135.wav");
	sound3 = Audio::SoundLoadWave("Resources/Music/SE/決定ボタンを押す26.wav");
	sound4 = Audio::SoundLoadWave("Resources/Music/SE/cursor.wav");
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
	start = (double)time(NULL);

	PoseFlag = false;//ゲーム中断フラグ
	TitleFlag = false;//タイトルに戻るフラグ
	PS = 0;
	audio->SoundPlayWave(sound2);
	audio->SetBGMVolume(0.2f);
	total = 0.0;
	SetTime = 180;
	start = clock() / CLOCKS_PER_SEC;
	dt = SetTime;
	TR = (float)dt;
}

void GameScene::Update()
{


	//光線方向初期値                  上奥
	//static XMVECTOR lightDir = { 0, 4, 0, 0 };


	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0,0 }));
	lightGroup->SetCircleShadowCasterPos(0, player->GetPlayerPos());
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(0.5f, 0.6f, 0.0f));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(0.0f, 0.5f));

#pragma region	当たり判定
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < gameObject->GetOBJCount(j); i++) {

			gameObject->SetHIT(i, j, false);
			if (gameObject->GetObject3d(i, j)->GetParentFlag() == false) {
				if (Collision::CheckSphere2Sphere(player->GetSphere(), gameObject->GetCSphere(i, j))) {
					//if (Tsize >= gameObject->GetObject(i)->GetScale().x) {
					gameObject->SetHIT(i, j, true);
					HitCount++;
					//player->SetColFlag(true, i);
					gameObject->GetObject3d(i, j)->SetParentFlag(true);
					//}
					DebugText::GetInstance()->Printf(100, 60, 3.0f,{1,1,1,1}, "Hit");
				}
			}
			if (gameObject->GetHIT(i, j) == true) {
				gameObject->GetObject3d(i, j)->SetParent(player->GetObject());
			}
			if (HitCount == 1) {
				gameObject->GetObject3d(i, j)->transformParent();
				audio->SEPlayWave(sound1);
				HitCount = 0;
				gameObject->SetHIT(i, j, false);
				Tsize += gameObject->GetOSize(i, j);
			}




			if (gameObject->GetObject3d(i, j)->GetParentFlag() == true)
			{
				player->SetColFlag(false, i);

			}
			else if (gameObject->GetObject3d(i, j)->GetParentFlag() == false)
			{
				player->SetColFlag(true, i);
			}
		}
	}
#pragma endregion
	//DebugText::GetInstance()->Printf(100, 500, 3.0f, "%d", gameObject->GetObject3d(0,0)->GetParentFlag());


	colMan->SetTsize2(Tsize);

	//プレイヤーの大きさ
	DebugText::GetInstance()->Printf(100, 40, 3.0f, { 1,1,1,1 }, "%dcm", (int)colMan->GetTsize());

	Tsize2 = (int)colMan->GetTsize();
	if (Tsize2 % 10 == 0) {
		TCount++;
	}
	else {
		TCount = 0;
		Bflag = false;
	}
	if (TCount == 1) {
		distance += 2;
		Bflag = true;;
	}

	timeSprite->SetAnchorPoint({ 0.5,0.5 });
	timeSprite2->SetAnchorPoint({ 0.5,0.5 });
	timeSprite3->SetAnchorPoint({ 0.5,0.5 });
	//TimeUI
	//3分
	//5分(18000/60)は0.02
	//10分(36000/60)は0.0015
	//25分(90000/60)は0.0006(多分)
	//tn,ut,ci,shp,kn,em,zm,syo,rb,gr,os

#pragma region ポーズなど
	if (PoseFlag == false) {
		if (Input::GetInstance()->TriggerKey(DIK_R)) {
			PoseFlag = true;
			audio->SEPlayWave(sound3);
		}
	}
	if (PoseFlag == true) {
		if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW)) {
			PS = 1;
			audio->SEPlayWave(sound4);
		}
		else if (Input::GetInstance()->TriggerKey(DIK_UPARROW)) {
			PS = 0;
			audio->SEPlayWave(sound4);
		}

		if (PS == 0) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				PoseFlag = false;
				audio->SEPlayWave(sound3);
			}
			BackSprite->SetSize({ 500,110 });
			TitleBackSprite->SetSize({ 350,55 });
			BackSprite->SetPosition({ 400,500 });
			TitleBackSprite->SetPosition({ 500,600 });
		}
		else if (PS == 1) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				TitleFlag = true;
				audio->StopWave();
				gameObject->RC();
				player->RC();
				audio->SEPlayWave(sound3);
			}
			BackSprite->SetSize({ 250,55 });
			TitleBackSprite->SetSize({ 500,110 });
			BackSprite->SetPosition({ 500,550 });
			TitleBackSprite->SetPosition({ 400,600 });
		}
	}


	else if (PoseFlag == false) {
		if (dt > 60) {
			TR = (float)dt;
		}
		else if (dt == 60) {
			TimeRot = 180;
		}
		else if (dt <= 60) {
			TR = (float)dt * 3;
		}
		TimeRot = TR * 2;
		if (dt > 0) {
			end = clock() / CLOCKS_PER_SEC;
			total = end - start;
			dt = SetTime - total;

		}
		else if (dt <= 0) {
			if (Tsize2 < 30) {
				DebugText::GetInstance()->Printf(500, 400, 3.0f, { 1,1,1,1 }, "GameOver");
				overFlag = true;
				audio->StopWave();
				gameObject->RC();
				player->RC();
			}
			else if (Tsize2 >= 30) {
				DebugText::GetInstance()->Printf(500, 400, 3.0f, { 1,1,1,1 }, "Clear");
				clearFlag = true;
				audio->StopWave();
				gameObject->RC();
				player->RC();
			}
		}
		stageObj->Update();
		player->Update();
		gameObject->Update();
	}
#pragma endregion
#if _DEBUG 
	//デバッグでクリアとゲームオーバー見るために作ったやつ
	if (Input::GetInstance()->TriggerKey(DIK_Q)) {
		overFlag = true;
		audio->StopWave();
		gameObject->RC();
		player->RC();
	}
	else if (Input::GetInstance()->TriggerKey(DIK_E)) {
		clearFlag = true;
		audio->StopWave();
		gameObject->RC();
		player->RC();
	}
#endif


	timeSprite2->SetRotation(-TimeRot);

	object3d3->SetScale({ 4.0f,4.0f,4.0f });

	//object3d->SetRotation({ a,0,b });
	//TouchableObjectのobjは	playerの前に書かないとエラー起こるよ

	if (TitleFlag == true) {
		gameObject->RC();
		player->RC();
	}
	camera->FollowCamera(player->GetPlayerPos(), XMFLOAT3{ 0,2,-distance }, 0, player->GetPlayerAngle().y);
	camera->Update();


	particleMan->Update();
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
	player->DrawSprite();
	if (PoseFlag == true) {
		PBSprite->Draw();
		PoseSprite->Draw();
		TitleBackSprite->Draw();
		BackSprite->Draw();
		InfoSprite->Draw();
	}
	//DebugText::GetInstance()->Printf(100, 20, 3.0f, "%d", player->GetOnGround());
	//DebugText::GetInstance()->Printf(100, 40, 3.0f, "%f", Tsize);
	//DebugText::GetInstance()->Printf(100, 80, 3.0f, "%d", Alive[1]);
	DebugText::GetInstance()->Printf(100, 200, 3.0f, { 1,1,1,1 }, "WASD:MOVE");
	DebugText::GetInstance()->Printf(100, 240, 3.0f, { 1,1,1,1 }, "LRARROW:ANGLE");
	DebugText::GetInstance()->Printf(100, 280, 3.0f, { 1,1,1,1 }, "UPARROW:DASH");
	DebugText::GetInstance()->Printf(100, 320, 3.0f, { 1,1,1,1 }, "SPACE:JUMP");

	//DebugText::GetInstance()->Printf(460, 150, 3.0f, "%f,%f,%f",
		//player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z );

	if (((int)dt / 60 == 0)) {
		timeSprite3->Draw();
		DebugText::GetInstance()->Printf(960, 50, 3.0f, { 1.0f,0.5f,0,1 }, "%d", (int)dt);
	}
	else
	{
		timeSprite->Draw();
		DebugText::GetInstance()->Printf(960, 50, 3.0f, { 1,1,1,1 }, "%d", (int)(dt / 60) + 1);
	}
	timeSprite2->Draw();
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