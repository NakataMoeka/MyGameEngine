#pragma once


#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "DebugCamera.h"
#include "Collision.h"
#include"../Ease.h"
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

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);


	void Update();

	void Draw();
	void CreateParticles();
private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;

	Input* input = nullptr;

	Audio* audio = nullptr;

	DebugText debugText;

	DebugCamera* camera = nullptr;
	ParticleManager* particleMan = nullptr;

	Sprite* sprite = nullptr;
	Sprite* sprite2 = nullptr;
	Object3d* object3d = nullptr;
	Model*	model = nullptr;

	Object3d* object3d2 = nullptr;
	Model* model2 = nullptr;

	const int debugTextTexNumber = 0;


	
	bool Mflag = false;
#pragma region 今回は使わん
	//MT4_課題1
	//XMFLOAT3 playerPosition = { -50.0f,-30.0f,0.0f };
	//XMFLOAT2 playerPosition2 = { 0.0f,500.0f };
	//XMFLOAT2 v2 = { 0.0f,0.0f };

	//bool tFlag = false;

	//loat f=1;
	//float v = 40.0f;
	//float k = 1.0f;
	//float a = 0.f;
	//float g = 9.8f/60.0f;
	//float fx1 = 1.0f;
	//float m = 5.0f;
	//float t=0.0f;
	//Mt4_課題2
	//float mg = 9.8f;

	//float fk = 0.0f;
	//float fs = 0.0f;
	//float us = 0.8f;
	//float uk = 1.5f;
	//float N = 0.0f;
	//float fx = 0.0f;
	//float fy = 0.0f;
	//float PI = 3.141592;
	//MT4課題3

	//const float minus = -1.0f;
	//float vB = 0.0f;
	//float vu;
	//float vBu;

	//float a = 0.01f;
	//float a2 = 0.01f;

	//float m = 1.0f;
	//float m2 = 2.0f;
	//float e = 0.5;
	//Sphere sphereA;
	//Sphere sphereB;
#pragma endregion

	XMFLOAT3 playerPosition = { 0.0f,0.0f,0.0f };
	XMFLOAT3 playerEndPosition = { 10.0f,0.0f,0.0f };
	XMFLOAT3 playerPositionB = { 0.0f,0.0f,0.0f };

	XMFLOAT2 playerPos2d = {300, 300};
	XMFLOAT2 playerEndPos2d = { 500,300 };
	XMFLOAT2 playerSize2d = { 100, 100 };
	XMFLOAT2 playerEndSize2d = { 200,200 };
	//XMFLOAT2 playerPos2d2= { 0.0f,0.0f };
	//XMFLOAT2 playerEndPos2d2 = { 0,0 };

	int EaseFlag = 0;

	float angle = 0;

	//float angl = 0;
	Sphere circle;
	Box line;
};
