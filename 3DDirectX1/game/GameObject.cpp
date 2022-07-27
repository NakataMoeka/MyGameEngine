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
			//position‚Í‰½‚È‚Ì‚©center‚É‚Í‰½‚ð‘ã“ü‚·‚é‚Ì‚©
		cube[i]->SetPosition(position[i]);
		cube[i]->SetScale(size);
		cube[i]->Quaternion();
		cube[i]->Update();
			cSphere[i].radius = r;
			//cSphere[i].center = XMVectorSet(position[i].x, position[i].y, position[i].z, 1);
			cSphere[i].center = XMVectorSet(cube[i]->GetMat().r[3].m128_f32[0], cube[i]->GetMat().r[3].m128_f32[1], cube[i]->GetMat().r[3].m128_f32[2], 1);
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
//‚±‚±‚ÅSet‚·‚é‚Æ—£‚ê‚Ä‚­‚Á‚Â‚­‚©‚ç‚µ‚È‚¢‚æ‚¤‚É!!
	for (int i = 0; i < 2; i++) {
		cSphere[i].radius = r;
		cSphere[i].center = XMVectorSet(cube[i]->GetMat().r[3].m128_f32[0], cube[i]->GetMat().r[3].m128_f32[1], cube[i]->GetMat().r[3].m128_f32[2], 1);

		//obb[i].m_NormaDirect[0] = { cube[i]->GetMatRot().r[0].m128_f32[0],cube[i]->GetMatRot().r[0].m128_f32[1] ,cube[i]->GetMatRot().r[0].m128_f32[2] };
		//obb[i].m_NormaDirect[1] = { cube[i]->GetMatRot().r[1].m128_f32[0],cube[i]->GetMatRot().r[1].m128_f32[1] ,cube[i]->GetMatRot().r[1].m128_f32[2] };
		//obb[i].m_NormaDirect[2] = { cube[i]->GetMatRot().r[2].m128_f32[0],cube[i]->GetMatRot().r[2].m128_f32[1] ,cube[i]->GetMatRot().r[2].m128_f32[2] };
		//obb[i].m_fLength[0] = 0.5;
		//obb[i].m_fLength[1] = 0.5;
		//obb[i].m_fLength[2] = 0.5;
		//obb[i].m_Pos = { position[i].x, position[i].y, position[i].z };

		//cube[i]->SetPosition(position[i]);
			//cube[i]->SetScale(size);
			//cube[i]->Quaternion();
			cube[i]->Update();
	}
}

void GameObject::Draw()
{
	for (int i = 0; i < 2; i++) {
		cube[i]->Draw();
	}
}

void GameObject::Delete(int i)
{
	//delete cBox[i];
}

float GameObject::GetMat()
{
	return 	cube[0]->GetMatRot().r[3].m128_f32[0];
}


