#include "DXUT.h"
#include "Timer.h"

namespace KMT 
{

	// �^�C�}�[��i�߂�֐�
	const bool CTimer::TimeCount()
	{
		if( count < time ){
			++count ;
			return false ;
		}
		else{
			ResetCount() ;
			return true ;
		}
	}


	// �^�C�}�[��i�߂�֐�����2
	const bool CTimer::TimeCountZero()
	{
		if( 0 == count ){
			++count ;
			return true ;
		}
		else if( count > 0 && count < time ){
			++count ;
			return false ;
		}
		else{
			ResetCount() ;
			return false ;
		}
	}

}