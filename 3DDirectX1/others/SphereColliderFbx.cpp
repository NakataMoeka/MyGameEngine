#include "SphereColliderFbx.h"

using namespace DirectX;

void SphereColliderFbx::Update()
{

	const XMMATRIX& matWorld2 = Fobject->GetMatWorld();
	// ���̃����o�ϐ����X�V
	Sphere::center = matWorld2.r[3] + offset;
	Sphere::radius = radius;
}
