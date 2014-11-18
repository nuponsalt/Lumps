#include "DXUT.h"
#include "EffectDiffusion.h"

// コンストラクタ
CEffectDiffusion::CEffectDiffusion()
{
	// エフェクトタイプの設定
	personalType = DIFFUSION;

	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Effect/Diffusion.xml");

	// ポイントスプライト生成
	Particle = CPointSprite::CreatePointSprite(
		xml->GetElement("Path")->GetString(),
		xml->GetElement("Number")->GetInt(),
		xml->GetElement("Size")->GetFloat()
		);

	Particle->isRender = false;
	Particle->setisAddBlend(true);

	// 各値のロード
	
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