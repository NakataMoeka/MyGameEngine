#include "GameObject.h"
using namespace DirectX;
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
	cBox.minPosition = XMVectorSet(position.x - r, position.y - r, position.z - r, 1);
	cBox.maxPosition = XMVectorSet(position.x + r, position.y + r, position.z + r, 1);
}

void GameObject::Update()
{
	cube->SetPosition(position);
	cube->SetScale({ 0.1,0.1,0.1 });
	cube->Update();
}

void GameObject::Draw()
{
	cube->Draw();
}
