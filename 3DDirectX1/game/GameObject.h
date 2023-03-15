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

	//オブジェクト配列
	std::vector<object*>oData;//ブロック
	std::vector<object*>oData2;//車
	std::vector<object*>oData3;//クマ
	std::vector<object*>oData4;//ロボット
	std::vector<object*>oData5;//カード
public:
	

	GameObject();
	~GameObject();
	void Initialize();
	void Init();
	void stageInit(int stageNum);
	void Update();
	void RC();//コライダー消すやつ
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
private://Update()にまとめるもの
	void Col(Object3d* object, XMFLOAT3 pos);
private://変数

	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ配置用(予定)
	static const int OBJNumber = 70;//objの最大数(多いやつ)
	static const int OBJNumber2 = 30;//objの最大数(少なめのやつ)
	static const int OBJType = 2;
	//オブジェクト
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


	std::array < Sphere, OBJNumber> cSphere;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere2;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere3;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere4;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere5;//当たり判定のやつ
	float r = 3;//
	//サイズ角度位置
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
	bool moveFlag = true;//動いているか否か
	float oSpeed = 0;//
	int randRot = 0;//角度ランダム
	int stageNum = 0;//ステージ番号
	bool onGround = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV = {};
};

