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
class GameObjects
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
	std::vector<object*>oData;//ブロック,ゲーム機
	std::vector<object*>oData2;//車,コマ
	std::vector<object*>oData3;//クマ,将棋のコマ
	std::vector<object*>oData4;//ロボット,けん玉
	std::vector<object*>oData5;//カード,折鶴
public:
	

	GameObjects();
	~GameObjects();
	void Initialize();//1度のみ初期化
	void Init();//何度もする
	void stageInit(int stageNum);//ステージ初期化
	
	void Update();
	void RC();//コライダー消すやつ
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
private://関数
	static const int OBJNumber = 100;//objの最大数(多いやつ)
	static const int OBJNumber2 = 30;//objの最大数(少なめのやつ)
	static const int OBJType = 2;
	/// <summary>
	/// csvからobjの位置の読み込み
	/// </summary>
	/// <param name="oData">vector配列</param>/// <param name="stageNum">ステージの数</param>
	/// <param name="y">高さ</param>/// <param name="size">大きさ</param>
	/// <param name="i">横</param>/// <param name="j">縦</param>
	void InitNum(std::vector<object*>oData, int stageNum, float y, float size, size_t i, size_t j);
	void InitUpd(std::array < Object3d*, OBJNumber> obj, int i, std::vector<object*>oData);
	void RCC(std::array < Object3d*, OBJNumber>obj,int i);//コライダー削除共通の処理
	//アップデート共通の処理
	void Upd(std::array < Object3d*, OBJNumber> obj, int i, std::vector<object*>oData,bool move);
private://変数

	int	spawnMap[MAP_HEIGHT][MAP_WIDTH];//OBJ配置用(予定)

	int  num = 0;
	//オブジェクト
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
	std::array < Sphere, OBJNumber> cSphere;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere2;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere3;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere4;//当たり判定のやつ
	std::array < Sphere, OBJNumber> cSphere5;//当たり判定のやつ
	float r = 3;//
	float oy = 0;
	//サイズ角度位置
	XMFLOAT3 pos{ 10,2,0 };
	XMFLOAT3 size[OBJType] = { {3,3,3},{5,5,5} };
	XMVECTOR rota = { 0,0,0,0 };
	int randRot = 0;//角度ランダム
	int stageNum = 0;//ステージ番号
};

