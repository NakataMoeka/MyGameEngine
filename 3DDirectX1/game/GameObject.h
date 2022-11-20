#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include"LoadCSV.h"
#include<array>
#include"ObjectHelper.h"
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

	//�I�u�W�F�N�g�z��
	std::vector<object*>oData;
	std::vector<object*>oData2;
public:

	GameObject();
	~GameObject();
	void Initialize();
	void Init();
	void Update();
	void RC();//�R���C�_�[�������
	void Draw();
	//GetterSetter
	Sphere GetCSphere(int i, int j);

	XMFLOAT3 GetPos(int i) { return position2[i]; }
	XMFLOAT3 SetPos(XMFLOAT3 pos ,int i) { return this->position[i] = pos; }
	XMFLOAT3 GetSize(int i) { return size[i]; }
	int GetOBJCount(int j);
	float GetMat();
	Object3d* GetObject3d(int i, int j);
	bool GetAlive(int i, int j);
	bool GetHIT(int i, int j);
	bool SetHIT(int i, int j,bool Hit);
private://Update()�ɂ܂Ƃ߂����
	void move(int i);//�ړ�
private://�ϐ�

	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ�z�u�p(�\��)
	static const int OBJNumber = 100;//obj�̍ő吔
	static const int OBJType = 2;
	std::array < Object3d*, OBJNumber> cube = {};
	std::array < Object3d*, OBJNumber> moveObj = {};
	Model* modelCube = nullptr;
	Model* modelMove = nullptr;
	std::array < Sphere, OBJNumber> cSphere;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere2;//�����蔻��̂��

	float r = 3;//
	//�T�C�Y�p�x�ʒu
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 position[OBJNumber] = {};
	XMFLOAT3 position2[OBJNumber] = {};
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
	bool moveFlag = true;
	float oSpeed = 0;
};

