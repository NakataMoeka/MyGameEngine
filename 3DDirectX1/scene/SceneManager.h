#pragma once
#pragma once
#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "Camera.h"
#include "FbxObject.h"
#include"LightGroup.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"ClearScene.h"
#include"SelectScene.h"
#include"Loading.h"
#include <thread>
#include<mutex>
#include"BaseScene.h"

#include"SceneChange.h"
class SceneManager
{
public:
	enum Scene
	{
		TITLE, SELECT, GAME, END, LOAD
	};
	enum Load_Situation
	{
		NOLOAD, NOWLOAD, ENDLOAD,
	};
	~SceneManager();
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//�J��Ԃ�����
	void Update();
	//�w�i�摜�`��
	void DrawBG();
	//�I�u�W�F�N�g�`��
	void Draw();
	//�O�i�摜�`��
	void DrawFront();
	void InitTH();
	//���̃V�[���\��
	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }
private:
	const int debugTextTexNumber = 0;
	//�ŏ��̃V�[��
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	//���̃V�[��
	BaseScene* scene_ = nullptr;
	//���̃V�[��
	BaseScene* nextScene_ = nullptr;
	Scene scene;
	std::unique_ptr < Loading> loadScene = nullptr;
	//���[�h��ʍ�肽��
	std::thread t = {};
	Load_Situation Load_s = NOLOAD;
	bool loadFlag = false;
};

