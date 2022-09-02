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
	modelSlope = Model::Create("Slope", false);
	slope = TouchableObject::Create(modelSlope);
	slope->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

}

void StageObject::Init()
{
}

void StageObject::Update()
{
	slope->Quaternion();
	slope->Update();
}

void StageObject::Draw()
{
	slope->Draw();
}
