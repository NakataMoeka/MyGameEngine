#pragma once

#include "CollisionPrimitive.h"

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
	int GetColCount() { return colCount; }
	bool GetColflag() { return colflag; }
private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;

	// コライダーのリスト
	std::forward_list<BaseCollider*> colliders;
	int colCount = 0;
	bool colflag = false;
};

