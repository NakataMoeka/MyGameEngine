cbuffer cbuff0 : register(b0)
{
	//float4 color;
	matrix mat; // ３Ｄ変換行列
	matrix matBillboard;
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 pos : POSITION; // システム用頂点座標
	float scale : TEXCOORD;

};
struct GSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv:TEXCOORD;
};