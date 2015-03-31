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
	output.position = position;
	output.colour = colour;
	output.texcoord = texcoord;
	return output;
}

Texture2D tex;
SamplerState Sampler;

float4 PS(VOut input) : SV_TARGET
{
	float4 base = tex.Sample(Sampler, input.texcoord);
	
	return base;
}