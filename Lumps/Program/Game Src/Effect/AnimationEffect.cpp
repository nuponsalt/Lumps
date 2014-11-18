#include "DXUT.h"
#include "AnimationEffect.h"

int CAnimationEffect::AnimationSpeed = 0;
std::list<CAnimationEffectSP> CAnimationEffect::EffectList;

CAnimationEffectSP CAnimationEffect::CreateEffect(std::string xmlpath, const CVector3& pos)
{
	// XML�̃��[�h
	CWsbXmlSP xml = CWsbXml::LoadXmlFile(xmlpath);
	// �G�t�F�N�g�̐���
	CAnimationEffectSP eff = CAnimationEffectSP(new CAnimationEffect());
	// �r���{�[�h�̐���
	eff->Board = CGPlane::CreateFromTexture(
		xml->GetElement("Path")->GetString(),
		xml->GetElement("DevideNumber")->GetElement("X")->GetInt(),
		xml->GetElement("DevideNumber")->GetElement("Y")->GetInt(),
		xml->GetElement("Size")->GetElement("Width")->GetInt(),
		xml->GetElement("Size")->GetElement("Height")->GetInt()
		);
	// ���W�Z�b�g
	eff->Board->Position = pos;
	eff->Board->setPlayMode(PLAY_ONCE);
	eff->Board->isBillBoard = true;
	eff->Board->setisAddBlend(true);
	// �A�j���[�V�����̃X�s�[�h���Z�b�g
	AnimationSpeed = xml->GetElement("AnimationSpeed")->GetInt();
	// �G�t�F�N�g
	EffectList.push_back(eff);

	return eff;
}

void CAnimationEffect::updateAllEffect()
{
	auto it = EffectList.begin();
	while(it != EffectList.end())
	{
		// �A�j���[�V�����Ǘ�
		if((*it)->Board->UpdateAnimation(AnimationSpeed))
		{
			// �A�j���[�V�������I�����Ă����ꍇ���X�g���珜�O���X�L�b�v
			it = EffectList.erase(it);
			continue;
		}
		it++;
	}
}

void CAnimationEffect::DestroyEffect()
{
	EffectList.clear();
}