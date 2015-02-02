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
	float4 color : COLOR;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float4 color : COLOR)
{
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    output.TexCoord = inTexCoord;
    output.color = color;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 base = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
	float4 color = float4(base.rgb, base.a);

	color.a *= alpha;

	return color;
}
