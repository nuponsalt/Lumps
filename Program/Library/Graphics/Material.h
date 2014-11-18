//*********************************************
// �J���[�Ǘ��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#include "../Math/Vector.h"

namespace KMT {

	class CMaterial
	{
	public :
		
		// �J���[(�r�b�g�l)
		int nColor;
		// �J���[(4D�x�N�g��)
		CVector4 vColorRGBA;
		// �R���X�g���N�^
		CMaterial() : vColorRGBA(1, 1, 1, 1), isAddBlend(false) { }
		// �f�X�g���N�^
		virtual ~CMaterial() { }
		// �擾 : ���Z�t���O
		inline bool getisAddBlend() { return isAddBlend; }
		// �ݒ� : ���Z�t���O
		inline void setisAddBlend(bool _add) { isAddBlend = _add; }
		// �擾 : �J���[
		inline CVector4 getColorRGBA() const { return vColorRGBA; }
		// �ݒ� : �J���[
		inline void setColorRGBA(const float &r, const float &g, const float &b, const float &a) { vColorRGBA = CVector4(r, g, b, a); }
		inline void setColorRGBA(const CVector4 &_v4color) { vColorRGBA = _v4color; }

	protected :
		// ���Z�����邩�A�ۂ�
		bool isAddBlend;

	};

}