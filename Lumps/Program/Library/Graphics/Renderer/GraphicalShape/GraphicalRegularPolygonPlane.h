#pragma once

#pragma warning(disable:4018)
#pragma warning(disable:4244)

#include <memory>
#include "../GraphicBehavior.h"
#include "../../Animation.h"

namespace KMT {

	enum FACE_GENERATE_TYPE
	{
		// �ʂ��Ƃ�3���_
		TRI_VTX,
		// �p��+1 = ���_��
		POLYNUM_VTX
	};

	class CGraphicalRegularPolygonPlane;
	typedef std::shared_ptr<CGraphicalRegularPolygonPlane> CGraphicalRegularPolygonPlaneSP, CRegPolyPlaneSP;
	
	class CGraphicalRegularPolygonPlane : public CGraphicBehavior
	{
	public :
		// �T�C�Y
		CVector3 Size ;

		// �f�X�g���N�^
		~CGraphicalRegularPolygonPlane(){}
		// ����
		// _radius : �����T�C�Y
		// _facenum : �c���T�C�Y
		// _type : �ʐ����^�C�v
		// _texture : �e�N�X�`���[
		static CRegPolyPlaneSP Create(const int &_radius, const int &_facenum, const FACE_GENERATE_TYPE &_type, const CTextureSP &_texture = NULL);
	
	private :
		CVector3 TextureSize ;

		// �R���X�g���N�^
		CGraphicalRegularPolygonPlane();
		// �����p�`�|���S���̍쐬(���O�p�`�ȏ�)
		// _radius : ���a
		// _facenum : �ʐ�(3�Ő��O�p�`,����������قǉ~�ɋ߂��Ȃ�)
		// _texture : �e�N�X�`���[
		bool GenerateRegularPolygonBoard(const int &_radius, const int &_facenum, const FACE_GENERATE_TYPE &_type, const CTextureSP &_texture = NULL);
	};

}