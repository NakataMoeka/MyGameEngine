#include "CollisionManager.h"
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
	Ssize = { 0,0,0 };
	IsHit = false;
	radius = 0;
	SY = 0;
}


//gamesceneでオブジェクト同士の当たり判定やりたかったがうまくいかなかったのでこちらで
/*プレイヤーとオブジェクトの当たり判定もこっちに移植したかったが
うまくいかなかったのでとりあえずこのまま。*/
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
			//oSize設定
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
			else if (colB->GetNum() == 5) {
				oSize = 10;
			}
			else if (colB->GetNum() == 6) {
				oSize = 20;
			}
			else if (colB->GetNum() == 7) {
				oSize = 30;
			}
			else if (colB->GetNum() == 8) {
				oSize = 40;
			}
			else if (colB->GetNum() == 9) {
				oSize = 50;
			}

			if (colB->attribute == 4U) {
				//DebugText::GetInstance()->Printf(100, 500, 3.0f, { 1,1,1,1 }, "%d", testCount);
				// ともに球
				//DebugText::GetInstance()->Printf(100, 60, 3.0f, { 1,1,1,1 }, "Hit");
				if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
					colB->GetShapeType() == COLLISIONSHAPE_SPHERE) {
					Sphere* SphereA = dynamic_cast<Sphere*>(colA);
					Sphere* SphereB = dynamic_cast<Sphere*>(colB);
					DirectX::XMVECTOR inter;
					//オブジェクトが両方球にくっついていたら当たり判定はしない
					if (colB->GetObject3d()->GetParentFlag() == false) {

						if (Tsize3 >= oSize * 10 || oSize == 1 || oSize == 10) {
							//くっつく
							colB->GetObject3d()->SetColFlag(true);
							if (Collision::CheckSphere2Sphere2(*SphereA, *SphereB, &inter)) {
								//球のサイズが以上ならくっつくoSize*10またはoSizeが1または10ならば
								IsHit = true;
								HitCount++;
								PFlag = true;
								//親子関係のフラグtrueにする
								colB->GetObject3d()->SetParentFlag(true);
								audioFlag = true;
							}
							//DebugText::GetInstance()->Printf(100, 500, 3.0f, { 1,1,1,1 }, "HIT");

						}
					}
				}
				if (IsHit == true) {
					//親子関係を設定する
					colB->GetObject3d()->SetParent(colA->GetObject3d());
				}
				if (HitCount == 1) {
					//くっつく
					colB->GetObject3d()->transformParent();
					HitCount = 0;
					IsHit = false;
					Tsize += oSize;
					Ssize.x += 0.001f;
					Ssize.y += 0.001f;
					Ssize.z += 0.001f;
					radius += 0.001f;
					SY += 0.005f;
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
				IsHit = false;
				return;
			}
			DebugText::GetInstance()->Printf(100, 100, 3.0f, { 1,1,1,1 }, "Atatta");
			IsHit = true;
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
				IsHit = false;
				return;
			}
			IsHit = false;
		}
	
		DebugText::GetInstance()->Printf(100, 200, 3.0f, { 1,1,1,1 }, "%d",IsHit);
	}

}
