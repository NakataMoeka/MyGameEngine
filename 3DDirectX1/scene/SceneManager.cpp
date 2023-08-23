#include "SceneManager.h"
#include"Input.h"
SceneManager::~SceneManager()
{
	//#if _DEBUG
	if (scene == LOAD) {
		t.detach();
	}
	t.~thread();
	//#endif
}
void SceneManager::Initialize(DXCommon* dxCommon, Audio* audio)
{
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	DebugText::GetInstance()->Initialize(debugTextTexNumber);

	FbxObject3d::SetDev(dxCommon->Getdev());
	FbxObject3d::CreateGraphicsPipeline(L"Resources/shaders/FBXPS.hlsl", L"Resources/shaders/FBXVS.hlsl");
	loadScene = std::unique_ptr <Loading>(new Loading());
	loadScene->Initialize();
	loadScene->Init();
	BaseScene* scene1 = new TitleScene();
	//�V�[���}�l�[�W���ɍŏ��̃V�[���Z�b�g
	SetNextScene(scene1);
	Load_s = NOLOAD;
	loadFlag = false;
	//scene = LOAD;
}

void SceneManager::Update()
{
	if (nextScene_)
	{
		if (scene_)
		{
			scene_->Finalize();
			delete scene_;
		}
		//�V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;
		scene_->SetSceneManager(this);
		//���̃V�[��������������
		scene_->Initialize();
		scene_->InitTH();
		scene_->Init();
		loadFlag = true;
	}
	//if (loadFlag == false) {
		scene_->Update();
	//}

	//���[�f�B���O
	if (loadFlag == true) {
		switch (Load_s)
		{
		case SceneManager::NOLOAD://���[�h���Ă��Ȃ��Ƃ�
			t = std::thread([&] {
				InitTH();
				Load_s = ENDLOAD; });
			Load_s = NOWLOAD;
			break;
		case SceneManager::NOWLOAD://���[�h���Ă���Ƃ�
			break;
		case SceneManager::ENDLOAD://���[�h�I�������
			t.join();
			Load_s = NOLOAD;
			loadFlag = false;
			break;
			//default:
				//break;
		}

	}
	loadScene->Update();
	//change->Update();
}
void SceneManager::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	if (loadFlag == true) {
		loadScene->DrawBG();
	}
	else {
		scene_->DrawBG();
	}
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
}

void SceneManager::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());
	if (loadFlag == false) {
		scene_->Draw();
	}
	Object3d::PostDraw();
	FbxObject3d::PostDraw();
}

void SceneManager::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	if (loadFlag == true) {
		loadScene->DrawFront();
	}
	else {
		scene_->DrawFront();
	}
	DebugText::GetInstance()->Printf(0, 0, 3, { 0,0,0,1 }, "%d", loadFlag);
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}

void SceneManager::InitTH()
{

}
