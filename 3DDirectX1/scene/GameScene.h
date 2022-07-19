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
// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // ÉÅÉìÉoä÷êî


	GameScene();


	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);


	void Update();

	void Draw();
	void CreateParticles();
private: // ÉÅÉìÉoïœêî
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
#pragma region ç°âÒÇÕégÇÌÇÒ
	//MT4_â€ëË1
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
	//Mt4_â€ëË2
	//float mg = 9.8f;

	//float fk = 0.0f;
	//float fs = 0.0f;
	//float us = 0.8f;
	//float uk = 1.5f;
	//float N = 0.0f;
	//float fx = 0.0f;
	//float fy = 0.0f;
	//float PI = 3.141592;
	//MT4â€ëË3

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

	XMFLOAT2 playerPos2d = {500, 0};
	XMFLOAT2 playerPos22d = {501, 500};
	XMFLOAT2 playerSize2d = { 1, 500 };
	XMFLOAT2 playerEndSize2d = { 200,200 };
	//XMFLOAT2 playerPos2d2= { 300.0f,150.0f };
	//XMFLOAT2 playerEndPos2d2 = { 0,0 };
	float k = 1.0f;
	float m = 30.0f;
	//float gacc = 0.2f;
	XMFLOAT2 acc;
	XMFLOAT2 vel;
	float dist = 0;
	float f = 0.0;
	float a = 0.0;
	float v = 0.0;
	float kv = 2;
	int EaseFlag = 0;
	float easeTimer = 0;
	float angle = 0;
	float playerAngle = 0;
	//float angl = 0;
	Sphere circle;
	Ray ray;
	Box line;
	int x;
};
