#pragma once
#include<DirectXMath.h>

struct Sphere
{
	//中心座標
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//半径
	float radius = 1.0f;
};
struct Box
{
	//最小値
	DirectX::XMVECTOR minPosition;
	//最大値
	DirectX::XMVECTOR maxPosition;

};

struct Plane
{
	//法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//原点からの距離
	float distance = 0.0f;
};
struct Ray
{
	DirectX::XMVECTOR start = { 0,0,0,1 };
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};
class Triangle
{
public:
	//頂点座標3つ
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;
	//法線ベクトル
	DirectX::XMVECTOR normal;

	void ComputeNormal();
};
class OBB {

public:
	
		DirectX::XMVECTOR m_Pos;
		DirectX::XMVECTOR m_NormaDirect[3];
		float m_fLength[3];

		DirectX::XMVECTOR GetDirect(int elem) { return m_NormaDirect[elem]; }   // 指定軸番号の方向ベクトルを取得
		float GetLen_W(int elem) { return m_fLength[elem]; }          // 指定軸方向の長さを取得
		DirectX::XMVECTOR GetPos_W() { return m_Pos; }
};