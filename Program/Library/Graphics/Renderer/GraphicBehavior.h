#pragma once

#pragma warning(disable : 4482)

#include "../../Math/Transformation.h"
#include "../Material.h"
#include "../Mesh.h"
#include "../Texture.h"

#include <vector>
#include <memory>

namespace KMT {

	//* �O���錾 *//
	class CCamera;
	class CShader;
	typedef std::shared_ptr<CShader> CShaderSP;

	class CGraphicBehavior;
	typedef std::shared_ptr<CGraphicBehavior> CGraphicBehaviorSP;
	typedef std::weak_ptr<CGraphicBehavior> CGraphicBehaviorWP;

	class CGraphicBehavior : public CTransformation, public CMaterial
	{
	public :
		// �\�[�g�p�̒l
		float CameraDistance;
		// �`��t���O
		bool isRender;
		// �r���{�[�h�t���O
		bool isBillBoard;

		// �R���X�g���N�^
		CGraphicBehavior() : CameraDistance(0), isRender(true), isBillBoard(false), d3dCull(D3DCULL_CCW){ }
		// �f�X�g���N�^
		virtual ~CGraphicBehavior() { }

		//* �擾 *//
		// ���b�V��
		inline CMeshSP getpMesh() { return Mesh; }
		// �e�N�X�`���x�N�^�[�z��
		inline std::vector<CTextureSP> getptextures() { return Textures; }
		// �e�N�X�`���x�N�^�[�z��(���ڃC���f�b�N�X�w��)
		inline CTextureSP getptexturesArray(size_t nAry) { return Textures[nAry]; }
		// �g�U���ːF(�f�B�t���[�Y�F)
		inline CVector4 getDiffuseColors(size_t nAry) { return DiffuseColors[nAry]; }

		//* �ݒ� *//
		// �V�F�[�_�[
		inline void setShader(CShaderSP sdr) { Shader = sdr; }
		// �J�����O���[�h
		inline void setd3dCull(const _D3DCULL _d3dCull) { d3dCull = _d3dCull; }
		// �e�N�X�`��
		inline void setTexture(const CTextureSP& _ptex) { Textures.push_back(_ptex); }
		
		//* std::list��sort�g�p�֐� *//
		static inline bool comp(const CGraphicBehaviorWP riLeft, const CGraphicBehaviorWP riRight)
		{
			return (riRight.lock()->CameraDistance < riLeft.lock()->CameraDistance);
		}
		static inline bool compBack(const CGraphicBehaviorWP riLeft, const CGraphicBehaviorWP riRight)
		{
			return (riRight.lock()->CameraDistance < riLeft.lock()->CameraDistance);
		}
		static inline bool comp2D(const CGraphicBehaviorWP riLeft, const CGraphicBehaviorWP riRight)
		{
			return (riRight.lock()->Position.z > riLeft.lock()->Position.z);
		}
		// �`��
		virtual void Render(const CCamera* camera) = 0;

	private :
	protected :
		// �t�@�C���p�X
		std::string Path;
		// ���b�V��
		CMeshSP Mesh;
		// �V�F�[�_�[
		CShaderSP Shader;
		// �`�掞�̃J�����O���[�h�ۑ��ϐ�
		_D3DCULL d3dCull;
		
		// �e�N�X�`���[�z��(std::vector)
		std::vector<CTextureSP> Textures;
		// ���_�J���[�z��(std::vector)
		std::vector<CVector4> DiffuseColors;

	};

}