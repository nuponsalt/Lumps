#pragma once

#include "../../Library/Library.h"
#include <memory>
using namespace KMT;

class CEffect;
typedef std::shared_ptr<CEffect> CEffectSP;

// �G�t�F�N�g�̎��
enum EffectType {
	// �g�U
	DIFFUSION,
	// �����~��
	FLYDOWN
};

class CEffect
{
public :
	// �R���X�g���N�^
	CEffect() { }
	// �f�X�g���N�^
	virtual ~CEffect() { }
	
	// ������
	virtual void initializeEffect() = 0;
	// �j��
	virtual void destroyEffect() = 0;

	// �X�V
	virtual void updateEffect() = 0;
	
	//* �ݒ� *//
	// �������W�ݒ�
	inline void setParticlePosition(const CVector3& pos) { Particle->Position = pos; }

protected :
	// �p�[�e�B�N��
	CPointSpriteSP Particle;
	// �G�t�F�N�g�̎��
	EffectType personalType;
	// �|�C���g�X�v���C�g���W(std::vector)
	std::vector<D3DXVECTOR3> Positions;
	// �|�C���g�X�v���C�g���x(std::vector)
	std::vector<float> Speeds;
};