#include "SelectScene.h"

void SelectScene::Initialize(DXCommon* dxCommon, Audio* audio)
{	//u
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	FbxObject3d::SetDev(dxCommon->Getdev());
	//���C�g����
	lightGroup = LightGroup::Create();

	Object3d::SetLight(lightGroup);

	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
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
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	DebugText::GetInstance()->Initialize(debugTextTexNumber);
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });

	Sprite::LoadTexture(40, L"Resources/UI/Select0.png");
	Sprite::LoadTexture(41, L"Resources/UI/Select1.png");
	Sprite::LoadTexture(42, L"Resources/UI/Select2.png");
	Sprite::LoadTexture(43, L"Resources/UI/Select3.png");
	Sprite::LoadTexture(44, L"Resources/UI/Select4.png");

	backSprite[0] = Sprite::CreateSprite(40, { 0,0 });
	backSprite[1] = Sprite::CreateSprite(41, { 0,0 });
	backSprite[2] = Sprite::CreateSprite(42, { 0,0 });
	backSprite[3] = Sprite::CreateSprite(43, { 0,0 });
	backSprite[4] = Sprite::CreateSprite(44, { 0,0 });

}

void SelectScene::Init()
{
	spriteCount = 0;
}

void SelectScene::Update()
{
}

void SelectScene::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	dxCommon->ClearDepthBuffer();
	backSprite[spriteCount]->Draw();
	Sprite::PostDraw();
}

void SelectScene::Draw()
{
}

void SelectScene::DrawFront()
{
}

void SelectScene::CreateParticles()
{
}
