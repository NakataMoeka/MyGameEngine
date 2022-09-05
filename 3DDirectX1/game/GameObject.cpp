#include "GameObject.h"
#include "SphereCollider.h"
//#include "CollisionManager.h"
//#include "CollisionAttribute.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
using namespace DirectX;
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	for (int i = 0; i < 3; i++) {
		modelCube = Model::Create("cube", false);
		cube[i] = Object3d::Create(modelCube);
		cube[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	}

}

void GameObject::Init()
{

	for (int i = 0; i < 3; i++) {
			//positionは何なのかcenterには何を代入するのか
				// コライダーの追加
		float radius = 2.0f;
		//cube[i]->SetCollider(new SphereCollider(XMVECTOR({ 0,0,0,0 }), radius));

		cube[i]->SetPosition(position[i]);
		cube[i]->SetScale(size);
		cube[i]->Quaternion();
		cube[i]->SetRotation(rota);
		cube[i]->Update();
			cSphere[i].radius = r;
			//cSphere[i].center = XMVectorSet(position[i].x, position[i].y, position[i].z, 1);
			cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);
			//obb[i].m_NormaDirect[0] = { cube[i]->GetMatRot().r[0].m128_f32[0],cube[i]->GetMatRot().r[0].m128_f32[1] ,cube[i]->GetMatRot().r[0].m128_f32[2] };
			//obb[i].m_NormaDirect[1] = { cube[i]->GetMatRot().r[1].m128_f32[0],cube[i]->GetMatRot().r[1].m128_f32[1] ,cube[i]->GetMatRot().r[1].m128_f32[2] };
			//obb[i].m_NormaDirect[2] = { cube[i]->GetMatRot().r[2].m128_f32[0],cube[i]->GetMatRot().r[2].m128_f32[1] ,cube[i]->GetMatRot().r[2].m128_f32[2] };
			//obb[i].m_fLength[0] = 0.5;
			//obb[i].m_fLength[1] = 0.5;
			//obb[i].m_fLength[2] = 0.5;
			//obb[i].m_Pos = { position[i].x, position[i].y, position[i].z};
		
		
	}


}

void GameObject::Update()
{
//ここでSetすると離れてくっつくからしないように!!
	for (int i = 0; i < 3; i++) {
		cSphere[i].radius = r;
		cSphere[i].center = XMVectorSet(cube[i]->GetMatWorld().r[3].m128_f32[0], cube[i]->GetMatWorld().r[3].m128_f32[1], cube[i]->GetMatWorld().r[3].m128_f32[2], 1);

		//obb[i].m_NormaDirect[0] = { cube[i]->GetMatRot().r[0].m128_f32[0],cube[i]->GetMatRot().r[0].m128_f32[1] ,cube[i]->GetMatRot().r[0].m128_f32[2] };
		//obb[i].m_NormaDirect[1] = { cube[i]->GetMatRot().r[1].m128_f32[0],cube[i]->GetMatRot().r[1].m128_f32[1] ,cube[i]->GetMatRot().r[1].m128_f32[2] };
		//obb[i].m_NormaDirect[2] = { cube[i]->GetMatRot().r[2].m128_f32[0],cube[i]->GetMatRot().r[2].m128_f32[1] ,cube[i]->GetMatRot().r[2].m128_f32[2] };
		//obb[i].m_fLength[0] = 0.5;
		//obb[i].m_fLength[1] = 0.5;
		//obb[i].m_fLength[2] = 0.5;
		//obb[i].m_Pos = { position[i].x, position[i].y, position[i].z };

		//cube[i]->SetPosition(position[i]);
			//cube[i]->SetScale(size);
			cube[i]->Quaternion();
			cube[i]->SetRotation(rota);
			cube[i]->Update();
	}
	
}

void GameObject::Draw()
{
	for (int i = 0; i < 3; i++) {
		cube[i]->Draw();
	}

}

void GameObject::Delete(int i)
{
	//cSphere[i].
}

float GameObject::GetMat()
{
	return 	cube[0]->GetMatRot().r[3].m128_f32[0];
}


