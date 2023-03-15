#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
/// <summary>
/// 地形オブジェクト
/// </summary>
class TouchableObject;
class StageObject
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	StageObject();
	~StageObject();
	void Initialize();
	void Init();
	void stageInit(int stageNum);
	void Update();
	void Draw();
	void RC();//コライダー消すやつ

private:

	TouchableObject* Kotatu = nullptr;
	Model* modelKotatu = nullptr;
	TouchableObject* TV = nullptr;
	Model* modelTV = nullptr;
	TouchableObject* Chest = nullptr;
	Model* modelChest = nullptr;
	TouchableObject* Slide = nullptr;
	Model* modelSlide = nullptr;
	TouchableObject* Ground = nullptr;
	Model* modelGround = nullptr;
	TouchableObject* Home = nullptr;
	Model* modelHome = nullptr;
	TouchableObject* saku = nullptr;
	Model* modelSaku = nullptr;
	Model* modelSkydome = nullptr;
	Object3d* skydome = nullptr;
	XMFLOAT3 position[2] = { {0,0,0} ,{0,0,-50} };
	XMFLOAT3 size = { 1,1,1 };
	XMVECTOR rota = { 0,0,0,0 };
	int stageNum = 0;
};

