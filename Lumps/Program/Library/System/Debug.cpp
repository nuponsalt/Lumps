#include "DXUT.h"
//#include "Debug.h"
//
//#include "../Extension.h"
//
//namespace KMT {
//
//	//-----------------------------------
//	// �ÓI�ϐ��錾
//	CTextDebugSP CDebug::text ;
//	std::vector< std::string > CDebug::strings ;
//
//	void CDebug::Initialize()
//	{
//		// �t�H���g�̐���
//		text = CTextDebug::Create( 14, 20, L"�l�r �S�V�b�N" ) ;
//	}
//	
//	void CDebug::Destroy()
//	{
//		text.reset() ;
//	}
//
//	void CDebug::AddString( const std::string _string ) 
//	{
//		// �������ǉ�
//		strings.push_back( _string ) ;
//	}
//
//	void CDebug::RenderText()
//	{
//		text->setRect( 0, 0 ) ;
//		// �o�^����Ă��镶�����S�ĕ`��
//		for( size_t i = 0 ; i < strings.size() ; ++i )
//		{
//			// WCHAR�ɕϊ����Ă���`��
//			WCHAR buff_str[256] = {0} ;
//			DXconvAnsiToWide( buff_str, strings[i].c_str(), ( strings[i].length()+1) ) ;
//			text->drawText( buff_str ) ;
//
//			text->setRect( 0, ( i + 1 ) * 20 ) ;
//
//		}
//	}
//
//	void CDebug::setTextColor( int _col )
//	{
//		// �J���[���Z�b�g
//		text->setColor( _col ) ;
//	}
//
//}