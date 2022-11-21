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

	//for (int i = 0; i < 2; i++) {
	//	slope[i] = TouchableObject::Create(modelSlope);
	//	slope[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	//}
}

void StageObject::Init()
{
	position[0] = { 0,0,10 };
	position[1] = { 0,0,-50 };
	size = { 5,5,5 };
	rota = { 0,0,0 };

}

void StageObject::Update()
{
	/*for (int i = 0; i < 2; i++) {
		slope[i]->Quaternion();
		slope[i]->SetScale(size);
		slope[i]->SetRotation(rota);
		slope[i]->SetPosition(position[i]);
		slope[i]->Update();
	}*/
	//Block->Quaternion();
	//Block->SetScale({ 5,70,5 });
	//Block->SetRotation({0,0,0,0});
	Kotatu->SetPosition({ 0,38,-80 });
	Kotatu->Update();
	Ground->SetScale({ 4,4,4 });
	Ground->SetPosition({ 0,0,0 });
	Ground->SetRotation({ 0,0,0 });
	Ground->Quaternion();
	Ground->Update();
	Home->Update();
}

void StageObject::Draw()
{
	/*for (int i = 0; i < 2; i++) {
		slope[i]->Draw();
	}*/
	Kotatu->Draw();
	Ground->Draw();
	Home->Draw();
}
