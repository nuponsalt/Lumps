#include "DXUT.h"
#include "Collision.h"
#include "../Extension.h"


namespace KMT {

	bool CorrectInfinitePlane(const float &posY, float &posA,const float &radius)
	{
		// �Ώ۔��a�Ŕ���
		if(posY > (posA - radius))
		{
			// �␳
			posA = posY + radius ;
			return true ;	// �^
		}
		return false ;	// �U
	}

	CVector3* calculateReflectVector(CVector3 *pOut, const CVector3 &Front, const CVector3 &Normal)
	{
		CVector3 N;
		Vector3Normalize(&N, &Normal);
		return Vector3Normalize(pOut, &(Front - 2.0f * Vector3Dot(&Front, &N) * N));
	}

	void getReflectVelocity(CVector3 *pOut, CVector3 &Axis,CVector3 &V, float Ref)
	{
		Normalize(Axis);
		*pOut = V - (1 + Ref) * Dot(Axis, V) * Axis;
	}

	void getReflectedPosition(float ResTime, Circle &circle, CVector3 &RefV)
	{
		// �Փˈʒu
		// 0.99�͕ǂɂ߂荞�܂Ȃ����߂̕␳
		circle.Position = circle.PreviousPosition + circle.Velocity * (1 - ResTime) * 0.99f;
		// ���˃x�N�g��
		circle.Velocity = RefV;
		// �ʒu��␳
		circle.Position += circle.Velocity * ResTime;
	}

	bool getCollideSegments(CVector3 *pOut, const CVector3 &a1, const CVector3 &a2, const CVector3 &b1, const CVector3 &b2)
	{
		CVector2 seg1_s = a1;
		CVector2 seg1_e = a2;

		CVector2 seg2_s = b1;
		CVector2 seg2_e = b2;

		CVector2 seg1_v = seg1_e - seg1_s;
		CVector2 seg2_v = seg2_e - seg2_s;

		CVector2 v = seg2_s - seg1_s;

		float C_v1_v2 = Vector2Cross(seg1_v, seg2_v);
		if (C_v1_v2 == 0.0f) {
			// ���s���
			return false;
		}

		float C_v_v1 = Vector2Cross(v, seg1_v);
		float C_v_v2 = Vector2Cross(v, seg2_v);

		float t1 = C_v_v2 / C_v1_v2;
		float t2 = C_v_v1 / C_v1_v2;

		const float eps = 0.00001f;
		if ( t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1 ) {
			// �������Ă��Ȃ�
			return false;
		}

		CVector2 pp = seg1_s + seg1_v * t1 ;
		pOut = (CVector3*)&pp;

		return true;
	}

	//bool getCollideSegmentPlane(CVector3 *pOut, CVector3 A, CVector3 B, Plane PL)
	//{
	//	//���ʏ�̓_P
	//	CVector3 P = CVector3(PL.a * PL.d, PL.b * PL.d, PL.c * PL.d);
	//	//PA PB�x�N�g��
	//	CVector3 pA = P - A;
	//	CVector3 pB = P - B;
	//	//PA PB���ꂼ��𕽖ʖ@���Ɠ���
	//	double dotPA = (pA.x * PL.a) + (pA.y * PL.b) + (pA.z * PL.c);
	//	double dotPB = (pB.x * PL.a) + (pB.y * PL.b) + (pB.z * PL.c);
	//	//����͐��[�����ʏ�ɂ��������̌v�Z�̌덷���z�����Ă��܂��B�������Ďg���Ă��������B
	//	if (abs(dotPA) < 0.000001) { dotPA = 0.0; }	
	//	if (abs(dotPB) < 0.000001) { dotPB = 0.0; }
	//	//��������
	//	if (dotPA == 0.0 && dotPB == 0.0) 
	//		//���[�����ʏ�ɂ���A��_���v�Z�ł��Ȃ��B
	//		return false;
	//
	//	else if ((dotPA >= 0.0 && dotPB <= 0.0) || (dotPA <= 0.0 && dotPB >= 0.0)) {
	//		//���ς̕Е����v���X�ŕЕ����}�C�i�X�Ȃ̂ŁA�������Ă���
	//	} else 
	//		//�������Ă��Ȃ�
	//		return false;
	//
	//	//�ȉ��A��_�����߂� 
	//	CVector3 AB = B - A;
	//	//��_��A�̋��� : ��_��B�̋��� = dot_PA : dot_PB
	//	float distance = (float)abs(dotPA) / ((float)abs(dotPA) + (float)abs(dotPB));
	//
	//	pOut = &(A + (AB * distance));
	//
	//	return true;
	//
	//}

	bool getisBackSpherePlane(const SphereVolume& sphere, const PlaneVolume& plane)
	{
		// ���ʂɑ΂��鋗�����Z�o
		float dist = Dot(sphere.Position, plane.Normal) - plane.Distance;

		// ���������̔��a��菬�����ꍇ�͗����ɂ���
		return dist < -sphere.Radius;
	}

	// �J�����ɑ΂��鎋���䕽�ʂ𐶐�����
	//void CreateViewFrustumPlane(const CCamera* camera, PlaneVolume* outputs)
	//{
	//	// �X�N���[�����W��̎�����̊e���_���Z�o����
	//	D3DXVECTOR4 NTL(-1,  1, 0, 1); // near top left
	//	D3DXVECTOR4 NTR( 1,  1, 0, 1); // near top right
	//	D3DXVECTOR4 NBL(-1, -1, 0, 1); // near bottom left
	//	D3DXVECTOR4 NBR( 1, -1, 0, 1); // near bottom right
	//	D3DXVECTOR4 FTL(-1,  1, 1, 1); // far top left
	//	D3DXVECTOR4 FTR( 1,  1, 1, 1); // far top right
	//	D3DXVECTOR4 FBL(-1, -1, 1, 1); // far bottom left
	//	D3DXVECTOR4 FBR( 1, -1, 1, 1); // far bottom right

	//	// �J�����̃r���[�v���W�F�N�V�����s��̋t�s����Z�o����
	//	D3DXMATRIX INVCVP = 
	//		camera->getMatrix(CViewBehavior::VIEW) * camera->getMatrix(CViewBehavior::PROJECTION);
	//	D3DXMatrixInverse(&INVCVP, NULL, &INVCVP);

	//	// �J�������W�n�̎�����̊e���_���Z�o����
	//	D3DXVec3Transform(&NTL, (D3DXVECTOR3*)&NTL, &INVCVP);
	//	D3DXVec3Transform(&NTR, (D3DXVECTOR3*)&NTR, &INVCVP);
	//	D3DXVec3Transform(&NBL, (D3DXVECTOR3*)&NBL, &INVCVP);
	//	D3DXVec3Transform(&NBR, (D3DXVECTOR3*)&NBR, &INVCVP);
	//	D3DXVec3Transform(&FTL, (D3DXVECTOR3*)&FTL, &INVCVP);
	//	D3DXVec3Transform(&FTR, (D3DXVECTOR3*)&FTR, &INVCVP);
	//	D3DXVec3Transform(&FBL, (D3DXVECTOR3*)&FBL, &INVCVP);
	//	D3DXVec3Transform(&FBR, (D3DXVECTOR3*)&FBR, &INVCVP);

	//	// w�ŏ��Z����
	//	NTL /= NTL.w;
	//	NTR /= NTR.w;
	//	NBL /= NBL.w;
	//	NBR /= NBR.w;
	//	FTL /= FTL.w;
	//	FTR /= FTR.w;
	//	FBL /= FBL.w;
	//	FBR /= FBR.w;

	//	// �X�N���[�����W��̒��_���畽�ʂ�����������
	//	outputs[0].Initialize((D3DXVECTOR3)NTR, (D3DXVECTOR3)NTL, (D3DXVECTOR3)NBL); // near
	//	outputs[1].Initialize((D3DXVECTOR3)FBL, (D3DXVECTOR3)FTL, (D3DXVECTOR3)FTR); // far
	//	outputs[2].Initialize((D3DXVECTOR3)NBR, (D3DXVECTOR3)FBR, (D3DXVECTOR3)FTR); // right
	//	outputs[3].Initialize((D3DXVECTOR3)FTL, (D3DXVECTOR3)FBL, (D3DXVECTOR3)NBL); // left
	//	outputs[4].Initialize((D3DXVECTOR3)FTL, (D3DXVECTOR3)NTL, (D3DXVECTOR3)NTR); // top
	//	outputs[5].Initialize((D3DXVECTOR3)NBR, (D3DXVECTOR3)NBL, (D3DXVECTOR3)FBL); // bottom
	//}

	//bool getisCulingFrustumSphere(const CCamera* camera, const SphereVolume& sphere)
	//{
	//	// ���ʂ𐶐�����
	//	PlaneVolume planes[FRUSTUM_FACE];
	//	CreateFrustumCullingPlane(camera, planes);
	//}

	bool getCollideSpheres(CVector3& posA, CVector3& posB, float rA, float rB) 
	{
		return LengthSq(posA - posB) < ((rA + rB) * (rA + rB));
	}
	
	bool calculateParticleCollision(float rA, float rB, 
									CVector3 *pPrePosA, CVector3 *pPosA,
									CVector3 *pPrePosB, CVector3 *pPosB,
									float *pOutTime,
									CVector3 *pOutCollidedA, CVector3 *pOutCollidedB)
	{
		// �O�ʒu�y�ѓ��B�ʒu�ɂ�����p�[�e�B�N���Ԃ̃x�N�g�����Z�o
		CVector3 C0 = *pPrePosB - *pPrePosA;
		CVector3 C1 = *pPosB - *pPosA;
		CVector3 D = C1 - C0;
		// �Փ˔���p��2���֐��W���̎Z�o
		float P = LengthSq(D); if(P == 0) return false; // ���������Ɉړ�
		float Q = Dot(C0, D);
		float R = LengthSq(C0);
		// �p�[�e�B�N������
		float r = rA + rB;
		// �Փ˔��莮
		float Judge = (Q * Q) - (P * (R - (r * r)));
		if(Judge < 0){
			// �Փ˂��Ă��Ȃ�
			return false;
		}
		// �Փˎ��Ԃ̎Z�o
		float t_plus = (-Q + sqrt(Judge)) / P;
		float t_minus = (-Q - sqrt(Judge)) / P;
		// �Փˎ��Ԃ�0����1���傫���ꍇ�A�Փ˂��Ȃ�
		if( (t_plus < 0 || t_plus > 1) && (t_minus < 0 || t_minus > 1)) return false;
		// �Փˎ��Ԃ̌���it_minus������ɍŏ��̏Փˁj
		*pOutTime = t_minus;
		// �Փˈʒu�̌���
		*pOutCollidedA = *pPrePosA + t_minus * (*pPosA - *pPrePosA);
		*pOutCollidedB = *pPrePosB + t_minus * (*pPosB - *pPrePosB);
		// �Փ˕�
		return true;
	}

	bool calculateParticlePositionAfterCollision(CVector3 *pColPosA, CVector3 *pVelocityA,
											CVector3 *pColPosB, CVector3 *pVelocityB,
											float massA, float massB,
											float resA, float resB,
											float time,
											CVector3 *pOutPosA, CVector3 *pOutVelocityA,
											CVector3 *pOutPosB, CVector3 *pOutVelocityB)
	{
		// ���ʂ̍��v
		float TotalMass = massA + massB;
		// ������
		float RefRate = (1 + resA * resB);
		// �Փˎ��x�N�g��
		CVector3 C = *pColPosB - *pColPosA;
		Normalize(C);
		CVector3 V = (*pVelocityA - *pVelocityB);
		// ���ώZ�o
		float D = Dot(V, C);
		// �萔�x�N�g��
		const CVector3 VEC = RefRate * D / TotalMass * C;
		// �Փˌ㑬�x�x�N�g���̎Z�o
		*pOutVelocityA = -massB * VEC + *pVelocityA;
		*pOutVelocityB = massA * VEC + *pVelocityB;
		// �Փˌ�ʒu�̎Z�o
		*pOutPosA = *pColPosA + time * (*pOutVelocityA);
		*pOutPosB = *pColPosB + time * (*pOutVelocityB);

		return true;
	}

}