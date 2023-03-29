#pragma once
#include"Sprite.h"
#include"Audio.h"
#include <memory>
/// <summary>
/// ポーズ機能(ゲームシーンからの移植)
/// </summary>
class Pose
{
public:
	void Initialize(Audio* audio);//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void Update();//アプデ
	void Draw();//モデルの描画
	bool GetPFlag() { return PoseFlag; }
	bool GetTFlag() { return TitleFlag; }
	bool GetJFlag() { return jFlag; }
private:

	Audio* audio = nullptr;
	SoundData sound1 = {};
	SoundData sound2 = {};
	std::unique_ptr<Sprite> PoseSprite = nullptr;
	std::unique_ptr<Sprite> TitleBackSprite = nullptr;
	std::unique_ptr<Sprite> BackSprite = nullptr;
	std::unique_ptr<Sprite> InfoSprite = nullptr;
	std::unique_ptr<Sprite> PBSprite = nullptr;
	bool PoseFlag = false;//ゲーム中断フラグ
	bool TitleFlag = false;//タイトルに戻るフラグ
	int PS = 0;//ポーズ時のやつ
	bool jFlag = false;//ジャンプ
};

