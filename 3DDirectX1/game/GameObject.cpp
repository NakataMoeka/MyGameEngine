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
	LoadCSV(spawnMap, "Resources/objMap.csv");
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
				oData[num]->pos = { -180 + (float)i * 10,40, 0 + (float)j * (-10) };

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
		size[0] = { 3,3,3 };
		size[1] = { 5,5,5 };
		rota = { 0,0,0,0 };

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
		moveObj[i]->SetScale(size[0]);
		moveObj[i]->Update();
		position2[i] = moveObj[i]->GetPosition();
		cSphere2[i].radius = 4;
		cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);
		moveObj[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 4));
		moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		moveObj[i]->SetParentFlag(false);
	}
	//重くなる

	moveFlag = false;
	oSpeed = 0;
}

void GameObject::Update()
{
	//ここでSetすると離れてくっつくからしないように!!
	for (int i = 0; i < OBJNumber; i++) {

		cSphere[i].radius = r;
		cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		cube[i]->Update();

	}
	for (int i = 0; i < oData2.size(); i++) {

		//移動のやつ(うまくいかないif分がいうこと聞かない)
		if (moveObj[i]->GetParentFlag() == false) {

			oData2[i]->pos.z += oSpeed;

			if (moveObj[i]->GetPosition().z < position2[i].z + 10) {
				oSpeed = 0.5f;
			}
			else {
				oSpeed = 0;
			}
			if (moveObj[i]->GetPosition().z > position2[i].z - 10) {
				oSpeed = -0.5f;
			}
			else {
				oSpeed = 0;
			}



			moveObj[i]->SetPosition(oData2[i]->pos);
			cSphere2[i].radius = 4;
			cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);

		}

		moveObj[i]->Update();
	}
}


void GameObject::RC()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--)
	{
		cube[i]->RemoveCollider();
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
	for (int i = (int)oData2.size() - 1; i >= 0; i--)
	{
		moveObj[i]->RemoveCollider();
		delete oData2[i];
		oData2.erase(oData2.begin() + i);
	}
}

void GameObject::Draw()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--)
	{
		cube[i]->Draw();
	}
	for (int i = (int)oData2.size() - 1; i >= 0; i--)
	{
		moveObj[i]->Draw();
	}

}


float GameObject::GetMat()
{
	return 	cube[0]->GetMatRot().r[3].m128_f32[0];
}
int GameObject::GetOBJCount(int j)
{
	if (j == 0) {
		return (int)oData.size();
	}
	else {
		return (int)oData2.size();
	};
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
Object3d* GameObject::GetObject3d(int i, int j)
{
	if (j == 0) {
		return cube[i];
	}
	else {
		return moveObj[i];
	};
}
void GameObject::move(int i)
{
	//ランダムに動かす(オブジェクト中心から半径(距離未定)以内で動かす)

}