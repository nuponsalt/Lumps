#pragma once

#include "../Shader.h"
#include <memory>

namespace KMT {

	class CTexture;
	typedef std::shared_ptr<CTexture> CTextureSP;

	class CShaderToon : public CShader
	{
	public :
		// �f�X�g���N�^
		~CShaderToon() { }
	
		// �V�F�[�_�[����
		static CShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�ݒ�
		void applyEffect(const CMatrix& _rotmtx, const CVector4& _campos);
	
	private :
		// �g�D�[���e�N�X�`���[
		CTextureSP ToonTexture;

		// �R���X�g���N�^
		CShaderToon();
	
	protected :
	};

}