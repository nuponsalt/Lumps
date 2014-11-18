#pragma once

#include <memory>
#include "GraphicBehavior.h"

namespace KMT {

	// ���C���̒��_���`
	typedef struct LineVertex {
		float x, y, z;
		DWORD color;

		// �R���X�g���N�^
		LineVertex() { }
		LineVertex(CVector3 _v, DWORD _color) : x(_v.x), y(_v.y), z(_v.z), color(_color) { }

	}*pLineVertex;

	class CLine;
	typedef std::shared_ptr<CLine> CLineSP;
	typedef std::weak_ptr<CLine> CLineWP;

	// ���C���`��
	class CLine : public CGraphicBehavior
	{
	public :
		// �f�X�g���N�^
		~CLine() { }
		// ����
		static CLineSP Create(const CVector3& _posA, const CVector3& _posB, DWORD _color);

		// �`��
		void Render(const CCamera* _camera);

	private :
		// ���C���̒��_
		LineVertex Vertices[2];

		// �R���X�g���N�^
		CLine() { }

	protected :
	};

}