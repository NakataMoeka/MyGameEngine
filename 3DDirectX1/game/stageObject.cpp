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
	modelKotatu = Model::Create("Kotatu", false);
	modelGround = Model::Create("ground", false);
	modelHome = Model::Create("home", false);
	Kotatu = TouchableObject::Create(modelKotatu);
	Kotatu->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Ground = TouchableObject::Create(modelGround);
	Ground->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Home = TouchableObject::Create(modelHome);
	Home->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");


}

void StageObject::Init()
{

}

void StageObject::stageInit(int stageNum)
{
	if (stageNum == 1) {
		Kotatu->SetPosition({ 0,38,-80 });
		Kotatu->Update();
		Ground->SetScale({ 6,6,6 });
		Ground->SetPosition({ 0,0,0 });
		Ground->SetRotation({ 0,0,0 });
		Ground->Quaternion();
		Ground->Update();
		Home->Update();
	}
	else if (stageNum == 2) {

	}
	else if (stageNum == 3) {

	}
}

void StageObject::Update()
{

	Kotatu->Update();

	Ground->Update();
	Home->Update();
}

void StageObject::Draw()
{

	Kotatu->Draw();
	Ground->Draw();
	Home->Draw();
}
