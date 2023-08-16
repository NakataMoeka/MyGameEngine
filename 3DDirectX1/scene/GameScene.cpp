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
#include"SceneManager.h"
#include"ClearScene.h"
#include"TitleScene.h"
#include"SelectScene.h"
GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	// カメラ生成
	camera = std::unique_ptr < Camera>(new Camera(WinApp::window_width, WinApp::window_height));

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());
	FbxObject3d::SetCamera(camera.get());

	//ライト生成
	lightGroup = std::unique_ptr <LightGroup>(LightGroup::Create());

	Object3d::SetLight(lightGroup.get());
	FbxObject3d::SetLight(lightGroup.get());
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
	//particleMan = std::unique_ptr < ParticleManager>(ParticleManager::Create(dxCommon->Getdev(), camera.get(), L"Resources/effect2.png", true));
	//particleMan->LoadTexture();
	//particleMan->CreateModel();

	// カメラ注視点をセット
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });
	InitTH();
}

void GameScene::InitTH()
{
	Sprite::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(2, L"Resources/background.png");
	sprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(1, { 0,0 }));
	tmSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(2, { 0,0 }));
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/po.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/BGM/oo39_ys135.wav");
	sound3 = Audio::SoundLoadWave("Resources/Music/SE/door.wav");
	sound4 = Audio::SoundLoadWave("Resources/Music/BGM/追いかけっこキャッハー.wav");
	player = std::unique_ptr <Player>(new Player());//newすればエラー吐かない
	player->Initialize();
	gameObjects = std::unique_ptr <GameObjects>(new GameObjects());//newすればエラー吐かない
	gameObjects->Initialize();
	for (int i = 0; i < 9; i++) {
		stageObj[i] = std::unique_ptr <StageObject>(new StageObject());//newすればエラー吐かない	
	}
	SOCreate();
	modelSkydome = std::unique_ptr<Model>(Model::Create("skydome", true));
	skydome = std::unique_ptr < Object3d>(Object3d::Create(modelSkydome.get()));
	skydome->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	timer = std::unique_ptr <Timer>(new Timer());
	timer->Initialize();
	tutorial = std::unique_ptr <Tutorial>(new Tutorial());
	tutorial->Initialize();
	sphereSize = std::unique_ptr <SphereSize>(new SphereSize());
	sphereSize->Initialize();
	pose = std::unique_ptr <Pose>(new Pose());
	pose->Initialize();
	st = std::unique_ptr < start>(new start());
	st->Initialize();
}

void GameScene::Init()
{
	stageNum = nextStage;
	//別クラスの初期化
	player->Init();
	gameObjects->Init();
	colMan->Init();
	timer->Init();
	pose->Init();
	tutorial->Init();
	st->Init();
	SOInit();
	skydome->SetPosition({ 0.0f,100.0f,0.0f });
	skydome->SetScale({ 4.0f,4.0f,4.0f });
	skydome->SetColor({ 1,1,1,1 });
	skydome->Update();
	//GameSceneの初期化
	distance = { 0,2.0f,10.0f };
	distanceC = { 0, 4.0f, -10.0f };
	distanceNum = { 0,0,0 };
	colMan->SetParentFlag(false);
	colMan->SetTsize(0);
	endFlag = false;
	endNum = 0;
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
	radius = 2.0f;
	SZV = 5;
	SY = 2;
	Ssize = { 0.8f,0.8f,0.8f };
	audioCount = 0;
	OY = 0;
	srand((unsigned)time(NULL));
	InitStageNum();
}

void GameScene::InitStageNum()
{
	player->stageInit(stageNum);
	gameObjects->stageInit(stageNum);
	sphereSize->Init(stageNum);
	if (stageNum == 0) {
		sphereSize->InitStage(0);
	}
	else if (stageNum == 1) {
		GoalCount = 120;
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
	//深いネストの改善
	if (st->GetStartFlag() == true) {
		if (tutorial->GetTCount() != 1) {
			for (int j = 0; j < 5; j++) {
				for (int i = 0; i < gameObjects->GetOBJCount(j); i++) {
					ObjCollision(i, j);
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
	if (colMan->GetHit() == true) {
		//CreateParticles();
		if (HitCC < 3) {
			HitCC++;
		}
	}
	else {
		HitCC = 0;
	}
	if (HitCC == 1) {
		audio->SEPlayWave(sound3);
	}
	//DebugText::GetInstance()->Printf(100, 60, 3.0f, { 1,1,1,1 }, "%d",HitCC);
#pragma endregion

#pragma region	サイズ
	//colMan->SetTsize2(Tsize);
	//プレイヤーの大きさ
	sphereSize->SetTsize((int)Tsize);
	//sphereSize->SetTsize(Tsize);
	player->SetRadius(radius);
	player->SetSphereSize(Ssize);
	player->SetSY(SY);
	//gameObjects->SetY(OY);
	if (sphereSize->GetTcount() > 0 && sphereSize->GetTcount() < 4) {
		//くっつくオブジェクトが増えたらカメラの距離を変える
		if (distanceNum.z < 0.5f) {
			distanceNum.z += 0.1f;
		}
		if (distanceNum.y < 0.2f) {
			distanceNum.y += 0.1f;
		}
		distance.z += distanceNum.z;
		distance.y += distanceNum.y;
		SZV += 0.2f;
	}
	else {
		distanceNum = { 0,0,0 };
	}
	player->SetSZV(SZV);
#pragma endregion

#pragma region ポーズなど

	pose->Update();

	player->SetPFlag(pose->GetJFlag());
	//----------要改善----------
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
						endFlag = true;
						endNum = 0;
						BaseScene* scene = new ClearScene();
						scene->nextStage = 0;
						sceneManager_->SetNextScene(scene);
						audio->StopWave();
						gameObjects->RC();
						player->RC();
						for (int i = 0; i < 9; i++) {
							stageObj[i]->RC();
						}
					}
					//目標サイズ以上ゲームクリア
					else if (sphereSize->GetTsize() >= GoalCount) {
						BaseScene* scene = new ClearScene();
						scene->nextStage = 0;
						sceneManager_->SetNextScene(scene);
						endFlag = true;
						endNum = 1;
						audio->StopWave();
						gameObjects->RC();
						player->RC();
						for (int i = 0; i < 9; i++) {
							stageObj[i]->RC();
						}

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
		for (int i = 0; i < 9; i++) {
			stageObj[i]->Update();
		}
		gameObjects->Update();
		timer->Update();
		skydome->Update();
		//particleMan->Update();
	}

	if (audioCount == 1) {
		if (stageNum == 0 || stageNum == 1) {
			audio->SoundPlayWave(sound2);
		}
		else if (stageNum == 2) {
			audio->SoundPlayWave(sound4);
		}
		audio->SetBGMVolume(0.4f);
	}
	//ポーズ画面でタイトルに戻るときの処理
	if (pose->GetTFlag() == true) {
		BaseScene* scene = new TitleScene();
		sceneManager_->SetNextScene(scene);
		//audio->StopWave();
		//コライダーを削除
		gameObjects->RC();
		player->RC();
		for (int i = 0; i < 9; i++) {
			stageObj[i]->RC();
		}

	}
	if (Input::GetInstance()->TriggerKey(DIK_C)) {
		BaseScene* scene = new ClearScene();
		sceneManager_->SetNextScene(scene);
		scene->nextStage = 1;
		audio->StopWave();
		//コライダーを削除
		gameObjects->RC();
		player->RC();
		for (int i = 0; i < 9; i++) {
			stageObj[i]->RC();
		}
	}
	if (Input::GetInstance()->TriggerKey(DIK_E)) {
		BaseScene* scene = new ClearScene();
		sceneManager_->SetNextScene(scene);
		scene->nextStage = 0;
		audio->StopWave();
		//コライダーを削除
		gameObjects->RC();
		player->RC();
		for (int i = 0; i < 9; i++) {
			stageObj[i]->RC();
		}
	}
	sphereSize->Update();

#pragma endregion

#pragma region チュートリアル
	//チュートリアルの時
	if (stageNum == 0) {
		//歩いた距離をplayerクラスからチュートリアルに送る
		tutorial->SetWalkCount(player->GetTWCount());
		if (tutorial->GetColFlag() == true) {
			//くっつけるようになる
			if (gameObjects->GetObject3d(0, 0)->GetParentFlag() == true) {
				//テキスト画像をを4番目にする
				tutorial->SetTCount(4);
				tutorial->SetColFlag(false);
			}
		}
		//チュートリアルが終わったら
		if (tutorial->GetEndFlag() == true) {
			//コライダー削除する
			//セレクトシーンに戻る
			TSFlag = true;
			BaseScene* scene = new SelectScene();
			sceneManager_->SetNextScene(scene);
			audio->StopWave();
			gameObjects->RC();
			player->RC();
			for (int i = 0; i < 9; i++) {
				stageObj[i]->RC();
			}
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
	camera->FollowCamera({ player->GetPlayerPos().x,player->GetPlayerPos().y + distance.y,player->GetPlayerPos().z }
	, XMFLOAT3{ distanceC.x,distanceC.y,-distanceC.z }, 0, player->GetPlayerAngle().y);
	//カメラのめり込み対策(一部うまくいかない部分あり)
	camera->CameraCollision(player->GetPlayerPos(), player->GetPlayerAngle());
	if (camera->GetCCFlag() == true) {
		//if (camera->GetDistance() <=8) {
		distanceC.z = camera->GetDistance();
		distanceC.y = 0;
		//}
	}
	else if (camera->GetCCFlag() == false) {
		distanceC.y = 4;
		distanceC.z = distance.z;
	}
	camera->Update();
#pragma endregion
	lightGroup->Update();
}
void GameScene::DrawBG()
{
	//背景
	sprite->Draw();
}
void GameScene::Draw()
{
	//オブジェクトの描画
	player->Draw();
	gameObjects->Draw();
	stageObj[0]->Draw();
	if (stageNum == 1) {
		for (int i = 1; i < 6; i++) {
			stageObj[i]->Draw();
		}
	}
	else if (stageNum == 2) {
		for (int i = 6; i < 9; i++) {
			stageObj[i]->Draw();
		}
	}
	skydome->Draw();
}
void GameScene::DrawFront()
{
	//前景
	player->DrawSprite();
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
}
void GameScene::Finalize()
{
}
void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.005f;
		XMFLOAT3 pos = player->GetSpherePos();
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += ((float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f) + 4;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.0001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 2.0f, 0.0f, { 1,0.5,0 }, { 1,1,1 });
	}
}

bool GameScene::GetSCangeFlag()
{
	return false;
}

bool GameScene::GetTitleFlag()
{
	return pose->GetTFlag();
}

void GameScene::ObjCollision(int i, int j)
{
	//jはobjの種類数
	//iは種類ごとの数
	gameObjects->SetHIT(i, j, false);
	if (gameObjects->GetObject3d(i, j)->GetParentFlag() == false &&
		(Tsize >= gameObjects->GetOSize(i, j) * 10 ||
			gameObjects->GetOSize(i, j) == 1 ||
			gameObjects->GetOSize(i, j) == 10)) {
		gameObjects->GetObject3d(i, j)->SetColFlag(true);
		//当たり判定
		if (Collision::CheckSphere2Sphere(player->GetSphere(), gameObjects->GetCSphere(i, j))) {
			//HITフラグtrueにする
			gameObjects->SetHIT(i, j, true);
			HitCount++;
			gameObjects->GetObject3d(i, j)->SetParentFlag(true);
		}
	}
	if (gameObjects->GetHIT(i, j) == true) {
		//当たったら親子関係結ぶ
		gameObjects->GetObject3d(i, j)->SetParent(player->GetObject3d().get());
	}
	if (HitCount == 1) {
		//当たった時一瞬する処理
		gameObjects->GetObject3d(i, j)->transformParent();
		//くっついた時のぽこって音
		audio->SEPlayWave(sound1);
		HitCount = 0;
		//HITフラグfalseにする
		gameObjects->SetHIT(i, j, false);
		//オブジェクトのサイズを球のサイズに加算
		Tsize += gameObjects->GetOSize(i, j);
		if (j != 0) {
			//0のオブジェクト以外がくっついたときに半径など少し大きくする
			radius += 0.1f;
			SY += 0.1f;
			OY += 0.1f;
		}
	}
}

void GameScene::SOInit()
{
	//ステージにある飾りオブジェクト等の位置設定
	stageObj[0]->Init({ 0,0,0 }, { 6,6,6 }, { 0,0,0,0 });
	if (stageNum == 1) {
		stageObj[1]->Init({ 0,38,-80 }, { 1,1,1 }, { 0,0,0,0 });
		stageObj[2]->Init({ -20,28,-170 }, { 2,2,2 }, { 0,90,0,0 });
		stageObj[3]->Init({ 20,46,126 }, { 4,4,4 }, { 0,90,0,0 });
		stageObj[4]->Init({ 0,0,0 }, { 1,1,1 }, { 0,0,0,0 });
		stageObj[5]->Init({ -190,58,-47.5f }, { 2,2,2 }, { 0,0,0,0 });
	}
	else if (stageNum == 2) {
		stageObj[6]->Init({ 0,0,0 }, { 5,5,5 }, { 0,0,0,0 });
		stageObj[7]->Init({ -30,0,0 }, { 1,1,1 }, { 0,0,0,0 });
		stageObj[8]->Init({ -30,0,0 }, { 1,1,1 }, { 0,0,0,0 });
	}
}

void GameScene::SOCreate()
{
	//ステージにある飾りオブジェクト等の初期化
	stageObj[0]->Initialize("road");
	stageObj[1]->Initialize("Kota");
	stageObj[2]->Initialize("TV");
	stageObj[3]->Initialize("Chest");
	stageObj[4]->Initialize("home");
	stageObj[5]->Initialize("saku");
	stageObj[6]->Initialize("slide");
	stageObj[7]->Initialize("swing");
	stageObj[8]->Initialize("tree");
}