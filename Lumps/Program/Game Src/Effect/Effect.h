#pragma once

#include "../../Library/Library.h"
#include <memory>
using namespace KMT;

class CEffect;
typedef std::shared_ptr<CEffect> CEffectSP;

// エフェクトの種類
enum EffectType {
	// 拡散
	DIFFUSION,
	// 舞い降り
	FLYDOWN
};

class CEffect
{
public :
	// コンストラクタ
	CEffect() { }
	// デストラクタ
	virtual ~CEffect() { }
	
	// 初期化
	virtual void initializeEffect() = 0;
	// 破棄
	virtual void destroyEffect() = 0;

	// 更新
	virtual void updateEffect() = 0;
	
	//* 設定 *//
	// 初期座標設定
	inline void setParticlePosition(const CVector3& pos) { Particle->Position = pos; }

protected :
	// パーティクル
	CPointSpriteSP Particle;
	// エフェクトの種類
	EffectType personalType;
	// ポイントスプライト座標(std::vector)
	std::vector<D3DXVECTOR3> Positions;
	// ポイントスプライト速度(std::vector)
	std::vector<float> Speeds;
};