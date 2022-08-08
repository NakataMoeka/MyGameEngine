#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
/// <summary>
/// プレイヤー関連のクラス
/// </summary>
class Player
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
	Player();
	~Player();
	void Initialize();//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void Update();

	void Draw();

	//Getter
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	Sphere GetSphere() { return sphere; }
	OBB GetOBB() { return obb; }
	Object3d* GetObject() { return SphereObj; }
	float GetTsize() { return Tsize; }
	float SetTsize(float tsize) { return this->Tsize = tsize; }
	bool SetTransFlag(bool transFlag) { return this->transFlag=transFlag; }
private:
	void Move();//移動
	void Ball();//ボール関係
	void Jump();
private:
	Object3d* playerObj;
	Model* model;
	Object3d* SphereObj;
	Model* model2;
	XMFLOAT3 playerPos{ 1,0,0 };
	XMFLOAT3 spherePos{ 1,0,0 };
	XMFLOAT3 playerAngle{ 0,0,0 };
	XMVECTOR sphereAngle{ 0,0,0,0 };

	XMFLOAT3 sphereSize{ 1,1,1 };
	Sphere sphere;
	float sinRad = 0;
	float cosRad = 0;
	float radAD = 0.0f;
	float radWS = 0.0f;
	OBB obb;
	float Tsize = 1;//球のサイズ(左上に表示されているやつ)
	float r = 3;
	bool transFlag = false;
	bool JumpFlag = false;
	bool gFlag = false;
};