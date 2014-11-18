#pragma once

#include <memory>
#include "../GameObject.h"

// typedef�錾
class CSphere;
typedef std::shared_ptr<CSphere> CSphereSP;
typedef std::weak_ptr<CSphere> CSphereWP;

// ���I�u�W�F�N�g
class CSphere : public CGameObject
{
public :
	//* ���Փ˔����� *//
	// �����ڂƈ�v����Փ˔���
	Sphere realSphere;
	// �Q�[����̓����I�u�W�F�N�g�Ƃ̏Փ˔���͂���ōs��
	Sphere bvSphere;
	
	// �R���X�g���N�^
	CSphere();
	// �f�X�g���N�^
	virtual ~CSphere();
	
	// �X�V
	void Update();
	// �`��ݒ�
	void isVisible(const CCamera* camera);
	// ���݂̏�Ԃ���CState�I�u�W�F�N�g���쐬
	CState CreateState();

	// ���ʕ����̉�]��Ԃ�
	virtual CQuaternion getFrontRotation() const = 0;

private :
	// ���̔��f
	void applyParameter();

protected :
	// ���㋗��(�J���������_�p)
	float Overhead;
	// �e��Y���W
	float positionYShadow;

	// �h���N���X�ŗL�̍X�V����
	virtual void subUpdate(CCommand &command, CState &state) = 0;
	// ���̔��f
	virtual void subApplyParameter() = 0;
	
	// �s���̍X�V
	virtual void updateAction(CCommand &command, CState &state) = 0;

};