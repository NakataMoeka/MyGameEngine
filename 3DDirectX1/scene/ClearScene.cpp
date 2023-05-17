#include "ClearScene.h"

void ClearScene::Initialize()
{


	// カメラ生成
	camera = std::unique_ptr <Camera>(new Camera(WinApp::window_width, WinApp::window_height));

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());
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


	Sprite::LoadTexture(30, L"Resources/UI/mother1.png");
	Sprite::LoadTexture(31, L"Resources/UI/mother2.png");
	Sprite::LoadTexture(32, L"Resources/UI/title/over.png");
	Sprite::LoadTexture(33, L"Resources/UI/title/clear.png");
	Sprite::LoadTexture(34, L"Resources/UI/mother_angry.png");
	Sprite::LoadTexture(35, L"Resources/UI/mother_smile.png");
	Sprite::LoadTexture(36, L"Resources/UI/title/space.png");
	Sprite::LoadTexture(37, L"Resources/UI/back2.png");

	overTextSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(30, { 0,0 }));
	clearTextSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(31, { 0,0 }));
	overSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(32, { 0,0 }));
	clearSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(33, { 0,0 }));
	motherASprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(34, { 0,0 }));
	motherSSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(35, { 0,0 }));
	Space = std::unique_ptr<Sprite>(Sprite::CreateSprite(36, { 0,0 }));
	back = std::unique_ptr<Sprite>(Sprite::CreateSprite(37, { 0,0 }));

	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });

	eas = new Eas();
	sound1 = Audio::SoundLoadWave("Resources/Music/SE/決定ボタンを押す26.wav");
}

void ClearScene::Init()
{
	easeTimer = 0;
	pos = { 350,800 };
	pushFlag = false;
	SCangeFlag = false;
}

void ClearScene::Update()
{
	//文章のイージング
	if (easeTimer < 100) {
		easeTimer++;
	}
	pos.y = eas->ease(800, 100, easeTimer, 100, 1);
	if (pos.y <= 100) {
		pushFlag = true;
	}
	//イージングで文章が既定の位置についたらキーを押せるようになる
	if (pushFlag == true) {
		if (SCangeFlag == false) {
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				SCangeFlag = true;
				audio->SEPlayWave(sound1);
				clearFlag = false;
				overFlag = false;
			}
		}
	}
	//セット系
	motherASprite->SetPosition({ 800,200 });
	motherSSprite->SetPosition({ 800,200 });
	motherASprite->SetSize({ 400,400 });
	motherSSprite->SetSize({ 400,400 });
	Space->SetPosition({ 400,500 });
	clearTextSprite->SetPosition({ 50,250 });
	overTextSprite->SetPosition({ 50,250 });
	clearSprite->SetPosition(pos);
	overSprite->SetPosition(pos);
}

void ClearScene::DrawBG()
{
	back->Draw();
}

void ClearScene::Draw()
{
}

void ClearScene::DrawFront()
{
	if (clearFlag == true) {
		clearTextSprite->Draw();
		clearSprite->Draw();
		motherSSprite->Draw();
	}
	if (overFlag == true) {
		overTextSprite->Draw();
		overSprite->Draw();
		motherASprite->Draw();
	}
	if (pushFlag == true) {
		Space->Draw();
	}
	//DebugText::GetInstance()->Printf(200, 500, 3.0f, "PUSH SPACE");}
}