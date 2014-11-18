// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP;

// ��]�s��
float4x4 ROT;

// ���s�����̌���
float4 LightDir;

// �J�����̈ʒu�x�N�g��
float4 EyePos;

// �J���[
float4 Color;

// ����
float4 Ambient = 1.0f;

// �X�y�L�����[�͈̔�
float Specular = 0.0f;

// �X�y�L�����[�̋��x
float SpecularPower = 0.0f;

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
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

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos	: POSITION;		// ���_���W
	float4 Col	: COLOR0;			// ���_�J���[
	float2 Tex	: TEXCOORD0;	// �e�N�Z�����W
	float3 N		: TEXCOORD1;	// �I�u�W�F�N�g�̖@���x�N�g��
	float3 L		: TEXCOORD2;	// ���_ -> ���C�g�̈ʒu �x�N�g��
	float3 E		: TEXCOORD3;	// ���_ -> ���_ �x�N�g��
};

// -------------------------------------------------------------
// ���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass (
      float4 Pos : POSITION,       // ���f���̒��_
	  float4 Normal : NORMAL,	// �@��
      float2 Tex : TEXCOORD0		// �e�N�X�`�����W
){
    VS_OUTPUT Out = (VS_OUTPUT)0;	// �o�̓f�[�^
    
    // �ʒu���W
    Out.Pos = mul(Pos, WVP);

	Out.Tex = Tex;

	// ���C�g�����œ��͂����̂ŁA���_ -> ���C�g�ʒu�Ƃ��邽�߂ɋt�����ɕϊ�����B
	Out.L = normalize(-LightDir.xyz);

	// �@���x�N�g��
	float4 Norm = mul(Normal, ROT);
	Out.N = Norm.xyz;

	// ���C�g�x�N�g���Ɩ@���x�N�g���̓��ς��v�Z���A
	// �v�Z���ʂ̐F�̍Œ�l������(Ambient)�ɐ�������
	Out.Col = min(max(Ambient, dot(Out.N, Out.L)), 1.0f);

	// ���_ -> ���_ �ւ̃x�N�g�����v�Z
	Out.E = EyePos.xyz - Out.Pos.xyz;

    return Out;
}

// -------------------------------------------------------------
// �s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
float4 PS_pass(VS_OUTPUT In) : COLOR0
{   
    float4 OutColor = (float4)0;
	
	// �@���x�N�g���𐳋K������
	float3 N = normalize(In.N);
	// ���C�g�ʒu�x�N�g�� + ���_ -> ���_�x�N�g��
	float3 H = normalize(In.L + normalize(In.E));
	// �X�y�L�����[�J���[���v�Z����
   float S = pow(max(0.0f, dot(N, H)), Specular) * SpecularPower;
	
	// �X�y�L�����[�J���[�����Z����
	OutColor = tex2D(SrcSamp, In.Tex) * In.Col * Color + float4(S,S,S,Color.w);
	
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
