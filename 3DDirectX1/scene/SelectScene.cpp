#include "SelectScene.h"
#include"Input.h"

void SelectScene::Initialize(DXCommon* dxCommon, Audio* audio)
{	//u
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
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(debugTextTexNumber);
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });

	Sprite::LoadTexture(40, L"Resources/UI/Select0.png");
	Sprite::LoadTexture(41, L"Resources/UI/Select1.png");
	Sprite::LoadTexture(42, L"Resources/UI/Select2.png");
	Sprite::LoadTexture(43, L"Resources/UI/Select3.png");
	Sprite::LoadTexture(44, L"Resources/UI/Select4.png");

	Sprite::LoadTexture(45, L"Resources/UI/SelectUI.png");

	backSprite[0] = Sprite::CreateSprite(40, { 0,0 });
	backSprite[1] = Sprite::CreateSprite(41, { 0,0 });
	backSprite[2] = Sprite::CreateSprite(42, { 0,0 });
	backSprite[3] = Sprite::CreateSprite(43, { 0,0 });
	backSprite[4] = Sprite::CreateSprite(44, { 0,0 });
	backSprite[5] = Sprite::CreateSprite(40, { 0,0 });
	SelectUI = Sprite::CreateSprite(45, { 0,0 });
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/ビープ音1.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/SE/決定ボタンを押す26.wav");
	sound3 = Audio::SoundLoadWave("Resources/Music/SE/cursor.wav");
}

void SelectScene::Init()
{
	spriteCount = 0;
	stageNum = 0;
	SCangeFlag = false;
	SAFlag = 0;
}

void SelectScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW))
	{
		if (stageNum < 3) {
			stageNum++;
			spriteCount = 0;
			SAFlag = 1;
			audio->SEPlayWave(sound3);
		}
	}
	else if (Input::GetInstance()->TriggerKey(DIK_UPARROW))
	{
		if (stageNum > 0) {
			stageNum--;
			spriteCount = 5;
			SAFlag = 2;
			audio->SEPlayWave(sound3);
		}
	}
	if (SAFlag == 1) {
		if (spriteCount < 5) {
			spriteCount += 0.5f;
		}
		else if (spriteCount == 5) {
			SAFlag = 0;
		}

	}
	else if (SAFlag == 2) {
		if (spriteCount > 0) {
			spriteCount -= 0.5f;
		}
		else if (spriteCount == 0) {
			SAFlag = 0;
		}

	}
	else if (SAFlag == 0) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			if (stageNum == 0 || stageNum == 1) {
				SCangeFlag = true;
				audio->SEPlayWave(sound2);
			}
			else {
				audio->SEPlayWave(sound1);
			}

		}
	}
}

void SelectScene::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	dxCommon->ClearDepthBuffer();
	backSprite[(int)spriteCount]->Draw();
	Sprite::PostDraw();
}

void SelectScene::Draw()
{
}

void SelectScene::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	SelectUI->Draw();
	if (SAFlag == 0) {
		DebugText::GetInstance()->Printf(600, 300, 6.0f, { 0,0,0,1 }, "%d", stageNum);
		if (stageNum == 2 || stageNum == 3) {
			DebugText::GetInstance()->Printf(250, 400, 6.0f, { 0,0,0,1 }, "MADA,ASOBENAIYO");
		}
	}

	//DebugText::GetInstance()->Printf(0, 0, 3.0f, { 0,0,0,1 }, "%f", spriteCount);
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}

void SelectScene::CreateParticles()
{
}
