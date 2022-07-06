#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
/// <summary>
/// ステージに配置されているオブジェクトのクラス
/// </summary>
class GameObject
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	GameObject();
	~GameObject();
	void Initialize();
	void Init();
	void Update();
	void Draw();
	Box	GetCBox() { return cBox; }
private:
	Object3d* cube;
	Model* modelCube;
	Box cBox;
	float r = 0.1;
	XMFLOAT3 position = { 0,-0.8,0 };
};

