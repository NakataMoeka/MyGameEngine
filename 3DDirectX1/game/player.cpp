#include "player.h"
#include"input.h"
Player::Player()
{
}
void Player::Initialize()
{
	model = model->Create("car", false);
	playerObj = Object3d::Create(model);
	//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる
	playerObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

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
