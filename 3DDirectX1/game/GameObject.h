#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include"LoadCSV.h"
#include<array>
#include"ObjectHelper.h"
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
	void RC();//コライダー消すやつ
	void Draw();
	//GetterSetter
	Sphere GetCSphere(int i, int j);

	XMFLOAT3 GetPos(int i) { return position[i]; }
	XMFLOAT3 SetPos(XMFLOAT3 pos ,int i) { return this->position[i] = pos; }
	XMFLOAT3 GetSize(int i) { return size[i]; }
	int GetOBJNumber() { return OBJNumber; }
	float GetMat();
	Object3d* GetObject(int i) { return cube[i]; }
private://Update()にまとめるもの
	void move();//移動
private://変数
	//敵配列
	std::vector<object*>oData;
	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ配置用(予定)
	static const int OBJNumber = 10;
	static const int OBJMax = 100;
	static const int OBJType = 2;
	std::array < Object3d*,OBJNumber> cube = {};
	std::array < Object3d*, OBJNumber> moveObj = {};
	Model* modelCube = nullptr;
	Model* modelMove = nullptr;
	std::array < Sphere, OBJNumber> cSphere;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere2;//当たり判定のやつ
	float r = 3;//
	//サイズ角度位置
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 position[OBJNumber] = {};
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
};

