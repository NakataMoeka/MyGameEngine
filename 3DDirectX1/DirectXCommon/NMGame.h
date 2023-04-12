#pragma once
#include"Framework.h"
#include "SceneManager.h"
class SceneManager;
class NMGame :public Framework
{
public:
	// ‰Šú‰»
	void Initialize() override;
	//I—¹
	void Finalize() override;
	// –ˆƒtƒŒ[ƒ€ˆ—
	void Update() override;
	// •`‰æ
	void Draw() override;
private:
	SceneManager* gameScene = nullptr;

};

