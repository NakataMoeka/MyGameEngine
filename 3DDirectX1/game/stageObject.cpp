#include "stageObject.h"
#include"TouchableObject.h"
StageObject::StageObject()
{
}

StageObject::~StageObject()
{
}

void StageObject::Initialize()
{
	modelSlope = Model::Create("Cone", false);
	slope = TouchableObject::Create(modelSlope);
	slope->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

}

void StageObject::Init()
{
	position = { 0,0,10 };
	size = { 5,5,5 };
	rota = { 0,0,0 };
}

void StageObject::Update()
{
	slope->Quaternion();
	slope->SetScale(size);
	slope->SetRotation(rota);
	slope->SetPosition(position);
	slope->Update();
}

void StageObject::Draw()
{
	slope->Draw();
}
