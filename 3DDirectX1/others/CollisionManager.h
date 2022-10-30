#pragma once

#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include"QueryCallback.h"
#include <d3d12.h>
#include <forward_list>

class BaseCollider;

class CollisionManager
{
public:// 静的メンバ関数
	static CollisionManager* GetInstance();

public:// メンバ関数

	inline void AddCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	inline void RemoveCollider(BaseCollider* collider) {
		colliders.remove(collider);
	}


	void CheckAllCollisions();
	//オブジェクト指定できる球と球の当たり判定
	void ColSphere();
	bool Raycast(const Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);
	bool Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffffffff);

	bool GetAudioFlag() { return audioFlag; }
	bool SetAudioFlag(bool audioFlag) { return this->audioFlag=audioFlag; }
	float GetTsize() { return Tsize; }
	float SetTsize(float Tsize2) { return this->Tsize2 = Tsize2; }
	float GetHitCount() { return HitCount; }
	bool GetHit() { return IsHit; }
	bool SetParentFlag(bool parentFlag){ return parentFlag = false; }
private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;

	// コライダーのリスト
	std::forward_list<BaseCollider*> colliders;
	bool IsHit = false;
	int HitCount = 0;
	bool HitAlive = true;
	float Tsize = 0;
	bool audioFlag = false;
	float Tsize2 = 0;
};