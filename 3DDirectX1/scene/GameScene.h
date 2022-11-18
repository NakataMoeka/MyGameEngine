#pragma once


#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "Camera.h"
#include "FbxObject.h"
#include"LightGroup.h"
#include"player.h"
#include"GameObject.h"
#include"stageObject.h"
#include"Collision.h"
#include<vector>
class CollisionManager;
class TouchableObject;
class GameScene
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
	//起動したら一回しか行われない初期化(モデルの読み込みなど)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init();
	//繰り返し処理
	void Update();
	//背景画像描画
	void DrawBG();
	//オブジェクト描画
	void Draw();
	//前景画像描画
	void DrawFront();
	//パーティクル
	void CreateParticles();
	bool GetClearFlag() { return clearFlag; }
	bool GetOverFlag() { return overFlag; }
	bool SetClearFlag(bool clearFlag) { return this->clearFlag=clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
	bool GetBFlag() { return Bflag; }
	bool GetTitleFlag() { return TitleFlag; }
private: // メンバ変数
	DXCommon* dxCommon = nullptr;


	Audio* audio = nullptr;

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	SoundData sound4 = {};
	Camera* camera = nullptr;
	ParticleManager* particleMan = nullptr;
	
	Sprite* sprite = nullptr;
	Sprite* timeSprite = nullptr;//円
	Sprite* timeSprite2 = nullptr;//バー
	Sprite* PoseSprite = nullptr;
	Sprite* TitleBackSprite = nullptr;
	Sprite* BackSprite = nullptr;
	Sprite* InfoSprite = nullptr;
	Sprite* PBSprite = nullptr;

	Object3d* object3d = nullptr;
	Model* model = nullptr;

	FbxObject3d* object3d2 = nullptr;
	FbxModel* model2 = nullptr;

	Object3d* object3d3 = nullptr;
	Model* model3 = nullptr;

	TouchableObject* object3d4 = nullptr;
	Model* model4 = nullptr;

	LightGroup* lightGroup = nullptr;

	CollisionManager* colMan = nullptr;

	Player* player=nullptr;
	GameObject* gameObject=nullptr;
	StageObject* stageObj=nullptr;

	const int debugTextTexNumber = 0;


	static const int OBJNumber = 100;//OBJの最大数を記載
	
	int HitCount=0;

	
	//サイズ
	float Tsize = 1;
	int Tsize2 = 1;
	int TCount = 0;
	bool TFlag = false;

	float distance = 20.0f;//プレイヤーとカメラの距離
	
	//タイマー系
	float TimeRot = 0;
	int TimeCount = 0;
	float clearTimer = 18000;//1800/60が30秒
	int clearTimer2 = 0;
	bool clearFlag = false;
	bool overFlag = false;
	float sphereSize = 1;
	float spherePosY = 3;

	bool Bflag = false;//ブラーを掛けるか否か
	
	bool PoseFlag = false;//ゲーム中断フラグ
	bool TitleFlag = false;//タイトルに戻るフラグ
	int PS = 0;//ポーズ時のやつ
};