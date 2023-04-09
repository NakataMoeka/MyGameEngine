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
	modelTV = Model::Create("TV", false);
	modelChest = Model::Create("Chest", false);
	modelGround = Model::Create("road", false);
	modelHome = Model::Create("home", false);
	modelSkydome = Model::Create("skydome", true);
	modelSaku = Model::Create("saku", false);
	modelSlide = Model::Create("slide", false);
	modelSwing = Model::Create("swing", false);
	modelTree = Model::Create("tree", false);
	Ground = TouchableObject::Create(modelGround);
	Ground->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	skydome = Object3d::Create(modelSkydome);
	skydome->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Home = TouchableObject::Create(modelHome);
	Home->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Kotatu = TouchableObject::Create(modelKotatu);
	Kotatu->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	TV = TouchableObject::Create(modelTV);
	TV->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Chest = TouchableObject::Create(modelChest);
	Chest->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	saku = TouchableObject::Create(modelSaku);
	saku->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Slide = TouchableObject::Create(modelSlide);
	Slide->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Swing = TouchableObject::Create(modelSwing);
	Swing->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Tree = TouchableObject::Create(modelTree);
	Tree->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

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
		Ground->SetColor({ 1,1,1,1 });
		Ground->Update();
		skydome->SetPosition({ 0.0f,100.0f,0.0f });
		skydome->SetScale({ 4.0f,4.0f,4.0f });
		skydome->SetColor({ 1,1,1,1 });
		skydome->Update();
	}
	else if (stageNum == 1) {
		Kotatu->SetTouchCollider();
		Kotatu->SetPosition({ 0,38,-80 });
		Kotatu->SetColor({ 1,1,1,1 });
		Kotatu->Update();
		TV->SetTouchCollider();
		TV->SetPosition({ -20,28,-170 });
		TV->SetScale({ 2,2,2, });
		TV->SetRotation({ 0,90,0,0 });
		TV->Quaternion();
		TV->SetColor({ 1,1,1,1 });
		TV->Update();
		Chest->SetTouchCollider();
		Chest->SetPosition({ 20,46,126 });
		Chest->SetScale({ 4,4,4, });
		Chest->SetRotation({ 0,90,0,0 });
		Chest->Quaternion();
		Chest->SetColor({ 1,1,1,1 });
		Chest->Update();
		Ground->SetScale({ 6,6,6 });
		Ground->SetPosition({ 0,0,0 });
		Ground->SetRotation({ 0,0,0 });
		Ground->Quaternion();
		Ground->SetColor({ 1,1,1,1 });
		Ground->Update();
		Home->SetTouchCollider();
		Home->SetColor({ 1,1,1,1 });
		Home->Update();
		skydome->SetPosition({ 0.0f,100.0f,0.0f });
		skydome->SetScale({ 4.0f,4.0f,4.0f });
		skydome->SetColor({ 1,1,1,1 });
		skydome->Update();
		saku->SetTouchCollider();
		saku->SetPosition({ -190,58,-47.5f });
		saku->SetScale({ 2.0f,2.0f,2.0f });
		saku->SetColor({ 1,1,1,1 });
		saku->Update();
	}
	else if (stageNum == 2) {
		Ground->SetScale({ 6,6,6 });
		Ground->SetPosition({ 0,0,0 });
		Ground->SetRotation({ 0,0,0 });
		Ground->Quaternion();
		Ground->SetColor({ 1,1,1,1 });
		Ground->Update();
		skydome->SetPosition({ 0.0f,100.0f,0.0f });
		skydome->SetScale({ 4.0f,4.0f,4.0f });
		skydome->SetColor({ 1,1,1,1 });
		skydome->Update();
		Slide->SetTouchCollider();
		Slide->SetScale({ 5, 5, 5 });
		Slide->Update();
		Swing->SetTouchCollider();
		Swing->SetPosition({ -30,0,0 });
		Swing->Update();
		Tree->SetTouchCollider();
		Tree->SetPosition({ 30,0,0 });
		Tree->Update();
	}
}

void StageObject::Update()
{
	skydome->Update();
	Ground->Update();
	if (stageNum == 1) {
		Kotatu->Update();
		Home->Update();
		TV->Update();
		Chest->Update();
		saku->Update();
	}
	else if (stageNum == 2) {
		Slide->Update();
		Swing->Update();
		Tree->Update();
	}


}

void StageObject::Draw()
{
	//全ステージ共通
	skydome->Draw();
	Ground->Draw();


	if (stageNum == 1) {
		Kotatu->Draw();
		Home->Draw();
		TV->Draw();
		Chest->Draw();
		saku->Draw();
	}
	else if (stageNum == 2) {
		Slide->Draw();
		Swing->Draw();
		Tree->Draw();
	}


}

void StageObject::RC()
{
	Kotatu->RemoveCollider();
	TV->RemoveCollider();
	Chest->RemoveCollider();
	saku->RemoveCollider();
	Home->RemoveCollider();
	Ground->RemoveCollider();
	Slide->RemoveCollider();
	Swing->RemoveCollider();
	Tree->RemoveCollider();
}
