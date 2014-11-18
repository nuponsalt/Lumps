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

// ����(0�x)
const float DOT_0								= 1.0f ;		

// ����(30�x)
const float DOT_30								= 0.866f ;	

// ����(45�x)
const float DOT_45								= 0.707f ;	

// ����(60�x)
const float DOT_60								= 0.5f ;		

// ����(90�x)
const float DOT_90								= 0 ;		

// ����(180�x)
const float DOT_180								= -1.0f ;

// �p�x(360�x)
const float ANGLE_360						= 360.0f ;

// �~����
const float PI										= 3.141592654f ;

//-----------------------------------------------------------------
//CVector3

// �S�v�f��0�̃x�N�g��
const CVector3 ZERO_VECTOR3						= CVector3( ZERO, ZERO, ZERO ) ;

// �S�v�f��1�̃x�N�g��
const CVector3 ONE_VECTOR3						= CVector3( ONE, ONE, ONE ) ;

// �⊮���x : �Ȃ�
const float INTERPOLATE_NONE					= 0.0f ;

// �ۊǑ��x : ����
const float INTERPOLATE_EX						= 0.01 ;

// �ۊǑ��x : �Œ�
const float INTERPOLATE_MIN						= 0.05f ;

// �⊮���x : ��
const float INTERPOLATE_LOW						= 0.1f ;

// �⊮���x : ��
const float INTERPOLATE_MIDDLE					= 0.375f ;	

// �⊮���x : ��
const float INTERPOLATE_HIGH					= 0.5f ;		

// �⊮���x : �ō�
const float INTERPOLATE_MAX						= 1.0f ;		

// �����̉�]
const CQuaternion DEFAULT_ROTATION				= CQuaternion() ;

// �����̐��`�⊮�W��(��])
const float DEFAULT_ROTATION_INTERPOLATE		= INTERPOLATE_MAX ;

// �����̑��x
const CVector3 DEFAULT_VELOCITY					= CVector3() ;					

// �����̐��`�⊮�W��(���x)
const CVector3 DEFAULT_VELOCITY_INTERPOLATE		= CVector3(INTERPOLATE_HIGH, ZERO, INTERPOLATE_HIGH) ;

// ���C�W��
const float FRICTION_GROUND						= 0.95f ;		// �n��

const float FRICTION_AIR						= 0.98f ;		// ��

const float FRICTION_ = 0 ;

// �n�ʈʒu
const float GROUND_POSITION = 0.0f ;