#ifndef JOY_PAD_MANAGER
#define JOY_PAD_MANAGER

/*
	
	[ 準備 ]
	dinput8.lib をリンクする
	OnD3D9CreateDevice	で Initialzie 関数を呼ぶ
	OnFrameMove			で UpData 関数を呼ぶ
	OnD3D9DestroyDevice で Desytroy 関数を呼ぶ
	
	[ 使い方 ]
	好きなところで以下の関数を呼ぶ

	それぞれ引数は パッド番号とキー番号を指定

	入力しっぱなし
	static bool IsKeyKeep( const int _pad, int _key ) ;

	トリガ
	static bool IsKeyTrigger( const int _pad, int _key ) ;

	リリース
	static bool IsKeyReleased( const int _pad, int _key ) ;

	スティックの傾き( x, y しか使わない )
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