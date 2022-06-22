#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Eas
{

private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	static const XMFLOAT3 lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float t);
	static const XMFLOAT3 easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t);
};

