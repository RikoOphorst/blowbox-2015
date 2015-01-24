cbuffer cbPerObject : register(b0)
{
	float4x4 WVP;
	float alpha;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD)
{
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    output.TexCoord = inTexCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 base = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

	base.a *= 0.5f;

	return base;
}
