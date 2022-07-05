#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	modelCube = modelCube->Create("cube", false);
	cube = Object3d::Create(modelCube);
	cube->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
}

void GameObject::Init()
{
}

void GameObject::Update()
{
	cube->SetPosition({ 0,-0.8,0 });
	cube->SetScale({ 0.1,0.1,0.1 });
	cube->Update();
}

void GameObject::Draw()
{
	cube->Draw();
}
