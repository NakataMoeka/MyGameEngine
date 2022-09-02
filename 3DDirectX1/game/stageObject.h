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
	void Update();
	void Draw();


private:
	TouchableObject* slope;
	Model* modelSlope;

	XMFLOAT3 position = {0,0,0 };
	XMFLOAT3 size = { 1,1,1 };
	XMVECTOR rota = { 0,0,0,0 };

};

