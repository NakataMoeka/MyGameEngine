#pragma once
#include "Sprite.h"
class PostEffect :public Sprite
{
private:

	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	PostEffect();

	void Initialize();

	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff;
	//デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

};

