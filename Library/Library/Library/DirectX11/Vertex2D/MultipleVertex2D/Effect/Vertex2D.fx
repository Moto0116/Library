Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global : register(b0)
{
	float4 g_ViewPort;
};

struct VS_INPUT
{
	float4 Pos		: POSITION;
	float2 UV		: TEXCOORD;
	float4 Color	: COLOR;
	float4x4 Mat    : MATRIX;          // �C���X�^���X���Ƃɐݒ肳���s��
	uint InstanceId : SV_InstanceID;   // �C���X�^���X�h�c
};

struct VS_OUTPUT
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD;
	float4 Color	: COLOR;
};

struct PS_INPUT
{
	float4 Pos   : SV_POSITION;
	float2 UV    : TEXCOORD;
	float4 Color : COLOR;
};

VS_OUTPUT VS(VS_INPUT In)
{
	VS_OUTPUT Out;
	
	Out.Pos = mul(In.Pos, In.Mat);
	Out.Pos.x = (Out.Pos.x / g_ViewPort.x) * 2 - 1;
	Out.Pos.y = 1 - (Out.Pos.y / g_ViewPort.y) * 2;
	Out.UV = In.UV;
	Out.Color = In.Color;

	return Out;
}

float4 PS(PS_INPUT In) : SV_Target
{
	float4 OutColor;
	OutColor = g_Texture.Sample(g_Sampler, In.UV);
	OutColor *= In.Color;
	return OutColor;
}
