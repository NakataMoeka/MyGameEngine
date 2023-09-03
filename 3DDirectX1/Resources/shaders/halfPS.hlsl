#include"OBJ.hlsli"
Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
float4 main(VSOutput input) : SV_TARGET
{

	// �e�N�X�`���}�b�s���O
	float4 texcolor = tex.Sample(smp, input.uv);
	//// ����x
	//const float shininess = 4.0f;
	//// ���_���王�_�ւ̕����x�N�g��
	//float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	//float3 P = input.svpos.xyz;
	//float3 N = normalize(input.normal);
	////�@Ambient Color
	//float3 ambient = m_ambient;
	//float4 shadecolor = float4(ambientColor * ambient, m_alpha);
	//for (int i = 0; i < DIRLIGHT_NUM; i++) {
	//	if (dirLights[i].active) {
	//		// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
	//		float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
	//		// ���ˌ��x�N�g��
	//		float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
	//		// �g�U���ˌ�
	//		float3 diffuse = dotlightnormal * m_diffuse;
	//		// ���ʔ��ˌ�
	//		float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//		// �S�ĉ��Z����
	//		shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
	//	}
	//}

	//// �V�F�[�f�B���O�ɂ��F�ŕ`��
	//return (shadecolor * texcolor) * color;
	float3 P = input.svpos.xyz;
	float3 N = normalize(input.normal);
	float Ka = 0.5;

	//�@Ambient Color
	float3 ambient = m_ambient * Ka;
	float3 diffuse = float3(0, 0, 0);
	//�@Diffuse Color
	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLights[i].active) {
			float3 L = normalize(float3(0, 0, 1) - P);	//�@���[�J�����W�n�̂ł̃��C�g�x�N�g��
			float diffuseLight = max(dot(L, N), 0) * 0.5 + 0.5;
			diffuse = dirLights[i].lightcolor * (diffuseLight * diffuseLight);
		}
	}
	return float4(ambient + diffuse, 1.0f) * texcolor;
}