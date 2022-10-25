#include "SphereColliderFbx.h"

using namespace DirectX;

void SphereColliderFbx::Update()
{

	const XMMATRIX& matWorld2 = Fobject->GetMatWorld();
	// 球のメンバ変数を更新
	Sphere::center = matWorld2.r[3] + offset;
	Sphere::radius = radius;
}
