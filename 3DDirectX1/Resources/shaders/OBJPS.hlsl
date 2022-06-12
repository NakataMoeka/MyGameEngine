#include "OBJ.hlsli"

Texture2D<float4> tex : register(t0);	//0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);		//0番スロットに設定されたサンプラー
struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

PSOutput main(VSOutput input) 
{
		PSOutput output;
	float4 texcolor = tex.Sample(smp, input.uv);
	float4 shadercolor;
	//光沢度
	const float shininess = 4.0f;
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	float3 dotlightnormal = dot(lightv, input.normal);
	float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
	float3 ambient = m_ambient;
	float3 diffuse = dotlightnormal * m_diffuse;
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	shadercolor.rgb = (ambient + diffuse + specular) * lightcolor;
	shadercolor.a = m_alpha;


	output.target0 = shadercolor * texcolor;
	output.target1 = float4(1 - (shadercolor * texcolor).rgb, 1);
	return output;
}