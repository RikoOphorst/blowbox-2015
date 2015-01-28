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

    inPos.x += abs(sin(time));
    inPos.y += abs(sin(time * 5));

    output.Pos = mul(inPos, WVP);
    output.TexCoord = inTexCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	input.TexCoord.y += sin(input.TexCoord.x + time * 10);
	float4 base = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

	base.r += abs(sin(time * 10));
	base.g += abs(sin(time * 7));
	base.b += abs(sin(time * 5));

	//base.a *= alpha;

	return base;
}
