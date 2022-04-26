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

	Object3d* object3d = nullptr;
	Model*	model = nullptr;

	Object3d* object3d2 = nullptr;
	Model* model2 = nullptr;

	const int debugTextTexNumber = 0;

	//XMFLOAT3 playerPosition = {0.0f,0.0f,0.0f};
	
	
	bool Mflag = false;

	//MT4_â€ëË1
	XMFLOAT3 playerPosition = { -50.0f,0.0f,0.0f };
	float vx = 2.0f;
	float a = 0.0f;
	float g = 9.8f/60.0f;
	float fx1 = 1.0f;
	float m = 10.0f;

	//Mt4_â€ëË2
	float mg = 9.8f;

	float fk = 0.0f;
	float fs = 0.0f;
	float us = 0.8f;
	float uk = 1.5f;
	float N = 0.0f;
	float fx = 0.0f;
	float fy = 0.0f;
	float PI = 3.141592;
};


