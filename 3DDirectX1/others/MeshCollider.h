#pragma once
#include"BaseCollider.h"
#include"CollisionPrimitive.h"
#include<DirectXMath.h>
class MeshCollider:public BaseCollider
{
public:
	MeshCollider() 
	{
		shapeType = COLLISIONSHAPE_MESH;
	}

	void ConstructTriangles(Model* model);

	void Update() override;

	bool CheckCollisionSphere(const Sphere& sphere, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);


	bool CheckCollisionRay(const Ray& ray, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

private:
	std::vector<Triangle> triangles;
	// ���[���h�s��̋t�s��
	DirectX::XMMATRIX invMatWorld;
};

