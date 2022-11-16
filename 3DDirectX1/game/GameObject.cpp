#include "GameObject.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
#include"Input.h"

using namespace DirectX;
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	for (int i = 0; i < OBJNumber; i++) {
		modelCube = Model::Create("lego", false);
		cube[i] = Object3d::Create(modelCube);
		cube[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		modelMove = Model::Create("car", false);
		moveObj[i] = Object3d::Create(modelMove);
		moveObj[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	}

}

void GameObject::Init()
{

	LoadCSV(spawnMap, "Resources/objMap2.csv");
	int  num = 0;
	for (size_t j = 0; j < MAP_HEIGHT; j++)
	{
		for (size_t i = 0; i < MAP_WIDTH; i++)
		{
			num = 0;
		
			if (spawnMap[j][i] == 1)
			{
				oData.push_back(new object);
				num = (int)oData.size() - 1;
				oData[num]->pos = {-180 + (float)i * 10,40, 0 + (float)j * (-10)};

			}
			if (spawnMap[j][i] == 2)
			{
				oData2.push_back(new object);
				num = (int)oData2.size() - 1;
				oData2[num]->pos = { -180 + (float)i * 10,40, 0 + (float)j * (-10) };

			}
		}
	}
	for (int i = 0; i < oData.size(); i++) {

		float radius = 2.0f;
		//csvでやるつもり

		size[0] = { 3,3,3 };
	
		cube[i]->SetPosition(oData[i]->pos);
		cube[i]->SetScale(size[0]);
		cube[i]->Update();
	
		//ここに書かないとバグる
		cSphere[i].radius = r;
		cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);

		cube[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 2));
		cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		cube[i]->SetParentFlag(false);
	}
	for (int i = 0; i < oData2.size(); i++) {
		moveObj[i]->SetPosition(oData2[i]->pos);
		moveObj[i]->Update();
		
	/*	cSphere2[i].radius = r;
		cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);*/

		moveObj[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 2));
		moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		moveObj[i]->SetParentFlag(false);
	}
	//重くなる

}

void GameObject::Update()
{
	// クエリーコールバッククラス
	//class PlayerQueryCallback : public QueryCallback
	//{
	//public:
	//	PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};
	//	// 衝突時コールバック関数
	//	bool OnQueryHit(const QueryHit& info) {

	//		const XMVECTOR up = { 0,1,0,0 };

	//		XMVECTOR rejectDir = XMVector3Normalize(info.reject);
	//		float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

	//		// 地面判定しきい値
	//		const float threshold = cosf(XMConvertToRadians(30.0f));

	//		if (-threshold < cos && cos < threshold) {
	//			sphere->center += info.reject;
	//			move += info.reject;
	//		}
	//		return true;
	//	}

	//	Sphere* sphere = nullptr;
	//	DirectX::XMVECTOR move = { 0,0,0,0 };
	//};

	//ここでSetすると離れてくっつくからしないように!!
	for (int i = 0; i < OBJNumber; i++) {
	
	/*	cSphere[i].radius = r;
		cSphere[6].radius = 4;
		cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		cSphere2[i].radius = r;
		cSphere2[6].radius = 4;
		cSphere2[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		*///SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(cube[i]->GetCollider());
		//assert(sphereCollider);


		//PlayerQueryCallback callback(sphereCollider);
		//// 球と地形の交差を全検索

		//CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_OBJECT);
		//XMFLOAT3 posback[OBJNumber];
		//posback[i] = {cube[i]->GetMatWorld().r[3].m128_f32[0] ,cube[i]->GetMatWorld().r[3].m128_f32[1] ,cube[i]->GetMatWorld().r[3].m128_f32[2]};
		//// 交差による排斥分動かす
		//posback[i].x += callback.move.m128_f32[0];
		//posback[i].y += callback.move.m128_f32[1];
		//posback[i].z += callback.move.m128_f32[2];
		//cube[i]->SetPosition(posback[i]);
		//if (cube[i]->GetParentFlag() == false) {
		//	cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		//}
		//else if (cube[i]->GetParentFlag() == true) {
		//	cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_ALLIES);
		//}

	}
	for (int i = 0; i < oData.size(); i++) {
		cube[i]->Update();
	}
	for (int i = 0; i < oData2.size(); i++) {
		moveObj[i]->Update();
	}
}

void GameObject::RC()
{
	for (int i = 0; i < OBJNumber; i++) {
		cube[i]->RemoveCollider();
		cube[i]->RemoveCollider();
	}
}

void GameObject::Draw()
{
	for (int i = 0; i < oData.size(); i++) {
		cube[i]->Draw();
	}
	for (int i = 0; i < oData2.size(); i++) {
		moveObj[i]->Draw();
	}
}

Sphere GameObject::GetCSphere(int i, int j)
{
	if (j == 0) {
		return cSphere[i];
	}
	else {
		return cSphere2[i];
	};
	//return;
}


//float GameObject::GetMat()
//{
//	//return 	cube[0]->GetMatRot().r[3].m128_f32[0];
//}

int GameObject::GetOBJCount()
{
	int num = 0;
	num = (int)oData.size() + (int)oData2.size();
	return num;
}

Object3d* GameObject::GetObject3d(int i, int j)
{
	if (j == 0) {
		return cube[i];
	}
	else {
		return moveObj[i];
	};
}

void GameObject::move()
{
	//ランダムに動かす(オブジェクト中心から半径(距離未定)以内で動かす)

}
