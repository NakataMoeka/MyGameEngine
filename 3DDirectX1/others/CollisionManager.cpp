﻿#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Collision.h"
#include"DebugText.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
using namespace DirectX;

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::Init()
{

	IsHit = false;
	audioFlag2 = false;

}

void CollisionManager::CheckAllCollisions()
{
	////重い一番の原因
	//std::forward_list<BaseCollider*>::iterator itA;
	//std::forward_list<BaseCollider*>::iterator itB;

	//// 全ての組み合わせについて総当りチェック
	//itA = colliders.begin();
	//for (; itA != colliders.end(); ++itA) {
	//	itB = itA;
	//	++itB;
	//	for (; itB != colliders.end(); ++itB) {
	//		BaseCollider* colA = *itA;
	//		BaseCollider* colB = *itB;

	//		// ともに球
	//		if (colA->attribute == 2) {
	//			
	//			if (colA->GetShapeType() == COLLISIONSHAPE_MESH &&
	//				colB->GetShapeType() == COLLISIONSHAPE_SPHERE) {
	//				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);
	//				Sphere* sphere = dynamic_cast<Sphere*>(colB);
	//				DirectX::XMVECTOR inter;
	//				if (meshCollider->CheckCollisionSphere(*sphere, &inter)) {
	//					//colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
	//					//colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
	//					DebugText::GetInstance()->Printf(100, 40, 3.0f, "Hit");

	//				}
	//			}
	//			else if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
	//				colB->GetShapeType() == COLLISIONSHAPE_MESH) {
	//				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colB);
	//				Sphere* sphere = dynamic_cast<Sphere*>(colA);
	//				DirectX::XMVECTOR inter;
	//				if (meshCollider->CheckCollisionSphere(*sphere, &inter)) {
	//					//colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
	//					//colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
	//					DebugText::GetInstance()->Printf(100, 40, 3.0f, "Hit");
	//				}
	//			}
	//		}
	//	}
	//}
}

void CollisionManager::ColSphere()
{

	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	// 全ての組み合わせについて総当りチェック
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA) {
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB) {
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;
			if (colB->GetNum() == 0) {
				oSize = 1;
			}
			else if (colB->GetNum() == 1) {
				oSize = 2;
			}
			else if (colB->GetNum() == 2) {
				oSize = 3;
			}
			else if (colB->GetNum() == 3) {
				oSize = 4;
			}
			else if (colB->GetNum() == 4) {
				oSize = 5;
			}
			if (colB->attribute==4U) {
				// ともに球
				//DebugText::GetInstance()->Printf(100, 60, 3.0f, { 1,1,1,1 }, "Hit");
				if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
					colB->GetShapeType() == COLLISIONSHAPE_SPHERE) {
					Sphere* SphereA = dynamic_cast<Sphere*>(colA);
					Sphere* SphereB = dynamic_cast<Sphere*>(colB);
					DirectX::XMVECTOR inter;
					//オブジェクトが両方球にくっついていたら当たり判定はしない
					if (colB->GetObject3d()->GetParentFlag() == false) {
						if (Collision::CheckSphere2Sphere2(*SphereA, *SphereB, &inter)) {
							if (Tsize3 >= oSize * 10||oSize==1) {
								IsHit = true;
								HitCount++;
								PFlag = true;
								colB->GetObject3d()->SetParentFlag(true);
								audioFlag = true;
							}
							

						}
						if (IsHit == true) {
							colB->GetObject3d()->SetParent(colA->GetObject3d());
						}
						if (HitCount == 1) {
							colB->GetObject3d()->transformParent();
							HitCount = 0;
							IsHit = false;
							Tsize += oSize;
						}
					}
				}
			}

		}
	}
	Tsize3 = Tsize + Tsize2;
}

bool CollisionManager::Raycast(const Ray& ray, RaycastHit* hitInfo, float maxDistance)
{
	return Raycast(ray, 0xffff, hitInfo, maxDistance);
}

bool CollisionManager::Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo, float maxDistance)
{
	bool result = false;
	std::forward_list<BaseCollider*>::iterator it;
	std::forward_list<BaseCollider*>::iterator it_hit;
	float distance = maxDistance;
	XMVECTOR inter;

	// 全てのコライダーと総当りチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it) {
		BaseCollider* colA = *it;

		// 属性が合わなければスキップ
		if (!(colA->attribute & attribute)) {
			continue;
		}

		if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE) {
			Sphere* sphere = dynamic_cast<Sphere*>(colA);

			float tempDistance;
			XMVECTOR tempInter;

			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter)) continue;
			if (tempDistance >= distance) continue;

			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
		else if (colA->GetShapeType() == COLLISIONSHAPE_MESH) {
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);

			float tempDistance;
			DirectX::XMVECTOR tempInter;
			if (!meshCollider->CheckCollisionRay(ray, &tempDistance, &tempInter)) continue;
			if (tempDistance >= distance) continue;


			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
	}

	if (result && hitInfo) {
		hitInfo->distance = distance;
		hitInfo->inter = inter;
		hitInfo->collider = *it_hit;
		hitInfo->object = hitInfo->collider->GetObject3d();
	}

	return result;
}

void CollisionManager::QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	// 全てのコライダーと総当りチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it) {
		BaseCollider* col = *it;

		// 属性が合わなければスキップ
		if (!(col->attribute & attribute)) {
			continue;
		}

		// 球
		if (col->GetShapeType() == COLLISIONSHAPE_SPHERE) {
			Sphere* sphereB = dynamic_cast<Sphere*>(col);

			XMVECTOR tempInter;
			XMVECTOR tempReject;
			if (!Collision::CheckSphere2Sphere2(sphere, *sphereB, &tempInter, &tempReject)) continue;
			
			// 交差情報をセット
			QueryHit info;
			info.collider = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;
		
			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info)) {
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
			
		}
		// メッシュ
		else if (col->GetShapeType() == COLLISIONSHAPE_MESH) {
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(col);

			XMVECTOR tempInter;
			XMVECTOR tempReject;
			if (!meshCollider->CheckCollisionSphere(sphere, &tempInter, &tempReject)) continue;

			// 交差情報をセット
			QueryHit info;
			info.collider = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info)) {
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
		}
	}

}
