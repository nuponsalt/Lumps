//*********************************************************************
// Collision Detect Infomation
// Last Update : 2014.07.19
// Yuta Komatsu
//*********************************************************************
#pragma once

#include <memory>
#include <vector>

#include "BoundingVolume.h"
#include "../Graphics/View/Camera.h"

namespace KMT {

	// �Փ˔���␳�̕���
	enum COLLIDE_DIRECTION
	{
		COL_ERROR = -0x01,
		COL_NONE = 0x00,
		COL_COLLIDE = 0x01,
		COL_LEFT = 0x02,
		COL_RIGHT = 0x04,
		COL_FRONT = 0x08,
		COL_BACK = 0x10,
		COL_TOP = 0x20,
		COL_BOTTOM = 0x40
	};

	// Z���������ʌ�������(�␳)
	// posY : �������ʂ̍���
	// posA : �I�u�W�F�N�g�̍���
	// radius : �I�u�W�F�N�g�̔��a
	bool CorrectInfinitePlane(const float& posY, float& posA, const float& radius);

	// ���˃x�N�g���̌v�Z
	// pOut : ���K�����˃x�N�g��
	// Front : �i�s�����x�N�g��
	// Normal : �Փ˓_�ł̖@���x�N�g��
	CVector3* calculateReflectVector(CVector3* pOut, const CVector3& Front, const CVector3& Normal);

	// �ǂƋ��̔��˃x�N�g�����v�Z
	// pOut : ���ʂ��󂯎��, Axis : ���ˎ�, V : �Z�o��, Ref : �����W��
	void getReflectVelocity(CVector3* pOut, CVector3& Axis, CVector3& V, float Ref);

	// �ǂƂ̔��ˌ�̈ʒu���Z�o
	void getReflectedPosition(float ResTime, Circle& circle, CVector3& RefV);

	// �擾 : �����̏Փ˔���
	// a1 : A�����n�[���_���W, a2 : A�����I�[���_���W
	// b1 : B�����n�[���_���W, b2 : B�����I�[���_���W
	// pOutIP : ��_���i�[����CVector3�^�̃|�C���^
	bool getCollideSegments(CVector3* pOut, const CVector3& a1, const CVector3& a2, const CVector3& b1, const CVector3& b2);

	// �擾 : �����ƕ��ʂ̏Փ˔���
	// 
	bool getCollideSegmentPlane(CVector3* pOut, CVector3 A, CVector3 B, Plane PL);

	// �������ʂ̗����ɂ��邩���肷��
	// 
	bool getisBackSpherePlane(const SphereVolume &sphere, const PlaneVolume &plane);

	// ������ɂ���������J�����O�𔻒肷��
	bool getisCulingFrustumSphere(const CCamera* camera, const SphereVolume& sphere);

	// �擾 : �����m�̏Փ˔���
	// posA : �~A�̍��W, posB : �~B�̍��W
	// rA : �~A�̔��a, rB : �~B�̔��a
	bool getCollideSpheres(CVector3& posA, CVector3& posB, float rA, float rB);

	// �p�[�e�B�N���Փ˔���E�����E�ʒu�Z�o�֐�
	// rA : �p�[�e�B�N��A�̔��a, rB : �p�[�e�B�N��B�̔��a
	// prePosA : �p�[�e�B�N��A�̑O�̈ʒu, posA : �p�[�e�B�N��A�̎��̓��B�ʒu
	// prePosB : �p�[�e�B�N��B�̑O�̈ʒu, posB : �p�[�e�B�N��B�̎��̓��B�ʒu
	// poutTime : �Փˎ��Ԃ��i�[����FLOAT�^�ւ̃|�C���^
	// poutCollidedA : �p�[�e�B�N��A�̏Փˈʒu���i�[����CVector3�^�ւ̃|�C���^, poutColldediB : �p�[�e�B�N��A�̏Փˈʒu���i�[����CVector3�^�ւ̃|�C���^
	bool calculateParticleCollision(float rA, float rB, 
											CVector3* pPrePosA, CVector3* pPosA,
											CVector3* pPrePosB, CVector3* pPosB,
											float* pOutTime,
											CVector3* pOutCollidedA, CVector3* pOutCollidedB);

	// �p�[�e�B�N���Փˌ㑬�x�ʒu�Z�o�֐�
	// pColPosA : �Փ˒��̃p�[�e�B�N��A�̒��S�ʒu, pVelocityA : �Փ˂̏u�Ԃ̃p�[�e�B�N��A�̑��x
	// pColPosB : �Փ˒��̃p�[�e�B�N��B�̒��S�ʒu, pVelocityB : �Փ˂̏u�Ԃ̃p�[�e�B�N��B�̑��x
	// massA : �p�[�e�B�N��A�̎���, massB : �p�[�e�B�N��B�̎���
	// resA : �p�[�e�B�N��A�̔�����(restitution), resB : �p�[�e�B�N��B�̔�����(restitution)
	// time : ���ˌ�̈ړ��\����
	// pOutPosA : �p�[�e�B�N��A�̔��ˌ�ʒu, pOutVelocityA : �p�[�e�B�N��A�̔��ˌ㑬�x�x�N�g��
	// pOutPosB : �p�[�e�B�N��B�̔��ˌ�ʒu, pOutVelocityB : �p�[�e�B�N��B�̔��ˌ㑬�x�x�N�g��
	bool calculateParticlePositionAfterCollision(CVector3* pColPosA, CVector3* pVelocityA,
															CVector3* pColPosB, CVector3* pVelocityB,
															float massA, float massB,
															float resA, float resB,
															float time,
															CVector3* pOutPosA, CVector3* pOutVelocityA,
															CVector3* pOutPosB, CVector3* pOutVelocityB);

}