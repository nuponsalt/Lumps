#pragma once

#include <memory>
#include "../Sphere.h"

#include "../../../Camera/CameraThirdPerson.h"

class CPlayer;
typedef std::shared_ptr<CPlayer> CPlayerSP;

// �v���C���[
class CPlayer : public CSphere
{
public: 
	// �f�X�g���N�^
	~CPlayer();
	// ����
	static CPlayerSP Create();

	//* �擾 *// 
	// �J����
	inline CCameraSP getCamera() const { return Camera; }
	// �T�C�Y 
	static inline float getStSize() { return StatusSize; }
	// �o���l
	inline float getExpNext() { return nextLevelExp; }

	// �O������]�𓾂�
	CQuaternion getFrontRotation() const;
	// �ݒ� : �J����
	void setCamera(CCameraThirdPersonSP _camera){ Camera = _camera; }

private :
	// �ړ�����
	CVector3 Direction;
	// ���ʉ�]
	CQuaternion frontRotation;
	// �J����(�O�l��)
	CCameraThirdPersonSP Camera;

	// ���x��
	int Level;
	// ���̃��x���ɕK�v�Ȍo���l
	int nextLevelExp;
	// �O�̃��x���ɕK�v�������o���l
	int prevLevelExp;
	// ���x���ɉ����ďオ��T�C�Y
	static float StatusSize;

	// SE
	std::string pathLvUpSE;

	// �R���X�g���N�^
	CPlayer();

	// ���͂�ZX���ʂɕϊ�
	CVector3 getZXVector(CCommand &command);
	// �ړ��ʌv�Z
	void calculateVelocity(CCommand &command);
	// ��]�ʌv�Z
	void calculateRotation(CCommand &command);
	// ���x���v�Z
	void calculateLevel();
	// �s���̍X�V
	void updateAction(CCommand &command, CState &state);
	
protected :
	// �h���N���X�ŗL�̍X�V����
	void subUpdate(CCommand &command, CState &state);
	// ���̔��f
	void subApplyParameter();

};