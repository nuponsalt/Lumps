#include "DXUT.h"
#include "ViewBehavior.h"

#include "../../Extension.h"

namespace KMT {

	tag_Perspective::tag_Perspective() : Angle(D3DX_PI / 4.0f), Aspect((float)SCREEN_WIDTH / SCREEN_HEIGHT), Near(1), Far(10000) { }

	CViewBehavior::CViewBehavior()
	{
		ZeroMemory(viewFrustum, sizeof(PlaneVolume) * FRUSTUM_MAX);
		ZeroMemory(Matrix, sizeof(CMatrix) * VIEW_OR_PROJECTION);
	}

	CViewBehavior::~CViewBehavior() { }

	void CViewBehavior::calculateViewFructum()
	{
		// �X�N���[�����W��̎�����̊e���_���W
		CVector4 nearTL(-1, 1, 0, 1);
		CVector4 nearTR(1, 1, 0, 1);
		CVector4 nearBL(-1, -1, 0, 1);
		CVector4 nearBR(1, -1, 0, 1);
		CVector4 farTL(-1, 1, 1, 1);
		CVector4 farTR(1, 1, 1, 1);
		CVector4 farBL(-1, -1, 1, 1);
		CVector4 farBR(1, -1, 1, 1);

		// �r���[�v���W�F�N�V�����s��̋t�s������߂�
		CMatrix MVP = Matrix[VIEW] * Matrix[PROJECTION];
		CMatrix invMVP;
		D3DXMatrixInverse(&invMVP, NULL, &MVP);

		// ���[���h���W��̎�����̊e���_�����߂�
		nearTL.Transform(invMVP);
		nearTR.Transform(invMVP);
		nearBL.Transform(invMVP);
		nearBR.Transform(invMVP);
		farTL.Transform(invMVP);
		farTR.Transform(invMVP);
		farBL.Transform(invMVP);
		farBR.Transform(invMVP);

		// w�ŏ��Z
		nearTL /= nearTL.w;
		nearTR /= nearTR.w;
		nearBL /= nearBL.w;
		nearBR /= nearBR.w;
		farTL /= farTL.w;
		farTR /= farTR.w;
		farBL /= farBL.w;
		farBR /= farBR.w;

		viewFrustum[TOP] = PlaneVolume(nearTL, nearTR, farTL);
		viewFrustum[BOTTOM] = PlaneVolume(nearBL, farBL, nearBR);
		viewFrustum[LEFT] = PlaneVolume(nearBL, nearTL, farTL);
		viewFrustum[RIGHT] = PlaneVolume(nearBR, farBR, nearTR);
		viewFrustum[FRONT] = PlaneVolume(nearBL, nearBR, nearTL);
		viewFrustum[BACK] = PlaneVolume(farTL, farTR, farBL);
	}

	const bool CViewBehavior::isCullingFrustum(const SphereVolume& sphere) const
	{
		for(int i = 0; i < FRUSTUM_MAX; i++){
			// �Ώۂƕ��ʂ̋������Z�o
			float dist = Dot(sphere.Position, viewFrustum[i].Normal) - viewFrustum[i].Distance;
			if(dist < -sphere.Radius)
				return true;
		}
		return false;
	}

}