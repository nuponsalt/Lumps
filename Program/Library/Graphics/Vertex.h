#pragma once

#include "../Math/Vector.h"

namespace KMT {

	// ���_���
	class CVertex
	{
	public :
		// ���_���W
		CVector3 Position;
		// �@��
		CVector3 Normal;
		// ���_�J���[
		DWORD	 Color;
		// �e�N�Z�����W
		CVector2 UV;

		// �萔FVF
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

		// �R���X�g���N�^
		CVertex() : Position(0, 0, 0), Normal(0, 1, 0), UV(0, 0), Color(0xFFFFFFFF) { }

	};

	struct SCREEN_VERTEX
	{
		// XYZRHW
		float x, y, z, rhw ;

		//DIFFUSE
		DWORD color ;

		// TEX1
		float tu0, tv0 ;

		const static DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
	} ;

}