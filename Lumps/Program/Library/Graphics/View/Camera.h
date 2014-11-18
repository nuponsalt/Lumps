//*********************************************
// �J�����̊�{���Ǘ��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#include "ViewBehavior.h"
#include "../../System/Command.h"

#include <memory>

namespace KMT { 

	class CCamera;
	typedef std::shared_ptr<CCamera> CCameraSP;
	typedef std::weak_ptr<CCamera> CCameraWP;

	class CCamera : public CViewBehavior
	{
	public :
		// �f�X�g���N�^
		virtual ~CCamera();

		// ����
		static CCameraSP Create();
		
		// �ݒ�
		inline void setSize(const float &_Size) { Size = _Size; }
		void setSizeIPO(const float &_Size);
		/* �R�}���h */
		inline void setCommand(const CCommand& _command) { Command = _command; }
		
		// �擾
		inline CVector3 getDirection() const { return Direction; } //0�x�N�g���ɂȂ�悤�ȕ����ł̈��p�̓o�O�̉����ɂȂ邩��NG
		inline float getSize() const { return Size; }

		// �s��X�V
		void updateView();
		// �e�J�������W�Z�o
		virtual void Calculate();

	protected :
		// �J�����̌���
		CVector3 Direction;		
		// �T�C�Y
		float Size;
		// �R�}���h
		CCommand Command;

		// �R���X�g���N�^
		CCamera();

	} ;

}