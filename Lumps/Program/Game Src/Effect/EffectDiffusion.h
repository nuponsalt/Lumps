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
	// デストラクタ
	~CEffectDiffusion() { }

	// 初期化
	void initializeEffect();
	// 破棄
	void destroyEffect();

	// 生成
	static CEffectDiffusionSP CreateEffect();
	// 更新
	void updateEffect();

private :
	// 拡散パーティクル
	CPointSpriteSP diffuseParticle;
	// サイズの変化値
	float transformSize;
	// 重力
	float gravity;
	// エミッターの数
	int emitterNumber;

	// コンストラクタ
	CEffectDiffusion();
};