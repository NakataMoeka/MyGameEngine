#include "Blur.hlsli"

Texture2D<float4> tex : register(t0);	//0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);		//0番スロットに設定されたサンプラー
float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d) / (2 * sigma * sigma));
}
float4 main(VSOutput input) : SV_TARGET
{
	//	//ぼかし
	//float oU = 2.5 / 1280;
	//float oV = 2.5 / 720;
	//float4 texcolor = tex.Sample(smp, input.uv);
	//
	//texcolor += tex.Sample(smp, input.uv + float2(oU, 0.0f));
	//texcolor += tex.Sample(smp, input.uv + float2(-oU, 0.0f));
	//texcolor += tex.Sample(smp, input.uv + float2(0.0f, oV));
	//texcolor += tex.Sample(smp, input.uv + float2(0.0f, -oV));
	//texcolor += tex.Sample(smp, input.uv + float2(0.0f, 0.0f));
	//texcolor += tex.Sample(smp, input.uv + float2(oU, oV));
	//texcolor += tex.Sample(smp, input.uv + float2(oU, -oV));
	//texcolor += tex.Sample(smp, input.uv + float2(-oU, oV));
	//texcolor += tex.Sample(smp, input.uv + float2(-oU, -oV));
	//
	//texcolor /= 9.0f;
	////ここまで
	//
	//return texcolor;

			float totalWeight = 0, _Sigma = 0.005, _StepWight = 0.001;
			float4 col = float4(0, 0, 0, 0);

			for (float py = -_Sigma * 2; py <= _Sigma * 2; py += _StepWight)
			{
				for (float px = -_Sigma * 2; px <= _Sigma * 2; px += _StepWight)
				{
					float2 pickUV = input.uv + float2(px, py);
					float weight = Gaussian(input.uv, pickUV, _Sigma);
					col += tex.Sample(smp, pickUV) * weight;
					totalWeight += weight;
				}
			}
			col.rgb = col.rgb / totalWeight;



				return col;
}



