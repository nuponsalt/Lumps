#include "DXUT.h"
#include "JoyPadManager.h"


int CJoyPadManager::joystick_count = 0 ;
LPDIRECTINPUT8       CJoyPadManager::m_lpDI ;
DIDEVCAPS            CJoyPadManager::m_diDevCaps ;
std::vector< LPDIRECTINPUTDEVICE8 > CJoyPadManager::m_lpDIDevices ;
std::vector< CPadData* > CJoyPadManager::m_pads ;


void CPadData::SetOn( bool _f, int _num ){
	if( _f ){
		trg[ _num ] = ( xor[ _num ]^0x01 ) ;
		xor[ _num ] = 0x01 ;
		keep[ _num ] = true ;
	}else{
		xor[ _num ] = 0 ;
	}
	if( _f ){
		xor2[ _num ] = 0 ;
	}else{
		released[ _num ] = ( xor2[ _num ]^0x01 ) ;
		xor2[ _num ] = 0x01 ;
	}
}


BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE *pdidInstance , VOID *pContext )
{
	HRESULT hr;
	LPDIRECTINPUTDEVICE8 dev ;

	hr = CJoyPadManager::m_lpDI->CreateDevice( pdidInstance->guidInstance , &dev, NULL );
	CJoyPadManager::m_lpDIDevices.push_back( dev ) ;
	CJoyPadManager::joystick_count++ ;

	if ( FAILED( hr ) ){
		return DIENUM_CONTINUE;
	}
	return DIENUM_CONTINUE;
}

BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *pdidoi , VOID *pContext )
{
	HRESULT     hr;
	DIPROPRANGE diprg;
	
	diprg.diph.dwSize       = sizeof( DIPROPRANGE );
	diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.diph.dwObj        = pdidoi->dwType;
	diprg.lMin              = 0 - 1000;
	diprg.lMax              = 0 + 1000;

	for( int i = 0 ; i < CJoyPadManager::joystick_count ; i++ ){
		hr = CJoyPadManager::m_lpDIDevices[i]->SetProperty( DIPROP_RANGE , &diprg.diph );
		if ( FAILED( hr ) ) return DIENUM_STOP;
	}
	
	return DIENUM_CONTINUE;
}

void CJoyPadManager::Initialize()
{

	DirectInput8Create( (HINSTANCE)GetModuleHandle(0), DIRECTINPUT_VERSION , IID_IDirectInput8, (void**)&m_lpDI , NULL );
	m_lpDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY );

	for( int i= 0 ; i < joystick_count ; i++ ){
		CJoyPadManager::m_lpDIDevices[i]->SetDataFormat( &c_dfDIJoystick2 );
		CJoyPadManager::m_lpDIDevices[i]->SetCooperativeLevel( DXUTGetHWND() , DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		CJoyPadManager::m_lpDIDevices[i]->GetCapabilities( &CJoyPadManager::m_diDevCaps );
		CJoyPadManager::m_lpDIDevices[i]->EnumObjects( EnumAxesCallback , (VOID*)DXUTGetHWND() , DIDFT_AXIS );

		CPadData* p_pad = new CPadData() ;
		m_pads.push_back( p_pad ) ;
	}

}

void CJoyPadManager::Destroy()
{
	for( int i = 0 ; i < (int)m_pads.size() ; i++ ){
		SAFE_DELETE( m_pads[i] ) ;
	}
	m_pads.clear() ;
}


void CJoyPadManager::UpData()
{

	for( int i = 0 ; i < (int)m_pads.size() ; i++ ){
		memset( &m_pads[i]->trg, 0, sizeof( int ) * KEY_MAX ) ;	
		memset( &m_pads[i]->keep, 0, sizeof( bool ) * KEY_MAX ) ;	
		memset( &m_pads[i]->released, 0, sizeof( int ) * KEY_MAX ) ;	
		m_pads[i]->stick_l = D3DXVECTOR3(0,0,0) ;
		m_pads[i]->stick_r = D3DXVECTOR3(0,0,0) ;
	}

	for( int n = 0 ; n < CJoyPadManager::joystick_count ; n++ ){
		HRESULT    hr;
		DIJOYSTATE2 js;
		memset( &js, 0, sizeof(DIJOYSTATE) ) ;
		hr = CJoyPadManager::m_lpDIDevices[ n ]->Poll();
		if ( FAILED( hr ) ){
			hr = CJoyPadManager::m_lpDIDevices[ n ]->Acquire();
			while( hr == DIERR_INPUTLOST ){
				hr = CJoyPadManager::m_lpDIDevices[ n ]->Acquire();
			}
		}
		m_lpDIDevices[ n ]->GetDeviceState( sizeof( DIJOYSTATE2 ) , &js );

		for( int i= 0 ; i < 128 ; i++ ){
			m_pads[ n ]->SetOn( (bool)(js.rgbButtons[ i ] & 0x80), i ) ;
		}
		m_pads[ n ]->SetOn( (js.lY == -1000), 128+1 ) ;
		m_pads[ n ]->SetOn( (js.lY ==  1000), 128+2 ) ;
		m_pads[ n ]->SetOn( (js.lX == -1000), 128+3 ) ;
		m_pads[ n ]->SetOn( (js.lX ==  1000), 128+4 ) ;

		m_pads[ n ]->SetOn( ( 0 == js.rgdwPOV[0] ), 128+5 ) ;
		m_pads[ n ]->SetOn( ( 4500 == js.rgdwPOV[0] ), 128+6 ) ;
		m_pads[ n ]->SetOn( ( 9000 == js.rgdwPOV[0] ), 128+7 ) ;
		m_pads[ n ]->SetOn( ( 13500 == js.rgdwPOV[0] ), 128+8 ) ;
		m_pads[ n ]->SetOn( ( 18000 == js.rgdwPOV[0] ), 128+9 ) ;
		m_pads[ n ]->SetOn( ( 22500 == js.rgdwPOV[0] ), 128+10 ) ;
		m_pads[ n ]->SetOn( ( 27000 == js.rgdwPOV[0] ), 128+11 ) ;
		m_pads[ n ]->SetOn( ( 31500 == js.rgdwPOV[0] ), 128+12 ) ;

		m_pads[ n ]->stick_l = D3DXVECTOR3( (js.lX * 0.001f), (js.lY * 0.001f), 0 ) ;
		m_pads[ n ]->stick_r = D3DXVECTOR3( (js.lZ * 0.001f), (js.lRz * 0.001f), 0 ) ;
	}


}

D3DXVECTOR3& CJoyPadManager::GetStickLeft( const int _pad )
{
	D3DXVECTOR3 ret ;
	if( m_pads.size() > _pad ){
		ret = m_pads[ _pad ]->stick_l ;
	}
	return ret ;
}


D3DXVECTOR3& CJoyPadManager::GetStickRight( const int _pad )
{
	D3DXVECTOR3 ret ;
	if( m_pads.size() > _pad ){
		ret = m_pads[ _pad ]->stick_r ;
	}
	return ret ;
}


bool CJoyPadManager::IsKeyKeep( const int _pad, const int _key )
{
	if( (int)m_pads.size() > _pad ){
		return m_pads[ _pad ]->keep[ _key ] ;
	}
	return false ;
}

bool CJoyPadManager::IsKeyTrigger( const int _pad, const int _key )
{
	if( (int)m_pads.size() > _pad ){
		if( 0 != m_pads[ _pad ]->trg[ _key ] ) return true ;
	}
	return false ;
}

bool CJoyPadManager::IsKeyReleased( const int _pad, const int _key )
{
	if( (int)m_pads.size() > _pad ){
		if( 0 != m_pads[ _pad ]->released[ _key ] ) return true ;
	}
	return false ;
}

