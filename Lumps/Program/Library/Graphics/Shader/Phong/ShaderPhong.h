#pragma once

#include "../Shader.h"

namespace KMT {

	class CShaderPhong : public CShader
	{
	public :
		// �f�X�g���N�^
		~CShaderPhong() { }

		// ����
		static CShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�K�p
		void applyEffect(const CMatrix& _rotmtx, const CVector4& _campos);

	private :
		// �R���X�g���N�^
		CShaderPhong();

	protected :
	};

}