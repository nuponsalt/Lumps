#pragma once 

#include "../Shader.h"

namespace KMT {
	
	class CShaderLambert : public CShader
	{
	public :
		// �f�X�g���N�^
		~CShaderLambert() { }
		// �V�F�[�_�[����
		static CShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�ݒ�
		void applyEffect(const CMatrix& _rotmtx, const CVector4& _campos);
	
	private :
		// �R���X�g���N�^
		CShaderLambert();

	};

}