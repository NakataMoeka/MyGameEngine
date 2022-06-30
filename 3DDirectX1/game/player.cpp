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
			radWS = XMConvertToRadians(playerAngle.y+90.0f);
			XMVECTOR move = { 0,0,0.1f,0 };
			XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.y));
			move = XMVector3TransformNormal(move, matRot);
			if (Input::GetInstance()->PushKey(DIK_E))
			{
				playerAngle.y += 1;

			}
			else if (Input::GetInstance()->PushKey(DIK_Q))
			{
				playerAngle.y-= 1;

			}
			if (Input::GetInstance()->PushKey(DIK_W))
			{
				playerPos.x += move.m128_f32[0];
				playerPos.z += move.m128_f32[2];
			}
			else if (Input::GetInstance()->PushKey(DIK_S))
			{
				playerPos.x -= move.m128_f32[0];
				playerPos.z -= move.m128_f32[2];
			}



	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerAngle);
	playerObj->Update();
}

void Player::Draw()
{
	playerObj->Draw();
}
