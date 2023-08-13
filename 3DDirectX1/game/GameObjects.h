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
class GameObjects
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
	std::vector<object*>oData;//�u���b�N,�Q�[���@
	std::vector<object*>oData2;//��,�R�}
	std::vector<object*>oData3;//�N�},�����̃R�}
	std::vector<object*>oData4;//���{�b�g,�����
	std::vector<object*>oData5;//�J�[�h,�ܒ�
public:
	

	GameObjects();
	~GameObjects();
	void Initialize();//1�x�̂ݏ�����
	void Init();//���x������
	void stageInit(int stageNum);//�X�e�[�W������
	
	void Update();
	void RC();//�R���C�_�[�������
	void Draw();
	//GetterSetter
	Sphere GetCSphere(int i, int j);
	XMFLOAT3 GetSize(int i) { return size[i]; }
	int GetOBJCount(int j);
	float GetMat();
	Object3d* GetObject3d(int i, int j);
	bool GetHIT(int i, int j);
	bool SetHIT(int i, int j, bool Hit);
	float GetOSize(int i, int j);
	XMFLOAT3 GetOPos(int i, int j);
	float SetY(float y) { return this->oy = y; }
private://�֐�
	static const int OBJNumber = 100;//obj�̍ő吔(�������)
	static const int OBJNumber2 = 30;//obj�̍ő吔(���Ȃ߂̂��)
	static const int OBJType = 2;
	/// <summary>
	/// csv����obj�̈ʒu�̓ǂݍ���
	/// </summary>
	/// <param name="oData">vector�z��</param>/// <param name="stageNum">�X�e�[�W�̐�</param>
	/// <param name="y">����</param>/// <param name="size">�傫��</param>
	/// <param name="i">��</param>/// <param name="j">�c</param>
	void InitNum(std::vector<object*>oData, int stageNum, float y, float size, size_t i, size_t j);
	void InitUpd(std::array < Object3d*, OBJNumber> obj, int i, std::vector<object*>oData);
	void RCC(std::array < Object3d*, OBJNumber>obj,int i);//�R���C�_�[�폜���ʂ̏���
	//�A�b�v�f�[�g���ʂ̏���
	void Upd(std::array < Object3d*, OBJNumber> obj, int i, std::vector<object*>oData,bool move);
private://�ϐ�

	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ�z�u�p(�\��)

	int  num = 0;
	//�I�u�W�F�N�g
	std::array < Object3d*, OBJNumber> cube = {};
	std::array < Object3d*, OBJNumber> moveObj = {};
	std::array < Object3d*, OBJNumber> Bear = {};
	std::array < Object3d*, OBJNumber> Robot = {};
	std::array < Object3d*, OBJNumber> Card = {};

	std::array < Object3d*, OBJNumber> Kendama = {};  
	std::array < Object3d*, OBJNumber> Koma = {};
	std::array < Object3d*, OBJNumber> Shogi = {};
	std::array < Object3d*, OBJNumber> Turu = {};
	std::array < Object3d*, OBJNumber> Game = {};

	std::unique_ptr<Model> modelCube = nullptr;
	std::unique_ptr<Model> modelMove = nullptr;
	std::unique_ptr<Model> modelBear = nullptr;
	std::unique_ptr<Model> modelRobot = nullptr;
	std::unique_ptr<Model> modelCard = nullptr;
	std::unique_ptr<Model> modelPencil = nullptr;

	std::unique_ptr<Model> modelKendama = nullptr;
	std::unique_ptr<Model> modelKoma = nullptr;
	std::unique_ptr<Model> modelShogi = nullptr;
	std::unique_ptr<Model> modelTuru = nullptr;
	std::unique_ptr<Model> modelCont = nullptr;
	std::unique_ptr<Model> modelGame = nullptr;
	std::array < Sphere, OBJNumber> cSphere;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere2;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere3;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere4;//�����蔻��̂��
	std::array < Sphere, OBJNumber> cSphere5;//�����蔻��̂��
	float r = 3;//
	float oy = 0;
	//�T�C�Y�p�x�ʒu
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
	int randRot = 0;//�p�x�����_��
	int stageNum = 0;//�X�e�[�W�ԍ�
};

