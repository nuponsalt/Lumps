#pragma once

namespace KMT {

	// �s��
	class CMatrix : public D3DXMATRIX {
	public :

		// �P�ʍs��𐶐�
		CMatrix(){ D3DXMatrixIdentity( this ) ; }

		// �z��ŗv�f���w�肵�čs��𐶐�
		CMatrix( const float* f ) : D3DXMATRIX( f ) {}

		// D3DXMATRIX����̕ϊ�
		CMatrix( const D3DXMATRIX& m ) : D3DXMATRIX( m ) {}

		// �g��k�����A��]�A���s�ړ���g�ݍ��킹���s��̐���
		CMatrix(const CVector3& scale, const CQuaternion& rotation, const CVector3& position) ;

		// ���
		CMatrix& operator= ( const CMatrix& m ) ;

	} ;
}