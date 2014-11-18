// �v���R���p�C���ς݃w�b�_�[�t�@�C���Ăяo��
#include "DXUT.h"

#include "CameraThirdPerson.h"
#include "../Define.h"

CCameraThirdPerson::CCameraThirdPerson() 
	: CCamera(), Offset(ZERO, ZERO, ONE), OverheadDistance(ONE), rotation(), rotationAxisVertical(), rotationAxisY()
{}

CCameraThirdPersonSP CCameraThirdPerson::Create()
{
	CCameraThirdPerson* cam_ptr = new CCameraThirdPerson() ;
	
	return CCameraThirdPersonSP(cam_ptr);
}

void CCameraThirdPerson::Spin()
{
	CQuaternion qua = CQuaternion();
	float _speed = (!CCommand::CheckMoveCommand(Command)) ? Speed : Speed * HALF;
	// ������
	if(Command.Check(CCommand::SQUARE))
		qua = RotationY(D3DXToRadian(-_speed));
	// �E����
	if(Command.Check(CCommand::CIRCLE))
		qua = RotationY(D3DXToRadian(_speed));
	// ���𔽉f
	rotationAxisY *= qua;
}

void CCameraThirdPerson::Calculate()
{
	Spin();
	// Y�I�t�Z�b�g��ݒ�
	Offset.y = OverheadDistance;
	// �J�����̎p��
	rotation = rotationAxisVertical * rotationAxisY;
	// �p������l�������J�����ʒu
	CVector3 resofs = Offset * rotation;
	// 1�t���[���O�̏�Ԃ̃J�������W��ۑ�
	View.previousEye = View.Eye;
	// �J�������W��ݒ�
	View.Eye += ((View.LookAt + (resofs) * Size) - View.previousEye) * INTERPOLATE_MIDDLE;
	// �J�����̕������v�Z
	Direction = (View.LookAt - View.Eye).Normalize();
}

CQuaternion CCameraThirdPerson::getRotation(const RotateAxis &_type) const
{
	return (_type == AXISX) ? rotation : (_type == AXISY) ? rotationAxisY : (_type == AXISZ) ? rotation : rotation;
}