#pragma once

#include <memory>
#include "../../Library/Library.h"
using namespace KMT;

class CAnimationEffect;
typedef std::shared_ptr<CAnimationEffect> CAnimationEffectSP;

class CAnimationEffect
{
public :
	// 板ポリ
	CGPlaneSP Board;
	// アニメーション再生速度
	static int AnimationSpeed;

	// 生成したエフェクトを格納しておくリスト
	static std::list<CAnimationEffectSP> EffectList;

	// コンストラクタ
	CAnimationEffect() { }
	// デストラクタ
	~CAnimationEffect() { }

	// 生成関数
	// xmlpath : エフェクト情報のXMLファイルのパス
	// pos : エフェクトの座標
	static CAnimationEffectSP CreateEffect(std::string xmlpath, const CVector3& pos);
	// 開放処理
	static void DestroyEffect();

	// すべてのエフェクトを更新する
	static void updateAllEffect();

private :
};