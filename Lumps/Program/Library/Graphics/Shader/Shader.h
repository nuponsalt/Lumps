//*********************************************************************
// �V�F�[�_�[�N���X
// Last Update : 2013.12.11
// Yuta Komatsu
//*********************************************************************
#pragma once 

#pragma warning( disable:4238 )

#include <memory>
#include <string>
#include <hash_map>

#include "../../Math/Vector.h"

namespace KMT {

	class CGraphicBehavior;

	class CShader;
	typedef std::shared_ptr<CShader> CShaderSP;
	typedef std::weak_ptr<CShader> CShaderWP;

	class CShader
	{
	public :
		enum BEGINorEND
		{
			BEGIN = true,
			END = false
		};

		// �t�H�O�̎��
		enum FogType
		{
			LINEAR_DISTANCE_FOG,
			EXPONENTIAL_DISTANCE_FOG,
			HEIGHT_FOG
		};

		// �f�X�g���N�^
		~CShader();
		
		// �j��
		static void Destroy(std::string _name = "all");

		//* �擾 *//
		// �G�t�F�N�g
		inline LPD3DXEFFECT getpd3dEffect() { return pd3dEffect; }
		// �n���h��
		inline D3DXHANDLE* getpWVP() { return &pWVP; }	// ���[���h * �r���[ * �v���W�F�N�V����
		D3DXHANDLE* getpHandle(const std::string &_path);	// �w�肵�Ď擾
		
		//* �V�F�[�_�[�ݒ� *//
		// �A�N�e�B�u�ȃe�N�j�b�N���V�F�[�_�[�ɐݒ�
		void setTechnique() const;
		// ���[���h * �r���[ * �v���W�F�N�V���� �s����V�F�[�_�[�ɐݒ�
		void setWVPMatrix(const CMatrix& wvp) const;
		// �J���[���V�F�[�_�[�ɐݒ�
		void setColor(const CVector4& color) const;
		// �e�N�X�`�����V�F�[�_�[�ɐݒ�
		void setTexture(const LPDIRECT3DTEXTURE9 texture) const;
		// �V�F�[�_�[�̎g�p�J�n
		void BeginShader() const;
		// �V�F�[�_�[�̎g�p�I��
		void EndShader() const;
		// �p�X�̎g�p
		void BeginPass(const bool isAddBlend);
		// �p�X�̏I��
		void EndPass();
		// ���L�̃V�F�[�_�[�ݒ�(�������z�֐�)
		// _rotmtx : ��]�s��
		// _campos : �J�����̎��_�̍��W
		virtual void applyEffect(const CMatrix &_rotmtx, const CVector4& _campos) = 0;

		//* �p�����[�^�[�ݒ� *//
		// ���C�g�̍��W
		inline void setLightDirection(CVector4 _dir) { LightDirection = _dir; }
		inline void setLightDirection(const float _x, const float _y, const float _z) { LightDirection = CVector4(_x, _y, _z, 0.0f);	}
		// ����
		inline void setAmbient(const float _ambient) { Ambient = _ambient; }
		// �X�y�L�����[�͈�
		inline void setSpecular(const float _specular) { Specular = _specular; }
		// �X�y�L�����[���x
		inline void setSpecularPower(const float _specularpower) { SpecularPower = _specularpower; }
		// �t�H�O�J���[
		inline void setFogColor(const CVector4& _fogcolor) { fogColor = _fogcolor; }
		// �t�H�O�̃p�����[�^�[�̐ݒ�
		inline void setfogCoord(const float param1, const float param2) { fogCoord = CVector4(param1, param2, 0, 0); }

	protected :
		// �g�p����V�F�[�_�[�t�@�C����
		std::string	FilePath;
		// ����
		float Ambient;
		// ���s����
		CVector4 LightDirection;
		// �X�y�L�����[�͈̔�
		float Specular;
		// �X�y�L�����[�̋��x
		float SpecularPower;
		// �t�H�O�J���[
		CVector4 fogColor;
		// �t�H�O�͈̔�
		CVector4 fogCoord;

		// �V�F�[�_�[�̃^�C�v�̗񋓌^
		enum ShaderType_
		{
			SHADER_NORMAL,
			SHADER_LAMBERT,
			SHADER_HLAMBERT,
			SHADER_PHONG,
			SHADER_TOON,
			SHADER_TYPEMAX
		};
		// �V�F�[�_�[�̃^�C�v
		size_t Type;

		// �G�t�F�N�g�̐ݒ�Ɩ₢���킹�A����уe�N�j�b�N�̑I��
		// ��������|�C���^
		// �V�F�[�_�{��
		LPD3DXEFFECT pd3dEffect;
		// �e�N�j�b�N
		D3DXHANDLE	pTechnique;
		// ���[���h x �r���[ x �v���W�F�N�V����
		D3DXHANDLE	pWVP;
		// �f�B�t���[�Y�F
		D3DXHANDLE pColor;
		// �e�N�X�`��
		D3DXHANDLE pSrcTex;
		// �V�F�[�_�[�ɓn���n���h����o�^�����n�b�V���}�b�v
		stdext::hash_map<std::string, D3DXHANDLE> handles;
		// �V�F�[�_�[�Ǘ��n�b�V���}�b�v�z��
		static std::hash_map<std::string, CShaderSP> Shaders;

		// �R���X�g���N�^
		CShader();
		CShader(std::string _xmlpath);

	};

	class CShaderNormal;
	typedef std::shared_ptr<CShaderNormal> CShaderNormalSP;
	typedef std::weak_ptr<CShaderNormal> CShaderNormalWP;

	class CShaderNormal : public CShader
	{
	public :
		// �f�X�g���N�^
		~CShaderNormal() { }
		// �V�F�[�_�[����
		static CShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�K�p
		void applyEffect(const CMatrix& _rotmtx, const CVector4& _campos);

	private :
		// �R���X�g���N�^
		CShaderNormal();

	};

}