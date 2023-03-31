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
	FbxObject3d::CreateGraphicsPipeline(L"Resources/shaders/FBXPS.hlsl", L"Resources/shaders/FBXVS.hlsl");
	Object3d::SetLight(lightGroup);
	FbxObject3d::SetLight(lightGroup);
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



	colMan = CollisionManager::GetInstance();
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera, L"Resources/effect2.png", true);
	//particleMan->LoadTexture();
	//particleMan->CreateModel();
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

}

void GameScene::InitTH()
{

	//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる

	Sprite::LoadTexture(1, L"Resources/background.png");

	sprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(1, { 0,0 }));

	sound1 = Audio::SoundLoadWave("Resources/Music/SE/po.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/BGM/oo39_ys135.wav");
	sound3 = Audio::SoundLoadWave("Resources/Music/SE/door.wav");
	sound4 = Audio::SoundLoadWave("Resources/Music/BGM/追いかけっこキャッハー.wav");
	player = new Player;//newすればエラー吐かない
	player->Initialize();
	gameObjects = new GameObjects;//newすればエラー吐かない
	gameObjects->Initialize();
	stageObj = new StageObject;//newすればエラー吐かない
	stageObj->Initialize();
	timer = new Timer;
	timer->Initialize();
	tutorial = new Tutorial();
	tutorial->Initialize();
	sphereSize = new SphereSize();
	sphereSize->Initialize();
	pose = new Pose;
	pose->Initialize(audio);
	st = new start();
	st->Initialize(audio);
}

void GameScene::Init()
{
	//別クラスの初期化
	player->Init();
	gameObjects->Init();
	stageObj->Init();
	colMan->Init();
	timer->Init();
	pose->Init();
	tutorial->Init();
	st->Init();
	//GameSceneの初期化
	distance = 10.0f;
	distanceC = 10.0f;
	distanceY = 2.0f;
	distanceCY = 4.0f;
	colMan->SetParentFlag(false);
	colMan->SetTsize(0);

	clearFlag = false;
	overFlag = false;
	Bflag = false;
	//ステージが0と1の時は初期サイズ1,2の時は10
	if (stageNum == 1 || stageNum == 0) {
		Tsize = 1;
	}
	else if (stageNum == 2) {
		Tsize = 10;
	}
	Tsize2 = (int)Tsize;
	TCount = 0;
	HitCount = 0;
	TSFlag = false;
	cACount = 0;
	caFlag = false;
	radius = 3.0f;
	SZV = 5;
	SY = 3;
	Ssize = { 0.8f,0.8f,0.8f };
	audioCount = 0;
	OY = 0;

}

void GameScene::InitStageNum(int stageNum)
{
	this->stageNum = stageNum;
	player->stageInit(stageNum);
	gameObjects->stageInit(stageNum);
	stageObj->stageInit(stageNum);
	sphereSize->Init(stageNum);
	if (stageNum == 0) {
		sphereSize->InitStage(0);
	}
	else if (stageNum == 1) {
		GoalCount = 80;
		sphereSize->InitStage(GoalCount);
	}
	else if (stageNum == 2) {
		GoalCount = 700;
		sphereSize->InitStage(GoalCount);
	}
}

void GameScene::Update()
{

	//光線方向初期値                  上奥
	//static XMVECTOR lightDir = { 0, 4, 0, 0 };

	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0,0 }));
	lightGroup->SetCircleShadowCasterPos(0, { player->GetPlayerPos().x,player->GetPlayerPos().y + 1.0f,player->GetPlayerPos().z });
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(0.5f, 0.6f, 0.0f));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(0.0f, 0.5f));

#pragma region	当たり判定
	//チュートリアルで動いてみてよの後ならくっつく
	if (tutorial->GetTCount() != 1) {
		//jはobjの種類数
		//iは種類ごとの数
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < gameObjects->GetOBJCount(j); i++) {
				gameObjects->SetHIT(i, j, false);
				if (gameObjects->GetObject3d(i, j)->GetParentFlag() == false) {
					if (Tsize >= gameObjects->GetOSize(i, j) * 10 || gameObjects->GetOSize(i, j) == 1 || gameObjects->GetOSize(i, j) == 10) {
						gameObjects->GetObject3d(i, j)->SetColFlag(true);
						if (Collision::CheckSphere2Sphere(player->GetSphere(), gameObjects->GetCSphere(i, j))) {
							gameObjects->SetHIT(i, j, true);
							HitCount++;
							gameObjects->GetObject3d(i, j)->SetParentFlag(true);
						}
						//DebugText::GetInstance()->Printf(100, 60, 3.0f, { 1,1,1,1 }, "Hit");
					}
				}
				if (gameObjects->GetHIT(i, j) == true) {
					gameObjects->GetObject3d(i, j)->SetParent(player->GetObject3d());
				}
				if (HitCount == 1) {
					gameObjects->GetObject3d(i, j)->transformParent();
					audio->SEPlayWave(sound1);
					HitCount = 0;
					gameObjects->SetHIT(i, j, false);
					Tsize += gameObjects->GetOSize(i, j);
					if (j != 0) {
						radius += 0.1f;
						SY += 0.1f;
						player->SetSY(SY);
						player->SetRadius(radius);
						OY += 0.1f;
						gameObjects->SetY(OY);
					}

					/*		Ssize.x += 0.001f;
							Ssize.y += 0.001f;
							Ssize.z += 0.001f;
							radius += 0.001f;
							SY += 0.005f;*/
				}
			}
		}
	}
	

	//colMan->ColSphere();
	if (colMan->GetAudioFlag() == true) {
		//音を鳴らしたりなど
		audio->SEPlayWave(sound1);
		colMan->SetAudioFlag(false);
	}
#pragma endregion


#pragma region	サイズ
	//colMan->SetTsize2(Tsize);
	//プレイヤーの大きさ
	sphereSize->SetTsize((int)Tsize);
	//sphereSize->SetTsize(Tsize);
	player->SetRadius(radius);
	player->SetSphereSize(Ssize);
	player->SetSY(SY);
	if (sphereSize->GetTcount() == 1) {
		distance += 1;
		distanceY += 0.5f;
		SZV += 1;
	}
	player->SetSZV(SZV);
#pragma endregion



#pragma region ポーズなど

	pose->Update();

	player->SetPFlag(pose->GetJFlag());
	//ポーズ状態じゃなかったら
	if (pose->GetPFlag() == false) {

		//チュートリアル以外
		if (stageNum != 0) {
			st->Update();
			//開始カウントダウンが終わっている
			if (st->GetStartFlag() == true) {
				if (audioCount < 2) {
					audioCount++;
				}

				timer->SetSFlag(true);
				timer->SetFlag(false);
				//タイマーが0以下になったら
				if (timer->GetDT() <= 0) {
					//目標サイズ未満ゲームオーバー
					if (sphereSize->GetTsize() < GoalCount) {
						//DebugText::GetInstance()->Printf(500, 400, 3.0f, { 1,1,1,1 }, "GameOver");
						overFlag = true;
						audio->StopWave();
						gameObjects->RC();
						player->RC();
						stageObj->RC();
					}
					//目標サイズ以上ゲームクリア
					else if (sphereSize->GetTsize() >= GoalCount) {
						//DebugText::GetInstance()->Printf(500, 400, 3.0f, { 1,1,1,1 }, "Clear");
						clearFlag = true;
						audio->StopWave();
						gameObjects->RC();
						player->RC();
						stageObj->RC();
					}
				}
				player->SetWalkFlag(true);
			}
			else {
				//タイマー止める、移動等止める
				timer->SetFlag(true);
				timer->SetSFlag(false);
				player->SetWalkFlag(false);
			}
		}
		//プレイヤー、ステージ、オブジェクト、タイマーのアップデート
		player->Update();
		stageObj->Update();
		gameObjects->Update();
		timer->Update();
		//CreateParticles();
		particleMan->Update();
	}

	if (audioCount == 1) {
		if (stageNum == 0 || stageNum == 1) {
			audio->SoundPlayWave(sound2);
		}
		else if (stageNum == 2) {
			audio->SoundPlayWave(sound4);
		}
		audio->SetBGMVolume(0.2f);
	}
	//ポーズ画面でタイトルに戻るときの処理
	if (pose->GetTFlag() == true) {
		//audio->StopWave();
		//コライダーを削除
		gameObjects->RC();
		player->RC();
		stageObj->RC();
	}
	sphereSize->Update();
#pragma endregion
#if _DEBUG 
	//デバッグでクリアとゲームオーバー見るために作ったやつ
	if (Input::GetInstance()->TriggerKey(DIK_Q)) {
		overFlag = true;
		audio->StopWave();
		gameObjects->RC();
		player->RC();
		stageObj->RC();
	}
	else if (Input::GetInstance()->TriggerKey(DIK_E)) {
		clearFlag = true;
		audio->StopWave();
		gameObjects->RC();
		player->RC();
		stageObj->RC();
	}
#endif

	//object3d->SetRotation({ a,0,b });
	//TouchableObjectのobjは	playerの前に書かないとエラー起こるよ

#pragma region チュートリアル
	//チュートリアルの時
	if (stageNum == 0) {
		if (audioCount < 2) {
			audioCount++;
		}
		//1になったら
		if (tutorial->GetTCount() == 1) {
			//プレイヤーのZ座標位置が0以上になったら
			if (player->GetTWCount() == 100) {
				//2にする
				tutorial->SetTCount(2);
			}
			tutorial->SetCountFlag(true);
		}
		//3になったら
		else if (tutorial->GetTCount() == 3) {
			//くっつけるようになる
			if (gameObjects->GetObject3d(0, 0)->GetParentFlag() == true) {
				//4にする
				tutorial->SetTCount(4);
			}
			tutorial->SetCountFlag(true);
		}
		else {
			//TutorialCountが1と3以外は説明文を勝手に進められる。
			tutorial->SetCountFlag(false);
		}
		//チュートリアルが終わったら
		if (tutorial->GetEndFlag() == true) {
			//コライダー削除する
			TSFlag = true;
			audio->StopWave();
			gameObjects->RC();
			player->RC();
			stageObj->RC();
		}
		//MoveFlag(動けるか否か)がtrueならば
		if (tutorial->GetMoveFlag() == true) {
			//プレイヤー動ける
			player->SetWalkFlag(true);
		}
		//falseならば
		else if (tutorial->GetMoveFlag() == false) {
			//プレイヤー動けない
			player->SetWalkFlag(false);
		}
		tutorial->Update();
	}
#pragma endregion

#pragma region カメラ
	//追従カメラ
	camera->FollowCamera({ player->GetPlayerPos().x,player->GetPlayerPos().y + distanceY,player->GetPlayerPos().z }
	, XMFLOAT3{ 0,distanceCY,-distanceC }, 0, player->GetPlayerAngle().y);
	//カメラのめり込み(一部うまくいかない部分あり)
	camera->CameraCollision(player->GetPlayerPos(), player->GetPlayerAngle());
	if (camera->GetCCFlag() == true) {
		//if (camera->GetDistance() <=8) {
		distanceC = camera->GetDistance();
		distanceCY = 0;
		//}
	}
	else if (camera->GetCCFlag() == false) {
		distanceCY = 4;
		distanceC = distance;
	}
	camera->Update();
#pragma endregion
	lightGroup->Update();

}


void GameScene::DrawBG()
{
	//背景
	Sprite::PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());
	player->Draw();
	gameObjects->Draw();
	stageObj->Draw();
	Object3d::PostDraw();
	FbxObject3d::PostDraw();
	particleMan->Draw(dxCommon->GetCmdList());

}
void GameScene::DrawFront()
{
	//前景
	Sprite::PreDraw(dxCommon->GetCmdList());
	//player->DrawSprite();
	if (stageNum == 0) {
		tutorial->Draw();
	}
	else if (stageNum != 0) {
		st->Draw(stageNum);
	}
	timer->Draw();
	if (pose->GetPFlag() == true) {
		pose->Draw();
	}
sphereSize->Draw();

	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}
void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.5f;
		XMFLOAT3 pos = player->GetPlayerPos();
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 0.3f, 0.0f, { 1,1,1 }, { 1,1,1 });
	}
}

bool GameScene::GetTitleFlag()
{
	return pose->GetTFlag();
}
