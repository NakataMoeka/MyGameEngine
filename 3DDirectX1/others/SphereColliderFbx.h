#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>


class SphereColliderFbx : public BaseCollider, public Sphere
{
private: // エイリアス
	// DirectX::を省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	SphereColliderFbx(XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f) :
		offset(offset),
		radius(radius)
	{
		shapeType = COLLISIONSHAPE_SPHERE;
	}
	//球でも指定OK
	SphereColliderFbx(Sphere sphere)
		: offset(sphere.center), radius(sphere.radius)
	{

		shapeType = COLLISIONSHAPE_SPHERE;
	}


	void Update() override;

	inline const XMVECTOR& GetOffset() { return offset; }

	inline void SetOffset(const XMVECTOR& offset) { this->offset = offset; }

	inline float GetRadius() { return radius; }

	inline void SetRadius(float radius) { this->radius = radius; }

private:

	XMVECTOR offset;

	float radius;
};

