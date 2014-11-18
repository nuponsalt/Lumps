#pragma once

#include <memory>
#include "../GameObject.h"

// typedef宣言
class CSphere;
typedef std::shared_ptr<CSphere> CSphereSP;
typedef std::weak_ptr<CSphere> CSphereWP;

// 球オブジェクト
class CSphere : public CGameObject
{
public :
	//* 球衝突判定情報 *//
	// 見た目と一致する衝突判定
	Sphere realSphere;
	// ゲーム上の動くオブジェクトとの衝突判定はこれで行う
	Sphere bvSphere;
	
	// コンストラクタ
	CSphere();
	// デストラクタ
	virtual ~CSphere();
	
	// 更新
	void Update();
	// 描画設定
	void isVisible(const CCamera* camera);
	// 現在の状態からCStateオブジェクトを作成
	CState CreateState();

	// 正面方向の回転を返す
	virtual CQuaternion getFrontRotation() const = 0;

private :
	// 情報の反映
	void applyParameter();

protected :
	// 頭上距離(カメラ注視点用)
	float Overhead;
	// 影のY座標
	float positionYShadow;

	// 派生クラス固有の更新処理
	virtual void subUpdate(CCommand &command, CState &state) = 0;
	// 情報の反映
	virtual void subApplyParameter() = 0;
	
	// 行動の更新
	virtual void updateAction(CCommand &command, CState &state) = 0;

};