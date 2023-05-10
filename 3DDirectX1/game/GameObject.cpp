#include "GameObject.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
#include"Input.h"
#include<time.h>
using namespace DirectX;
GameObjects::GameObjects()
{
}

GameObjects::~GameObjects()
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
	for (int i = (int)oData5.size() - 1; i >= 0; i--) {
		delete oData5[i];
		oData5.erase(oData5.begin() + i);
	}
	for (int i = 0; i < OBJNumber; i++) {
		safe_delete(cube[i]);
		safe_delete(moveObj[i]);
		safe_delete(Game[i]);
	}
	for (int i = 0; i < OBJNumber2; i++) {
		safe_delete(Bear[i]);
		safe_delete(Robot[i]);
		safe_delete(Card[i]);
		safe_delete(Kendama[i]);
		safe_delete(Koma[i]);
		safe_delete(Shogi[i]);
		safe_delete(Turu[i]);
	}
}

void GameObjects::Initialize()
{
	modelCube = std::unique_ptr<Model>(Model::Create("lego", false));
	modelMove = std::unique_ptr<Model>(Model::Create("car", false));
	modelBear = std::unique_ptr<Model>(Model::Create("bear", false));
	modelRobot = std::unique_ptr<Model>(Model::Create("robot", false));
	modelCard = std::unique_ptr<Model>(Model::Create("card", false));
	modelPencil = std::unique_ptr<Model>(Model::Create("pencil", false));
	modelKendama = std::unique_ptr<Model>(Model::Create("kendama", false));
	modelKoma = std::unique_ptr<Model>(Model::Create("koma", false));
	modelShogi = std::unique_ptr<Model>(Model::Create("shogi", false));
	modelTuru = std::unique_ptr<Model>(Model::Create("tsuru", false));
	modelCont = std::unique_ptr<Model>(Model::Create("cont", false));
	modelGame = std::unique_ptr<Model>(Model::Create("game", false));
	for (int i = 0; i < OBJNumber; i++) {
		cube[i] = Object3d::Create(modelCube.get());
		cube[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		moveObj[i] = Object3d::Create(modelMove.get());
		moveObj[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Game[i] = Object3d::Create(modelGame.get());
		Game[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

	}
	for (int i = 0; i < OBJNumber2; i++) {
		Bear[i] = Object3d::Create(modelBear.get());
		Bear[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Robot[i] = Object3d::Create(modelRobot.get());
		Robot[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Card[i] = Object3d::Create(modelCard.get());
		Card[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Kendama[i] = Object3d::Create(modelKendama.get());
		Kendama[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Koma[i] = Object3d::Create(modelKoma.get());
		Koma[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Shogi[i] = Object3d::Create(modelShogi.get());
		Shogi[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		Turu[i] = Object3d::Create(modelTuru.get());
		Turu[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
		//Cont[i] = Object3d::Create(modelCont);
		//Cont[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

	}

}

void GameObjects::Init()
{
	size[0] = { 1.0f,1.0f,1.0f };
	size[1] = { 5,5,5 };
	y = 0;
	for (int i = 0; i < oData.size(); i++) {

		float radius = 1.0f;
		if (stageNum == 0 || stageNum == 1) {
			//stage1
			InitUpd(cube, i, oData);
			//Ç±Ç±Ç…èëÇ©Ç»Ç¢Ç∆ÉoÉOÇÈ
			cSphere[i].radius = 0.5;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			cube[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,1,0,0 }), 0.5f));
			cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			cube[i]->GetCollider()->SetNum(0);

		}
		else if (stageNum == 2) {
			//stage2
			InitUpd(Game, i, oData);
			//Ç±Ç±Ç…èëÇ©Ç»Ç¢Ç∆ÉoÉOÇÈ
			cSphere[i].radius = 0.5;
			cSphere[i].center = XMVectorSet(Game[i]->GetMatWorld().r[3].m128_f32[0], Game[i]->GetMatWorld().r[3].m128_f32[1], Game[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Game[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,1,0,0 }), 0.5f));
			Game[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Game[i]->GetCollider()->SetNum(5);
		}
	}
	for (int i = 0; i < oData2.size(); i++) {
		if (stageNum == 1) {
			oData2[10]->pos.y = 52;
			oData2[12]->pos.y = 52;
			InitUpd(moveObj, i, oData2);
			cSphere2[i].radius = 1.0f;
			cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1], moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);
			moveObj[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 1.0f));
			moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			moveObj[i]->GetCollider()->SetNum(1);
		}
		else if (stageNum == 2) {
			/*	oData2[10]->pos.y = 52;
				oData2[11]->pos.y = 52;*/
			InitUpd(Koma, i, oData2);
			cSphere2[i].radius = 1.0f;
			cSphere2[i].center = XMVectorSet(Koma[i]->GetMatWorld().r[3].m128_f32[0], Koma[i]->GetMatWorld().r[3].m128_f32[1], Koma[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Koma[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 1.0f));
			Koma[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Koma[i]->GetCollider()->SetNum(6);
		}
	}
	for (int i = 0; i < oData3.size(); i++) {
		if (stageNum == 1) {
			InitUpd(Bear, i, oData3);
			cSphere3[i].radius = 1.0f;
			cSphere3[i].center = XMVectorSet(Bear[i]->GetMatWorld().r[3].m128_f32[0], Bear[i]->GetMatWorld().r[3].m128_f32[1], Bear[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Bear[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,4,0,0 }), 1.0f));
			Bear[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Bear[i]->GetCollider()->SetNum(2);
		}
		else if (stageNum == 2) {
			InitUpd(Shogi, i, oData3);
			cSphere3[i].radius = 1.0f;
			cSphere3[i].center = XMVectorSet(Shogi[i]->GetMatWorld().r[3].m128_f32[0], Shogi[i]->GetMatWorld().r[3].m128_f32[1], Shogi[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Shogi[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 1.0f));
			Shogi[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Shogi[i]->GetCollider()->SetNum(7);
		}
	}
	for (int i = 0; i < oData4.size(); i++) {
		if (stageNum == 1) {
			InitUpd(Robot, i, oData4);
			cSphere4[i].radius = 1.0f;
			cSphere4[i].center = XMVectorSet(Robot[i]->GetMatWorld().r[3].m128_f32[0], Robot[i]->GetMatWorld().r[3].m128_f32[1], Robot[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Robot[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,4,0,0 }), 1.5f));
			Robot[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Robot[i]->GetCollider()->SetNum(3);
		}
		else if (stageNum == 2) {
			InitUpd(Kendama, i, oData4);
			cSphere4[i].radius = 1.0f;
			cSphere4[i].center = XMVectorSet(Kendama[i]->GetMatWorld().r[3].m128_f32[0], Kendama[i]->GetMatWorld().r[3].m128_f32[1], Kendama[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Kendama[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,4,0,0 }), 1.0f));
			Kendama[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Kendama[i]->GetCollider()->SetNum(8);
		}
	}
	for (int i = 0; i < oData5.size(); i++) {
		if (stageNum == 1) {
			InitUpd(Card, i, oData5);
			cSphere5[i].radius = 1.5f;
			cSphere5[i].center = XMVectorSet(Card[i]->GetMatWorld().r[3].m128_f32[0], Card[i]->GetMatWorld().r[3].m128_f32[1], Card[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Card[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 2.0f));
			Card[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Card[i]->GetCollider()->SetNum(4);
		}
		else if (stageNum == 2) {
			InitUpd(Turu, i, oData5);
			cSphere5[i].radius = 1.0f;
			cSphere5[i].center = XMVectorSet(Turu[i]->GetMatWorld().r[3].m128_f32[0], Turu[i]->GetMatWorld().r[3].m128_f32[1], Turu[i]->GetMatWorld().r[3].m128_f32[2], 1);
			Turu[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), 1.0f));
			Turu[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
			Turu[i]->GetCollider()->SetNum(9);
		}
	}
	//èdÇ≠Ç»ÇÈ

	moveFlag = false;
	oSpeed = 0;
}

void GameObjects::stageInit(int stageNum)
{
	srand((unsigned)time(NULL));
	randRot = 0;
	this->stageNum = stageNum;
	if (stageNum == 0) {
		LoadCSV(spawnMap, (char*)"Resources/objMap2.csv");
	}
	if (stageNum == 1) {
		LoadCSV(spawnMap, (char*)"Resources/objMap.csv");
	}
	else if (stageNum == 2) {
		LoadCSV(spawnMap, (char*)"Resources/objMap3.csv");
	}
	//csvÇ©ÇÁobjÇÃà íuÇÃì«Ç›çûÇ›
	for (size_t j = 0; j < MAP_HEIGHT; j++)
	{
		for (size_t i = 0; i < MAP_WIDTH; i++)
		{
			num = 0;
			float y = 0;
			if (spawnMap[j][i] == 1)
			{
				oData.push_back(new object);
				num = (int)oData.size() - 1;
				if (stageNum == 0 || stageNum == 2) {
					y = 0;
				}
				else if (stageNum == 1) {
					y = 35;
				}
				InitNum(oData, stageNum, y, 1, i, j);
			}
			else if (spawnMap[j][i] == 2)
			{
				oData2.push_back(new object);
				num = (int)oData2.size() - 1;
				if (stageNum == 2) {
					y = 0;
				}
				else if (stageNum == 1) {
					y = 37;
				}
				InitNum(oData2, stageNum, y, 2, i, j);
			}
			else if (spawnMap[j][i] == 3)
			{
				oData3.push_back(new object);
				num = (int)oData3.size() - 1;
				if (stageNum == 0 || stageNum == 2) {
					y = 0;
				}
				else if (stageNum == 1) {
					y = 50;
				}
				InitNum(oData3, stageNum, y, 3, i, j);
			}
			else if (spawnMap[j][i] == 4)
			{
				oData4.push_back(new object);
				num = (int)oData4.size() - 1;
				if (stageNum == 2) {
					y = 0;
				}
				else if (stageNum == 1) {
					y = 35;
				}
				InitNum(oData4, stageNum, y, 4, i, j);
			}
			else if (spawnMap[j][i] == 5)
			{
				oData5.push_back(new object);
				num = (int)oData5.size() - 1;
				if (stageNum == 2) {
					y = 0;
				}
				else if (stageNum == 1) {
					y = 36;
				}
				InitNum(oData5, stageNum, y, 5, i, j);
			}
		}
	}
}

void GameObjects::InitNum(std::vector<object*> oData, int stageNum, float y, float size, size_t i, size_t j)
{
	//ç≈èâÇÃêîílÇ™í[ÇÃà íuÅBiÇ™â°ÅAjÇ™ècÅB
	if (stageNum == 0) {
		oData[num]->pos = { -180 + (float)i * 10,y, 120 + (float)j * (-10) };
	}
	else if (stageNum == 1) {
		oData[num]->pos = { -180 + (float)i * 4,y, 120 + (float)j * (-10) };
	}
	else if (stageNum == 2) {
		oData[num]->pos = { -180 + (float)i * 4,y, 120 + (float)j * (-10) };
	}
	oData[num]->rot = { 0,0,0,0 };
	randRot = rand() / 360;
	oData[num]->rot.m128_f32[1] = (float)randRot;

	oData[num]->IsHit = false;
	if (stageNum == 0 || stageNum == 1) {
		oData[num]->oSize = 1.0f * size;
	}
	else if (stageNum == 2) {
		oData[num]->oSize = 10.0f * size;
	}
}
void GameObjects::InitUpd(std::array<Object3d*, OBJNumber> obj, int i, std::vector<object*> oData)
{
	obj[i]->SetPosition(oData[i]->pos);
	obj[i]->SetScale(size[0]);
	obj[i]->Quaternion();
	obj[i]->SetRotation(oData[i]->rot);
	obj[i]->Update();
	obj[i]->SetParentFlag(false);
	obj[i]->SetColFlag(false);
}

void GameObjects::Update()
{
	if (stageNum == 0) {
		for (int i = 0; i < oData.size(); i++) {

			cSphere[i].radius = 0.5f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1] + y, cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			if (cube[i]->GetColFlag() == true) {
				cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			cube[i]->Update();
		}
	}
	else if (stageNum == 1) {
		//Ç±Ç±Ç≈SetÇ∑ÇÈÇ∆ó£ÇÍÇƒÇ≠Ç¡Ç¬Ç≠Ç©ÇÁÇµÇ»Ç¢ÇÊÇ§Ç…!!
		for (int i = 0; i < oData.size(); i++) {


			cSphere[i].radius = 0.5f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1] + y, cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (cube[i]->GetColFlag() == true) {
				cube[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			cube[i]->SetRotation(oData[i]->rot);
			cube[i]->Quaternion();
			cube[i]->Update();
		}
		for (int i = 0; i < oData2.size(); i++) {

			//objÇÃà⁄ìÆèàóù
			cSphere2[i].radius = 1.0f;
			cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1] + y, moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇƒÇ¢Ç»Ç¢Ç∆Ç´ÇÕâÒì]Ç∑ÇÈ
			if (moveObj[i]->GetParentFlag() == false) {
				oData2[i]->rot.m128_f32[1] += 2;

			}
			if (moveObj[i]->GetColFlag() == true) {
				moveObj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			moveObj[i]->Quaternion();
			moveObj[i]->SetRotation(oData2[i]->rot);
			moveObj[i]->Update();
		}
		for (int i = 0; i < oData3.size(); i++) {

			cSphere3[i].radius = 1.0f;
			cSphere3[i].center = XMVectorSet(Bear[i]->GetMatWorld().r[3].m128_f32[0], Bear[i]->GetMatWorld().r[3].m128_f32[1] + y, Bear[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Bear[i]->GetColFlag() == true) {
				Bear[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			Bear[i]->SetRotation(oData3[i]->rot);
			Bear[i]->Quaternion();
			Bear[i]->Update();
		}
		for (int i = 0; i < oData4.size(); i++) {

			cSphere4[i].radius = 1.5f;
			cSphere4[i].center = XMVectorSet(Robot[i]->GetMatWorld().r[3].m128_f32[0], Robot[i]->GetMatWorld().r[3].m128_f32[1] + y, Robot[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Robot[i]->GetColFlag() == true) {
				Robot[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			Robot[i]->SetRotation(oData4[i]->rot);
			Robot[i]->Quaternion();
			Robot[i]->Update();
		}
		for (int i = 0; i < oData5.size(); i++) {

			cSphere5[i].radius = 2.0f;
			cSphere5[i].center = XMVectorSet(Card[i]->GetMatWorld().r[3].m128_f32[0], Card[i]->GetMatWorld().r[3].m128_f32[1] + y, Card[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Card[i]->GetColFlag() == true) {
				Card[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}

			Card[i]->SetRotation(oData5[i]->rot);
			Card[i]->Quaternion();
			Card[i]->Update();
		}
	}
	else if (stageNum == 2) {
		for (int i = 0; i < oData.size(); i++) {

			cSphere[i].radius = 0.5f;
			cSphere[i].center = XMVectorSet(Game[i]->GetMatWorld().r[3].m128_f32[0], Game[i]->GetMatWorld().r[3].m128_f32[1] + y, Game[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Game[i]->GetColFlag() == true) {
				Game[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			Game[i]->Quaternion();
			Game[i]->SetRotation(oData[i]->rot);
			Game[i]->Update();
		}
		for (int i = 0; i < oData2.size(); i++) {

			//objÇÃà⁄ìÆèàóù
			cSphere2[i].radius = 1.0f;
			cSphere2[i].center = XMVectorSet(Koma[i]->GetMatWorld().r[3].m128_f32[0], Koma[i]->GetMatWorld().r[3].m128_f32[1] + y, Koma[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇƒÇ¢Ç»Ç¢Ç∆Ç´ÇÕâÒì]Ç∑ÇÈ
			if (Koma[i]->GetParentFlag() == false) {
				oData2[i]->rot.m128_f32[1] += 2;
			}
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Koma[i]->GetColFlag() == true) {
				Koma[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			Koma[i]->Quaternion();
			Koma[i]->SetRotation(oData2[i]->rot);
			Koma[i]->Update();
		}
		for (int i = 0; i < oData3.size(); i++) {

			cSphere3[i].radius = 1.0f;
			cSphere3[i].center = XMVectorSet(Shogi[i]->GetMatWorld().r[3].m128_f32[0], Shogi[i]->GetMatWorld().r[3].m128_f32[1] + y, Shogi[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Shogi[i]->GetColFlag() == true) {
				Shogi[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			Shogi[i]->Quaternion();
			Shogi[i]->SetRotation(oData3[i]->rot);
			Shogi[i]->Update();
		}
		for (int i = 0; i < oData4.size(); i++) {

			cSphere4[i].radius = 1.0f;
			cSphere4[i].center = XMVectorSet(Kendama[i]->GetMatWorld().r[3].m128_f32[0], Kendama[i]->GetMatWorld().r[3].m128_f32[1] + y, Kendama[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Kendama[i]->GetColFlag() == true) {
				Kendama[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			Kendama[i]->Quaternion();
			Kendama[i]->SetRotation(oData4[i]->rot);
			Kendama[i]->Update();
		}
		for (int i = 0; i < oData5.size(); i++) {

			cSphere5[i].radius = 1.0f;
			cSphere5[i].center = XMVectorSet(Turu[i]->GetMatWorld().r[3].m128_f32[0], Turu[i]->GetMatWorld().r[3].m128_f32[1] + y, Turu[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//Ç≠Ç¡Ç¬Ç¢ÇΩÇÁîrêÀÇµÇ»Ç¢
			if (Turu[i]->GetColFlag() == true) {
				Turu[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
			}
			Turu[i]->Quaternion();
			Turu[i]->SetRotation(oData5[i]->rot);
			Turu[i]->Update();
		}
	}
}

void GameObjects::RC()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--)
	{
		RCC(cube, i);
		RCC(Game, i);
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
	for (int i = (int)oData2.size() - 1; i >= 0; i--)
	{
		RCC(moveObj, i);
		RCC(Koma, i);
		delete oData2[i];
		oData2.erase(oData2.begin() + i);
	}
	for (int i = (int)oData3.size() - 1; i >= 0; i--)
	{
		RCC(Bear,i);
		RCC(Shogi, i);
		delete oData3[i];
		oData3.erase(oData3.begin() + i);
	}
	for (int i = (int)oData4.size() - 1; i >= 0; i--)
	{
		RCC(Robot, i);
		RCC(Kendama, i);
		delete oData4[i];
		oData4.erase(oData4.begin() + i);
	}
	for (int i = (int)oData5.size() - 1; i >= 0; i--)
	{
		RCC(Card, i);
		RCC(Turu, i);
		delete oData5[i];
		oData5.erase(oData5.begin() + i);
	}
}
void GameObjects::RCC(std::array < Object3d*, OBJNumber>obj,int i)
{
	obj[i]->SetParentFlag(false);
	obj[i]->RemoveCollider();
}
void GameObjects::Draw()
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
		for (int i = 0; i < oData5.size(); i++)
		{
			Card[i]->Draw();
		}
	}
	else if (stageNum == 2) {
		for (int i = 0; i < oData.size(); i++)
		{
			Game[i]->Draw();
		}
		for (int i = 0; i < oData2.size(); i++)
		{
			Koma[i]->Draw();
		}
		for (int i = 0; i < oData3.size(); i++)
		{
			Shogi[i]->Draw();
		}
		for (int i = 0; i < oData4.size(); i++)
		{
			Kendama[i]->Draw();
		}
		for (int i = 0; i < oData5.size(); i++)
		{
			Turu[i]->Draw();
		}
	}
}


float GameObjects::GetMat()
{
	return 	cube[0]->GetMatRot().r[3].m128_f32[0];
}
int GameObjects::GetOBJCount(int j)
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
	else if (j == 3) {
		return (int)oData4.size();
	}
	else {
		return (int)oData5.size();
	}
}
Sphere GameObjects::GetCSphere(int i, int j)
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
	else if (j == 3) {
		return cSphere4[i];
	}
	else {
		return cSphere5[i];
	}
	//return;
}
Object3d* GameObjects::GetObject3d(int i, int j)
{

	if (j == 0) {
		if (stageNum == 0 || stageNum == 1) {
			return cube[i];
		}
		else if (stageNum == 2) {
			return Game[i];
		}
	}
	else if (j == 1) {
		if (stageNum == 1) {
			return moveObj[i];
		}
		else if (stageNum == 2) {
			return Koma[i];
		}
	}
	else if (j == 2) {
		if (stageNum == 1) {
			return Bear[i];
		}
		else if (stageNum == 2) {
			return Shogi[i];
		}
	}
	else if (j == 3) {
		if (stageNum == 1) {
			return Robot[i];
		}
		else if (stageNum == 2) {
			return Kendama[i];
		}
	}
	else {
		if (stageNum == 1) {
			return Card[i];
		}
		else if (stageNum == 2) {
			return Turu[i];
		}
	}
	return 0;
}

bool GameObjects::GetHIT(int i, int j)
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
	else if (j == 3) {
		return oData4[i]->IsHit;
	}
	else {
		return oData5[i]->IsHit;
	}
}

bool GameObjects::SetHIT(int i, int j, bool Hit)
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
	else if (j == 3) {
		return this->oData4[i]->IsHit = Hit;
	}
	else {
		return this->oData5[i]->IsHit = Hit;
	}
}

float GameObjects::GetOSize(int i, int j)
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
	else if (j == 3) {
		return this->oData4[i]->oSize;
	}
	else {
		return this->oData5[i]->oSize;
	}
}

XMFLOAT3 GameObjects::GetOPos(int i, int j)
{
	if (j == 0) {
		return cube[i]->GetPosition();
	}
	else if (j == 1) {
		return moveObj[i]->GetPosition();
	}
	else if (j == 2) {
		return Bear[i]->GetPosition();
	}
	else if (j == 3) {
		return Robot[i]->GetPosition();
	}
	else {
		return Card[i]->GetPosition();
	}
}