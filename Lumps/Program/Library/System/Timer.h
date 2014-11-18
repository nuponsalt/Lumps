#pragma once

#include <memory>

namespace KMT
{

	class CTimer ;
	typedef std::shared_ptr< CTimer > CTimerSP ;

	class CTimer
	{
	private :
		int count ;	// �J�E���g
		int time ;	// true��Ԃ�����

	public :

		// �f�t�H���g�R���X�g���N�^
		CTimer() : count(0), time(0)
		{}

		// �R���X�g���N�^
		// arg1... true��Ԃ��܂ł̎���
		CTimer(const int _time) : count( 0 ), time( _time )
		{}

		// �f�X�g���N�^
		~CTimer(){}

		// �^�C�}�[��i�߂�֐�
		// ret.... [ false : �Z�b�g�������Ԃɂ͂܂��B���Ă��Ȃ� ] [ true : �Z�b�g�������ԂɒB���� ]
		// tips... �Z�b�g�������ԂɂȂ��true��Ԃ��A�J�E���g�����Z�b�g����
		const bool TimeCount() ;

		// �^�C�}�[��i�߂�֐�����2
		// ret.... [ false : �J�E���g��0�ȊO ] [ true : �J�E���g��0 ]
		// tips... TimeCount�֐��Ƃ͈Ⴂ�A�J�E���g��0�ɂȂ����Ƃ���true��Ԃ��B����TimeCount�֐��Ɠ���
		const bool TimeCountZero() ;

		// ���Ԃ��Z�b�g����֐�
		// arg1... �Z�b�g����������
		void setTime( const int _time ){ time = _time ; count = 0 ; }

		// �J�E���g�����Z�b�g����֐�
		void ResetCount(){ count = 0 ; }

		// ���݃Z�b�g���Ă��鎞�Ԃ��擾����֐�
		// ret.... [ �߂�l : ���݃Z�b�g���Ă��鎞�� ]
		const int getTime() const { return time ; }

		// ���݂̃J�E���g�̎擾�֐�
		// ret.... [ �߂�l : ���݂̃J�E���g ]
		const int getCount() const { return count ; }
	} ;

}