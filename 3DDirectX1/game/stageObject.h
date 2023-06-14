#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include <memory>
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
	void InitUpd(std::unique_ptr < TouchableObject>&obj,XMFLOAT3 position,XMFLOAT3 scale,XMVECTOR rot);
	std::unique_ptr < TouchableObject> Kotatu = nullptr;
	std::unique_ptr < Model> modelKotatu = nullptr;
	std::unique_ptr < TouchableObject> TV = nullptr;
	std::unique_ptr < Model> modelTV = nullptr;
	std::unique_ptr < TouchableObject> Chest = nullptr;
	std::unique_ptr < Model> modelChest = nullptr;
	std::unique_ptr < TouchableObject> Slide = nullptr;
	std::unique_ptr < Model> modelSlide = nullptr;
	std::unique_ptr < TouchableObject> Swing = nullptr;
	std::unique_ptr < Model> modelSwing = nullptr;
	std::unique_ptr < TouchableObject> Tree = nullptr;
	std::unique_ptr < Model> modelTree = nullptr;
	std::unique_ptr < TouchableObject> Ground = nullptr;
	std::unique_ptr < Model> modelGround = nullptr;
	std::unique_ptr < TouchableObject> Home = nullptr;
	std::unique_ptr < Model> modelHome = nullptr;
	std::unique_ptr < TouchableObject> saku = nullptr;
	std::unique_ptr < Model> modelSaku = nullptr;
	std::unique_ptr < Model> modelSkydome = nullptr;
	std::unique_ptr <Object3d> skydome = nullptr;
	XMFLOAT3 position[2] = { {0,0,0} ,{0,0,-50} };
	XMFLOAT3 size = { 1,1,1 };
	XMVECTOR rota = { 0,0,0,0 };
	int stageNum = 0;
};

