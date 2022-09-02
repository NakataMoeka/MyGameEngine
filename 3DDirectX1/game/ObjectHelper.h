#pragma once
#include"Collision.h"
//オブジェクトの構造体を書くヘッダーファイル

// Microsoft::WRL::を省略
template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMMATRIX = DirectX::XMMATRIX;
using XMVECTOR = DirectX::XMVECTOR;
struct object
{
	Sphere sphere;//当たり判定用の球
	float oSize;//オブジェクトのサイズ(球を大きくするために設定するやつ)
	//これより下にpositionなど書いていく
	XMFLOAT3 pos = {};//位置
	XMVECTOR rot = {};//角度(クォータニオンを使用しているため、XMVECTOR)
	XMFLOAT3 size = {};//見た目のサイズ(oSizeとは違う)
};