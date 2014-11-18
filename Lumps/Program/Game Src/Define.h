#pragma once

const enum LR{
		RIGHT = 1,
		LEFT = -1
} ;

//------------------------------------------------------------
// float

// 0
const float ZERO								= 0.0f ;		

// 1
const float ONE									= 1.0f ;

// 2
const float TWO								=2.0f ;

// 1/4
const float QUARTER								= 0.25f ;	

// 1/2
const float HALF								= 0.5f ;		

// 3/4
const float QUARTER_THREE						= 0.75f ;	

// 内積(0度)
const float DOT_0								= 1.0f ;		

// 内積(30度)
const float DOT_30								= 0.866f ;	

// 内積(45度)
const float DOT_45								= 0.707f ;	

// 内積(60度)
const float DOT_60								= 0.5f ;		

// 内積(90度)
const float DOT_90								= 0 ;		

// 内積(180度)
const float DOT_180								= -1.0f ;

// 角度(360度)
const float ANGLE_360						= 360.0f ;

// 円周率
const float PI										= 3.141592654f ;

//-----------------------------------------------------------------
//CVector3

// 全要素が0のベクトル
const CVector3 ZERO_VECTOR3						= CVector3( ZERO, ZERO, ZERO ) ;

// 全要素が1のベクトル
const CVector3 ONE_VECTOR3						= CVector3( ONE, ONE, ONE ) ;

// 補完速度 : なし
const float INTERPOLATE_NONE					= 0.0f ;

// 保管速度 : 特例
const float INTERPOLATE_EX						= 0.01 ;

// 保管速度 : 最低
const float INTERPOLATE_MIN						= 0.05f ;

// 補完速度 : 低
const float INTERPOLATE_LOW						= 0.1f ;

// 補完速度 : 中
const float INTERPOLATE_MIDDLE					= 0.375f ;	

// 補完速度 : 高
const float INTERPOLATE_HIGH					= 0.5f ;		

// 補完速度 : 最高
const float INTERPOLATE_MAX						= 1.0f ;		

// 初期の回転
const CQuaternion DEFAULT_ROTATION				= CQuaternion() ;

// 初期の線形補完係数(回転)
const float DEFAULT_ROTATION_INTERPOLATE		= INTERPOLATE_MAX ;

// 初期の速度
const CVector3 DEFAULT_VELOCITY					= CVector3() ;					

// 初期の線形補完係数(速度)
const CVector3 DEFAULT_VELOCITY_INTERPOLATE		= CVector3(INTERPOLATE_HIGH, ZERO, INTERPOLATE_HIGH) ;

// 摩擦係数
const float FRICTION_GROUND						= 0.95f ;		// 地上

const float FRICTION_AIR						= 0.98f ;		// 空中

const float FRICTION_ = 0 ;

// 地面位置
const float GROUND_POSITION = 0.0f ;