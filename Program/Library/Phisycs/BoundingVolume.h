//*********************************************************************
// Bounding Volume Infomation
// Last Update : 2014.7.19
// Yuta Komatsu
//*********************************************************************
#pragma once
#pragma warning(disable : 4238)
#pragma warning(disable : 4239)

#include <vector>
#include <memory>
#include "../Math/Vector.h"
#include "../Math/Quaternion.h"

namespace KMT {

	//* typedef�錾 *//
	struct BoundingVolume;
	typedef std::shared_ptr<BoundingVolume> BoundingVolumeSP, BVSP;

	struct Sphere;
	typedef std::shared_ptr<Sphere> SphereSP;

	//* �N���X�錾 *//
	// �Փ˃{�����[�����\����
	struct BoundingVolume
	{
		// �ԍ�
		DWORD ID;
		// ����
		bool isDetect;
		// ���x
		CVector3 Velocity;
		// �����x
		CVector3 Acceleration;
		// ����
		float Mass;
		// �X�P�[��
		float Scale;
		
		// �R���X�g���N�^
		BoundingVolume() : ID(0), Mass(1.0f), Scale(1.0f), isDetect(true)
		{
			static int cnt;
			ID = cnt++;
		}

		virtual ~BoundingVolume() { }
	};

	// �����\����
	struct Segment : public BoundingVolume
	{
		// �n�_���W
		CVector3 s;
		// �I�_���W
		CVector3 e;

		// �R���X�g���N�^(�S�Ă̒��_�����_�̐�������)
		Segment() { }
		// �R���X�g���N�^(�w�肵�����_���W�̐����𐶐�)
		Segment(const CVector3 &_s, const CVector3 &_e) : s(_s), e(_e) { }

	};

	// ���ʍ\����
	typedef struct Plane : public BoundingVolume
	{
		// �@��
		CVector3 Normal;
		// �������ʏ�̓_���猸�_�܂ł̋���
		float Distance;

		// �R���X�g���N�^
		Plane() : Normal(0, 1, 0), Distance(0) { }
		/// �^����ꂽ3�_���畽�ʂ�����������
		/// �����͎��v���̏��ŗ^����
		Plane(const CVector3& v1, const CVector3& v2, const CVector3& v3);

	}PlaneVolume, *pPlaneVolume;

	// ���\����(�~�Ƃ��Ă����p�\)
	typedef struct Sphere : public BoundingVolume
	{
		// �~�̍��W
		CVector3 Position;
		// 1�O�̍��W
		CVector3 PreviousPosition;
		// ���a
		float Radius;

		// �R���X�g���N�^
		Sphere() : Radius(1.0f) { }
	
	}CSVolume, Circle, CircleVolume, *PCircleVolume, SphereVolume, *PSphereVolume;
	
	// �O�p�`�\����
	typedef struct Triangle : public BoundingVolume
	{
		// ���_���W
		CVector3 Position[3];
		// 1�O�̒��_���W
		CVector3 PreviousPosition[3];

		// �R���X�g���N�^
		Triangle() { for (int i = 0; i < 3; i++) { Position[i] = PreviousPosition[i] = 0; } }

		// �擾 : �O�p�`�̖@��
		CVector3 getNomal() const { return Normalize(Cross(Position[1] - Position[0], Position[2] - Position[0])); }

	}*PTriangle, PolygonVolume, *PPolygonVolume;

	struct AABB : public BoundingVolume
	{
		// ���S���W
		CVector3 Position;
		// 1�O�̒��S���W
		CVector3 PreviousPosition;
		// ���a
		CVector3 Radius;

		// �R���X�g���N�^
		AABB() { }

	};
}

