//*********************************************
// ���Z�̊g���֐�
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

namespace KMT {

	class CVector3 ;
	class CQuaternion ;
	
	extern const CVector3 AXIS_X ;
	extern const CVector3 AXIS_Y ;
	extern const CVector3 AXIS_Z ;
	
	// X������̉�]��\���N�H�[�^�j�I�����擾
	CQuaternion RotationX( float angle ) ;
	// Y������̉�]��\���N�H�[�^�j�I�����擾
	CQuaternion RotationY( float angle ) ;
	// Z������̉�]��\���N�H�[�^�j�I�����擾
	CQuaternion RotationZ( float angle ) ;

	// ���`���
	// ���ʂ�float�l�𐶐�
	// f=0�̂Ƃ�a�Af=1�̂Ƃ�b�ƂȂ�
	inline float Interpolate( float a, float b, float f ) 
	{
		return a * ( 1 - f ) + b * f ; 
	}

	// ���`���
	// ���ʂ�CVector3�𐶐�
	// ��L��float���`��Ԋ֐����g�p
	CVector3 Interpolate(const CVector3 &v1, const CVector3 &v2, float f) ;

	// ���ʐ��`���
	// f = 0�̂Ƃ�v1, f = 1�̂Ƃ�v2
	// �@�\�͊Y������R���X�g���N�^�Ɠ���
	CQuaternion Interpolate( const CQuaternion& q1, const CQuaternion& q2, float f ) ;

	// �N�H�[�^��I���̍���
	// pQ1 : 
	// pQ2 : 
	// return : ���Z���ʂ̃N�H�[�^�j�I��
	// tips1 : pQ1 -> pQ2 �ւ̍���
	// tips2 : ���̊֐��̖߂�l��pOut�̖߂�l�Ɠ����ł���B�ʂ̊֐��̈����Ƃ��Ă�������B
	CQuaternion* QuaternionDelta( CQuaternion *pOut, const CQuaternion *pQ1, const CQuaternion *pQ2 ) ;

	// �_�ƕ��ʂ̋������o��
	// vPt : �_�̍��W
	// vPNml : ���ʂ̖@��
	// vPPt : ���ʏ�̍��W
	// return : ���ʂ̋���
	float DistancePointPlane( D3DXVECTOR3 vPt, D3DXVECTOR3 vPNml, D3DXVECTOR3 vPPt ) ;

}