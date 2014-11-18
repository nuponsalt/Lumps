#pragma once

#include <memory>
#include "../../Library/Library.h"
using namespace KMT;

#include "Effect.h"

class CEffectDiffusion;
typedef std::shared_ptr<CEffectDiffusion> CEffectDiffusionSP;

class CEffectDiffusion : public CEffect
{
public :
	// �f�X�g���N�^
	~CEffectDiffusion() { }

	// ������
	void initializeEffect();
	// �j��
	void destroyEffect();

	// ����
	static CEffectDiffusionSP CreateEffect();
	// �X�V
	void updateEffect();

private :
	// �g�U�p�[�e�B�N��
	CPointSpriteSP diffuseParticle;
	// �T�C�Y�̕ω��l
	float transformSize;
	// �d��
	float gravity;
	// �G�~�b�^�[�̐�
	int emitterNumber;

	// �R���X�g���N�^
	CEffectDiffusion();
};