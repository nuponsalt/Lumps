#pragma once

#include <memory>
#include "../Sphere.h"

#include "../../../Camera/CameraThirdPerson.h"

class CPlayer;
typedef std::shared_ptr<CPlayer> CPlayerSP;

// プレイヤー
class CPlayer : public CSphere
{
public: 
	// デストラクタ
	~CPlayer();
	// 生成
	static CPlayerSP Create();

	//* 取得 *// 
	// カメラ
	inline CCameraSP getCamera() const { return Camera; }
	// サイズ 
	static inline float getStSize() { return StatusSize; }
	// 経験値
	inline float getExpNext() { return nextLevelExp; }

	// 前方向回転を得る
	CQuaternion getFrontRotation() const;
	// 設定 : カメラ
	void setCamera(CCameraThirdPersonSP _camera){ Camera = _camera; }

private :
	// 移動方向
	CVector3 Direction;
	// 正面回転
	CQuaternion frontRotation;
	// カメラ(三人称)
	CCameraThirdPersonSP Camera;

	// レベル
	int Level;
	// 次のレベルに必要な経験値
	int nextLevelExp;
	// 前のレベルに必要だった経験値
	int prevLevelExp;
	// レベルに応じて上がるサイズ
	static float StatusSize;

	// SE
	std::string pathLvUpSE;

	// コンストラクタ
	CPlayer();

	// 入力をZX平面に変換
	CVector3 getZXVector(CCommand &command);
	// 移動量計算
	void calculateVelocity(CCommand &command);
	// 回転量計算
	void calculateRotation(CCommand &command);
	// レベル計算
	void calculateLevel();
	// 行動の更新
	void updateAction(CCommand &command, CState &state);
	
protected :
	// 派生クラス固有の更新処理
	void subUpdate(CCommand &command, CState &state);
	// 情報の反映
	void subApplyParameter();

};