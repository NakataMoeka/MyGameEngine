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
#include"GameObject.h"
#include"stageObject.h"
#include"Collision.h"
#include<vector>
#include<array>
#include"Timer.h"
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
	//OBJ等初期化用()
	void InitTH();
	//そのシーンを通るたびに何度も行われる初期化(位置など)
	void Init();
	//ステージ初期化
	void InitStageNum(int stageNum);
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
	bool SetClearFlag(bool clearFlag) { return this->clearFlag = clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
	bool GetBFlag() { return Bflag; }
	bool GetTitleFlag() { return TitleFlag; }
	int SetStageNum(int stageNum) { return this->stageNum = stageNum; }
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

	Sprite* PoseSprite = nullptr;
	Sprite* TitleBackSprite = nullptr;
	Sprite* BackSprite = nullptr;
	Sprite* InfoSprite = nullptr;
	Sprite* PBSprite = nullptr;
	//サイズ表示用のやつ
	std::array < Sprite*, 4>Number = {};//数字。4つなのはcmとmの一の位と十の位があるため。
	Sprite* Meters = nullptr;
	Sprite* Centimeter = nullptr;

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

	Player* player = nullptr;
	GameObject* gameObject = nullptr;
	StageObject* stageObj = nullptr;

	Timer* timer = nullptr;

	const int debugTextTexNumber = 0;


	static const int OBJNumber = 100;//OBJの最大数を記載

	int HitCount = 0;


	//サイズ
	float Tsize = 1;
	int Tsize2 = 1;
	int TCount = 0;
	bool TFlag = false;

	float distance = 20.0f;//プレイヤーとカメラの距離



	bool clearFlag = false;
	bool overFlag = false;

	bool Bflag = false;//ブラーを掛けるか否か

	bool PoseFlag = false;//ゲーム中断フラグ
	bool TitleFlag = false;//タイトルに戻るフラグ
	int PS = 0;//ポーズ時のやつ

	//ステージナンバー
	int stageNum = 0;
};