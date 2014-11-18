#pragma once

#include <memory>
#include "../../Library/Library.h"
using namespace KMT;

class CAnimationEffect;
typedef std::shared_ptr<CAnimationEffect> CAnimationEffectSP;

class CAnimationEffect
{
public :
	// �|��
	CGPlaneSP Board;
	// �A�j���[�V�����Đ����x
	static int AnimationSpeed;

	// ���������G�t�F�N�g���i�[���Ă������X�g
	static std::list<CAnimationEffectSP> EffectList;

	// �R���X�g���N�^
	CAnimationEffect() { }
	// �f�X�g���N�^
	~CAnimationEffect() { }

	// �����֐�
	// xmlpath : �G�t�F�N�g����XML�t�@�C���̃p�X
	// pos : �G�t�F�N�g�̍��W
	static CAnimationEffectSP CreateEffect(std::string xmlpath, const CVector3& pos);
	// �J������
	static void DestroyEffect();

	// ���ׂẴG�t�F�N�g���X�V����
	static void updateAllEffect();

private :
};