#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include <memory>
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
	void Initialize(const std::string& modelname);
	void Init(XMFLOAT3 pos, XMFLOAT3 size, XMVECTOR rot);
	void Update();
	void Draw();
	void RC();//コライダー消すやつ
private:
	std::unique_ptr < TouchableObject> obj = nullptr;
	std::unique_ptr < Model> model = nullptr;
};

