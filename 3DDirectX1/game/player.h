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
	~Player();
	void Initialize();
	void Update();
	void Draw();
	int GetPower() { return power; }
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetPlayerAngle() { return playerAngle; }
private:
	void Move();
private:
	Object3d* playerObj;
	Model* model;

	XMFLOAT3 playerPos{ 0,0,0 };

	XMFLOAT3 playerAngle{ 0,0,0 };
	float sinRad = 0;
	float cosRad = 0;
	float radAD = 0.0f;
	float radWS = 0.0f;
	int HP = 50;
	int power = 100;

};

