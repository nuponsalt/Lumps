#pragma once

// ��Ԃ��Ǘ�����
class CState
{
private :

	// �l ( �r�b�g�t���O )
	int Value ;

public :

	// ��Ԃ̎��
	enum 
	{
		GROUNDING	= 0x01		// �ڒn���Ă邩�ۂ�
	} ;

	// �R���X�g���N�^
	CState( int state = 0 ) : Value( state ) {}

	// �f�X�g���N�^
	~CState() {}

	// ��Ԃ�ǉ�
	void Add( int state ) { Value |= state ; }

	// �w�肵����Ԃ̃t���O�`�F�b�N
	bool Check( int state ) { return ( Value & state ) == state ; }

} ;