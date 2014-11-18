//*********************************************************************
// �N�H�[�^�j�I���N���X
// Last Update : 2013.12.11
// Yuta Komatsu
//*********************************************************************
#pragma once

namespace KMT {
	
	// �N�H�[�^�j�I��
	class CQuaternion : public D3DXQUATERNION {
	public :

		// �R���X�g���N�^
		// �P�ʃN�H�[�^�j�I���𐶐�
		CQuaternion() : D3DXQUATERNION( 0, 0, 0, 1 ){}

		// �w�肵���v�f�Ő���
		CQuaternion( float x, float y, float z, float w ) : D3DXQUATERNION( x, y, z, w ){}

		// �w�肵�����Ɗp�x�̉�]��\���N�H�[�^�j�I���𐶐�
		// �w��p�x�̓��W�A���l
		CQuaternion( const CVector3& axis, float angle ) ;

		// �w�肵�����Ɗp�x�̉�]��\���N�H�[�^�j�I���𐶐�
		// ��L�R���X�g���N�^�Ƌ@�\�͓���
		friend CQuaternion RotationAroundAxis( const CVector3& axis, float angle ){
			return CQuaternion( axis, angle ) ;
		}
		
		// �w�莲�̉�]��\���N�H�[�^�j�I���𐶐�
		// ���̒������p�x�ɂȂ�
		CQuaternion( const CVector3& axis ) ;

		// �w��x�N�g���Ԃ̉�]��\���N�H�[�^�j�I���𐶐�
		// �x�N�g���͐��K�����Ă����K�v�Ȃ�
		CQuaternion( CVector3 vfrom, CVector3 vto ) ;

		// �w��x�N�g���Ԃ̉�]��\���N�H�[�^�j�I���𐶐�
		// �x�N�g���͐��K�����Ă����K�v�Ȃ�
		// ��L�R���X�g���N�^�Ƌ@�\�͓���
		friend CQuaternion RotationBetweenVectors(const CVector3& vfrom, const CVector3& vto) {
			return CQuaternion( vfrom, vto ) ;
		} 

		// �w��x�N�g���Ԃ̉�]��\���N�H�[�^�j�I���𐶐�
		// �x�N�g���͐��K�����Ă����K�v�Ȃ�
		// �w�肵�����𒆐S�ɉ�]����̂ŁA�J�����ȂǂœV�n�𔽓]���������Ȃ��ꍇ�ȂǂɎg�p
		CQuaternion( CVector3 vfrom, CVector3 vto, CVector3 axis ) ;

		// �w��x�N�g���Ԃ̉�]��\���N�H�[�^�j�I���𐶐�
		// �x�N�g���͐��K�����Ă����K�v�Ȃ�
		// �w�肵�����𒆐S�ɉ�]����̂ŁA�J�����ȂǂœV�n�𔽓]���������Ȃ��ꍇ�ȂǂɎg�p
		// �@�\�͊Y������R���X�g���N�^�Ɠ���
		friend CQuaternion RotationBetweenVectorsAroundAxis( const CVector3& vfrom, const CVector3& vto, const CVector3& axis ) {
			return CQuaternion( vfrom, vto, axis );
		}

		// ���ʐ��`���
		// f = 0�̂Ƃ�v1, f = 1�̂Ƃ�v2
		CQuaternion( const CQuaternion& v1, const CQuaternion& v2, float f ) ;

		// D3DXQUATERNION����̕ϊ�
		CQuaternion( const D3DXQUATERNION& q ) ;

		// D3DXQUATERNION�ւ̕ϊ�
		operator D3DXQUATERNION() const ;

		// ���
		CQuaternion& operator= ( const CQuaternion& q ) ;

		// ���K��
		// �����̃N�H�[�^�j�I���ɑ��
		CQuaternion& Normalize() ;

		// ���K��
		// ���ʂ̃N�H�[�^�j�I���𐶐�
		friend CQuaternion Normalize( CQuaternion q ) {
			return q.Normalize() ;
		}

		// �t�N�H�[�^�j�I��
		// �����̃N�H�[�^�j�I���ɑ��
		CQuaternion& Inverse() ;
		
		// �t�N�H�[�^�j�I��
		// ���ʂ̃N�H�[�^�j�I���𐶐�
		friend CQuaternion Inverse( CQuaternion q ) {
			return q.Inverse() ;
		}

		CQuaternion& Delta( CQuaternion q ) ;

		friend CQuaternion Delta( CQuaternion q1, CQuaternion q2 ) {
			return q1.Delta( q2 ) ;
		}

	} ;

}