#pragma once
#include<DirectXMath.h>
//押し戻し処理を書くクラス
//くっつくオブジェクト用(壁とかは別のやつでやる)
class pushCollision
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
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