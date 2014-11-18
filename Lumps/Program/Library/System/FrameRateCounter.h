#pragma once
// 
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <list>
using namespace std;

namespace KMT {

	class CFrameRateCounter
	{
	public :
		// �R���X�g���N�^
		CFrameRateCounter(unsigned int smp = 10);
		// �f�X�g���N�^
		virtual ~CFrameRateCounter();

		// FPS�l���擾
		double getFrameRate_();
		// �T���v������ύX
		void setSampleNumber_(unsigned int smp);

	private :
		// �g�p����v���֐��̔���t���O
		int CounterFlag_;
		// �N���b�N�J�E���g��
		LARGE_INTEGER Counter_;
		// 1�b������N���b�N�J�E���g��(���g��)
		double Frequency_;
		// �ȑO�̃N���b�N�J�E���g��
		LONGLONG PreviousCount_;
		// �ȑO�̎����i�~���b�j
		DWORD TGTPreviousCount_;
		// ���ԃ��X�g
		list<double> diffTimeList_;
		// �ړ����όv�Z���̃f�[�^��
		UINT Number_;
		// ���ʕ����̍��v�l
		double summationTimes_;

	protected :
		// ���݂̎������擾
		double getCurrentDiffTime_();
		// �t���[�����[�g���X�V
		double updateFrameRate_(double _Diff);

	};

}