#pragma once

#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include"QueryCallback.h"
#include <d3d12.h>
#include <forward_list>

class BaseCollider;

class CollisionManager
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
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
	bool SetAudioFlag(bool audioFlag) { return this->audioFlag = audioFlag; }
	float GetTsize() { return Tsize3; }
	float SetTsize2(float Tsize2) { return this->Tsize2 = Tsize2; }
	float SetTsize(float Tsize) { return this->Tsize = Tsize; }
	int GetHitCount() { return HitCount; }
	bool GetHit() { return IsHit; }
	bool SetParentFlag(bool parentFlag) { return this->PFlag = parentFlag; }
	float SetoSize(float size) { return this->oSize = size; }
	float GetoSize() { return oSize; }
	XMFLOAT3 GetSsize() { return Ssize; }
	float GetRadius() { return radius; }
	float GetSY() { return SY; }
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
	XMFLOAT3 Ssize = { 1,1,1 };
	float Tsize2 = 0;
	float Tsize3;
	bool PFlag = false;
	float oSize = 0;
	float radius = 0;
	float SY = 0;
};