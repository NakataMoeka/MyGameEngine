#pragma once
#include "Sprite.h"
class PostEffect :public Sprite
{
private:

	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static const float clearColor[4];
	PostEffect();

	void Initialize();

	void Draw(ID3D12GraphicsCommandList* cmdList);

	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

private:
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff;
	//デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	// 深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	// RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	// DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;

};

