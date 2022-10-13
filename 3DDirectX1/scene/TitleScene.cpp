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
	Sprite::LoadTexture(10, L"Resources/UI/Title.png");
	Sprite::LoadTexture(12, L"Resources/UI/Title2.png");
	TSprite = Sprite::CreateSprite(10, { 300,100 });
	TBSprite = Sprite::CreateSprite(11, { 0,0 });
	TSSprite = Sprite::CreateSprite(12, { 400,500 });
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
}

void TitleScene::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	TBSprite->Draw();
	Sprite::PostDraw();
}

void TitleScene::Draw()
{
}

void TitleScene::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	TSprite->Draw();
	TSSprite->Draw();
	//DebugText::GetInstance()->Printf(200, 200, 3.0f, "TITLE");
	//DebugText::GetInstance()->Printf(200, 500, 3.0f, "PUSH SPACE");
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}
