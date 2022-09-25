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
	for (int i = 0; i < OBJNomber; i++) {
		modelCube = Model::Create("cube", false);
		cube[i] = Object3d::Create(modelCube);
		cube[i]->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	}

}

void GameObject::Init()
{

	for (int i = 0; i < OBJNomber; i++) {

		float radius = 2.0f;
		//csv�ł�����
		position[0] = { 10,2,0 };
		position[1] = { 0,10,10 };
		position[2] = { -10, 2, 0 };
		position[3] = { -50,2,-40 };
		position[4] = { 0, 2, 10 };
		position[5] = { -10, 2, 60 };
		position[6] = { 50,2,30 };
		position[7] = { 0, 2, 50 };
		position[8] = { -30, 2, 20 };
		position[9] = { 30, 2, -20 };
		size = { 1,1,1 };
		rota = { 0,0,0,0 };
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
//������Set����Ɨ���Ă��������炵�Ȃ��悤��!!
	for (int i = 0; i < OBJNomber; i++) {
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
	for (int i = 0; i < OBJNomber; i++) {
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


