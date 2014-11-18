//*********************************************
// ゲーム内オブジェクト基礎クラス
// Last Update : 2013.12.5
// Yuta Komatsu
//*********************************************
#pragma once

#include "../../Library/Library.h"
using namespace KMT;

#include <memory>
#include "State.h"

class CGameObject;
typedef std::shared_ptr<CGameObject> CGameObjectSP;
typedef std::weak_ptr<CGameObject> CGameObjectWP;

enum GameObjectType
{
	PLAYER,
	DROP,
	OBJECT_MAX
};

class CGameObject : public std::enable_shared_from_this<CGameObject>
{
public :
	// 自身の行動権
	bool isActive;
	// 拡縮・回転・座標(これの要素が最終的な数値になっているべき)
	CTransformation Transform;
	// 体積
	float Volume;
	// 重力
	float Gravity;
	// 移動速度
	float Speed, MaxSpeed;
	CVector3 Velocity;
	// 与える回転
	CQuaternion ImpactRotation;
	// オブジェクトが所持するモデル
	CGRendererSP Model;
	// 影(板ポリで代用)
	CGPlaneSP Shadow;
	// マーカー(ミニマップで使う)
	CGPlaneSP Marker;

	// 自分とリンクしているオブジェクト
	std::vector<CGameObjectWP> Links;
	// 付いた瞬間の姿勢を記憶
	std::vector<CQuaternion> BaseRotations;
	// 付いた瞬間の相対座標を記憶
	std::vector<CVector3> LocalPositions;

	// コンストラクタ
	CGameObject();
	// デストラクタ
	virtual ~CGameObject() 
	{
		Model.reset();
		Shadow.reset();
		Links.clear();
	}

	// 現在の状態からCStateオブジェクトを作成
	virtual CState CreateState() = 0;

	// リンク状態の更新(再帰処理)
	void UpdateLink(const CGameObjectSP _parent, CQuaternion &_parent_rotation, CQuaternion &_local_rotation, CVector3 _local_position);
	// 更新
	virtual void Update() = 0;
	// 描画設定
	virtual void isVisible(const CCamera* camera) = 0;

	//* 取得 *//
	// サイズ
	inline float getSize() const { return Size; }
	inline float getSizeMax() const { return MaxSize; }
	// ライフ
	inline int getLife() const { return Life; }
	inline int getLifeMax() const { return MaxLife; }
	// 描画フラグ
	inline bool getisRender() const { return isRender; }

	// この物体のX軸正方向の単位ベクトル
	CVector3 AxisX() { return CVector3(1, 0, 0) * Transform.qRotation; }
	// この物体のY軸正方向の単位ベクトル
	CVector3 AxisY() { return CVector3(0, 1, 0) * Transform.qRotation; }
	// この物体のZ軸正方向の単位ベクトル
	CVector3 AxisZ() { return CVector3(0, 0, 1) * Transform.qRotation; }

	//* 設定 *//
	// 描画フラグ
	inline void setisRender(const bool _isrender) { isRender = _isrender; }

private :
protected :
	// 状態
	CState State;
	// 描画座標
	CVector3 RenderPosition;
	// 座標履歴(1フレーム前の座標)
	CVector3 PreviousPosition;
	// サイズ(直径センチメートル)
	float Size, MinSize, MaxSize;
	// ライフ
	int Life, MaxLife;
	// 描画フラグ
	bool isRender;

	// 入力からCCommandオブジェクトを作成
	CCommand CreateCommand();
};