#include "GameObject.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
#include"Input.h"
#include<time.h>
using namespace DirectX;
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--) {
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
	for (int i = (int)oData2.size() - 1; i >= 0; i--) {
		delete oData2[i];
		oData2.erase(oData2.begin() + i);
	}
	for (int i = (int)oData3.size() - 1; i >= 0; i--) {
		delete oData3[i];
		oData3.erase(oData3.begin() + i);
	}
	for (int i = (int)oData4.size() - 1; i >= 0; i--) {
		delete oData4[i];
		oData4.erase(oData4.begin() + i);
	}
	for (int i = 0; i < OBJNumber; i++) {
		safe_delete(cube[i]);
		safe_delete(moveObj[i]);
		safe_delete(Bear[i]);
	}
}

void GameObject::Initialize()
{
	modelCube = Model::Create("lego", false);
	modelMove = Model::Create("car", false);
	modelBear = Model::Create("bear", false);
	modelRobot = Model::Create("robot", false);

	for (int i = 0; i < OBJNumber; i++) {
		cube[i] = Object3d::Create(modelCube);
		cube[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		moveObj[i] = Object3d::Create(modelMove);
		moveObj[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Bear[i] = Object3d::Create(modelBear);
		Bear[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Robot[i] = Object3d::Create(modelRobot);
		Robot[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

	}

}

void GameObject::Init()
{
	size[0] = { 1.5f,1.5f,1.5f };
	size[1] = { 5,5,5 };
	for (int i = 0; i < oData.size(); i++) {

		float radius = 1.0f;
		rota = { 0,0,0,0 };
		cube[i]->SetPosition(oData[i]->pos);
		cube[i]->SetScale(size[0]);
		cube[i]->Quaternion();
		cube[i]->SetRotation(oData[i]->rot);
		cube[i]->Update();
		//‚±‚±‚É‘‚©‚È‚¢‚ÆƒoƒO‚é
		cSphere[i].radius = 1.0f;
		cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		cube[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,1,0,0 }), 1.0f));
		cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		cube[i]->GetCollider()->SetNum(0);
		cube[i]->SetParentFlag(false);

	}
	for (int i = 0; i < oData2.size(); i++) {
		moveObj[i]->SetPosition(oData2[i]->pos);
		moveObj[i]->SetScale(size[0]);
		moveObj[i]->Quaternion();
		moveObj[i]->Update();
		cSphere2[i].radius = 2;
		cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);
		moveObj[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,4,0,0 }), 2));
		moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		moveObj[i]->GetCollider()->SetNum(1);
		moveObj[i]->SetParentFlag(false);
	}
	for (int i = 0; i < oData3.size(); i++) {
		Bear[i]->SetPosition(oData3[i]->pos);
		Bear[i]->SetScale({ 0.8f,0.8f,0.8f });
		Bear[i]->Quaternion();
		Bear[i]->Update();
		cSphere3[i].radius = 2;
		cSphere3[i].center = XMVectorSet(Bear[i]->GetMatWorld().r[3].m128_f32[0], Bear[i]->GetMatWorld().r[3].m128_f32[1], Bear[i]->GetMatWorld().r[3].m128_f32[2], 1);
		Bear[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,4,0,0 }), 2));
		Bear[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		Bear[i]->GetCollider()->SetNum(2);
		Bear[i]->SetParentFlag(false);
	}
	for (int i = 0; i < oData4.size(); i++) {
		Robot[i]->SetPosition(oData4[i]->pos);
		Robot[i]->SetScale(size[0]);
		Robot[i]->Quaternion();
		Robot[i]->Update();
		cSphere4[i].radius = 2;
		cSphere4[i].center = XMVectorSet(Robot[i]->GetMatWorld().r[3].m128_f32[0], Robot[i]->GetMatWorld().r[3].m128_f32[1], Robot[i]->GetMatWorld().r[3].m128_f32[2], 1);
		Robot[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,4,0,0 }), 2));
		Robot[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		Robot[i]->GetCollider()->SetNum(3);
		Robot[i]->SetParentFlag(false);
	}
	//d‚­‚È‚é

	moveFlag = false;
	oSpeed = 0;
}

void GameObject::stageInit(int stageNum)
{
	srand((unsigned)time(NULL));
	randRot = 0;
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
					oData[num]->pos = { -180 + (float)i * 10,0, 100 + (float)j * (-10) };
				}
				else if (stageNum == 1) {
					oData[num]->pos = { -180 + (float)i * 10,35, 100 + (float)j * (-10) };
				}
				oData[num]->rot = { 0,0,0,0 };
				randRot = rand() / 360;
				oData[num]->rot.m128_f32[1] = (float)randRot;

				oData[num]->IsHit = false;
				oData[num]->oSize = 1.0f;
			}
			if (spawnMap[j][i] == 2)
			{
				oData2.push_back(new object);
				num = (int)oData2.size() - 1;
				oData2[num]->pos = { -180 + (float)i * 10,37, 100 + (float)j * (-10) };
				oData2[num]->rot = { 0,0,0,0 };
				oData2[num]->IsHit = false;
				oData2[num]->oSize = 3.0f;
			}
			if (spawnMap[j][i] == 3)
			{
				oData3.push_back(new object);
				num = (int)oData3.size() - 1;
				oData3[num]->pos = { -180 + (float)i * 10,50, 100 + (float)j * (-10) };
				oData3[num]->rot = { 0,0,0,0 };
				randRot = rand() / 360;
				oData3[num]->rot.m128_f32[1] = (float)randRot;
				oData3[num]->IsHit = false;
				oData3[num]->oSize = 4.0f;
			}
			if (spawnMap[j][i] == 4)
			{
				oData4.push_back(new object);
				num = (int)oData4.size() - 1;
				oData4[num]->pos = { -180 + (float)i * 10,37, 100 + (float)j * (-10) };
				oData4[num]->rot = { 0,0,0,0 };
				randRot = rand() / 360;
				oData4[num]->rot.m128_f32[1] = (float)randRot;
				oData4[num]->IsHit = false;
				oData4[num]->oSize = 6.0f;
			}
		}
	}
}

void GameObject::Update()
{
	if (stageNum == 0) {
		for (int i = 0; i < oData.size(); i++) {

			cSphere[i].radius = 1.0f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (cube[i]->GetParentFlag() == true) {
				cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			cube[i]->Update();
		}
	}
	else if (stageNum == 1) {
		//‚±‚±‚ÅSet‚·‚é‚Æ—£‚ê‚Ä‚­‚Á‚Â‚­‚©‚ç‚µ‚È‚¢‚æ‚¤‚É!!
		for (int i = 0; i < oData.size(); i++) {

			cSphere[i].radius = 1.0f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (cube[i]->GetParentFlag() == true) {
				cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			cube[i]->SetRotation(oData[i]->rot);
			cube[i]->Quaternion();
			cube[i]->Update();
		}
		for (int i = 0; i < oData2.size(); i++) {

			//obj‚ÌˆÚ“®ˆ—
			cSphere2[i].radius = 2;
			cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);

			if (moveObj[i]->GetParentFlag() == false) {
				oData2[i]->rot.m128_f32[1] += 2;

			}
			if (moveObj[i]->GetParentFlag() == true) {
				moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			moveObj[i]->Quaternion();
			moveObj[i]->SetRotation(oData2[i]->rot);
			moveObj[i]->Update();
		}
		for (int i = 0; i < oData3.size(); i++) {

			cSphere3[i].radius = 2.0f;
			cSphere3[i].center = XMVectorSet(Bear[i]->GetMatWorld().r[3].m128_f32[0], Bear[i]->GetMatWorld().r[3].m128_f32[1], Bear[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (Bear[i]->GetParentFlag() == true) {
				Bear[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			Bear[i]->SetRotation(oData3[i]->rot);
			Bear[i]->Quaternion();
			Bear[i]->Update();
		}
		for (int i = 0; i < oData4.size(); i++) {

			cSphere4[i].radius = 2.0f;
			cSphere4[i].center = XMVectorSet(Robot[i]->GetMatWorld().r[3].m128_f32[0], Robot[i]->GetMatWorld().r[3].m128_f32[1], Robot[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (Robot[i]->GetParentFlag() == true) {
				Robot[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			Robot[i]->SetRotation(oData3[i]->rot);
			Robot[i]->Quaternion();
			Robot[i]->Update();
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
	for (int i = (int)oData3.size() - 1; i >= 0; i--)
	{
		Bear[i]->SetParentFlag(false);
		Bear[i]->RemoveCollider();
		delete oData3[i];
		oData3.erase(oData3.begin() + i);
	}
	for (int i = (int)oData4.size() - 1; i >= 0; i--)
	{
		Robot[i]->SetParentFlag(false);
		Robot[i]->RemoveCollider();
		delete oData4[i];
		oData4.erase(oData4.begin() + i);
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

		for (int i = 0; i < oData.size(); i++) 
		{
			cube[i]->Draw();
		}
		for (int i = 0; i < oData2.size(); i++) 
		{
			moveObj[i]->Draw();
		}
		for (int i = 0; i < oData3.size(); i++) 
		{
			Bear[i]->Draw();
		}
		for (int i = 0; i < oData4.size(); i++) 
		{
			Robot[i]->Draw();
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
	else if (j == 1) {
		return (int)oData2.size();
	}
	else if (j == 2) {
		return (int)oData3.size();
	}
	else  {
		return (int)oData4.size();
	}
}
Sphere GameObject::GetCSphere(int i, int j)
{
	if (j == 0) {
		return cSphere[i];
	}
	else if (j == 1) {
		return cSphere2[i];
	}
	else if (j == 2) {
		return cSphere3[i];
	}
	else {
		return cSphere4[i];
	}
	//return;
}
Object3d* GameObject::GetObject3d(int i, int j)
{
	if (j == 0) {
		return cube[i];
	}
	else if (j == 1) {
		return moveObj[i];
	}
	else if (j == 2) {
		return Bear[i];
	}
	else {
		return Robot[i];
	}
}

bool GameObject::GetHIT(int i, int j)
{
	if (j == 0) {
		return oData[i]->IsHit;
	}
	else if (j == 1) {
		return oData2[i]->IsHit;
	}
	else if (j == 2) {
		return oData3[i]->IsHit;
	}
	else {
		return oData4[i]->IsHit;
	}
}

bool GameObject::SetHIT(int i, int j, bool Hit)
{
	if (j == 0) {
		return this->oData[i]->IsHit = Hit;
	}
	else if (j == 1) {
		return this->oData2[i]->IsHit = Hit;
	}
	else if (j == 2) {
		return this->oData3[i]->IsHit = Hit;
	}
	else {
		return this->oData4[i]->IsHit = Hit;
	}
}

float GameObject::GetOSize(int i, int j)
{
	if (j == 0) {
		return this->oData[i]->oSize;
	}
	else if (j == 1) {
		return this->oData2[i]->oSize;
	}
	else if (j == 2) {
		return this->oData3[i]->oSize;
	}
	else {
		return this->oData4[i]->oSize;
	}
}
