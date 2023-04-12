#pragma once

#include<DirectXMath.h>
class Object3d;
class BaseCollider;
struct QueryHit
{
	// 衝突相手のオブジェクト
	Object3d* object = nullptr;
	// 衝突相手のコライダー
	BaseCollider* collider = nullptr;
	// 衝突点
	DirectX::XMVECTOR inter;
	// 排斥ベクトル
	DirectX::XMVECTOR reject;
};

/// <summary>
/// クエリーで交差を検出した時の動作を規定するクラス
/// </summary>
class QueryCallback
{
public:
	QueryCallback() = default;
	virtual ~QueryCallback() = default;

	virtual bool OnQueryHit(const QueryHit& info) = 0;
};
