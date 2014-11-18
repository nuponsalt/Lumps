// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP;

// ��]�s��
float4x4 ROT;

// ���s�����̕����x�N�g��
float4 LightDir;

// �}�e���A���̃J���[
float4 Color;

// ---------------------------------------------------
// �e�N�X�`���[
// ---------------------------------------------------
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

// �g�D�[���}�b�v�e�N�X�`���[
texture ToonTex;
sampler ToonSamp = sampler_state
{
	Texture = <ToonTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Clamp;
	AddressV = Clamp;
};

// ----------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// ----------------------------------------------------
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
	Out.Normal = N.xyz;

	return Out;
}

float4 PS_pass(VS_OUTPUT In) : COLOR0
{
	float4 OutColor;

	// �n�[�t�����o�[�g�g�U�Ɩ��ɂ�郉�C�e�B���O�v�Z
	float p = dot(In.Normal, normalize(-LightDir));
	p = p * 0.5f + 0.5f;
	p = p * p;

	// �g�D�[���V�F�[�_�[����
	// �F�����e�N�Z����U�����Ƃ��A
	// �g�D�[���}�b�v�e�N�X�`��������̔��˗����擾
	float4 Col = tex2D(ToonSamp, float2(p, 0.0f));

	// �F�����i�[����
	OutColor = tex2D(SrcSamp, In.Tex) * Col * Color;

	return OutColor;
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	// �ʏ퍇��
    pass Normal
    {
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass();
        PixelShader  = compile ps_2_0 PS_pass();
		Sampler[0] = (SrcSamp);
    }

	// ���Z����
    pass Add
    {
		AlphaBlendEnable = true;
		SrcBlend = ONE;
		DestBlend = ONE;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass();
        PixelShader  = compile ps_2_0 PS_pass();
		Sampler[0] = (SrcSamp);
    }
}