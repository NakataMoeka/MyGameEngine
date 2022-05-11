#include "GameScene.h"
#include <cassert>
<<<<<<< HEAD
#include "FbxLoader.h"
#include "FbxObject.h"
=======
//#include "FbxLoader.h"
>>>>>>> MT4èª²é¡Œ
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

	// ƒJƒƒ‰¶¬
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// 3DƒIƒuƒWƒFƒNƒg‚ÉƒJƒƒ‰‚ðƒZƒbƒg
	Object3d::SetCamera(camera);
	FbxObject3d::SetDev(dxCommon->Getdev());
	FbxObject3d::SetCamera(camera);
	FbxObject3d::CreateGraphicsPipeline();

	// ƒp[ƒeƒBƒNƒ‹ƒ}ƒl[ƒWƒƒ¶¬
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera);

	model = model->Create("bullet",true);
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("cube");
	object3d = Object3d::Create(model);
	object3d2 = new FbxObject3d();
	object3d2->Initialize();
	object3d2->SetModel(model2);
	
	//object3d2->SetRotation({ 0,180,0 });
	//object3d2->SetPosition({ 0,0,0 });
	object3d->Update();
	object3d2->Update();
	//ƒ‚ƒfƒ‹–¼‚ðŽw’è‚µ‚Ä“Ç‚Ýž‚Ý
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	//‚ ‚ ‚ ‚ ‚ 

	//object3d2->Update();


	// ƒfƒoƒbƒOƒeƒLƒXƒg—pƒeƒNƒXƒ`ƒƒ“Ç‚Ýž‚Ý
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// ƒfƒoƒbƒOƒeƒLƒXƒg‰Šú‰»
	debugText.Initialize(debugTextTexNumber);
	
	Sprite::LoadTexture(1, L"Resources/jimenParticle.png");

	sprite = Sprite::CreateSprite(1, playerPosition2);

	//audio->SoundPlayWave("Resources/ƒVƒ‡ƒbƒg.wav",true);
	// ƒJƒƒ‰’Ž‹“_‚ðƒZƒbƒg
	camera->SetTarget({ 0, 1, 0 });
<<<<<<< HEAD
	camera->SetEye({ 0, 0, -5 });
=======
	//camera->SetDistance(20.0f);
			v2.x = v * cos(60 * PI / 180.0);
			v2.y = v * sin(60 * PI / 180.0);
>>>>>>> MT4èª²é¡Œ
}

void GameScene::Update()
{
<<<<<<< HEAD
	//XMFLOAT3 playerPosition
=======

#pragma region MT4_‰Û‘è1ƒRƒƒ“ƒgƒAƒEƒg	

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

#pragma region MT4_‰Û‘è2_1
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
	
#pragma region MT4_‰Û‘è2_2
	if (input->TriggerKey(DIK_SPACE)) {

		Mflag = true;
	}
	
		if (Mflag == true) {
			
			if (playerPosition2.y<= 500) {
				playerPosition2.x += v2.x;
				playerPosition2.y -= v2.y;


				v2.y = -g + v2.y;
				g = k * v / m;
		
		

			}
		}
	
	sprite->SetPosition(playerPosition2);
#pragma endregion

>>>>>>> MT4èª²é¡Œ

	if (input->PushMouse(0)) {
		debugText.Printf(100, 100, 5.0f, "www");
	}
	// ƒp[ƒeƒBƒNƒ‹¶¬
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
	FbxObject3d::PreDraw(dxCommon->GetCmdList());
	object3d->Draw();
	//object3d2->Draw();
	Object3d::PostDraw();
	FbxObject3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	char str[256];


	debugText.Printf(0, 140, 3.0f, "%f,%f",playerPosition2.y,v);
	debugText.Printf(0, 180, 3.0f, "%d", tFlag);
	debugText.Printf(0, 80, 3.0f, "SPACE:free fall");

	debugText.DrawAll(dxCommon->GetCmdList( ));
	sprite->PostDraw();
}
void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z‘S‚Ä[-5.0f,+5.0f]‚Åƒ‰ƒ“ƒ_ƒ€‚É•ª•z
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

		// ’Ç‰Á
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}

