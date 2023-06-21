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

	modelKotatu = std::unique_ptr<Model>(Model::Create("Kota", false));
	modelTV = std::unique_ptr<Model>(Model::Create("TV", false));
	modelChest = std::unique_ptr<Model>(Model::Create("Chest", false));
	modelGround = std::unique_ptr<Model>(Model::Create("road", false));
	modelHome = std::unique_ptr<Model>(Model::Create("home", false));
	modelSkydome = std::unique_ptr<Model>(Model::Create("skydome", true));
	modelSaku = std::unique_ptr<Model>(Model::Create("saku", false));
	modelSlide = std::unique_ptr<Model>(Model::Create("slide", false));
	modelSwing = std::unique_ptr<Model>(Model::Create("swing", false));
	modelTree = std::unique_ptr<Model>(Model::Create("tree", false));
	Ground = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelGround.get()));
	Ground->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	skydome = std::unique_ptr < Object3d>(Object3d::Create(modelSkydome.get()));
	skydome->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Home = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelHome.get()));
	Home->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Kotatu = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelKotatu.get()));
	Kotatu->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	TV = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelTV.get()));
	TV->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Chest = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelChest.get()));
	Chest->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	saku = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelSaku.get()));
	saku->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Slide = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelSlide.get()));
	Slide->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Swing = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelSwing.get()));
	Swing->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Tree = std::unique_ptr < TouchableObject>(TouchableObject::Create(modelTree.get()));
	Tree->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

}

void StageObject::Init()
{

}

void StageObject::stageInit(int stageNum)
{
	this->stageNum = stageNum;
	InitUpd(Ground, { 0,0,0 }, { 6,6,6 }, { 0,0,0,0 });
	skydome->SetPosition({ 0.0f,100.0f,0.0f });
	skydome->SetScale({ 4.0f,4.0f,4.0f });
	skydome->SetColor({ 1,1,1,1 });
	skydome->Update();
	if (stageNum == 1) {
		InitUpd(Kotatu, { 0,38,-80 }, { 1,1,1 }, { 0,0,0,0 });
		InitUpd(TV, { -20,28,-170 }, { 2,2,2 }, { 0,90,0,0 });
		InitUpd(Chest, { 20,46,126 }, { 4,4,4 }, { 0,90,0,0 });
		InitUpd(Home, { 0,0,0 }, { 1,1,1 }, { 0,0,0,0 });
		InitUpd(saku, { -190,58,-47.5f }, { 2,2,2 }, { 0,0,0,0 });
	}
	else if (stageNum == 2) {
		InitUpd(Slide, { 0,0,0 }, { 5,5,5 }, { 0,0,0,0 });
		InitUpd(Swing, { -30,0,0 }, { 1,1,1 }, { 0,0,0,0 });
		InitUpd(Tree, { -30,0,0 }, { 1,1,1 }, { 0,0,0,0 });
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

void StageObject::InitUpd(std::unique_ptr < TouchableObject>& obj, XMFLOAT3 position, XMFLOAT3 scale, XMVECTOR rot)
{
	obj->SetScale(scale);
	obj->SetPosition(position);
	obj->SetRotation(rot);
	obj->Quaternion();
	obj->SetColor({ 1,1,1,1 });
	obj->SetTouchCollider();
	obj->Update();
}