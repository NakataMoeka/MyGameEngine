#include "SphereColliderFbx.h"

using namespace DirectX;

void SphereColliderFbx::Update()
{

	const XMMATRIX& matWorld2 = Fobject->GetMatWorld();
	// ‹…‚Ìƒƒ“ƒo•Ï”‚ğXV
	Sphere::center = matWorld2.r[3] + offset;
	Sphere::radius = radius;
}
