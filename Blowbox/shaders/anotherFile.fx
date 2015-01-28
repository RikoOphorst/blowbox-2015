cbuffer cbPerObject : register(b0)
{
	float4x4 WVP;
	float alpha;
	float time;
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
	input.TexCoord.y += sin(input.TexCoord.x * 100 + time * 0.5);
	float4 base = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

	//base.a *= alpha;

	return base;
}
