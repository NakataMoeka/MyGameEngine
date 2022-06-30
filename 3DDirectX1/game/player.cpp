#include "player.h"
#include"input.h"
using namespace DirectX;
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
			if (Input::GetInstance()->PushKey(DIK_E))
			{
				playerAngle.y += 1;

			}
			else if (Input::GetInstance()->PushKey(DIK_Q))
			{
				playerAngle.y-= 1;

			}
			if (Input::GetInstance()->PushKey(DIK_D))
			{
				playerPos.x += 0.1;

			}
			else if (Input::GetInstance()->PushKey(DIK_A))
			{
				playerPos.x -= 0.1;

			}
			else if (Input::GetInstance()->PushKey(DIK_W))
			{
				playerPos.z += 0.1;

			}
			else if (Input::GetInstance()->PushKey(DIK_S))
			{
				playerPos.z -= 0.1;

			}
			//if (Input::GetInstance()->ConLeftInput())
			//{
			//	playerAngle.y = XMConvertToDegrees(atan2(sinRad, cosRad)) - 90;
			//	rad = Input::GetInstance()->GetLeftAngle();
			//	sinRad = sinf(-rad);
			//	cosRad = cosf(rad);
			//		
			//	//	playerPos.x += 0.1*sinRad;
			//	//	playerPos.z += 0.1*cosRad;
			//		
			//}
	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerAngle);
	playerObj->Update();
}

void Player::Draw()
{
	playerObj->Draw();
}
