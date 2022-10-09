#pragma once
#include<DirectXMath.h>
//�����߂������������N���X
//�������I�u�W�F�N�g�p(�ǂƂ��͕ʂ̂�ł��)
class pushCollision
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	void PushBack();
private:
	
	XMFLOAT3 oldPos{};
	XMFLOAT3 Pos{};
};