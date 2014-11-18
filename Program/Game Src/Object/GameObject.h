//*********************************************
// �Q�[�����I�u�W�F�N�g��b�N���X
// Last Update : 2013.12.5
// Yuta Komatsu
//*********************************************
#pragma once

#include "../../Library/Library.h"
using namespace KMT;

#include <memory>
#include "State.h"

class CGameObject;
typedef std::shared_ptr<CGameObject> CGameObjectSP;
typedef std::weak_ptr<CGameObject> CGameObjectWP;

enum GameObjectType
{
	PLAYER,
	DROP,
	OBJECT_MAX
};

class CGameObject : public std::enable_shared_from_this<CGameObject>
{
public :
	// ���g�̍s����
	bool isActive;
	// �g�k�E��]�E���W(����̗v�f���ŏI�I�Ȑ��l�ɂȂ��Ă���ׂ�)
	CTransformation Transform;
	// �̐�
	float Volume;
	// �d��
	float Gravity;
	// �ړ����x
	float Speed, MaxSpeed;
	CVector3 Velocity;
	// �^�����]
	CQuaternion ImpactRotation;
	// �I�u�W�F�N�g���������郂�f��
	CGRendererSP Model;
	// �e(�|���ő�p)
	CGPlaneSP Shadow;
	// �}�[�J�[(�~�j�}�b�v�Ŏg��)
	CGPlaneSP Marker;

	// �����ƃ����N���Ă���I�u�W�F�N�g
	std::vector<CGameObjectWP> Links;
	// �t�����u�Ԃ̎p�����L��
	std::vector<CQuaternion> BaseRotations;
	// �t�����u�Ԃ̑��΍��W���L��
	std::vector<CVector3> LocalPositions;

	// �R���X�g���N�^
	CGameObject();
	// �f�X�g���N�^
	virtual ~CGameObject() 
	{
		Model.reset();
		Shadow.reset();
		Links.clear();
	}

	// ���݂̏�Ԃ���CState�I�u�W�F�N�g���쐬
	virtual CState CreateState() = 0;

	// �����N��Ԃ̍X�V(�ċA����)
	void UpdateLink(const CGameObjectSP _parent, CQuaternion &_parent_rotation, CQuaternion &_local_rotation, CVector3 _local_position);
	// �X�V
	virtual void Update() = 0;
	// �`��ݒ�
	virtual void isVisible(const CCamera* camera) = 0;

	//* �擾 *//
	// �T�C�Y
	inline float getSize() const { return Size; }
	inline float getSizeMax() const { return MaxSize; }
	// ���C�t
	inline int getLife() const { return Life; }
	inline int getLifeMax() const { return MaxLife; }
	// �`��t���O
	inline bool getisRender() const { return isRender; }

	// ���̕��̂�X���������̒P�ʃx�N�g��
	CVector3 AxisX() { return CVector3(1, 0, 0) * Transform.qRotation; }
	// ���̕��̂�Y���������̒P�ʃx�N�g��
	CVector3 AxisY() { return CVector3(0, 1, 0) * Transform.qRotation; }
	// ���̕��̂�Z���������̒P�ʃx�N�g��
	CVector3 AxisZ() { return CVector3(0, 0, 1) * Transform.qRotation; }

	//* �ݒ� *//
	// �`��t���O
	inline void setisRender(const bool _isrender) { isRender = _isrender; }

private :
protected :
	// ���
	CState State;
	// �`����W
	CVector3 RenderPosition;
	// ���W����(1�t���[���O�̍��W)
	CVector3 PreviousPosition;
	// �T�C�Y(���a�Z���`���[�g��)
	float Size, MinSize, MaxSize;
	// ���C�t
	int Life, MaxLife;
	// �`��t���O
	bool isRender;

	// ���͂���CCommand�I�u�W�F�N�g���쐬
	CCommand CreateCommand();
};