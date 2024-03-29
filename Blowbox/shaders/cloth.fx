cbuffer Global : register(b0)
{
	float time;
	float4x4 view;
	float4x4 projection;
}

cbuffer Object : register(b1)
{
	float4x4 world;
	float alpha;
}

struct VOut
{
	float4 position : SV_POSITION;
	float4 colour : COLOUR;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

VOut VS(float4 position : POSITION, float3 normal : NORMAL, float2 texcoord : TEXCOORD0, float4 colour : COLOUR)
{
	VOut output;
	output.position = mul(position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	output.colour = colour;
	output.texcoord = texcoord;
	output.normal = normal;
	return output;
}

Texture2D tex;
SamplerState Sampler;

float4 PS(VOut input) : SV_TARGET
{
	float4 base = tex.Sample(Sampler, input.texcoord);
	float4 color = float4(base.rgb, base.a);

	color.a *= alpha;

	float3 lightDir = float3(0.5, 0.5, -1);

	color.rgb *= max(0.1, saturate(dot(-lightDir, input.normal)));

	return color;
}