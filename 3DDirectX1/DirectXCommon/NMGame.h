#pragma once
#include"Framework.h"
#include "SceneManager.h"
class SceneManager;
class NMGame :public Framework
{
public:
	// 初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	// 毎フレーム処理
	void Update() override;
	// 描画
	void Draw() override;
private:
	SceneManager* gameScene = nullptr;

};

