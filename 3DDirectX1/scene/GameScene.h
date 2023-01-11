﻿#pragma once


#include"SafeDelete.h"
#include <DirectXMath.h>
#include"Sprite.h"
#include"Audio.h"
#include"DXCommon.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "Camera.h"
#include "FbxObject.h"
#include"LightGroup.h"
#include"player.h"
#include"GameObject.h"
#include"stageObject.h"
#include"Collision.h"
#include<vector>
#include<array>
#include"Timer.h"
#include"Pose.h"
#include"Tutorial.h"
#include"SphereSize.h"
#include"start.h"
class CollisionManager;
class TouchableObject;
class GameScene
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // メンバ関数


	GameScene();

	~GameScene();
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//OBJ等初期化用()
	void InitTH();
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init();
	//ステージ初期化
	void InitStageNum(int stageNum);
	//繰り返し処理
	void Update();
	//背景画像描画
	void DrawBG();
	//オブジェクト描画
	void Draw();
	//前景画像描画
	void DrawFront();
	//パーティクル
	void CreateParticles();
	bool GetClearFlag() { return clearFlag; }
	bool GetOverFlag() { return overFlag; }
	bool SetClearFlag(bool clearFlag) { return this->clearFlag = clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
	bool GetBFlag() { return Bflag; }
	bool GetTitleFlag();
	int SetStageNum(int stageNum) { return this->stageNum = stageNum; }
	bool GetTSFlag() { return TSFlag; }

private: // メンバ変数
	DXCommon* dxCommon = nullptr;


	Audio* audio = nullptr;

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	SoundData sound4 = {};
	SoundData sound5 = {};
	Camera* camera = nullptr;
	ParticleManager* particleMan = nullptr;

	Sprite* sprite = nullptr;

	LightGroup* lightGroup = nullptr;

	CollisionManager* colMan = nullptr;

	Player* player = nullptr;
	GameObject* gameObject = nullptr;
	StageObject* stageObj = nullptr;

	Timer* timer = nullptr;
	Pose* pose = nullptr;
	SphereSize* sphereSize = nullptr;
	Tutorial* tutorial = nullptr;
	start* st = nullptr;

	const int debugTextTexNumber = 0;


	static const int OBJNumber = 100;//OBJの最大数を記載

	int HitCount = 0;
	//サイズ
	float Tsize = 1;
	int Tsize2 = 1;
	int TCount = 0;
	bool TFlag = false;

	float distance = 20.0f;//プレイヤーとカメラの距離

	float distanceY = 20.0f;//カメラの位置
	float distanceC = 20.0f;//カメラの位置
	float distanceCY = 20.0f;//カメラの位置

	float SY = 3;

	bool clearFlag = false;
	bool overFlag = false;

	bool Bflag = false;//ブラーを掛けるか否か

	//ステージナンバー
	int stageNum = 0;
	bool TSFlag;
	int cACount = 0;
	bool caFlag = false;

	int testCount = 0;//test
	int GoalCount = 0;
};