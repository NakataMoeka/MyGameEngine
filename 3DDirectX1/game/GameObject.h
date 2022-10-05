#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
/// <summary>
/// �X�e�[�W�ɔz�u����Ă���I�u�W�F�N�g�̃N���X
/// </summary>
class GameObject
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
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
	Box	GetCBox(int i) { return cBox[i]; }
	OBB GetOBB(int i) { return obb[i]; }
	Sphere GetCSphere(int i) { return cSphere[i]; }
	XMFLOAT3 GetPos(int i) { return position[i]; }
	XMFLOAT3 SetPos(XMFLOAT3 pos ,int i) { return this->position[i] = pos; }

	int GetOBJNumber() { return OBJNumber; }
	float GetMat();
	Object3d* GetObject(int i) { return cube[i]; }
private:
	static const int OBJNumber = 10;
	Object3d* cube[OBJNumber];
	Model* modelCube;
	Box cBox[2];
	OBB obb[2];
	Sphere cSphere[OBJNumber];
	float r = 2;

	XMFLOAT3 position[OBJNumber] = { {10,2,0},{0,10,10} ,{-10,2,0}
	,{-50,2,-40},{0,2,10} ,{-10,2,20}
	,{50,2,30},{0,2,50} ,{-10,2,0} ,{80,2,-20}};
	XMFLOAT3 size[OBJNumber];
	XMVECTOR rota = { 0,0,0,0 };
	float size2 = 5;
};

