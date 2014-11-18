//*********************************************************************
// ���W�E��]�E�g�k�̊Ǘ��N���X(�����N���C�u�����Ƃ��Ă̋@�\�����\��)
// Last Update : 2013.12.11
// Yuta Komatsu
//*********************************************************************
#pragma once
#include <memory>

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace KMT {

	class CVector3;
	class CMatrix;
	class CQuaternion;

	class CTransformation;
	typedef std::shared_ptr<CTransformation> CTransformationSP;
	typedef std::weak_ptr<CTransformation> CTransformationWP;

	// ��]�^�C�v
	enum ROTATE_TYPE
	{
			XYZ,
			MATRIX,
			QUATERNION
	};

	class CTransformation
	{
	public :
		//* ���W *//
		CVector3 Position;
		//* ��] *//
		// �x�N�g��
		CVector3 vRotation;
		// �s��
		CMatrix mRotationX, mRotationY, mRotationZ, mRotationWorld;
		// �N�H�[�^�j�I��
		CQuaternion qRotation;
		//* �g�k *//
		CVector3 Scale ;

		// ���݂̉�]�^�C�v
		ROTATE_TYPE CurrentRotateType;

		// �R���X�g���N�^
		CTransformation();
		// �f�X�g���N�^
		virtual ~CTransformation() { }
	
};

}