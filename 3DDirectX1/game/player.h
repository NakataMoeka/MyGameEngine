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
	//
	enum STATE{
		JUMP,
		WALK,
		STAND
	};
public:
	Player();
	~Player();
	void Initialize();//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void stageInit(int stageNo);//ステージが変わるごとの初期化
	void Update();//アプデ
	void Draw();//モデルの描画
	void DrawSprite();//画像の描画
	void RC();//コライダーを消すやつ

	//ゲッター
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	XMFLOAT3 GetPlayerAngle() { return playerAngle; }
	float GetRadius() { return radius; }
	Sphere GetSphere() { return sphere; }
	int GetTWCount() { return TWCount; }
	std::unique_ptr < Object3d>& GetObject3d() { return SphereObj; }
	//セッター
	XMFLOAT3 SetSphereSize(XMFLOAT3 sphereSize) { return this->sphereSize = sphereSize; }
	float SetSpherePos(float spherePos) { return this->spherePos.y = spherePos; }
	XMFLOAT3 SetPlayerPos(XMFLOAT3 playerPos) { return this->playerPos = playerPos; }
	bool SetWalkFlag(bool walkFlag) { return this->walkFlag = walkFlag; }
	bool SetPFlag(bool pFlag) { return this->pFlag = pFlag; }
	float SetSZV(float szv) { return this->sphereZV = szv; }
	float SetSY(float sy) { return this->sphereY = sy; }
	float SetRadius(float r) { return this->radius = r; }

private://Update()にまとめるもの
	void Move();//移動
	XMFLOAT3 vec(XMFLOAT3 pos, XMVECTOR vec);
	XMVECTOR vecTrans(XMVECTOR vec, float rot, float speed,float xyz);
	void Ball();//ボール関係
	void Jump();//ジャンプ
	void terrainCol();//地形との判定
	void Dash();//ダッシュ
private://変数
	//プレイヤーのモデル
	std::unique_ptr < FbxObject3d> playerObj = nullptr;
	std::unique_ptr < FbxModel> model = nullptr;
	//球のモデル
	std::unique_ptr < Object3d> SphereObj = nullptr;
	std::unique_ptr < Model> model2 = nullptr;
	//集中線
	std::unique_ptr<Sprite> dashSprite = nullptr;
	STATE state_;
	//位置サイズ角度
	XMFLOAT3 playerPos = { 0,0,0 };
	XMFLOAT3 spherePos = { 0,0,0 };
	XMFLOAT3 playerAngle = { 0,0,0 };
	XMVECTOR sphereAngle = { 0,0,0,0 };
	XMFLOAT3 sphereSize = { 1,1,1 };

	Sphere sphere;//当たり判定のやつ
	float r = 2;
	float radius = 3.0f;
	//移動
	XMVECTOR moveUD = { 0,0,0,0 };//前後移動用ベクトル
	XMVECTOR moveLR = { 0,0,0,0 };//左右移動用ベクトル
	XMVECTOR moveAngle = { 0,0,0,0 };//角度ベクトル
	float speedUD = 0;//前後移動スピード
	float speedLR = 0;//左右移動スピード
	float sphereZV = 0;//球との距離z軸
	float sphereY = 0;//球y軸高さ
	//ダッシュ関連の変数
	bool dashFlag = false;
	float dash = 1.5f;
	int dashCoolTime = 0;//クールタイム
	const int dashCoolTimeMax = 20;//クールタイム最大値
	float fade = 1;
	//ジャンプ＆地面との当たり判定系
	bool JumpFlag = false;
	bool onGround = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV = {};
	bool pFlag = false;//ポーズ用のフラグ
	//チュートリアル関連
	bool walkFlag = true;//チュートリアル用の歩けるか判定フラグ
	int TWCount = 0;//チュートリアルの移動カウント
	int stageNum = 0;//ステージ数
};