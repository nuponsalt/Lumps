#pragma once

#pragma warning( disable:4018 )
#pragma warning( disable:4244 )

#include <memory>
#include "../GraphicBehavior.h"
#include "../../Animation.h"

namespace KMT
{
	class CGraphicalPlane;
	typedef std::shared_ptr<CGraphicalPlane> CGraphicalPlaneSP, CGPlaneSP;

	typedef class CGraphicalPlane : public CGraphicBehavior, public CAnimation
	{
	public :
		// �T�C�Y
		CVector3 Size;

		// �f�X�g���N�^
		~CGraphicalPlane(){}
		// ����
		// _width : �����T�C�Y
		// _height : �c���T�C�Y
		// _texture : �e�N�X�`���[(��łȂ��ƃ_���ȏ��)
		static CGraphicalPlaneSP Create(const int &_width, const int &_height, const CTextureSP &_texture = NULL) ;
		// �e�N�X�`���[�̃T�C�Y�ɍ��킹���|���S���̐���
		// _path : �e�N�X�`���[�̃p�X
		// x_num, y_num : ������
		// size_x, size_y : �T�C�Y
		static CGraphicalPlaneSP CreateFromTexture(const std::string &_path, 
			const int &x_num = 1, const int &y_num = 1, const int &size_x = 0, const int &size_y = 0) ;
		static CGraphicalPlaneSP CreateFromTexture(const CTextureSP &_tex, 
			const int &x_num = 1, const int &y_num = 1, const int &size_x = 0, const int &size_y = 0) ;
		// �`��
		void Render(const CCamera* camera);

	private :
		// �e�N�X�`���[�̃T�C�Y
		CVector3 TextureSize;
		// �O�̃A�j���[�V�����ԍ�
		int PreviousNumber;
		// �|���̐����J�E���g
		static size_t CreateCount;

		// �R���X�g���N�^
		CGraphicalPlane();
		// �|���S���̍쐬
		// _width : �����T�C�Y
		// _height : �c���T�C�Y
		// _texture : �e�N�X�`���[
		bool GenerateBoard(const std::string& _path, const int &_width, const int &_height, const CTextureSP &_texture = NULL) ;
		// �e�N�X�`���̃T�C�Y�ɍ��킹���|���𐶐�����
		// _path : �e�N�X�`���̃p�X
		// x_num, y_num : �摜�̕������
		// size_x, size_y : �|���̑傫���w��
		void LoadTexture (const std::string &_path, const int &x_num = 1, const int &y_num = 1, const int &size_x = 0, const int &size_y = 0);
		void LoadTexture (const CTextureSP& _tex, const int& x_num = 1,const int &y_num = 1, const int &size_x = 0, const int &size_y = 0);

	}CGPlane;

}