#include "DXUT.h"
#include "FrameRateCounter.h"

const int FPSCOUNTER_QUERYPER_COUNTER = 1;
const int FPSCOUNTER_TIMEGETTIME = 2;

namespace KMT {

	CFrameRateCounter::CFrameRateCounter(unsigned int smp)
	{
		// �T���v�����̐ݒ�
		setSampleNumber_(smp);
		// �v�����鎞�v�̑I��
		if(QueryPerformanceCounter(&Counter_) != 0)
		{
			// QueryPerformanceCounter�֐����g���t���O
			CounterFlag_ = FPSCOUNTER_QUERYPER_COUNTER;
			// �������̎����i�N���b�N���j���擾
			PreviousCount_ = Counter_.QuadPart;
			LARGE_INTEGER Freq;
			// 1�b������N���b�N�����擾
			QueryPerformanceFrequency(&Freq);
			Frequency_ = (double)Freq.QuadPart;
		}
		else
		{
			// timeGetTime�֐����g���t���O
			CounterFlag_ = FPSCOUNTER_TIMEGETTIME;
			// ���x���グ��
			timeBeginPeriod(1);
			// �������̎����i�~���b�j���擾
			TGTPreviousCount_ = timeGetTime();
		}
		// �v��
		getFrameRate_();
	}

	CFrameRateCounter::~CFrameRateCounter()
	{
		if(CounterFlag_ == FPSCOUNTER_TIMEGETTIME)
			// �^�C�}�[�̐��x��߂�
			timeEndPeriod(1);
	}

	double CFrameRateCounter::getFrameRate_()
	{
		double Diff = getCurrentDiffTime_();
		// �v�Z�ł��Ȃ��̂ŕԂ�
		if (Diff == 0)	return 0;

		return updateFrameRate_(Diff);
	}

	double CFrameRateCounter::getCurrentDiffTime_()
	{
		// �������Ԃ��v��
		if(CounterFlag_ == FPSCOUNTER_QUERYPER_COUNTER)
		{
			// QueryPerformanceCounter�֐��ɂ��v��
			QueryPerformanceCounter(&Counter_); // ���݂̎������擾���A
			LONGLONG LongDef = Counter_.QuadPart - PreviousCount_; // �����J�E���g�����Z�o����B
			double dDef = (double)LongDef; // �{���x���������_�ɕϊ�
			PreviousCount_ = Counter_.QuadPart; // ���݂̎�����ێ�
			return dDef*1000 / Frequency_; // �������Ԃ��~���b�P�ʂŕԂ�
		}
		// timeGetTime�֐��ɂ��v��
		DWORD CurrentTime = timeGetTime();
		DWORD CurrentDiff = CurrentTime - TGTPreviousCount_; // �����J�E���g�����Z�o����
		TGTPreviousCount_ = CurrentTime; // ���݂̎�����ێ�
		return CurrentDiff;
	}

	double CFrameRateCounter::updateFrameRate_(double _Diff)
	{
		// �ł��Â��f�[�^������
		diffTimeList_.pop_front();
		// �V�����f�[�^��ǉ�
		diffTimeList_.push_back(_Diff);
		// �t���[�����[�g�Z�o
		double FPS = 0.0;
		double AveDiff = (summationTimes_ + _Diff) / Number_;
		if (AveDiff != 0)
			FPS = 1000.0 / AveDiff;
		// ���ʉ��Z�����̍X�V
		summationTimes_ += _Diff - *diffTimeList_.begin();
		// ���ʂ��߂�
		return FPS;
	}

	void CFrameRateCounter::setSampleNumber_(unsigned int smp)
	{
		// ���ς��v�Z�����
		Number_ = smp;
		// ���X�g������
		diffTimeList_.resize(Number_, 0.0);
		summationTimes_ = 0;
	}

}