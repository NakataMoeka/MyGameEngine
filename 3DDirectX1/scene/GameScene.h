﻿#pragma once


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
#include"player.h"
#include"GameObject.h"
#include"stageObject.h"
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
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init();
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
	bool SetClearFlag(bool clearFlag) { return this->clearFlag=clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
private: // メンバ変数
	DXCommon* dxCommon = nullptr;


	Audio* audio = nullptr;

	SoundData sound1;
	SoundData sound2;

	Camera* camera = nullptr;
	ParticleManager* particleMan = nullptr;
	Sprite* sprite = nullptr;
	Sprite* timeSprite = nullptr;//円
	Sprite* timeSprite2 = nullptr;//バー
	Object3d* object3d = nullptr;
	Model* model = nullptr;

	FbxObject3d* object3d2 = nullptr;
	FbxModel* model2 = nullptr;

	Object3d* object3d3 = nullptr;
	Model* model3 = nullptr;

	TouchableObject* object3d4 = nullptr;
	Model* model4 = nullptr;

	LightGroup* lightGroup = nullptr;

	CollisionManager* colMan = nullptr;

	Player* player;
	GameObject* gameObject;
	StageObject* stageObj;

	const int debugTextTexNumber = 0;

	XMFLOAT3 playerPosition = { 0.0f,0.0f,0.0f };

	static const int OBJNumber = 10;
	bool IsHit[OBJNumber];
	int HitCount=0;
	bool Alive[OBJNumber];
	bool parentFlag = false;
	float Tsize = 1;
	float distance = 20.0f;//プレイヤーとカメラの距離
	float TimeRot = 0;
	int TimeCount = 0;
	float clearTimer = 18000;//1800/60が30秒
	int clearTimer2 = 0;
	bool clearFlag = false;
	bool overFlag = false;
};