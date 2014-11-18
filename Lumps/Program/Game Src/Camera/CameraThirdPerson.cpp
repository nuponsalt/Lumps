// プリコンパイル済みヘッダーファイル呼び出し
#include "DXUT.h"

#include "CameraThirdPerson.h"
#include "../Define.h"

CCameraThirdPerson::CCameraThirdPerson() 
	: CCamera(), Offset(ZERO, ZERO, ONE), OverheadDistance(ONE), rotation(), rotationAxisVertical(), rotationAxisY()
{}

CCameraThirdPersonSP CCameraThirdPerson::Create()
{
	CCameraThirdPerson* cam_ptr = new CCameraThirdPerson() ;
	
	return CCameraThirdPersonSP(cam_ptr);
}

void CCameraThirdPerson::Spin()
{
	CQuaternion qua = CQuaternion();
	float _speed = (!CCommand::CheckMoveCommand(Command)) ? Speed : Speed * HALF;
	// 左入力
	if(Command.Check(CCommand::SQUARE))
		qua = RotationY(D3DXToRadian(-_speed));
	// 右入力
	if(Command.Check(CCommand::CIRCLE))
		qua = RotationY(D3DXToRadian(_speed));
	// 情報を反映
	rotationAxisY *= qua;
}

void CCameraThirdPerson::Calculate()
{
	Spin();
	// Yオフセットを設定
	Offset.y = OverheadDistance;
	// カメラの姿勢
	rotation = rotationAxisVertical * rotationAxisY;
	// 姿勢から考慮したカメラ位置
	CVector3 resofs = Offset * rotation;
	// 1フレーム前の状態のカメラ座標を保存
	View.previousEye = View.Eye;
	// カメラ座標を設定
	View.Eye += ((View.LookAt + (resofs) * Size) - View.previousEye) * INTERPOLATE_MIDDLE;
	// カメラの方向を計算
	Direction = (View.LookAt - View.Eye).Normalize();
}

CQuaternion CCameraThirdPerson::getRotation(const RotateAxis &_type) const
{
	return (_type == AXISX) ? rotation : (_type == AXISY) ? rotationAxisY : (_type == AXISZ) ? rotation : rotation;
}