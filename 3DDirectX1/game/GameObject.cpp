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
	for (int i = 0; i < 2; i++) {
		modelCube = modelCube->Create("cube", false);
		cube[i] = Object3d::Create(modelCube);
		cube[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	}
}

void GameObject::Init()
{
	for (int i = 0; i < 2; i++) {
		if (ColFlag[i] == false) {
			cSphere.radius = r;
			cSphere.center = XMVectorSet(position[i].x, position[i].y, position[i].z, 1);
			cBox[i].minPosition = XMVectorSet(position[i].x - r, position[i].y - r, position[i].z - r, 1);
			cBox[i].maxPosition = XMVectorSet(position[i].x + r, position[i].y + r, position[i].z + r, 1);
			cube[i]->SetPosition(position[i]);
			cube[i]->SetScale(size);
			cube[i]->Update();
		}
	}
}

void GameObject::Update()
{
//‚±‚±‚ÅSet‚·‚é‚Æ—£‚ê‚Ä‚­‚Á‚Â‚­‚©‚ç‚µ‚È‚¢‚æ‚¤‚É!!
	for (int i = 0; i < 2; i++) {
		if (ColFlag[i] == false) {
			cBox[i].minPosition = XMVectorSet(position[i].x - r, position[i].y - r, position[i].z - r, 1);
			cBox[i].maxPosition = XMVectorSet(position[i].x + r, position[i].y + r, position[i].z + r, 1);
			//cube[i]->SetPosition(position[i]);
			//cube[i]->SetScale(size);
		}
		cube[i]->Update();
	}
}

void GameObject::Draw()
{
	for (int i = 0; i < 2; i++) {
		cube[i]->Draw();
	}
}


