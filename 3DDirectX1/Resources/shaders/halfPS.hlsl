#include"OBJ.hlsli"
Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー
float4 main(VSOutput input) : SV_TARGET
{

	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	//// 光沢度
	//const float shininess = 4.0f;
	//// 頂点から視点への方向ベクトル
	//float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	//float3 P = input.svpos.xyz;
	//float3 N = normalize(input.normal);
	////　Ambient Color
	//float3 ambient = m_ambient;
	//float4 shadecolor = float4(ambientColor * ambient, m_alpha);
	//for (int i = 0; i < DIRLIGHT_NUM; i++) {
	//	if (dirLights[i].active) {
	//		// ライトに向かうベクトルと法線の内積
	//		float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
	//		// 反射光ベクトル
	//		float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
	//		// 拡散反射光
	//		float3 diffuse = dotlightnormal * m_diffuse;
	//		// 鏡面反射光
	//		float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//		// 全て加算する
	//		shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
	//	}
	//}

	//// シェーディングによる色で描画
	//return (shadecolor * texcolor) * color;
	float3 P = input.svpos.xyz;
	float3 N = normalize(input.normal);
	float Ka = 0.5;

	//　Ambient Color
	float3 ambient = m_ambient * Ka;
	float3 diffuse = float3(0, 0, 0);
	//　Diffuse Color
	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLights[i].active) {
			float3 L = normalize(float3(0, 0, 1) - P);	//　ローカル座標系のでのライトベクトル
			float diffuseLight = max(dot(L, N), 0) * 0.5 + 0.5;
			diffuse = dirLights[i].lightcolor * (diffuseLight * diffuseLight);
		}
	}
	return float4(ambient + diffuse, 1.0f) * texcolor;
}