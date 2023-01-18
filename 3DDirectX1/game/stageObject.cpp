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
	
	modelKotatu = Model::Create("Kota", false);
	modelGround = Model::Create("road", false);
	modelHome = Model::Create("home", false);
	modelSkydome = Model::Create("skydome", true);
	modelSaku = Model::Create("saku", false);
	Ground = TouchableObject::Create(modelGround);
	Ground->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");	
	skydome = Object3d::Create(modelSkydome);
	skydome->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Home = TouchableObject::Create(modelHome);
	Home->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Kotatu = TouchableObject::Create(modelKotatu);
	Kotatu->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	
	saku = TouchableObject::Create(modelSaku);
	saku->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

}

void StageObject::Init()
{

}

void StageObject::stageInit(int stageNum)
{
	Ground->SetTouchCollider();
	this->stageNum = stageNum;
	if (stageNum == 0) {

		Ground->SetScale({ 6,6,6 });
		Ground->SetPosition({ 0,0,0 });
		Ground->SetRotation({ 0,0,0 });
		Ground->Quaternion();
		Ground->Update();
		skydome->SetPosition({ 0.0f,100.0f,0.0f });
		skydome->SetScale({ 4.0f,4.0f,4.0f });
		skydome->Update();
	}
	else if (stageNum == 1) {
		Kotatu->SetTouchCollider();
		Kotatu->SetPosition({ 0,38,-80 });
		Kotatu->Update();
		Ground->SetScale({ 6,6,6 });
		Ground->SetPosition({ 0,0,0 });
		Ground->SetRotation({ 0,0,0 });
		Ground->Quaternion();
		Ground->Update();
		Home->SetTouchCollider();
		Home->Update();
		skydome->SetPosition({ 0.0f,100.0f,0.0f });
		skydome->SetScale({ 4.0f,4.0f,4.0f });
		skydome->Update();
		saku->SetTouchCollider();
		saku->SetPosition({ -190,58,-47.5f });
		saku->SetScale({ 2.0f,2.0f,2.0f });
		saku->Update();
	}
	else if (stageNum == 2) {

	}
	else if (stageNum == 3) {

	}
}

void StageObject::Update()
{
	if (stageNum == 1) {
		Kotatu->Update();
		Home->Update();
		saku->Update();
	}
	skydome->Update();
	Ground->Update();

}

void StageObject::Draw()
{
	if (stageNum == 1) {
		Kotatu->Draw();
		Home->Draw();
		saku->Draw();
	}
	skydome->Draw();

	Ground->Draw();

}

void StageObject::RC()
{
	Kotatu->RemoveCollider();
	saku->RemoveCollider();
	Home->RemoveCollider();
	Ground->RemoveCollider();
}
