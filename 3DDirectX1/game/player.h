#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
#include "FbxObject.h"
#include<array>
#include <memory>
/// <summary>
/// プレイヤー関連のクラス
/// </summary>
class Player
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
public:
	Player();
	~Player();
	void Initialize();//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void stageInit(int stageNo);
	void Update();//アプデ
	void Draw();//モデルの描画
	void DrawSprite();//画像の描画
	void RC();//コライダーを消すやつ

	//GetterSetter
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	XMFLOAT3 GetPlayerAngle() { return playerAngle; }
	float GetRadius() { return radius; }
	Sphere GetSphere() { return sphere; }
	Object3d* GetObject3d() { return SphereObj; }
	XMFLOAT3 SetSphereSize(XMFLOAT3 sphereSize) { return this->sphereSize = sphereSize; }
	float SetSpherePos(float spherePos) { return this->spherePos.y = spherePos; }
	XMFLOAT3 SetPlayerPos(XMFLOAT3 playerPos) { return this->playerPos = playerPos; }
	float GetTsize() { return Tsize; }
	float SetTsize(float tsize) { return this->Tsize = tsize; }
	bool SetWalkFlag(bool walkFlag) { return this->walkFlag = walkFlag; }
	bool SetPFlag(bool pFlag) { return this->pFlag = pFlag; }

	float SetSZV(float szv) { return this->sphereZV = szv; }
	float SetSY(float sy) { return this->sphereY = sy; }
	float SetRadius(float r) { return this->radius = r; }
	int GetTWCount() { return TWCount; }
private://Update()にまとめるもの
	void Move();//移動
	XMFLOAT3 vec(XMFLOAT3 pos, XMVECTOR vec);
	void Ball();//ボール関係
	void Jump();//ジャンプ
	void Dash();//ダッシュ
private://変数
	//プレイヤーのモデル
	FbxObject3d* playerObj = nullptr;
	FbxModel* model = nullptr;
	//球のモデル
	Object3d* SphereObj = nullptr;
	Model* model2 = nullptr;
	Object3d* SphereObj2 = nullptr;
	Model* model3 = nullptr;
	//集中線
	std::unique_ptr<Sprite> dashSprite = nullptr;


	//位置サイズ角度
	XMFLOAT3 playerPos = { 0,0,0 };
	XMFLOAT3 spherePos = { 0,0,0 };
	XMFLOAT3 playerAngle = { 0,0,0 };
	XMVECTOR sphereAngle = { 0,0,0,0 };
	XMFLOAT3 sphereSize = { 1,1,1 };

	Sphere sphere;//当たり判定のやつ

	float Tsize = 1;//球のサイズ(左上に表示されているやつ)
	float r = 3;
	float radius = 3.0f;
	//移動
	float speedUD = 0;
	float speedLR = 0;
	bool moveUDFlag = false;
	bool moveLRFlag = false;
	//球のz軸
	float sphereZV = 0;//球との距離z軸
	float sphereY = 0;//球y軸高さ
	//ダッシュ関連の変数
	bool dashFlag = false;
	float dash = 1.5f;
	float dashSpeed = 2.0f;
	int dashCoolTime = 0;
	const int dashCoolTimeMax = 20;
	int dashTime = 0;
	//const int dashTimeMax = 20;
	float fade = 1;
	//ジャンプ＆地面との当たり判定系
	bool JumpFlag = false;
	bool onGround = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV = {};

	bool onGround2 = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV2 = {};

	static const int OBJNumber = 100;

	//bool colFlag[OBJNumber][OBJNumber] = {};

	float PlayerWalkCount = 0;
	float CountWalk = 0;
	bool pFlag = false;//ポーズ用のフラグ
	bool walkFlag = true;//チュートリアル用の歩けるか判定フラグ
	int TWCount = 0;//チュートリアルの移動カウント
	int stageNum = 0;
};