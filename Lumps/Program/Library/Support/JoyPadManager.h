#ifndef JOY_PAD_MANAGER
#define JOY_PAD_MANAGER

/*
	
	[ ���� ]
	dinput8.lib �������N����
	OnD3D9CreateDevice	�� Initialzie �֐����Ă�
	OnFrameMove			�� UpData �֐����Ă�
	OnD3D9DestroyDevice �� Desytroy �֐����Ă�
	
	[ �g���� ]
	�D���ȂƂ���ňȉ��̊֐����Ă�

	���ꂼ������� �p�b�h�ԍ��ƃL�[�ԍ����w��

	���͂����ςȂ�
	static bool IsKeyKeep( const int _pad, int _key ) ;

	�g���K
	static bool IsKeyTrigger( const int _pad, int _key ) ;

	�����[�X
	static bool IsKeyReleased( const int _pad, int _key ) ;

	�X�e�B�b�N�̌X��( x, y �����g��Ȃ� )
	static D3DXVECTOR3& GetStickLeft( const int _pad ) ;
	static D3DXVECTOR3& GetStickRight( const int _pad ) ;

*/


#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <vector>
#define KEY_MAX (256)

class CPadData{
private :
	int xor[ KEY_MAX ] ;
	int xor2[ KEY_MAX ] ;
	int trg[ KEY_MAX ] ;
	int released[ KEY_MAX ] ;
	bool keep[ KEY_MAX ] ;
	D3DXVECTOR3 stick_l ;
	D3DXVECTOR3 stick_r ;
	void SetOn( bool _f, int _num ) ;
	friend class CJoyPadManager ;
} ;

class CJoyPadManager{
public :
	static LPDIRECTINPUT8       m_lpDI;
	static DIDEVCAPS            m_diDevCaps;
	static std::vector< LPDIRECTINPUTDEVICE8 > m_lpDIDevices ;
	static int joystick_count ;

private :
	static std::vector< CPadData* > m_pads ;
public :

	const static int PAD_BTN_1 = 0 ;
	const static int PAD_BTN_2 = 1 ;
	const static int PAD_BTN_3 = 2 ;
	const static int PAD_BTN_4 = 3 ;
	const static int PAD_BTN_5 = 4 ;
	const static int PAD_BTN_6 = 5 ;
	const static int PAD_BTN_7 = 6 ;
	const static int PAD_BTN_8 = 7 ;
	const static int PAD_BTN_9 = 8 ;
	const static int PAD_BTN_10 = 9 ;
	const static int PAD_BTN_11 = 10 ;
	const static int PAD_BTN_12 = 11 ;
	const static int STICK_UP			= 128+1 ;
	const static int STICK_DOWN			= 128+2 ;
	const static int STICK_LEFT			= 128+3 ;
	const static int STICK_RIGHT		= 128+4 ;

	const static int CROSS_UP			= 128+5 ;
	const static int CROSS_UP_RIGHT		= 128+6 ;
	const static int CROSS_RIGHT		= 128+7 ;
	const static int CROSS_RIGHT_DOWN	= 128+8 ;
	const static int CROSS_DOWN			= 128+9 ;
	const static int CROSS_DOWN_LEFT	= 128+10 ;
	const static int CROSS_LEFT			= 128+11 ;
	const static int CROSS_LEFT_UP		= 128+12 ;

	static void Initialize() ;
	static void UpData() ;
	static void Destroy() ;

	static bool IsKeyKeep( const int _pad, const int _key ) ;
	static bool IsKeyTrigger( const int _pad, const int _key ) ;
	static bool IsKeyReleased( const int _pad, const int _key ) ;
	static D3DXVECTOR3& GetStickLeft( const int _pad ) ;
	static D3DXVECTOR3& GetStickRight( const int _pad ) ;
	
} ;

#endif