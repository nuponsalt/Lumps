#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "DXUT.h"
#include <map>
#include <list>
#include <string>
#include <windows.h>
#include "sound.h"

//-------------------------------------------------------------
// �o�b�t�@�f�[�^
class CSoundWav{
private :
	CSoundWav() : m_p_buffer(NULL), m_is_delete_ok(false)
	{
	} ;
	~CSoundWav(){
		SAFE_DELETE( m_p_buffer ) ;
	} ;
	bool m_is_delete_ok ;
	CWaveFile m_wav ;
	BYTE* m_p_buffer ;
	friend class CSound ;
	friend class CSoundManager ;
} ;


//-------------------------------------------------------------
// �}�l�[�W���{��
class CSoundManager{

private :

	// new �֎~
	CSoundManager(){} ;

	// delete �֎~
	~CSoundManager(){} ;

	static int m_id_count ;
	static std::map< std::string, CSoundWav* > m_buffers ;
	static std::map< std::string, std::map<int,CSound*> > m_sounds ;
	static void Erase( const int sound_id ) ;
	friend class CSound ;

public :

	//-----------------------------------------------------------
	// �v���C���[�h
	enum{
		MODE_ONCE,	// ��x�����Đ�
		MODE_LOOP	// ���[�v�Đ�
	} ;

	//-----------------------------------------------------------
	// ���
	enum{
		STATE_NONE,		// ����( ���݂��Ȃ��� )
		STATE_STOP,		// �Đ�����Ă��Ȃ����
		STATE_PLAY,		// �Đ���
		STATE_REPLAY,	// ( �V�X�e�����Ŏg�p )
	} ;

	//-----------------------------------------------------------
	// �X�V
	// arg1... none
	// ret.... none
	// tips... ���t���[�����߂ɌĂяo���Ă�������
	static void Updata() ;

	//-----------------------------------------------------------
	// ��Ԃ̎擾
	// arg1... �T�E���hID
	// ret.... ��Ԃ��A���Ă��܂� ( STATE_NONE, STATE_STOP, STATE_PLAY )
	// tips... none
	static int GetState( const int sound_id ) ;

	//-----------------------------------------------------------
	// ���[�h
	// arg1... �t�@�C���p�X
	// ret.... none
	// tips... none
	static void Load( const std::string& file_name ) ;

	//-----------------------------------------------------------
	// �Đ�
	// arg1... �t�@�C���p�X
	// arg2... �v���C���[�h
	// ret.... �T�E���hID
	// tips... ���t���[���Ăяo���Ȃ���
	// tips... �P���Đ��Ŏw�肵�ĕԂ����T�E���hID�͍Đ����I������� ID �������ɂȂ�܂��B
	static int Play( const std::string& file_name, int mode = MODE_ONCE ) ;

	//-----------------------------------------------------------
	// ��~������ BGM �Ȃǂ̃��v���C
	// arg1... �T�E���hID
	// ret.... none
	// tips... ���t���[���Ăяo���Ȃ���
	static void Play( const int sound_id ) ;

	//-----------------------------------------------------------
	// ��~
	// arg1... �T�E���hID
	// ret.... none
	// tips... none
	static void Stop( const int sound_id ) ;

	//-----------------------------------------------------------
	// �J��
	// arg1... �t�@�C���p�X
	// ret.... none
	// tips... none
	static void Delete( const std::string& file_name ) ;

	//-----------------------------------------------------------
	// �}�l�[�W���̏I������
	// arg1... none
	// ret.... none
	// tips... �Q�[���I�����ɌĂяo��
	static void Destroy() ;

} ;

#endif

