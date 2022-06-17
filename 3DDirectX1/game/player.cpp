#include "player.h"
#include"input.h"
Player::Player()
{
}
void Player::Initialize()
{
	playerObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	model = model->Create("car", false);
	playerObj = Object3d::Create(model);
}


void Player::Move()
{
	if (HP != 0) {

		if (power > 0) {

			if (Input::GetInstance()->PushKey(DIK_D))
			{
				playerPos.x += 0.1;

			}
			if (Input::GetInstance()->PushKey(DIK_A))
			{
				playerPos.x -= 0.1;

			}
		}
	}

	playerObj->SetPosition(playerPos);
	playerObj->Update();
}

void Player::Draw()
{
	playerObj->Draw();
}
