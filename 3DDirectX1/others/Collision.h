#pragma once
#include"CollisionPrimitive.h"
#include<DirectXMath.h>

class Collision {
private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	static bool CheackSphere2Plane(const Sphere& sphere, const Plane& plane,
		DirectX::XMVECTOR* inter = nullptr);

	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point,
		const Triangle& triangle, DirectX::XMVECTOR* closest);

	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle,
		DirectX::XMVECTOR* inter = nullptr,DirectX::XMVECTOR* reject = nullptr);
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane,
		float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle,
		float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere,
		float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);
	static bool CheckSphere2Sphere2 (const Sphere& sphereA, const Sphere& sphereB, 
		DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);

	static bool CheckSphere2Box(const Sphere& sphere, const Box& box);
	static bool CheckSphere2OBB(Sphere& sphere, OBB& obb);
	static bool CheckOBB2OBB(OBB& obbA, OBB& obbB);
	static float LenSegOnSeparateAxis(DirectX::XMVECTOR* Sep, DirectX::XMVECTOR* e1, DirectX::XMVECTOR* e2, DirectX::XMVECTOR* e3 = 0);

};