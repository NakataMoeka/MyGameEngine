#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include"CSV.h"
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
	using XMVECTOR = DirectX::XMVECTOR;
public:
	GameObject();
	~GameObject();
	void Initialize();
	void Init();
	void Update();
	void Draw();
	void Delete(int i);
	//GetterSetter
	OBB GetOBB(int i) { return obb[i]; }
	Sphere GetCSphere(int i) { return cSphere[i]; }
	Sphere GetCSphere2(int i) { return cSphere2[i]; }
	XMFLOAT3 GetPos(int i) { return position[i]; }
	XMFLOAT3 SetPos(XMFLOAT3 pos ,int i) { return this->position[i] = pos; }
	XMFLOAT3 GetSize(int i) { return size[i]; }
	int GetOBJNumber() { return OBJNumber; }
	float GetMat();
	Object3d* GetObject(int i) { return cube[i]; }
private:
	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ配置用(予定)
	static const int OBJNumber = 10;
	static const int OBJType = 2;
	Object3d* cube[OBJNumber];
	Model* modelCube;

	OBB obb[OBJNumber];//バグが起きているためOBBは使いません
	Sphere cSphere[OBJNumber];//当たり判定のやつ
	Sphere cSphere2[OBJNumber];//当たり判定のやつ
	float r = 2;//

	//サイズ角度位置
	XMFLOAT3 position[OBJNumber] = { {10,2,0},{0,10,10} ,{-10,2,0}
	,{-50,2,-40},{30,2,10} ,{-10,2,20}
	,{50,2,30},{0,2,50} ,{-10,2,0} ,{80,2,-20}};
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
};

