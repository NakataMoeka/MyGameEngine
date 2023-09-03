#include "GameObjects.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
#include"Input.h"
#include<time.h>
#include"DebugText.h"
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
	modelCube = Model::Create("lego", false);
	modelMove = Model::Create("car", false);
	modelBear = Model::Create("bear", false);
	modelRobot = Model::Create("robot", false);
	modelCard = Model::Create("card", false);
	modelKendama = Model::Create("kendama", false);
	modelKoma = Model::Create("koma", false);
	modelShogi = Model::Create("shogi", false);
	modelTuru = Model::Create("tsuru", false);
	modelGame = Model::Create("game", false);
	for (int i = 0; i < OBJNumber; i++) {
		cube[i]->Initialize(modelCube);
		moveObj[i]->Initialize(modelMove);
		Game[i]->Initialize(modelGame);
		Bear[i]->Initialize(modelBear);
		Robot[i]->Initialize(modelRobot);
		Card[i]->Initialize(modelCard);
		Kendama[i]->Initialize(modelKendama);
		Koma[i]->Initialize(modelKoma);
		Shogi[i]->Initialize(modelShogi);
		Turu[i]->Initialize(modelTuru);
	}

}

void GameObjects::Init()
{
	size[0] = { 1.0f,1.0f,1.0f };
	size[1] = { 5,5,5 };
	oy = 0;
	//初期位置など設定
	for (int i = 0; i < oData.size(); i++) {

		float radius = 1.0f;
		if (stageNum == 0 || stageNum == 1) {
			cube[i]->Init(oData[i]->pos, size[0], oData[i]->rot, 1.0f, 0.5f);
		}
		else if (stageNum == 2) {
			Game[i]->Init(oData[i]->pos, size[0], oData[i]->rot, 1.0f, 0.5f);
		}
	}
	for (int i = 0; i < oData2.size(); i++) {
		if (stageNum == 1) {
			oData2[10]->pos.y = 52;
			oData2[12]->pos.y = 52;
			moveObj[i]->Init(oData2[i]->pos, size[0], oData2[i]->rot, 2.0f, 1.0f);
		}
		else if (stageNum == 2) {
			Koma[i]->Init(oData2[i]->pos, size[0], oData2[i]->rot, 2.0f, 1.0f);
		}
	}
	for (int i = 0; i < oData3.size(); i++) {
		if (stageNum == 1) {
			Bear[i]->Init(oData3[i]->pos, size[0], oData3[i]->rot, 4.0f, 1.0f);
		}
		else if (stageNum == 2) {
			Shogi[i]->Init(oData3[i]->pos, size[0], oData3[i]->rot, 2.0f, 1.0f);
		}
	}
	for (int i = 0; i < oData4.size(); i++) {
		if (stageNum == 1) {
			Robot[i]->Init(oData4[i]->pos, size[0], oData4[i]->rot, 4.0f, 1.5f);
		}
		else if (stageNum == 2) {
			Kendama[i]->Init(oData4[i]->pos, size[0], oData4[i]->rot, 4.0f, 1.0f);
		}
	}
	for (int i = 0; i < oData5.size(); i++) {
		if (stageNum == 1) {
			Card[i]->Init(oData5[i]->pos, size[0], oData5[i]->rot, 2.0f, 2.0f);
		}
		else if (stageNum == 2) {
			Turu[i]->Init(oData[i]->pos, size[0], oData[i]->rot, 2.0f, 1.0f);
		}
	}
}

void GameObjects::stageInit(int stageNum)
{
	srand((unsigned)time(NULL));
	randRot = 0;
	this->stageNum = stageNum;
	//csvファイル読み込み
	if (stageNum == 0) {
		LoadCSV(spawnMap, (char*)"Resources/objMap2.csv");
	}
	if (stageNum == 1) {
		LoadCSV(spawnMap, (char*)"Resources/objMap.csv");
	}
	else if (stageNum == 2) {
		LoadCSV(spawnMap, (char*)"Resources/objMap3.csv");
	}
	//csvからobjの位置の読み込み
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
	//最初の数値が端の位置。iが横、jが縦。
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
void GameObjects::Update()
{
	if (stageNum == 0) {
		for (int i = 0; i < oData.size(); i++) {
			cube[i]->Update(oData[i]->rot, false);
			cSphere[i].radius = 0.5f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1] + oy, cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
	}
	else if (stageNum == 1) {
		//ここでSetすると離れてくっつくからしないように!!
		for (int i = 0; i < oData.size(); i++) {
			cube[i]->Update(oData[i]->rot, false);
			cSphere[i].radius = 0.5f;
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1] + oy, cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData2.size(); i++) {
			moveObj[i]->Update(oData2[i]->rot, true);
			cSphere2[i].radius = 1.0f;
			cSphere2[i].center = XMVectorSet(moveObj[i]->GetMatWorld().r[3].m128_f32[0], moveObj[i]->GetMatWorld().r[3].m128_f32[1] + oy, moveObj[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData3.size(); i++) {
			Bear[i]->Update(oData3[i]->rot, false);
			cSphere3[i].radius = 1.0f;
			cSphere3[i].center = XMVectorSet(Bear[i]->GetMatWorld().r[3].m128_f32[0], Bear[i]->GetMatWorld().r[3].m128_f32[1] + oy, Bear[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData4.size(); i++) {
			Robot[i]->Update(oData4[i]->rot, false);
			cSphere4[i].radius = 1.5f;
			cSphere4[i].center = XMVectorSet(Robot[i]->GetMatWorld().r[3].m128_f32[0], Robot[i]->GetMatWorld().r[3].m128_f32[1] + oy, Robot[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData5.size(); i++) {
			Card[i]->Update(oData5[i]->rot, false);
			cSphere5[i].radius = 2.0f;
			cSphere5[i].center = XMVectorSet(Card[i]->GetMatWorld().r[3].m128_f32[0], Card[i]->GetMatWorld().r[3].m128_f32[1] + oy, Card[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
	}
	else if (stageNum == 2) {
		for (int i = 0; i < oData.size(); i++) {
			Game[i]->Update(oData[i]->rot, false);
			cSphere[i].radius = 0.5f;
			cSphere[i].center = XMVectorSet(Game[i]->GetMatWorld().r[3].m128_f32[0], Game[i]->GetMatWorld().r[3].m128_f32[1] + oy, Game[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData2.size(); i++) {
			Koma[i]->Update(oData2[i]->rot, true);
			cSphere2[i].radius = 1.0f;
			cSphere2[i].center = XMVectorSet(Koma[i]->GetMatWorld().r[3].m128_f32[0], Koma[i]->GetMatWorld().r[3].m128_f32[1] + oy, Koma[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData3.size(); i++) {
			Shogi[i]->Update(oData3[i]->rot, false);
			cSphere3[i].radius = 1.0f;
			cSphere3[i].center = XMVectorSet(Shogi[i]->GetMatWorld().r[3].m128_f32[0], Shogi[i]->GetMatWorld().r[3].m128_f32[1] + oy, Shogi[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData4.size(); i++) {
			Kendama[i]->Update(oData4[i]->rot, false);
			cSphere4[i].radius = 1.0f;
			cSphere4[i].center = XMVectorSet(Kendama[i]->GetMatWorld().r[3].m128_f32[0], Kendama[i]->GetMatWorld().r[3].m128_f32[1] + oy, Kendama[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
		for (int i = 0; i < oData5.size(); i++) {
			Turu[i]->Update(oData5[i]->rot, false);
			cSphere5[i].radius = 1.0f;
			cSphere5[i].center = XMVectorSet(Turu[i]->GetMatWorld().r[3].m128_f32[0], Turu[i]->GetMatWorld().r[3].m128_f32[1] + oy, Turu[i]->GetMatWorld().r[3].m128_f32[2], 1);
		}
	}
	//DebugText::GetInstance()->Printf(250, 400, 6.0f, { 1,1,1,1 }, "%f", cSphere[44].center.m128_f32[1]);
}

void GameObjects::RC()
{
	//コライダーの削除
	for (int i = (int)oData.size() - 1; i >= 0; i--)
	{
		cube[i]->RC();
		Game[i]->RC();
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
	for (int i = (int)oData2.size() - 1; i >= 0; i--)
	{
		moveObj[i]->RC();
		Koma[i]->RC();
		delete oData2[i];
		oData2.erase(oData2.begin() + i);
	}
	for (int i = (int)oData3.size() - 1; i >= 0; i--)
	{
		Bear[i]->RC();
		Shogi[i]->RC();
		delete oData3[i];
		oData3.erase(oData3.begin() + i);
	}
	for (int i = (int)oData4.size() - 1; i >= 0; i--)
	{
		Robot[i]->RC();
		Kendama[i]->RC();
		delete oData4[i];
		oData4.erase(oData4.begin() + i);
	}
	for (int i = (int)oData5.size() - 1; i >= 0; i--)
	{
		Card[i]->RC();
		Turu[i]->RC();
		delete oData5[i];
		oData5.erase(oData5.begin() + i);
	}
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
			return cube[i]->GetOBJ3d();
		}
		else if (stageNum == 2) {
			return Game[i]->GetOBJ3d();
		}
	}
	else if (j == 1) {
		if (stageNum == 1) {
			return moveObj[i]->GetOBJ3d();
		}
		else if (stageNum == 2) {
			return Koma[i]->GetOBJ3d();
		}
	}
	else if (j == 2) {
		if (stageNum == 1) {
			return Bear[i]->GetOBJ3d();
		}
		else if (stageNum == 2) {
			return Shogi[i]->GetOBJ3d();
		}
	}
	else if (j == 3) {
		if (stageNum == 1) {
			return Robot[i]->GetOBJ3d();
		}
		else if (stageNum == 2) {
			return Kendama[i]->GetOBJ3d();
		}
	}
	else {
		if (stageNum == 1) {
			return Card[i]->GetOBJ3d();
		}
		else if (stageNum == 2) {
			return Turu[i]->GetOBJ3d();
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
