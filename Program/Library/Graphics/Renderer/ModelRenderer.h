#pragma once 

#pragma warning( disable:4482 )

#include "GraphicBehavior.h"

#include <vector>
#include <memory>
#include <string>
#include <sstream>

namespace KMT {

	class CCamera;

	class CModelRenderer;
	typedef std::shared_ptr<CModelRenderer> CModelRendererSP, CGRendererSP;
	typedef std::weak_ptr<CModelRenderer> CModelRendererWP, CGRendererWP;

	typedef class CModelRenderer : public CGraphicBehavior
	{
	public :
		// �R���X�g���N�^
		CModelRenderer();
		// �f�X�g���N�^
		virtual ~CModelRenderer(){ Textures.clear(); }
		
		// ����
		static CModelRendererSP CreateFromX(const std::string &_path, const CShaderSP &_shader);
		// �`��
		virtual void Render(const CCamera* camera);		

	private :		
		// X�t�@�C���Ǎ�
		void LoadFromX(const std::string &_path);

	}CGRenderer;

}