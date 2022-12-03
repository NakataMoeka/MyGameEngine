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
	size[0] = { 2,2,2 };
	size[1] = { 5,5,5 };
	for (int i = 0; i < oData.size(); i++) {

		float radius = 2.0f;
		rota = { 0,0,0,0 };
		cube[i]->SetPosition(oData[i]->pos);
		cube[i]->SetScale(size[0]);
		cube[0]->SetRotation({ 0,90,0,0 });
		cube[i]->Quaternion();
		cube[i]->Update();
		//‚±‚±‚É‘‚©‚È‚¢‚ÆƒoƒO‚é
		cSphere[i].radius = 6.0f;
		cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		cube[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 2.0f));
		cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		cube[i]->GetCollider()->SetNum(0);
		cube[i]->SetParentFlag(false);

	}
	for (int i = 0; i < oData2.size(); i++) {
		moveObj[i]->SetPosition(oData2[i]->pos);
		moveObj[i]->SetScale(size[0]);
		moveObj[i]->Quaternion();
		moveObj[i]->Update();
		oData2[i]->o_pos = moveObj[i]->GetPosition();
		cSphere2[i].radius = 2;
		cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);
		moveObj[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 2));
		moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		moveObj[i]->GetCollider()->SetNum(1);
		moveObj[i]->SetParentFlag(false);
	}
	//d‚­‚È‚é

	moveFlag = false;
	oSpeed = 0;
}

void GameObject::stageInit(int stageNum)
{
	this->stageNum = stageNum;
	if (stageNum == 0) {
		LoadCSV(spawnMap, "Resources/objMap2.csv");
	}
	if (stageNum == 1) {
		LoadCSV(spawnMap, "Resources/objMap.csv");
	}
	else if (stageNum == 2) {

	}
	else if (stageNum == 3) {

	}
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
				if (stageNum == 0) {
					oData[num]->pos = { -180 + (float)i * 10,5, 0 + (float)j * (-10) };
				}
				else if (stageNum == 1) {
					oData[num]->pos = { -180 + (float)i * 10,40, 0 + (float)j * (-10) };
				}
				oData[num]->IsHit = false;
				oData[num]->oSize = 1.0f;
			}
			if (spawnMap[j][i] == 2)
			{
				oData2.push_back(new object);
				num = (int)oData2.size() - 1;
				oData2[num]->pos = { -180 + (float)i * 10,40, 0 + (float)j * (-10) };
				oData2[num]->o_pos = pos;
				oData2[num]->rot = { 0,0,0,0 };
				oData2[num]->IsHit = false;
				oData2[num]->oSize = 3.0f;
			}


		}
	}
}

void GameObject::Update()
{
	if(stageNum==0){
		for (int i = 0; i < OBJNumber; i++) {

			cSphere[i].radius = 2.0f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (cube[i]->GetParentFlag() == true) {
				cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			cube[i]->Update();
		}
	}
	else if (stageNum == 1) {
		//‚±‚±‚ÅSet‚·‚é‚Æ—£‚ê‚Ä‚­‚Á‚Â‚­‚©‚ç‚µ‚È‚¢‚æ‚¤‚É!!
		for (int i = 0; i < OBJNumber; i++) {

			cSphere[i].radius = 1.2f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (cube[i]->GetParentFlag() == true) {
				cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			cube[i]->Quaternion();
			cube[i]->SetRotation(rota);
			cube[0]->SetRotation({ 0,90,0 });
			cube[i]->Update();

		}
		for (int i = 0; i < oData2.size(); i++) {

			//obj‚ÌˆÚ“®ˆ—
			cSphere2[i].radius = 2;
			cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);

			if (moveObj[i]->GetParentFlag() == false) {
				oData2[i]->rot.m128_f32[1] += 2;
				moveObj[i]->Quaternion();
				moveObj[i]->SetRotation(oData2[i]->rot);
			}
			if (moveObj[i]->GetParentFlag() == true) {
				moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			moveObj[i]->Quaternion();
			moveObj[i]->Update();
		}
	}
}


void GameObject::RC()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--)
	{
		cube[i]->SetParentFlag(false);
		cube[i]->RemoveCollider();
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
	for (int i = (int)oData2.size() - 1; i >= 0; i--)
	{
		moveObj[i]->SetParentFlag(false);
		moveObj[i]->RemoveCollider();
		delete oData2[i];
		oData2.erase(oData2.begin() + i);
	}
}

void GameObject::Draw()
{
	if (stageNum == 0) {
		for (int i = (int)oData.size() - 1; i >= 0; i--)
		{
			cube[i]->Draw();
		}
	}
	else if (stageNum == 1) {

		for (int i = (int)oData.size() - 1; i >= 0; i--)
		{
			cube[i]->Draw();
		}
		for (int i = (int)oData2.size() - 1; i >= 0; i--)
		{
			moveObj[i]->Draw();
		}
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

bool GameObject::GetHIT(int i, int j)
{
	if (j == 0) {
		return oData[i]->IsHit;
	}
	else {
		return oData2[i]->IsHit;
	};
}

bool GameObject::SetHIT(int i, int j, bool Hit)
{
	if (j == 0) {
		return this->oData[i]->IsHit = Hit;
	}
	else {
		return this->oData2[i]->IsHit = Hit;
	};
}

float GameObject::GetOSize(int i, int j)
{
	if (j == 0) {
		return this->oData[i]->oSize;
	}
	else {
		return this->oData2[i]->oSize;
	};
}
