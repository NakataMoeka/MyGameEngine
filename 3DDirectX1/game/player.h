#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
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
	void Update();
	void OnCollision();
	void Draw();
	void DrawSprite();

	//Getter
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	XMVECTOR GetPlayerAngle() { return playerAngle; }
	float GetCameraAngle() { return cameraAngle; }
	Sphere GetSphere() { return sphere; }
	OBB GetOBB() { return obb; }
	Object3d* GetObject() { return SphereObj; }
	XMFLOAT3 SetSphereSize(XMFLOAT3 sphereSize) { return this->sphereSize = sphereSize; }
	float SetSpherePos(float spherePos) { return this->spherePos.y = spherePos; }
	XMFLOAT3 SetPlayerPos(XMFLOAT3 playerPos) { return this->playerPos = playerPos; }

	float GetTsize() { return Tsize; }
	float SetTsize(float tsize) { return this->Tsize = tsize; }
	bool GetOnGround() { return onGround; }
	bool SetColFlag(bool ColFlag,int i) { return this->colFlag[i] = ColFlag; }
private://プレイヤーの動き系
	void Move();//移動
	void Ball();//ボール関係
	void Jump();//ジャンプ
	void Dash();//ダッシュ
private://変数
	//プレイヤーのモデル
	Object3d* playerObj=nullptr;
	Model* model=nullptr;
	//球のモデル
	Object3d* SphereObj=nullptr;
	Model* model2=nullptr;
	//集中線
	Sprite* dashSprite=nullptr;
	//サイズ表示の円
	Sprite* sizeSprite=nullptr;
	//地球
	Sprite* earthSprite = nullptr;
	//位置サイズ角度
	XMFLOAT3 playerPos = { 0,0,0 };
	XMFLOAT3 spherePos = { 0,0,0 };
	XMVECTOR playerAngle = { 0,0,0,0 };
	XMVECTOR sphereAngle = { 0,0,0,0 };
	XMFLOAT3 sphereSize = { 1,1,1 };
	float cameraAngle = 0;
	
	Sphere sphere;//当たり判定のやつ

	OBB obb;//バグが起こっているため使わない
	float Tsize = 1;//球のサイズ(左上に表示されているやつ)
	float r = 3;

	//ダッシュ関連の変数
	bool dashFlag = false;
	float dashSpeed = 2.0f;
	int dashCoolTime = 0;
	const int dashCoolTimeMax = 20;
	int dashTime = 0;
	const int dashTimeMax = 20;
	float fade = 1;
	//ジャンプ＆地面との当たり判定系
	bool JumpFlag = false;
	bool onGround = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV;
	
	bool onGround2 = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV2;
	
	static const int OBJNumber = 10;
	
	bool colFlag[OBJNumber];
};