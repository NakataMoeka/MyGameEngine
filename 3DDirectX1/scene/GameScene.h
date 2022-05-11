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
class GameScene 
{
private: 
// Microsoft::WRL::‚ğÈ—ª
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // ƒƒ“ƒoŠÖ”


	GameScene();


	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);


	void Update();

	void Draw();
	void CreateParticles();
private: // ƒƒ“ƒo•Ï”
	DirectXCommon* dxCommon = nullptr;

	Input* input = nullptr;

	Audio* audio = nullptr;

	DebugText debugText;

	Camera* camera = nullptr;
	ParticleManager* particleMan = nullptr;

	Sprite* sprite = nullptr;

	Object3d* object3d = nullptr;
	Model*	model = nullptr;

	FbxObject3d* object3d2 = nullptr;
	FbxModel* model2 = nullptr;

	const int debugTextTexNumber = 0;

	XMFLOAT3 playerPosition = {0.0f,0.0f,0.0f};
	
<<<<<<< HEAD

=======
	
	bool Mflag = false;

	//MT4_‰Û‘è1
	XMFLOAT3 playerPosition = { -50.0f,-30.0f,0.0f };
	XMFLOAT2 playerPosition2 = { 0.0f,500.0f };
	XMFLOAT2 v2 = { 0.0f,0.0f };

	bool tFlag = false;

	float f = 10.0f;
	float v = 40.0f;
	float k = 1.0f;
	float a = 0.f;
	float g = 9.8f/60.0f;
	float fx1 = 1.0f;
	float m = 5.0f;
	float t=0.0f;
	//Mt4_‰Û‘è2
	float mg = 9.8f;

	float fk = 0.0f;
	float fs = 0.0f;
	float us = 0.8f;
	float uk = 1.5f;
	float N = 0.0f;
	float fx = 0.0f;
	float fy = 0.0f;
	float PI = 3.141592;
>>>>>>> MT4èª²é¡E

};


