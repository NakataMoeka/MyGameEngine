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

	void Init();
	void CheckAllCollisions();
	//オブジェクト指定できる球と球の当たり判定
	void ColSphere();
	bool Raycast(const Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);
	bool Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffffffff);

	bool GetAudioFlag() { return audioFlag; }
	bool GetAudioFlag2() { return audioFlag2; }
	bool SetAudioFlag(bool audioFlag) { return this->audioFlag=audioFlag; }
	float GetTsize() { return Tsize3; }
	float SetTsize2(float Tsize2) { return this->Tsize2 = Tsize2; }
	float SetTsize(float Tsize) { return this->Tsize = Tsize; }
	int GetHitCount() { return HitCount; }
	bool GetHit() { return IsHit; }
	bool SetParentFlag(bool parentFlag) { return this->PFlag = parentFlag; }
	float SetoSize(float size) { return this->oSize=size; }
	float GetoSize() { return oSize; }
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
	bool audioFlag2 = false;
	float Tsize2 = 0;
	float Tsize3;
	bool PFlag=false;
	float oSize=0;
};