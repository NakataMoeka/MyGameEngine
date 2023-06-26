#include "StageObject.h"
#include"TouchableObject.h"

StageObject::StageObject()
{
}

StageObject::~StageObject()
{
}

void StageObject::Initialize(const std::string& modelname)
{

	model = std::unique_ptr<Model>(Model::Create(modelname, false));
	obj = std::unique_ptr < TouchableObject>(TouchableObject::Create(model.get()));
	//obj = std::unique_ptr < Object3d>(Object3d::Create(model.get()));
	obj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

}

void StageObject::Init(XMFLOAT3 pos, XMFLOAT3 size, XMVECTOR rot)
{
	obj->SetScale(size);
	obj->SetPosition(pos);
	obj->SetRotation(rot);
	obj->Quaternion();
	obj->SetColor({ 1,1,1,1 });
	obj->SetTouchCollider();
	obj->Update();
}


void StageObject::Update()
{
	obj->Update();
}

void StageObject::Draw()
{
	obj->Draw();
}

void StageObject::RC()
{
	obj->RemoveCollider();
}
