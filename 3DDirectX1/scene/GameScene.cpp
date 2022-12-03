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

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(debugTextTexNumber);


	//audio->SoundPlayWave(sound1);
	//audio->SoundPlayWave(sound2);
	//audio->SetBGMVolume(0.5f);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });
	pose = new Pose;
	pose->Initialize(audio);
}

void GameScene::InitTH()
{

	//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる

	Sprite::LoadTexture(1, L"Resources/background.png");

	Sprite::LoadTexture(25, L"Resources/UI/number/Number.png");
	Sprite::LoadTexture(26, L"Resources/UI/number/m.png");
	Sprite::LoadTexture(27, L"Resources/UI/number/cm.png");
	sprite = Sprite::CreateSprite(1, { 0,0 });


	for (int i = 0; i < 4; i++) {
		Number[i] = Sprite::CreateSprite(25, { 0,0 });
	}
	Meters = Sprite::CreateSprite(26, { 0,0 });
	Centimeter = Sprite::CreateSprite(27, { 0,0 });
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/po.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/BGM/oo39_ys135.wav");
	player = new Player;//newすればエラー吐かない
	player->Initialize();
	gameObject = new GameObject;//newすればエラー吐かない
	gameObject->Initialize();
	stageObj = new StageObject;//newすればエラー吐かない
	stageObj->Initialize();
	timer = new Timer;
	timer->Initialize();
	tutorial = new Tutorial();
	tutorial->Initialize();

}

void GameScene::Init()
{
	player->Init();

	gameObject->Init();

	stageObj->Init();
	timer->Init();
	pose->Init();
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
	TSFlag = false;


	audio->SoundPlayWave(sound2);
	audio->SetBGMVolume(0.2f);

}

void GameScene::InitStageNum(int stageNum)
{
	this->stageNum = stageNum;
	gameObject->stageInit(stageNum);
	stageObj->stageInit(stageNum);
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
	if (tutorial->GetTCount() != 1) {
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < gameObject->GetOBJCount(j); i++) {

				gameObject->SetHIT(i, j, false);
				if (gameObject->GetObject3d(i, j)->GetParentFlag() == false) {
					if (Collision::CheckSphere2Sphere(player->GetSphere(), gameObject->GetCSphere(i, j))) {

						if (colMan->GetTsize() >= gameObject->GetOSize(i, j) * 10 || gameObject->GetOSize(i, j) == 1) {
							gameObject->SetHIT(i, j, true);
							HitCount++;
							gameObject->GetObject3d(i, j)->SetParentFlag(true);
						}

						DebugText::GetInstance()->Printf(100, 60, 3.0f, { 1,1,1,1 }, "Hit");
					}
				}
				if (gameObject->GetHIT(i, j) == true) {
					gameObject->GetObject3d(i, j)->SetParent(player->GetObject3d());
				}
				if (HitCount == 1) {
					gameObject->GetObject3d(i, j)->transformParent();
					audio->SEPlayWave(sound1);
					HitCount = 0;
					gameObject->SetHIT(i, j, false);
					Tsize += gameObject->GetOSize(i, j);
				}
			}
		}
	}
#pragma endregion
	//DebugText::GetInstance()->Printf(100, 500, 3.0f, "%d", gameObject->GetObject3d(0,0)->GetParentFlag());

#pragma region	サイズ
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
#pragma endregion
#pragma region ポーズなど

	pose->Update();

	player->SetPFlag(pose->GetJFlag());

	if (pose->GetPFlag() == false) {
		//player->SetPFlag(false);
		if (stageNum != 0) {
			timer->Update();
			if (timer->GetDT() <= 0) {
				if (Tsize2 < 30) {
					DebugText::GetInstance()->Printf(500, 400, 3.0f, { 1,1,1,1 }, "GameOver");
					overFlag = true;
					audio->StopWave();
					gameObject->RC();
					player->RC();
					stageObj->RC();
				}
				else if (Tsize2 >= 30) {
					DebugText::GetInstance()->Printf(500, 400, 3.0f, { 1,1,1,1 }, "Clear");
					clearFlag = true;
					audio->StopWave();
					gameObject->RC();
					player->RC();
					stageObj->RC();
				}
			}
		}
		stageObj->Update();
		player->Update();
		gameObject->Update();
	}
	if (pose->GetTFlag() == true) {
		//audio->StopWave();
		gameObject->RC();
		player->RC();
		stageObj->RC();
	}
#pragma endregion
#if _DEBUG 
	//デバッグでクリアとゲームオーバー見るために作ったやつ
	if (Input::GetInstance()->TriggerKey(DIK_Q)) {
		overFlag = true;
		audio->StopWave();
		gameObject->RC();
		player->RC();
		stageObj->RC();
	}
	else if (Input::GetInstance()->TriggerKey(DIK_E)) {
		clearFlag = true;
		audio->StopWave();
		gameObject->RC();
		player->RC();
		stageObj->RC();
	}
#endif

	//object3d->SetRotation({ a,0,b });
	//TouchableObjectのobjは	playerの前に書かないとエラー起こるよ

#pragma region チュートリアル
	if (stageNum == 0) {
		if (tutorial->GetTCount() == 1) {
			if (player->GetPlayerPos().z >= 0) {
				tutorial->SetTCount(2);
			
			}
			tutorial->SetCountFlag(true);
		}
		else if (tutorial->GetTCount() == 3) {
			if (gameObject->GetObject3d(0, 0)->GetParentFlag() == true) {
				tutorial->SetTCount(4);
			}
			tutorial->SetCountFlag(true);
		}
		else {
			tutorial->SetCountFlag(false);
		}
		if (tutorial->GetEndFlag() == true) {
			TSFlag = true;
			audio->StopWave();
			gameObject->RC();
			player->RC();
			stageObj->RC();
		}
		if (tutorial->GetMoveFlag() == true) {
			player->SetWalkFlag(true);
		}
		else if (tutorial->GetMoveFlag() == false) {
			player->SetWalkFlag(false);
		}
		tutorial->Update();
	}
#pragma endregion

	camera->FollowCamera(player->GetPlayerPos(), XMFLOAT3{ 0,2,-distance }, 0, player->GetPlayerAngle().y);
	camera->Update();
	particleMan->Update();
	lightGroup->Update();
	//colMan->ColSphere();
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
	if (stageNum == 0) {
		tutorial->Draw();
	}
	timer->Draw();
	if (pose->GetPFlag() == true) {
		pose->Draw();
	}
	//DebugText::GetInstance()->Printf(100, 20, 3.0f, "%d", player->GetOnGround());
	//DebugText::GetInstance()->Printf(100, 40, 3.0f, "%f", Tsize);
	//DebugText::GetInstance()->Printf(100, 80, 3.0f, "%d", Alive[1]);
	//DebugText::GetInstance()->Printf(100, 200, 3.0f, { 1,1,1,1 }, "WASD:MOVE");
	//DebugText::GetInstance()->Printf(100, 240, 3.0f, { 1,1,1,1 }, "LRARROW:ANGLE");
	//DebugText::GetInstance()->Printf(100, 280, 3.0f, { 1,1,1,1 }, "UPARROW:DASH");
	//DebugText::GetInstance()->Printf(100, 320, 3.0f, { 1,1,1,1 }, "SPACE:JUMP");
	//DebugText::GetInstance()->Printf(100, 360, 3.0f, { 1,1,1,1 }, "R:POSE");
	/*DebugText::GetInstance()->Printf(460, 150, 3.0f,{1,1,1,1}, "%f,%f,%f",
	gameObject->GetObject3d(0,0)->GetRotation().m128_f32[0], gameObject->GetObject3d(0, 0)->GetRotation().m128_f32[1], gameObject->GetObject3d(0, 0)->GetRotation().m128_f32[2]);
	*/
	DebugText::GetInstance()->Printf(460, 150, 3.0f, { 1,1,1,1 }, "%f,%f,%f",
		player->GetObject3d()->GetRotation().m128_f32[0], player->GetObject3d()->GetRotation().m128_f32[1], player->GetObject3d()->GetRotation().m128_f32[2]);

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

bool GameScene::GetTitleFlag()
{
	return pose->GetTFlag();
}
