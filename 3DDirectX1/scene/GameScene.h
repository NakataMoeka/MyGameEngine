#pragma once


#include"SafeDelete.h"
#include <DirectXMath.h>
#include"Sprite.h"
#include"Audio.h"
#include"DXCommon.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "Camera.h"
#include "FbxObject.h"
#include"LightGroup.h"
#include"player.h"
#include"GameObjects.h"
#include"stageObject.h"
#include"Collision.h"
#include<vector>
#include<array>
#include"Timer.h"
#include"Pose.h"
#include"Tutorial.h"
#include"SphereSize.h"
#include"start.h"
#include"BaseScene.h"
class CollisionManager;
class TouchableObject;
class GameScene :public BaseScene
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // メンバ関数

	GameScene();

	~GameScene();
	/// <summary>
	/// 起動したら一回しか行われない初期化(モデルの読み込みなど)
	/// </summary>
	void Initialize()override;
	/// <summary>
	/// OBJ用の初期化
	/// </summary>
	void InitTH()override;
	/// <summary>
	/// そのシーンを通るたびに何度も行われる初期化(位置など)
	/// </summary>
	void Init()override;
	/// <summary>
	/// ステージ初期化
	/// </summary>
	/// <param name="stageNum">ステージ番号</param>
	void InitStageNum(int stageNum)override;
	/// <summary>
	/// 繰り返し処理
	/// </summary>
	void Update()override;
	/// <summary>
	/// 背景画像描画
	/// </summary>
	void DrawBG()override;
	/// <summary>
	/// オブジェクト描画
	/// </summary>
	void Draw()override;
	/// <summary>
	/// 前景画像描画
	/// </summary>
	void DrawFront()override;

	void Finalize()override;
	/// <summary>
	/// パーティクル
	/// </summary>
	void CreateParticles();

	bool GetSCangeFlag()override;
	bool GetEndFlag() { return endFlag; }
	bool GetNum() { return endNum; };
	bool GetTitleFlag();
	int SetStageNum(int stageNum) { return this->stageNum = stageNum; }
	bool GetTSFlag() { return TSFlag; }

private: // メンバ変数
	void ObjCollision(int i, int j);
	//ステージobjの初期位置等設定
	void SOInit();
	//ステージobjの読み込み
	void SOCreate();
	Audio* audio = Audio::GetInstance();

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	SoundData sound4 = {};

	std::unique_ptr < Camera> camera = nullptr;
	std::unique_ptr < ParticleManager> particleMan = nullptr;

	std::unique_ptr<Sprite> sprite = nullptr;
	std::unique_ptr<Sprite> tmSprite = nullptr;//目標達成時にアナウンスする用
	std::unique_ptr<Sprite> btSprite = nullptr;//ぶつかった時用
	std::unique_ptr < LightGroup> lightGroup = nullptr;

	CollisionManager* colMan = nullptr;

	std::unique_ptr < Player> player = nullptr;
	std::unique_ptr < GameObjects> gameObjects = nullptr;
	std::array < std::unique_ptr < StageObject>, 9> stageObj = {};

	std::unique_ptr < Timer> timer = nullptr;
	std::unique_ptr < Pose> pose = nullptr;
	std::unique_ptr < SphereSize> sphereSize = nullptr;
	std::unique_ptr < Tutorial> tutorial = nullptr;
	std::unique_ptr < start> st = nullptr;
	std::unique_ptr < Model> modelSkydome = nullptr;
	std::unique_ptr <Object3d> skydome = nullptr;
	int HitCount = 0;
	//サイズ関係
	float Tsize = 1;
	int Tsize2 = 1;
	int TCount = 0;
	bool TFlag = false;
	float radius = 3.0f;

	XMFLOAT3 distance = { 0,2.0f,10.0f };//プレイヤーとカメラの距離
	XMFLOAT3 distanceNum = { 0,0,0 };
	XMFLOAT3 distanceC = { 0,20.0f,20.0f };//カメラの位置

	float SZV = 3;//sphereとの
	float SY = 3;//SphereのY軸高さ
	float OY = 0;//objの当たり判定用y足す変数

	bool endFlag = false;
	bool endNum;

	//ステージナンバー
	int stageNum = 0;
	bool TSFlag;

	int GoalCount = 0;//目標サイズ
	XMFLOAT3 Ssize = { 1,1,1 };//球のサイズ
	int audioCount = 0;

	//まだくっつかないobjに当たった時に音をだしたりエフェクトを出したり
	//する時に1回のみやるための変数
	int HitCC;
};