#include "SelectScene.h"
#include"Input.h"

void SelectScene::Initialize(DXCommon* dxCommon, Audio* audio)
{	//u
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	// カメラ生成
	camera = std::unique_ptr < Camera>(new Camera(WinApp::window_width, WinApp::window_height));

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());
	FbxObject3d::SetDev(dxCommon->Getdev());
	//ライト生成
	lightGroup = std::unique_ptr <LightGroup>(LightGroup::Create());

	Object3d::SetLight(lightGroup.get());

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
	Sprite::LoadTexture(46, L"Resources/UI/number/Number3.png");
	Sprite::LoadTexture(47, L"Resources/UI/Tutorial.png");

	backSprite[0] = std::unique_ptr<Sprite>(Sprite::CreateSprite(40, { 0,0 }));
	backSprite[1] = std::unique_ptr<Sprite>(Sprite::CreateSprite(41, { 0,0 }));
	backSprite[2] = std::unique_ptr<Sprite>(Sprite::CreateSprite(42, { 0,0 }));
	backSprite[3] = std::unique_ptr<Sprite>(Sprite::CreateSprite(43, { 0,0 }));
	backSprite[4] = std::unique_ptr<Sprite>(Sprite::CreateSprite(44, { 0,0 }));
	backSprite[5] = std::unique_ptr<Sprite>(Sprite::CreateSprite(40, { 0,0 }));
	SelectUI = std::unique_ptr<Sprite>(Sprite::CreateSprite(45, { 0,0 }));
	SelectNumber = std::unique_ptr<Sprite>(Sprite::CreateSprite(46, { 560,250 }));
	TutorialS = std::unique_ptr<Sprite>(Sprite::CreateSprite(47, { 450,400 }));
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
		if (stageNum < 2) {
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
	else if (SAFlag == 0&& SCangeFlag == false && Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				if (stageNum == 0 || stageNum == 1 || stageNum == 2) {
					SCangeFlag = true;
					audio->SEPlayWave(sound2);
				}
				else {
					audio->SEPlayWave(sound1);
				}
	}
	SelectNumber->SetSize({ 120,130 });
	TutorialS->SetSize({ 315, 70 });
	SelectNumber->SetTextureRect({ 0 + 32 * (float)stageNum,0 }, { 32,48 });
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
		/*	if (stageNum == 2 ) {
				DebugText::GetInstance()->Printf(250, 400, 6.0f, { 0,0,0,1 }, "MADA,ASOBENAIYO");
			}*/
		SelectNumber->Draw();
		//DebugText::GetInstance()->Printf(600, 300, 6.0f, { 0,0,0,1 }, "%d", stageNum);
		if (stageNum == 0) {
			TutorialS->Draw();
		}
	}

	//DebugText::GetInstance()->Printf(0, 0, 3.0f, { 0,0,0,1 }, "%f", spriteCount);
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}

void SelectScene::CreateParticles()
{
}
