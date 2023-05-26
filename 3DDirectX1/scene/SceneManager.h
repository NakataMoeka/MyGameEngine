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
	//���̃V�[����ʂ邽�тɉ��x���s���鏉����(�ʒu�Ȃ�)
	void Init();
	//�J��Ԃ�����
	void Update();

	//�w�i�摜�`��
	void DrawBG();
	//�I�u�W�F�N�g�`��
	void Draw();
	//�O�i�摜�`��
	void DrawFront();
	//���[�h�p������
	void InitTH();
private:
	const int debugTextTexNumber = 0;
	//�ŏ��̃V�[��
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Scene scene = LOAD;
	//���̃V�[��
	BaseScene* scene_ = nullptr;
	//���̃V�[��
	BaseScene* nextScene_ = nullptr;

	std::unique_ptr < TitleScene> titleScene = nullptr;
	std::unique_ptr < SelectScene> selectScene = nullptr;
	std::unique_ptr < GameScene> gameScene = nullptr;
	std::unique_ptr < ClearScene> clearScene = nullptr;
	std::unique_ptr < Loading> loadScene = nullptr;

	std::unique_ptr < SceneChange> change = nullptr;

	//���[�h��ʍ�肽��
	std::thread t = {};
	Load_Situation Load_s = NOLOAD;
};

