#include "GObject.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"

using namespace DirectX;
void GObject::Initialize(Model* model)
{
	obj = Object3d::Create(model);
	obj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
}

void GObject::Init(XMFLOAT3 pos, XMFLOAT3 size, XMVECTOR rot, float y, float radius)
{
	obj->SetPosition(pos);
	obj->SetScale(size);
	obj->Quaternion();
	obj->SetRotation(rot);
	obj->Update();
	obj->SetParentFlag(false);
	obj->SetColFlag(false);
	obj->SetCollider(new SphereCollider(XMVECTOR({ 0,y,0,0 }), radius));
	obj->GetCollider()->SetAttribute(COLLISION_ATTR_OBJECT);
}

void GObject::Update(XMVECTOR rot, bool move)
{
	//moveがtrueでくっついてない時y軸回転する。
	if (move == true) {
		if (obj->GetParentFlag() == false) {
			rot.m128_f32[1] += 2;
		}
	}
	if (obj->GetColFlag() == true) {
		//当たったらコライダーの削除
		obj->RemoveCollider();
	}
	obj->SetRotation(rot);
	obj->Quaternion();
	obj->Update();
}

void GObject::RC()
{
	obj->RemoveCollider();
	obj->SetParentFlag(false);
}

void GObject::Draw()
{
	obj->Draw();
}

Object3d* GObject::GetOBJ3d()
{
	return obj;
}

XMMATRIX GObject::GetMatWorld()
{
	return obj->GetMatWorld();
}

