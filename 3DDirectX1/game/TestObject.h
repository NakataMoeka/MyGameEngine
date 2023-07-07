#pragma once
#include"object3d.h"
#include"Model.h"
#include<array>
#include"LoadCSV.h"
#include"ObjectHelper.h"
#include"SafeDelete.h"
class TestObject
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
	std::vector<object*>oData;//�u���b�N,�Q�[���@
public:
	TestObject();
	~TestObject();
	void Initialize(const std::string& modelname);
	void Init(int type,float radius);
	void stageInit(int stageNum,float y2,float type );//�X�e�[�W������
	void Update(bool move);
	void Draw();
	void RC();//�R���C�_�[�������
	//GetterSetter
	Sphere GetCSphere(int i, int j);
	XMFLOAT3 GetSize(int i) { return size[i]; }
	int GetOBJCount(int j);
	Object3d* GetObject3d(int i, int j);
	bool GetHIT(int i, int j);
	bool SetHIT(int i, int j, bool Hit);
	float GetOSize(int i, int j);
	XMFLOAT3 GetOPos(int i, int j);
	float SetY(float y) { return this->oy = y; }
private:
	static const int OBJNumber = 100;
	void InitNum(std::vector<object*>oData, int stageNum, float y, float type, size_t i, size_t j);
	void InitUpd(std::array < Object3d*, OBJNumber> obj, int i, std::vector<object*>oData);
	void Upd(std::array < Object3d*, OBJNumber> obj, int i, std::vector<object*>oData, bool move);
	void RCC(std::array < Object3d*, OBJNumber>obj, int i);//�R���C�_�[�폜���ʂ̏���
	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ�z�u�p(�\��)
	int  num = 0;

	std::array < Object3d*, OBJNumber> obj = {};
	std::unique_ptr < Model> model = nullptr;
	std::array < Sphere, OBJNumber> cSphere;//�����蔻��̂��
	float radius = 0.5;//
	float oy = 0;
	//�T�C�Y�p�x�ʒu
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 size[2] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
	bool moveFlag = true;//�����Ă��邩�ۂ�
	float oSpeed = 0;//
	int randRot = 0;//�p�x�����_��
	int stageNum = 0;//�X�e�[�W�ԍ�
	bool onGround = true;
};

