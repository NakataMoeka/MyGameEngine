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
	
	//titleScene = std::unique_ptr <TitleScene>(new TitleScene());
	//titleScene->Initialize();
	//selectScene = std::unique_ptr <SelectScene>(new SelectScene());
	//selectScene->Initialize();
	//clearScene = std::unique_ptr <ClearScene>(new ClearScene());
	//clearScene->Initialize();
	//gameScene = std::unique_ptr <GameScene>(new GameScene());
	//gameScene->Initialize();
	//gameScene->InitTH();
	//loadScene = std::unique_ptr <Loading>(new Loading());
	//loadScene->Initialize();
	//change = std::unique_ptr <SceneChange>(new SceneChange());
	//change->Initialize();
	BaseScene* scene1 = new TitleScene();
	//�V�[���}�l�[�W���ɍŏ��̃V�[���Z�b�g
	SetNextScene(scene1);
	//Load_s = NOLOAD;
	//scene = LOAD;
}

void SceneManager::Update()
{
	if (nextScene_)
	{
		//if (scene_->GetSCangeFlag() == true) {
			//change->SetChangeSFlag(true);
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
			//if (change->GetChangeEFlag() == true) {
				scene_->Initialize();
				scene_->Init();
				//scene_->InitTH();
			//}
		//}
	}
	scene_->Update();
	//if (scene == TITLE) {
	//	if (titleScene->GetSCangeFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (change->GetChangeEFlag() == true) {
	//			selectScene->Init();
	//			scene = SELECT;
	//		}
	//	}
	//	titleScene->Update();
	//}
	////�Z���N�g
	//else if (scene == SELECT) {
	//	if (selectScene->GetSCangeFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (change->GetChangeEFlag() == true) {
	//			gameScene->InitStageNum(selectScene->GetStageNum());
	//			gameScene->Init();
	//			scene = GAME;
	//		}
	//	}
	//	selectScene->Update();
	//}
	////�Q�[���V�[��
	//else if (scene == GAME) {
	//	if (gameScene->GetEndFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (change->GetChangeEFlag() == true) {
	//			clearScene->InitStageNum(gameScene->GetNum());
	//			clearScene->Init();
	//			scene = END;
	//		}
	//	}
	//	if (gameScene->GetTitleFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (change->GetChangeEFlag() == true) {
	//			titleScene->Init();
	//			scene = TITLE;
	//		}
	//	}
	//	if (gameScene->GetTSFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (change->GetChangeEFlag() == true) {
	//			selectScene->Init();
	//			scene = SELECT;
	//		}
	//	}
	//	gameScene->Update();
	//}
	////�G���h
	//else if (scene == END) {
	//	if (clearScene->GetSCangeFlag() == true) {
	//		change->SetChangeSFlag(true);
	//		if (change->GetChangeEFlag() == true) {
	//			titleScene->Init();
	//			scene = TITLE;
	//		}
	//	}
	//	clearScene->Update();
	//}
	//���[�f�B���O
	//if (nextScene_)
	//{
	//	switch (Load_s)
	//	{
	//	case SceneManager::NOLOAD://���[�h���Ă��Ȃ��Ƃ�
	//		t = std::thread([&] {
	//		gameScene->InitTH();
	//		Load_s = ENDLOAD; });
	//		Load_s = NOWLOAD;
	//		break;
	//	case SceneManager::NOWLOAD://���[�h���Ă���Ƃ�
	//		break;
	//	case SceneManager::ENDLOAD://���[�h�I�������
	//		t.join();
	//		scene = TITLE;
	//		titleScene->Init();
	//		Load_s = NOLOAD;
	//		break;
	//	default:
	//		break;
	//	}
	//	loadScene->Update();
	//}
	//change->Update();
}
void SceneManager::DrawBG()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	/*if (scene == TITLE) {
		titleScene->DrawBG();
	}
	else if (scene == SELECT) {
		selectScene->DrawBG();
	}
	else if (scene == GAME) {
		gameScene->DrawBG();
	}
	else if (scene == END) {
		clearScene->DrawBG();
	}
	else if (scene == LOAD) {
		loadScene->DrawBG();
	}*/
	scene_->DrawBG();
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();
}

void SceneManager::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());
	//if (scene == TITLE) {
	//	titleScene->Draw();
	//}
	//else if (scene == GAME) {
	//	gameScene->Draw();
	//}
	//else if (scene == END) {
	//	clearScene->Draw();
	//}
	scene_->Draw();
	Object3d::PostDraw();
	FbxObject3d::PostDraw();
}

void SceneManager::DrawFront()
{
	Sprite::PreDraw(dxCommon->GetCmdList());
	/*if (scene == TITLE) {
		titleScene->DrawFront();
	}
	else if (scene == SELECT) {
		selectScene->DrawFront();
	}
	else if (scene == GAME) {
		gameScene->DrawFront();
	}
	else if (scene == END) {
		clearScene->DrawFront();
	}
	else if (scene == LOAD) {
		loadScene->DrawFront();
	}
	change->DrawFront();*/
	scene_->DrawFront();
	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();
}