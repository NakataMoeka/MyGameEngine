#include "SphereCollider.h"

using namespace DirectX;

void SphereCollider::Update()
{
	//重い原因①
	// ワールド行列から座標を抽出
	const XMMATRIX& matWorld = object3d->GetMatWorld();
	// 球のメンバ変数を更新
	Sphere::center = matWorld.r[3] + offset;
	Sphere::radius = radius;
}
