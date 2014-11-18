#pragma once

#include "../Shader.h"
#include <memory>

namespace KMT {

	class CShaderParticle;
	typedef std::shared_ptr<CShaderParticle> CShaderParticleSP;
	typedef std::weak_ptr<CShaderParticle> CShaderPartcleWP;

	class CShaderParticle : public CShader
	{
	public :
		// �f�X�g���N�^
		~CShaderParticle() { }
		// �V�F�[�_�[����
		static CShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�K�p
		void applyEffect(const CMatrix& _rotmtx, const CVector4& _campos);

	private :
		// �R���X�g���N�^
		CShaderParticle();

	};
}