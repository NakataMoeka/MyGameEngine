#pragma once
#include"Object3d.h"
#include"Model.h"
class Player
{
private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Player();
	void Initialize();
	void Move();
	void Draw();
	int GetPower() { return power; }
	XMFLOAT3 GetPlayerPos() { return playerPos; }
private:
	Object3d* playerObj;
	Model* model;

	XMFLOAT3 playerPos{ 0,0,0 };
	int HP = 50;
	int power = 100;

};

