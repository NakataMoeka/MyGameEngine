#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include"CSV.h"
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
	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ�z�u�p(�\��)
	static const int OBJNumber = 10;
	static const int OBJType = 2;
	Object3d* cube[OBJNumber];
	Model* modelCube;

	OBB obb[OBJNumber];//�o�O���N���Ă��邽��OBB�͎g���܂���
	Sphere cSphere[OBJNumber];//�����蔻��̂��
	Sphere cSphere2[OBJNumber];//�����蔻��̂��
	float r = 2;//

	//�T�C�Y�p�x�ʒu
	XMFLOAT3 position[OBJNumber] = { {10,2,0},{0,10,10} ,{-10,2,0}
	,{-50,2,-40},{30,2,10} ,{-10,2,20}
	,{50,2,30},{0,2,50} ,{-10,2,0} ,{80,2,-20}};
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
};

