#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Eas
{

private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	static const XMFLOAT2 lerp(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	static const XMFLOAT2 easeIn(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	static const XMFLOAT2 easeOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	static const XMFLOAT2 easeInOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 easeInOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	float easeInCubic(float x);//1
	float easeOutCubic(float x);//2
	float easeInQuad(float x);//3
	float easeOutQuad(float x);//4
	float easeOutBounce(float x);//5
	float easeInBounce(float x);//6
	/// <summary>
	/// イージング
	/// </summary>
	/// <param name="start">開始位置</param>
	/// <param name="end">終了位置</param>
	/// <param name="t">時間</param>
	/// <param name="d">終了時間</param>
	/// <param name="i">イージングの種類</param>
	float ease(const float& start, const float& end, float t, float d, int i);
	XMFLOAT2 ease(const XMFLOAT2& start, const XMFLOAT2& end, float t, float d, int i);
	XMFLOAT3 ease(const XMFLOAT3& start, const XMFLOAT3& end, float t, float d, int i);



};

