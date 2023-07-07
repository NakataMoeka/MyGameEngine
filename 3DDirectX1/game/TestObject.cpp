#include "TestObject.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
#include"Input.h"
#include<time.h>
#include"DebugText.h"
using namespace DirectX;
TestObject::TestObject()
{
}

TestObject::~TestObject()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--) {
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
	for (int i = 0; i < OBJNumber; i++) {
		safe_delete(obj[i]);
		;
	}

}

void TestObject::Initialize(const std::string& modelname)
{
	model = std::unique_ptr<Model>(Model::Create(modelname, false));
	for (int i = 0; i < OBJNumber; i++) {
		obj[i] = Object3d::Create(model.get());
		obj[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	}
}

void TestObject::Init(int type, float radius)
{
	size[0] = { 1.0f,1.0f,1.0f };
	size[1] = { 5,5,5 };
	oy = 0;
	for (int i = 0; i < oData.size(); i++) {
		if (type == 2) {
			oData[10]->pos.y = 52;
			oData[12]->pos.y = 52;
		}
		InitUpd(obj, i, oData);
		//ここに書かないとバグる
		cSphere[i].radius = radius;
		cSphere[i].center = XMVectorSet(obj[i]->GetMatWorld().r[3].m128_f32[0], obj[i]->GetMatWorld().r[3].m128_f32[1], obj[i]->GetMatWorld().r[3].m128_f32[2], 1);
		obj[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,1,0,0 }), radius));
		obj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
		obj[i]->GetCollider()->SetNum(type);
	}
	//重くなる

	moveFlag = false;
	oSpeed = 0;
}

void TestObject::stageInit(int stageNum, float y2, float type)
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
	//csvからobjの位置の読み込み
	for (size_t j = 0; j < MAP_HEIGHT; j++)
	{
		for (size_t i = 0; i < MAP_WIDTH; i++)
		{
			num = 0;
			float y = 0;
			if (spawnMap[j][i] == type)
			{
				oData.push_back(new object);
				num = (int)oData.size() - 1;
				if (stageNum == 0 || stageNum == 2) {
					y = 0;
				}
				else if (stageNum == 1) {
					y = y2;
				}
				InitNum(oData, stageNum, y, type, i, j);
			}
		}
	}
}

void TestObject::InitNum(std::vector<object*> oData, int stageNum, float y, float size, size_t i, size_t j)
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
void TestObject::InitUpd(std::array<Object3d*, OBJNumber> obj, int i, std::vector<object*> oData)
{
	obj[i]->SetPosition(oData[i]->pos);
	obj[i]->SetScale(size[0]);
	obj[i]->Quaternion();
	obj[i]->SetRotation(oData[i]->rot);
	obj[i]->Update();
	obj[i]->SetParentFlag(false);
	obj[i]->SetColFlag(false);
}

void TestObject::Update(bool move)
{
	for (int i = 0; i < oData.size(); i++) {
		Upd(obj, i, oData, move);
		cSphere[i].radius = 0.5f;
		cSphere[i].center = XMVectorSet(obj[i]->GetMatWorld().r[3].m128_f32[0], obj[i]->GetMatWorld().r[3].m128_f32[1] + oy, obj[i]->GetMatWorld().r[3].m128_f32[2], 1);
	}
	//DebugText::GetInstance()->Printf(250, 400, 6.0f, { 1,1,1,1 }, "%f", cSphere[44].center.m128_f32[1]);
}
void TestObject::Upd(std::array<Object3d*, OBJNumber> obj, int i, std::vector<object*> oData, bool move)
{
	if (move == true) {
		if (obj[i]->GetParentFlag() == false) {
			oData[i]->rot.m128_f32[1] += 2;
		}
	}
	if (obj[i]->GetColFlag() == true) {
		obj[i]->GetCollider()->SetAttribute(COLLISION_ATTR_POBJECT);
	}
	obj[i]->SetRotation(oData[i]->rot);
	obj[i]->Quaternion();
	obj[i]->Update();
}
void TestObject::RC()
{
	for (int i = (int)oData.size() - 1; i >= 0; i--)
	{
		RCC(obj, i);
		delete oData[i];
		oData.erase(oData.begin() + i);
	}
}
void TestObject::RCC(std::array < Object3d*, OBJNumber>obj, int i)
{
	obj[i]->SetParentFlag(false);
	obj[i]->RemoveCollider();
}

void TestObject::Draw()
{
	for (int i = 0; i < oData.size(); i++)
	{
		obj[i]->Draw();
	}
}

int TestObject::GetOBJCount(int j)
{
	if (j == 0) {
		return (int)oData.size();
	}
}
Sphere TestObject::GetCSphere(int i, int j)
{
	return cSphere[i];
}
Object3d* TestObject::GetObject3d(int i, int j)
{
	return obj[i];
}

bool TestObject::GetHIT(int i, int j)
{
	return oData[i]->IsHit;
}

bool TestObject::SetHIT(int i, int j, bool Hit)
{
	return this->oData[i]->IsHit = Hit;

}

float TestObject::GetOSize(int i, int j)
{
	return this->oData[i]->oSize;


}

XMFLOAT3 TestObject::GetOPos(int i, int j)
{
	return obj[i]->GetPosition();
}