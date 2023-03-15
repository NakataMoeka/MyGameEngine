#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include"LoadCSV.h"
#include<array>
#include"ObjectHelper.h"
#include"safedelete.h"
#include <vector>
#include <string>
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
	std::vector<object*>oData;//�u���b�N
	std::vector<object*>oData2;//��
	std::vector<object*>oData3;//�N�}
	std::vector<object*>oData4;//���{�b�g
	std::vector<object*>oData5;//�J�[�h
public:
	

	GameObject();
	~GameObject();
	void Initialize();
	void Init();
	void stageInit(int stageNum);
	void Update();
	void RC();//�R���C�_�[�������
	void Draw();
	//GetterSetter
	Sphere GetCSphere(int i, int j);

	//XMFLOAT3 GetPos(int i) { return position2[i]; }
	//XMFLOAT3 SetPos(XMFLOAT3 pos ,int i) { return this->position[i] = pos; }
	XMFLOAT3 GetSize(int i) { return size[i]; }
	int GetOBJCount(int j);
	float GetMat();
	Object3d* GetObject3d(int i, int j);
	bool GetHIT(int i, int j);
	bool SetHIT(int i, int j, bool Hit);
	float GetOSize(int i, int j);
	XMFLOAT3 GetOPos(int i, int j);
private://Update()�ɂ܂Ƃ߂����
	void Col(Object3d* object, XMFLOAT3 pos);
private://�ϐ�

	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ�z�u�p(�\��)
	static const int OBJNumber = 70;//obj�̍ő吔(�������)
	static const int OBJNumber2 = 30;//obj�̍ő吔(���Ȃ߂̂��)
	static const int OBJType = 2;
	//�I�u�W�F�N�g
	std::array < Object3d*, OBJNumber> cube = {};
	std::array < Object3d*, OBJNumber> moveObj = {};
	std::array < Object3d*, OBJNumber2> Bear = {};
	std::array < Object3d*, OBJNumber2> Robot = {};
	std::array < Object3d*, OBJNumber2> Card = {};
	//std::array < Object3d*, OBJNumber2> Pencil = {};

	std::array < Object3d*, OBJNumber2> Kendama = {};
	std::array < Object3d*, OBJNumber2> Koma = {};
	std::array < Object3d*, OBJNumber2> Shogi = {};
	std::array < Object3d*, OBJNumber2> Turu = {};
	//std::array < Object3d*, OBJNumber2> Cont = {};
	std::array < Object3d*, OBJNumber> Game = {};

	Model* modelCube = nullptr;
	Model* modelMove = nullptr;
	Model* modelBear = nullptr;
	Model* modelRobot = nullptr;
	Model* modelCard = nullptr;
	Model* modelPencil = nullptr;

	Model* modelKendama = nullptr;
	Model* modelKoma = nullptr;
	Model* modelShogi = nullptr;
	Model* modelTuru = nullptr;
	Model* modelCont = nullptr;
	Model* modelGame = nullptr;


	std::array < Sphere, OBJNumber> cSphere;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere2;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere3;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere4;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere5;//�����蔻��̂��
	float r = 3;//
	//�T�C�Y�p�x�ʒu
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
	bool moveFlag = true;//�����Ă��邩�ۂ�
	float oSpeed = 0;//
	int randRot = 0;//�p�x�����_��
	int stageNum = 0;//�X�e�[�W�ԍ�
	bool onGround = true;
	// �����x�N�g��
	DirectX::XMVECTOR fallV = {};
};

