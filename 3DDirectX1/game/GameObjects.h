#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
#include"LoadCSV.h"
#include<array>
#include"ObjectHelper.h"
#include"GObject.h"
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
	//�A�b�v�f�[�g���ʂ̏���
private://�ϐ�

	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ�z�u�p(�\��)

	int  num = 0;
	//�I�u�W�F�N�g
	std::array < GObject*, OBJNumber> cube = {};
	std::array < GObject*, OBJNumber> moveObj = {};
	std::array < GObject*, OBJNumber> Bear = {};
	std::array < GObject*, OBJNumber> Robot = {};
	std::array < GObject*, OBJNumber> Card = {};
	std::array < GObject*, OBJNumber> Kendama = {};
	std::array < GObject*, OBJNumber> Koma = {};
	std::array < GObject*, OBJNumber> Shogi = {};
	std::array < GObject*, OBJNumber> Turu = {};
	std::array < GObject*, OBJNumber> Game = {};

	Model* modelCube = nullptr;
	Model* modelMove = nullptr;
	Model* modelBear = nullptr;
	Model* modelRobot = nullptr;
	Model* modelCard = nullptr;
	Model* modelKendama = nullptr;
	Model* modelKoma = nullptr;
	Model* modelShogi = nullptr;
	Model* modelTuru = nullptr;
	Model* modelGame = nullptr;

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

