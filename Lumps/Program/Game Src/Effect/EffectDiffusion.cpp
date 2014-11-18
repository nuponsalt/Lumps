#include "DXUT.h"
#include "EffectDiffusion.h"

// �R���X�g���N�^
CEffectDiffusion::CEffectDiffusion()
{
	// �G�t�F�N�g�^�C�v�̐ݒ�
	personalType = DIFFUSION;

	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Effect/Diffusion.xml");

	// �|�C���g�X�v���C�g����
	Particle = CPointSprite::CreatePointSprite(
		xml->GetElement("Path")->GetString(),
		xml->GetElement("Number")->GetInt(),
		xml->GetElement("Size")->GetFloat()
		);

	Particle->isRender = false;
	Particle->setisAddBlend(true);

	// �e�l�̃��[�h
	
}

void CEffectDiffusion::initializeEffect()
{

}

void CEffectDiffusion::destroyEffect()
{

}

void CEffectDiffusion::updateEffect()
{

}