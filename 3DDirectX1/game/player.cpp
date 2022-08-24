#include "player.h"
#include"input.h"
#include <cassert>
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
using namespace DirectX;
Player::Player()
{
}
Player::~Player()
{
}
void Player::Initialize()
{
	model = Model::Create("car", false);
	playerObj = Object3d::Create(model);
	model2 = Model::Create("bullet", true);
	SphereObj = Object3d::Create(model2);
	//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる
	playerObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	SphereObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Sprite::LoadTexture(2, L"Resources/dash.png");

	dashSprite = Sprite::CreateSprite(2, { 0,0 });



}

void Player::Init()
{
	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);
	obb.m_NormaDirect[0] = { SphereObj->GetMatRot().r[0].m128_f32[0],SphereObj->GetMatRot().r[0].m128_f32[1] ,SphereObj->GetMatRot().r[0].m128_f32[2] };
	obb.m_NormaDirect[1] = { SphereObj->GetMatRot().r[1].m128_f32[0],SphereObj->GetMatRot().r[1].m128_f32[1] ,SphereObj->GetMatRot().r[1].m128_f32[2] };
	obb.m_NormaDirect[2] = { SphereObj->GetMatRot().r[2].m128_f32[0],SphereObj->GetMatRot().r[2].m128_f32[1] ,SphereObj->GetMatRot().r[2].m128_f32[2] };
	obb.m_fLength[0] = 1;
	obb.m_fLength[1] = 1;
	obb.m_fLength[2] = 1;
	obb.m_Pos = { spherePos.x,spherePos.y, spherePos.z };
	//playerPos={ 0,-0.8,0 };
	playerPos.y = -2;
	//SphereObj->collider->SetAttribute(COLLISION_ATTR_ALLIES);
		// コライダーの追加
	float radius = 3.0f;
	SphereObj->SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));

	playerObj->Quaternion();
	SphereObj->Quaternion();
	SphereObj->Update();
	playerObj->Update();

}


void Player::Move()
{
	XMVECTOR moveUD = { 0,0,0.5,0 };//前後方向用の移動ベクトル
	XMVECTOR moveLR = { 0.5,0,0,0 };//左右方向の移動用ベクトル
	XMVECTOR moveAngle = { 0,1,0,0 };//角度のベクトル
	XMVECTOR moveAngleX = { 10,0,0,0 };//角度のベクトル
	XMVECTOR moveAngleZ = { 0,0,10,0 };//角度のベクトル
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.m128_f32[1]));//y 軸を中心に回転するマトリックスを作成
	moveUD = XMVector3TransformNormal(moveUD, matRot);
	moveLR = XMVector3TransformNormal(moveLR, matRot);
	moveAngle = XMVector3TransformNormal(moveAngle, matRot);
	if (Input::GetInstance()->PushKey(DIK_RIGHTARROW))
	{
		sphereAngle.m128_f32[1] += moveAngle.m128_f32[1];
		playerAngle.m128_f32[1] += moveAngle.m128_f32[1];

	}
	else if (Input::GetInstance()->PushKey(DIK_LEFTARROW))
	{
		sphereAngle.m128_f32[1] -= moveAngle.m128_f32[1];
		playerAngle.m128_f32[1] -= moveAngle.m128_f32[1];
	}
	if (Input::GetInstance()->PushKey(DIK_W))
	{
		playerPos.x += moveUD.m128_f32[0];
		playerPos.z += moveUD.m128_f32[2];
		sphereAngle.m128_f32[0] += 10;
	}
	else if (Input::GetInstance()->PushKey(DIK_S))
	{
		playerPos.x -= moveUD.m128_f32[0];
		playerPos.z -= moveUD.m128_f32[2];
		sphereAngle.m128_f32[0] -= 10;
	}
	else if (Input::GetInstance()->PushKey(DIK_D))
	{
		playerPos.x += moveLR.m128_f32[0];
		playerPos.z += moveLR.m128_f32[2];
		sphereAngle.m128_f32[2] += 10;
	}
	else if (Input::GetInstance()->PushKey(DIK_A))
	{
		playerPos.x -= moveLR.m128_f32[0];
		playerPos.z -= moveLR.m128_f32[2];
		sphereAngle.m128_f32[2] -= 10;
	}

	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);
	obb.m_NormaDirect[0] = { SphereObj->GetMatRot().r[0].m128_f32[0],SphereObj->GetMatRot().r[0].m128_f32[1] ,SphereObj->GetMatRot().r[0].m128_f32[2] };
	obb.m_NormaDirect[1] = { SphereObj->GetMatRot().r[1].m128_f32[0],SphereObj->GetMatRot().r[1].m128_f32[1] ,SphereObj->GetMatRot().r[1].m128_f32[2] };
	obb.m_NormaDirect[2] = { SphereObj->GetMatRot().r[2].m128_f32[0],SphereObj->GetMatRot().r[2].m128_f32[1] ,SphereObj->GetMatRot().r[2].m128_f32[2] };
	obb.m_fLength[0] = 1;
	obb.m_fLength[1] = 1;
	obb.m_fLength[2] = 1;
	obb.m_Pos = { spherePos.x,spherePos.y, spherePos.z };

}

void Player::Ball()
{
#pragma region カメラ追従とほぼ同じ
	XMVECTOR v0 = { 0,0,10,0 };
	//angleラジアンだけy軸まわりに回転。半径は-100
	XMMATRIX rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(sphereAngle.m128_f32[1]));
	//rotM *= XMMatrixRotationX(XMConvertToRadians(sphereAngle.m128_f32[0]));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR bossTarget = {playerPos.x,playerPos.y,playerPos.z };
	XMVECTOR v3 = bossTarget + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	//target = { bossTarget.m128_f32[0], bossTarget.m128_f32[1], bossTarget.m128_f32[2] };
	spherePos.x = f.x;
	spherePos.z = f.z;
#pragma endregion


}

void Player::Jump()
{

	if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW) && JumpFlag == false)
	{
		JumpFlag = true;
	}
	if (JumpFlag == true) {
		if (playerPos.y < 40)
		{
			playerPos.y += jspeed;
			cameraAngle += jspeed;
			jspeed += g;
		}
		if (playerPos.y >= 40)
		{
			jspeed = 0;
			gFlag = true;
		}
	}
	if (gFlag == true) {
		JumpFlag = false;
		if (playerPos.y > -2)
		{
			playerPos.y += jspeed;
			cameraAngle += jspeed;
			jspeed -= g;
		}
		if (playerPos.y <= -2)
		{
			gFlag = false;
			jspeed = 0;
			playerPos.y = -2;
			cameraAngle = 0;
		}
	}

}

void Player::Dash()
{
	dashCoolTime--;
	if (dashCoolTime <= 0 && dashTime <= 0)
	{
		dashCoolTime = 0;
		dashFlag = false;
	}
	if (Input::GetInstance()->TriggerKey(DIK_UPARROW)&&dashFlag==false)
	{
		dashTime = dashTimeMax;
		fade = 1;
		dashFlag = true;
	}

	if (dashTime > 0)
	{
		dashTime--;
		if (dashTime <= 0)
		{
			dashCoolTime = dashCoolTimeMax;
		}
		XMVECTOR movedash = { 0,0,2,0 };//前後方向用の移動ベクトル
		
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.m128_f32[1]));//y 軸を中心に回転するマトリックスを作成
		movedash = XMVector3TransformNormal(movedash, matRot);

		playerPos.x += movedash.m128_f32[0];
		playerPos.z += movedash.m128_f32[2];
		if (fade > 0) {
			fade -= 0.05f;
		}
	}

}


void Player::Update()
{
	Move();
	Jump();
	Ball();
	Dash();

	SphereObj->SetPosition(spherePos);
	SphereObj->SetScale(sphereSize);
	SphereObj->SetRotation(sphereAngle);
	SphereObj->Quaternion();
	SphereObj->Update();
	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerAngle);
	playerObj->Quaternion();
	playerObj->SetScale({ 1,1,1 });
	playerObj->Update();
	dashSprite->SetColor({1, 1, 1, fade});
}

void Player::OnCollision(const CollisionInfo& info)
{
	SphereObj->OnCollision(info);
}


void Player::Draw()
{
	playerObj->Draw();
	SphereObj->Draw();
	
}

void Player::DrawSprite()
{
	if (dashFlag == true) {
		dashSprite->Draw();
	}
}
