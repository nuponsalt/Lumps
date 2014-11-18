#include "DXUT.h"
#include "AnimationEffect.h"

int CAnimationEffect::AnimationSpeed = 0;
std::list<CAnimationEffectSP> CAnimationEffect::EffectList;

CAnimationEffectSP CAnimationEffect::CreateEffect(std::string xmlpath, const CVector3& pos)
{
	// XMLのロード
	CWsbXmlSP xml = CWsbXml::LoadXmlFile(xmlpath);
	// エフェクトの生成
	CAnimationEffectSP eff = CAnimationEffectSP(new CAnimationEffect());
	// ビルボードの生成
	eff->Board = CGPlane::CreateFromTexture(
		xml->GetElement("Path")->GetString(),
		xml->GetElement("DevideNumber")->GetElement("X")->GetInt(),
		xml->GetElement("DevideNumber")->GetElement("Y")->GetInt(),
		xml->GetElement("Size")->GetElement("Width")->GetInt(),
		xml->GetElement("Size")->GetElement("Height")->GetInt()
		);
	// 座標セット
	eff->Board->Position = pos;
	eff->Board->setPlayMode(PLAY_ONCE);
	eff->Board->isBillBoard = true;
	eff->Board->setisAddBlend(true);
	// アニメーションのスピードをセット
	AnimationSpeed = xml->GetElement("AnimationSpeed")->GetInt();
	// エフェクト
	EffectList.push_back(eff);

	return eff;
}

void CAnimationEffect::updateAllEffect()
{
	auto it = EffectList.begin();
	while(it != EffectList.end())
	{
		// アニメーション管理
		if((*it)->Board->UpdateAnimation(AnimationSpeed))
		{
			// アニメーションが終了していた場合リストから除外しスキップ
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