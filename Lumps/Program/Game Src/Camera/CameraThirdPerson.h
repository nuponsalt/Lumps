#pragma once

#include "../../Library/Library.h"
using namespace KMT ;

#include <memory>

// 取得回転タイプ
enum RotateAxis
{
	AXISX = 0x01,
	AXISY = 0x02,
	AXISZ = 0x04,
	ALL = 0x08
};

class CCameraThirdPerson;
typedef std::shared_ptr<CCameraThirdPerson> CCameraThirdPersonSP;

class CCameraThirdPerson : public CCamera
{
public :

	// デストラクタ
	~CCameraThirdPerson() { }
	// 生成
	static CCameraThirdPersonSP Create();
	// 計算
	void Calculate();
	// 取得
	CQuaternion getRotation(const RotateAxis &_type) const;
	// 設定
	inline void setOffset(float _fx, float _fy, float _fz) { Offset = CVector3(_fx, _fy, _fz); }	// オフセット
	inline void setOffset(const CVector3 &_offset) { Offset = _offset; }
	inline void setOverhead(float _ohdist) { OverheadDistance = _ohdist; }
	inline void setSpeed(float _speed) { Speed = _speed; }
	
private :
	// 対象からのカメラの位置
	CVector3 Offset;
	// オブジェクトの頭上距離
	float OverheadDistance;
	// 回転スピード
	float Speed;
	// カメラの回転
	CQuaternion rotation;
	CQuaternion rotationAxisVertical; // ZX両軸回転情報
	CQuaternion rotationAxisY; // Y軸回転情報のみ

	// コンストラクタ
	CCameraThirdPerson();
	// カメラの回転
	void Spin();

} ;