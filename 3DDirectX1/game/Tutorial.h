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
	void Updata();
	void Draw();
private:
	std::array < Sprite*, 6> TutorialSprite = {};
};

