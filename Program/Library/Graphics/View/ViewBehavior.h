#pragma once

#include "../../Math/Vector.h"
#include "../../Math/Matrix.h"

#include "../../Phisycs/BoundingVolume.h"

namespace KMT {

	typedef struct tag_View
	{
		// ���W
		CVector3 Eye;
		// �O�t���[���̍��W
		CVector3 previousEye;
		// �����_
		CVector3 LookAt;
		// �O�t���[���̒����_
		CVector3 previousLookAt;
		// �A�b�p�[�x�N�g��
		CVector3 Up;
		// �O�t���[���̃A�b�p�[�x�N�g��
		CVector3 previousUp;

		// �R���X�g���N�^
		tag_View() : Up(0, 1, 0) { }

	}ViewInfo, *pViewInfo;

	typedef struct tag_Perspective
	{
		// ��p
		float Angle;
		// �A�X�y�N�g��
		float Aspect;
		// ���ʂ̍ŋߋ���
		float Near;
		// ���ʂ̍ŉ�����
		float Far;

		// �R���X�g���N�^
		tag_Perspective();

	}PerspectiveInfo, *pPerspectiveInfo;

	// �r���[�s��E�v���W�F�N�V�����s������I�u�W�F�N�g�̊�{���N���X
	class CViewBehavior
	{
	public :
		// �s��̎��
		enum MatrixState{
			VIEW,
			PROJECTION
		};

		// �R���X�g���N�^
		CViewBehavior();
		// �f�X�g���N�^
		virtual ~CViewBehavior();

		// �X�V
		virtual void updateView() = 0;

		// ������̎Z�o
		void calculateViewFructum();
		// ���I�u�W�F�N�g�ɂ�鎋����J�����O����
		const bool isCullingFrustum(const SphereVolume& sphere) const;

		// �ݒ�
		inline void setEye(const CVector3 &_Pt) { View.Eye = _Pt; }
		inline void setEye(const float &_fx, const float &_fy, const float &_fz) { View.Eye = CVector3(_fx, _fy, _fz); }
		inline void setLookAt(const CVector3 &_Pt) { View.LookAt = _Pt; }
		inline void setLookAt(const float &_fx, const float &_fy, const float &_fz) { View.LookAt = CVector3(_fx, _fy, _fz); }
		inline void setUp(const CVector3 &_Pt) { View.Up = _Pt; }
		inline void setUp(const float &_fx, const float &_fy, const float &_fz) { View.Up = CVector3(_fx, _fy, _fz); }
		inline void setAspect(const float &_aspect) { Persective.Aspect = _aspect; }

		// �擾 
		inline CVector3 getEye() const { return View.Eye; }
		inline CVector3 getLookAt() const { return View.LookAt; }
		inline float getAngle() const { return Persective.Angle; }
		/* �s�� */
		inline CMatrix getMatrix(const MatrixState& state) const { return Matrix[state]; }

	protected :
		// �����䕽�ʗ񋓌^
		enum VIEW_FRUSTUM{
			TOP,
			BOTTOM,
			LEFT,
			RIGHT,
			FRONT,
			BACK,
			// ������̕��ʂ̐�
			FRUSTUM_MAX
		};
		// �������6����
		PlaneVolume viewFrustum[FRUSTUM_MAX];

		// �r���[�s��[0], �v���W�F�N�V�����s��[1]
		static const int VIEW_OR_PROJECTION = 2;
		CMatrix Matrix[VIEW_OR_PROJECTION];
		// �r���[���
		ViewInfo View;
		// �v���W�F�N�V����
		PerspectiveInfo Persective;

	};

}