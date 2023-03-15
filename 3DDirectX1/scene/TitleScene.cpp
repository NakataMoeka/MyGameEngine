#include "TitleScene.h"

void TitleScene::Initialize(DXCommon* dxCommon, Audio* audio)
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
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(debugTextTexNumber);
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });

	Sprite::LoadTexture(11, L"Resources/UI/TitleB.png");
	Sprite::LoadTexture(10, L"Resources/UI/title/title.png");
	Sprite::LoadTexture(12, L"Resources/UI/title/Title2.png");
	Sprite::LoadTexture(13, L"Resources/UI/title/Title3.png");
	Sprite::LoadTexture(14, L"Resources/UI/TitleB2.png");
	TSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(10, { 0,0 }));
	TBSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(11, { 0,0 }));
	TSSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(12, { 500,500 }));
	TS2Sprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(13, { 500,600 }));
	TB2Sprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(14, { 0,0 }));
	sound1 = Audio::SoundLoadWave("Resources/Music/BGM/famipop.wav");
	sound2 = Audio::SoundLoadWave("Resources/Music/SE/決定ボタンを押す26.wav");
	sound3 = Audio::SoundLoadWave("Resources/Music/SE/cursor.wav");
}

void TitleScene::Init()
{
	SceneNum = 0;
	Scene = 0;
	TaCount = 0;
	SCangeFlag = false;
	TSSprite->SetSize({ 300,110 });
	TS2Sprite->SetSize({ 180,50 });
	TSSprite->SetPosition({ 450,500 });
	TS2Sprite->SetPosition({ 500,600 });
	TSprite->SetPosition({ 250,100 });
	TSprite->SetSize({ 128,128 });
	TSprite->SetTextureRect({ 0 ,0 }, { 0 + 146,170 });
	testCount = 0;
	audio->SoundPlayWave(sound1);
	audio->SetBGMVolume(0.2f);
}

void TitleScene::Update()
{
	if (Scene == 0) {
		if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW))
		{
			SceneNum = 1;
			audio->SEPlayWave(sound3);
		}
		else if (Input::GetInstance()->TriggerKey(DIK_UPARROW)) {
			SceneNum = 0;
			audio->SEPlayWave(sound3);
		}
	}
	if (SceneNum == 0) {
		if (SCangeFlag == false) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				SCangeFlag = true;
				audio->SEPlayWave(sound2);
				audio->StopWave();
			}
		}
		TSSprite->SetSize({ 300,110 });
		TS2Sprite->SetSize({ 180,50 });
		TSSprite->SetPosition({ 500,500 });
		TS2Sprite->SetPosition({ 560,600 });
	}
	else if (SceneNum == 1) {
		if (Scene == 0) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				audio->SEPlayWave(sound2);
				Scene = 1;
			}
		}
		else if (Scene == 1) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				audio->SEPlayWave(sound2);
				Scene = 0;
			}
		}

		TSSprite->SetSize({ 150,55 });
		TS2Sprite->SetSize({ 360,100 });
		TSSprite->SetPosition({ 560,550 });
		TS2Sprite->SetPosition({ 460,600 });
	}
	if (TaCount < 5) {
		TaCount += 0.5;
	}
	testCount++;
	TSprite->SetTextureRect({ 0 ,0 }, { 0 + 150 * TaCount,130 });
	TSprite->SetSize({ 770,130 });
}

void TitleScene::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	dxCommon->ClearDepthBuffer();
	if (Scene == 0) {
		TBSprite->Draw();
	}
	if (Scene == 1) {
		TB2Sprite->Draw();
	}
	Sprite::PostDraw();
}

void TitleScene::Draw()
{
}

void TitleScene::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	if (Scene == 0) {
		TSprite->Draw();
		TSSprite->Draw();
		TS2Sprite->Draw();
	}
	//DebugText::GetInstance()->Printf(0, 0, 3.0f, "%d",SceneNum);
	//DebugText::GetInstance()->Printf(200, 500, 3.0f, {0,0,0,1}, "%d", testCount);
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}
