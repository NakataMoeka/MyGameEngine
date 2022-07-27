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
	void Delete(int i);
	Box	GetCBox(int i) { return cBox[i]; }
	OBB GetOBB(int i) { return obb[i]; }
	Sphere GetCSphere(int i) { return cSphere[i]; }
	XMFLOAT3 GetPos(int i) { return position[i]; }
	XMFLOAT3 SetPos(XMFLOAT3 pos ,int i) { return this->position[i] = pos; }
	XMFLOAT3 GetSize() { return size; }
	XMFLOAT3 SetSize(XMFLOAT3 size) { return this->size = size; }
	float GetMat();
	bool SetColFlag(bool ColFlag,int i) { return this->ColFlag[i] = ColFlag; }
	Object3d* GetObject(int i) { return cube[i]; }
private:
	Object3d* cube[2];
	Model* modelCube;
	Box cBox[2];
	OBB obb[2];
	Sphere cSphere[2];
	float r = 2;
	XMFLOAT3 position[2] = { {10,0,0},{-10,0,0} };
	XMFLOAT3 size = {1,1,1 };
	//XMVECTOR rot[2] = { {0,0,0,0},{0,0,0,0} };
	bool ColFlag[2] = { false,false };
};

