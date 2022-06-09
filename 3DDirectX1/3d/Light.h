#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Light {
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	struct ConstBufferData
	{
		XMVECTOR lightv;
		XMFLOAT3  lightcolor;
	};

	static void StaticInitialize(ID3D12Device* device);

	static Light* Create();

	void Initialize();

	void TransferConstBuffer();

	void Update();

	void SetLightDir(const XMVECTOR& lightdir);

	void SetLightColor(const XMFLOAT3 lightcolor);

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

private://静的メンバ変数
	static ID3D12Device* device;
private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向(単位ベクトル)
	XMVECTOR lightdir = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor{ 1,1,1 };
	//ダーティーフラグ
	bool dirty = false;
}; 

