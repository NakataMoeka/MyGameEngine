#pragma once
#include"Sprite.h"
#include<array>
/// <summary>
/// �`���[�g���A���N���X
/// </summary>
class Tutorial
{
public:
	void Initialize();
	void Init();
	void Update();
	void Draw();
private:
	std::array < Sprite*, 7> TutorialSprite = {};
};

