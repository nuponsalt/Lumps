#pragma once

#include "../../Library/Library.h"
using namespace KMT ;

#include <memory>

// �擾��]�^�C�v
enum RotateAxis
{
	AXISX = 0x01,
	AXISY = 0x02,
	AXISZ = 0x04,
	ALL = 0x08
};

class CCameraThirdPerson;
typedef std::shared_ptr<CCameraThirdPerson> CCameraThirdPersonSP;

class CCameraThirdPerson : public CCamera
{
public :

	// �f�X�g���N�^
	~CCameraThirdPerson() { }
	// ����
	static CCameraThirdPersonSP Create();
	// �v�Z
	void Calculate();
	// �擾
	CQuaternion getRotation(const RotateAxis &_type) const;
	// �ݒ�
	inline void setOffset(float _fx, float _fy, float _fz) { Offset = CVector3(_fx, _fy, _fz); }	// �I�t�Z�b�g
	inline void setOffset(const CVector3 &_offset) { Offset = _offset; }
	inline void setOverhead(float _ohdist) { OverheadDistance = _ohdist; }
	inline void setSpeed(float _speed) { Speed = _speed; }
	
private :
	// �Ώۂ���̃J�����̈ʒu
	CVector3 Offset;
	// �I�u�W�F�N�g�̓��㋗��
	float OverheadDistance;
	// ��]�X�s�[�h
	float Speed;
	// �J�����̉�]
	CQuaternion rotation;
	CQuaternion rotationAxisVertical; // ZX������]���
	CQuaternion rotationAxisY; // Y����]���̂�

	// �R���X�g���N�^
	CCameraThirdPerson();
	// �J�����̉�]
	void Spin();

} ;