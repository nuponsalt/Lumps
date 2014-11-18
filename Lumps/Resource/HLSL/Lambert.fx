// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP;

// ��]�s��
float4x4 ROT;

// ���s�����̌���
float4 LightDir;

// ���_
float4 EyePos;

// �J���[
float4 Color;

// �����ɑ΂���}�e���A��
// 0.0f�`1.0f�̒l�������A1.0f�̂Ƃ��ł������Ȃ�
float4 Ambient = 0.0f;

// �t�H�O�J���[
float4 fogColor;
// �t�H�O�̊J�n�ʒu
float4 fogCoord = float4(0, 1, 0, 0);

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
    float4 Pos : POSITION;
	float4 Col : COLOR0;
	float2 Tex : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;
};

// -------------------------------------------------------------
// ���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass1 (
		float4 Pos : POSITION,	// ���f���̒��_
		float4 Normal : NORMAL,	// �@��
		float2 Tex : TEXCOORD0	// �e�N�X�`�����W
){
    VS_OUTPUT Out = (VS_OUTPUT)0;	// �o�̓f�[�^
    
    // �ʒu���W
    Out.Pos = mul(Pos, WVP);

	// �Ɩ����t�����ɂ���
	float3 L = normalize(-LightDir.xyz);

	// �@���x�N�g��
	float4 Norm = mul(Normal, ROT);
	float3 N = normalize(Norm.xyz);

	// �Ɩ��Ɩ@��������ς��v�Z����
	// �܂�max�֐��ɂ�蒸�_�J���[�̍ŏ��l�������ɗ}����悤�ɐݒ肷��
	Out.Col = max(Ambient, dot(N, L));

	Out.Tex = Tex;

	Out.LocalPos = Out.Pos;

    return Out;
}

// -------------------------------------------------------------
// �s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
float4 PS_pass1(VS_OUTPUT In) : COLOR0
{   
    float4 OutColor = (float4)0;

	// ���_�Ǝ��_�Ƃ̋������v�Z����
	float D = distance(In.LocalPos.xyz, EyePos.xyz);
	//
	float F = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, fogCoord.x), fogCoord.y);

	// �I�u�W�F�N�g�̃����o�[�g�g�U�Ɩ��̌v�Z���ʂƃt�H�O�J���[����`��������
	OutColor = (tex2D(SrcSamp, In.Tex) * In.Col * F + (fogColor * (1.0f - F))) * Color;

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
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
    }

	// ���Z����
    pass Add
    {
		AlphaBlendEnable = true;
		SrcBlend = ONE;
		DestBlend = ONE;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
    }


}
