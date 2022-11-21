#pragma once

#include "CollisionType.h"
#include "CollisionInfo.h"
#include "Object3d.h"
#include "FbxObject.h"

/// <summary>
/// �R���C�_�[���N���X
/// </summary>
class BaseCollider
{
	friend class CollisionManager;
public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	inline void SetObject(Object3d* object) {
		this->object3d = object;
	}
	inline void SetObject2(FbxObject3d* object) {
		this->Fobject = object;
	}
	inline Object3d* GetObject3d() {
		return object3d;
	}
	inline FbxObject3d* GetFbxObject() {
		return Fobject;
	}
	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType; }


	inline void OnCollision(const CollisionInfo& info) {
		object3d->OnCollision(info);
	}
	//inline void OnFCollision(const CollisionInfo& info) {
	//	Fobject->OnFCollision(info);
	//}
	inline void SetAttribute(unsigned short attribute) {
		this->attribute = attribute;
	}

	inline void AddAttribute(unsigned short attribute) {
		this->attribute |= attribute;
	}

	inline void RemoveAttribute(unsigned short attribute) {
		this->attribute &= !attribute;
	}
	inline int SetNum(int num) {
		return this->Num = num;
	}
	inline int GetNum() { return Num; }
protected:
	Object3d* object3d = nullptr;
	FbxObject3d* Fobject = nullptr;
	// �`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	// �����蔻�葮��
	unsigned short attribute = 0b1111111111111111;
	//���
	int Num = 0;
};

