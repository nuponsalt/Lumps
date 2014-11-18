// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP;

// ��]�s��
float4x4 ROT;

// ���s�����̕����x�N�g��
float4 LightDir;

// �}�e���A���̃J���[
float4 Color;

// �I�u�W�F�N�g�̃e�N�X�`���[
texture SrcTex;
sampler SrcSamp = sampler_state
{
	Texture = <SrcTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Clamp;
	AddressV = Clamp;
};

// -------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		:	POSITION;
	float2 Tex		:	TEXCOORD0;
	float3 Normal	:	TEXCOORD1;
};

VS_OUTPUT VS_pass(	float4 Pos		:	POSITION,
								float4 Normal	:	NORMAL,
								float2 Tex		:	TEXCOORD0 )
{
	VS_OUTPUT Out;

	Out.Pos = mul(Pos, WVP);
	Out.Tex = Tex;

	float4 N = mul(Normal, ROT);
	Out.Normal = normalize(N.xyz);

	return Out;
}

float4 PS_pass(VS_OUTPUT In) : COLOR0
{
	float4 OutColor;

	float p = dot(In.Normal, normalize(-LightDir));
	p = p * 0.5f + 0.5f;
	p = p * p;

	float4 Col = tex2D(SrcSamp, In.Tex) * p * Color;
	OutColor = float4(Col.x, Col.y, Col.z, Color.w);

	return OutColor;
}

technique TShader
{
	pass Normal
	{
		// �����_�����O�X�e�[�g
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;

		// �V�F�[�_
		VertexShader = compile vs_1_1 VS_pass();
		PixelShader = compile ps_2_0 PS_pass();
	}

	pass Add
	{
		// �����_�����O�X�e�[�g
		AlphaBlendEnable = true;
		SrcBlend = ONE;
		DestBlend = ONE;
		
		// �V�F�[�_
		VertexShader = compile vs_1_1 VS_pass();
		PixelShader = compile ps_2_0 PS_pass();
	}
}