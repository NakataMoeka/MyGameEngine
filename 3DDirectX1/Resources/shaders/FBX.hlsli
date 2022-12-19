
//ボーンの最大数
static const int MAX_BONES = 32;


cbuffer cbuff0 : register(b0)
{
	//float4 color; // 色(RGBA)
	//matrix mat; // ３Ｄ変換行列
	matrix viewproj;
	matrix world;
	float3 cameraPos;
};

cbuffer skinning: register(b3)
{
	matrix matSkinning[MAX_BONES];
};

// 平行光源の数
static const int DIRLIGHT_NUM = 3;

struct DirLight
{
	float3 lightv;    // ライトへの方向の単位ベクトル
	float3 lightcolor;    // ライトの色(RGB)
	uint active;
};
//// 点光源の数
//static const int POINTLIGHT_NUM = 3;
//
//struct PointLight
//{
//	float3 lightpos;    // ライト座標
//	float3 lightcolor;  // ライトの色(RGB)
//	float3 lightatten;	// ライト距離減衰係数
//	uint active;
//};
//// スポットライトの数
//static const int SPOTLIGHT_NUM = 3;
//
//struct SpotLight
//{
//	float3 lightv;		// ライトの光線方向の逆ベクトル（単位ベクトル）
//	float3 lightpos;    // ライト座標
//	float3 lightcolor;  // ライトの色(RGB)
//	float3 lightatten;	// ライト距離減衰係数
//	float2 lightfactoranglecos; // ライト減衰角度のコサイン
//	uint active;
//};
//// 丸影の数
//static const int CIRCLESHADOW_NUM = 3;
//
//struct CircleShadow
//{
//	float3 dir;		// 投影方向の逆ベクトル（単位ベクトル）
//	float3 casterPos;    // キャスター座標
//	float  distanceCasterLight;	// キャスターとライトの距離
//	float3 atten;	// 距離減衰係数
//	float2 factorAngleCos; // 減衰角度のコサイン
//	uint active;
//};
//
cbuffer cbuff2 : register(b2)
{
	float3 ambientColor;
	DirLight dirLights[DIRLIGHT_NUM];
	//PointLight pointLights[POINTLIGHT_NUM];
	//SpotLight spotLights[SPOTLIGHT_NUM];
	//CircleShadow circleShadows[CIRCLESHADOW_NUM];
}

struct VSInput
{
	float4 pos : POSITION; // システム用頂点座標
	float3 normal :NORMAL; // 法線ベクトル
	float2 uv  :TEXCOORD; // uv値
	uint4 boneIndices:BONEINDICES;
	float4 boneWeights: BONEWEIGHTS;
};


// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float4 worldpos : POSITION; // ワールド座標
	float3 normal :NORMAL; // 法線ベクトル
	float2 uv  :TEXCOORD; // uv値
};
