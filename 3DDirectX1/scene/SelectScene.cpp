#include "SelectScene.h"
#include"Input.h"
#include"SceneManager.h"
#include"GameScene.h"

void SelectScene::Initialize()
{	
	// カメラ生成
	camera = std::unique_ptr < Camera>(new Camera(WinApp::window_width, WinApp::window_height));

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());

	//ライト生成
	lightGroup = std::unique_ptr <LightGroup>(LightGroup::Create());
	// 3Dオブエクトにライトをセット
	Object3d::SetLight(lightGroup.get());

	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetDirLightDir(2, XMVECTOR{ 1,0,0,0 });
	//lightGroup->SetPointLightActive(0, true);
	//lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, true);

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

void SelectScene::InitTH()
{
}

void SelectScene::InitStageNum(int stageNum)
{
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
	else if (SAFlag == 0 && SCangeFlag == false && Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		if (stageNum == 0 || stageNum == 1 || stageNum == 2) {
			SCangeFlag = true;
			//BaseScene* scene = new GameScene();
			//sceneManager_->SetNum(stageNum);
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
	backSprite[(int)spriteCount]->Draw();
}

void SelectScene::Draw()
{
}

void SelectScene::DrawFront()
{
	SelectUI->Draw();
	if (SAFlag == 0) {

		SelectNumber->Draw();
		
		if (stageNum == 0) {
			TutorialS->Draw();
		}
	}


}

void SelectScene::Finalize()
{
}

void SelectScene::CreateParticles()
{
}

bool SelectScene::GetSCangeFlag()
{
	return SCangeFlag;
}
