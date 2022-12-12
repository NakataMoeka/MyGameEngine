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
#include <thread>
#include<mutex>
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
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//���̃V�[����ʂ邽�тɉ��x���s���鏉����(�ʒu�Ȃ�)
	void Init();
	//�J��Ԃ�����
	void Update();
	void SceneChange();
	//�w�i�摜�`��
	void DrawBG();
	//�I�u�W�F�N�g�`��
	void Draw();
	//�O�i�摜�`��
	void DrawFront();
	void InitTH();
	void SetLockFlag(bool _);
	bool GetLockFlag();
	void AsyncLoad();

	bool GetBFlag() { return Bflag; }
private:
	//�ŏ��̃V�[��
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Scene scene = LOAD;

	TitleScene* titleScene = nullptr;
	SelectScene* selectScene = nullptr;
	GameScene* gameScene = nullptr;
	ClearScene* clearScene = nullptr;
	bool Bflag = false;

	Sprite* Change = nullptr;
	float fade = 0;
	bool changeSFlag = false;
	bool changeEFlag = false;
	//���[�h��ʍ�肽��
	Sprite* loadingS = nullptr;
	std::thread t = {};
	std::thread t2 = {};
	std::mutex isLoadedMutex;
	Load_Situation Load_s = NOLOAD;
	bool LoadFlag = false;
	bool LoadFlagF = false;
};

