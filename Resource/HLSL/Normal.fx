// �J���[
float4 Color;

// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP;

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
    float4 Pos			: POSITION;
	float  Size			: PSIZE;
	float2 Tex			: TEXCOORD0;
};

// -------------------------------------------------------------
// ���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass1 (
      float4 Pos    : POSITION,         // ���f���̒��_
	  float Size	: PSIZE,			// ���_�T�C�Y
      float4 Tex    : TEXCOORD0	        // �e�N�X�`�����W
){

    VS_OUTPUT Out = (VS_OUTPUT)0;       // �o�̓f�[�^
    
    // �ʒu���W
    Out.Pos = mul(Pos, WVP);

	// �e�N�X�`��
    Out.Tex = Tex ;

	// �|�C���g�T�C�Y
	Out.Size = Size ;

    return Out;
}

// -------------------------------------------------------------
// �s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
float4 PS_pass1(VS_OUTPUT In) : COLOR
{   
    float4 OutColor;
	OutColor = tex2D(SrcSamp, In.Tex) * Color;
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
		AlphaBlendEnable = true ;
		SrcBlend = SRCALPHA ;
		DestBlend = INVSRCALPHA ;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
    }

	// ���Z����
    pass Add
    {
		AlphaBlendEnable = true ;
		SrcBlend = ONE ;
		DestBlend = ONE ;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
    }

}
