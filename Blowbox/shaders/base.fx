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
	return output;
}

float4 PS(VOut input) : SV_TARGET
{
	return input.colour;
}