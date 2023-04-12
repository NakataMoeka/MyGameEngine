#pragma once

#include<DirectXMath.h>
class Object3d;
class BaseCollider;
struct QueryHit
{
	// �Փˑ���̃I�u�W�F�N�g
	Object3d* object = nullptr;
	// �Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	// �Փ˓_
	DirectX::XMVECTOR inter;
	// �r�˃x�N�g��
	DirectX::XMVECTOR reject;
};

/// <summary>
/// �N�G���[�Ō��������o�������̓�����K�肷��N���X
/// </summary>
class QueryCallback
{
public:
	QueryCallback() = default;
	virtual ~QueryCallback() = default;

	virtual bool OnQueryHit(const QueryHit& info) = 0;
};
