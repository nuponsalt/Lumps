#include "DXUT.h"
#include "wsb_xml.h"
#include <stdlib.h>
#include <fstream>

#define WSB_XML_FAIL				(-1)
#define WSB_XML_FALSE				(0)
#define WSB_XML_TRUE				(1)
#define XML_READER_TYPE_ROOT		(99)
#define WSB_XML_PRINT_DEBUG			(0)

using namespace std ;

#pragma warning( push )
#pragma warning( disable: 4127 )



void Print( const xmlChar *str ) {
//	std::cout << (const char*)str << std::endl ;
}

void Print( std::string str ) {
//	std::cout << str << std::endl ;
}


//==================================================================
//	name....LoadXMLFile
//	work....�t�@�C������̓ǂݍ���
//	arg1....�t�@�C����
//	ret.....[ ���� : CWsbXml �ւ̃|�C���^ ]  [ ���s : NULL ]
//	tips....none
//==================================================================
CWsbXmlSP CWsbXml::LoadXmlFile( std::string _filename ) {

	// �t�@�C���p�X�̎擾
	xmlTextReaderPtr wkreader ;
	
	// XML ���[�_�[�̓ǂݍ���
	wkreader = xmlNewTextReaderFilename( _filename.c_str() ) ;
	
	CWsbXmlSP wkxml ;
	CWsbXmlSP wknullobj ;
	if ( NULL == wkreader ) {
		xmlFreeTextReader( wkreader ) ;
		return wknullobj ;
	}
	
	// �p�[�X�J�n
	int wkresult = xmlTextReaderRead( wkreader ) ;
	if ( WSB_XML_TRUE == wkresult ) {
		wkxml = CWsbXmlSP( new CWsbXml ) ;
		wkxml->m_this_week = CWsbXmlWP( wkxml ) ;
		wkresult = CWsbXml::ParseProcess( wkreader, wkxml, XML_READER_TYPE_ROOT ) ;
	}
	xmlFreeTextReader( wkreader ) ;
	
	// ��͎��s
	if ( wkresult == WSB_XML_FAIL ){
		return wknullobj ;
	}
	
    wkxml->m_file_name = _filename ;
	return wkxml ;
}


//==================================================================
//	name....LoadXmlString
//	work....������f�[�^����XML ���쐬
//	arg1....������f�[�^
//	ret.....[ ���� : CWsbXml �ւ̃|�C���^ ]  [ ���s : NULL ]
//	tips....none
//==================================================================
CWsbXmlSP CWsbXml::LoadXmlString( std::string _xmlstring ) {
	
    xmlParserInputBufferPtr wkinputbuf = xmlAllocParserInputBuffer(XML_CHAR_ENCODING_UTF8);
     
	CWsbXmlSP wkxml ;
	CWsbXmlSP wknullobj ;
    
	if( !wkinputbuf ) return wknullobj ;
	
	xmlBufferPtr wkxmlbuf = xmlBufferCreateStatic( (void*)_xmlstring.c_str(), _xmlstring.length() ) ;
	wkinputbuf->buffer = wkxmlbuf ;
	
	xmlTextReaderPtr wkreader = xmlNewTextReader( wkinputbuf, NULL ) ;
	if ( NULL == wkreader ) {
		xmlFreeTextReader( wkreader ) ;
		return wknullobj ;
	}

	/*
	 *	��͏���
	 */
	int wkresult = xmlTextReaderRead( wkreader ) ;
	if ( WSB_XML_TRUE == wkresult ) {
		wkxml = CWsbXmlSP( new CWsbXml ) ;
		wkxml->m_this_week = CWsbXmlWP( wkxml ) ;
		wkresult = CWsbXml::ParseProcess( wkreader, wkxml, XML_READER_TYPE_ROOT ) ;
	}
	xmlFreeTextReader( wkreader ) ;
	
	// ��͎��s
	if ( wkresult == WSB_XML_FAIL ){
		return wknullobj ;
	}
	
	return wkxml ;
}

//=======================================================================================
//	name... ParseProcess
//	work... �p�[�X����
//	arg1... xmlTextReaderPtr
//	ret.... [ ���s -1 ]	[ �Ȃ� 0 ] [ ���� 1 ] 
//	tips	:	none
//=======================================================================================
int wknowtype, wknexttype ;
const xmlChar *wkname, *wkvalue ;
CWsbXmlSP wkxml ;
CWsbXmlSP wk_add ;
CWsbXmlSP wk_attr_xml ;
int CWsbXml::ParseProcess( xmlTextReaderPtr _reader, CWsbXmlSP _prevxml, int _prevtype ) {
	
	
	// xmlTextReaderPtr �����݂��Ȃ�
	if ( _reader == NULL ) {
		#if WSB_XML_PRINT_DEBUG
		Print( "err : _reader is NULL" ) ;
		#endif
		return WSB_XML_FAIL ;
	}
	
	// �v�f�^�C�v�̎擾
	if ( ( wknowtype = xmlTextReaderNodeType( _reader ) ) == WSB_XML_FAIL ) {
		#if WSB_XML_PRINT_DEBUG
		Print( "err : �v�f�^�C�v is -1" ) ;
		#endif
		return WSB_XML_FAIL ;
	}
	
	/*
	 *
	 *	�v�f�^�C�v�ɂ���ċ������ω�
	 *
	 */
	switch ( wknowtype ) {
			
		/*
		 *	�J�n�v�f
		 */
		case XML_READER_TYPE_ELEMENT :
			{
				// �v�f���̎擾
				if ( ( wkname = xmlTextReaderConstName( _reader ) ) == NULL ) {
					#if WSB_XML_PRINT_DEBUG
					Print( "err : �v�f�������݂��Ȃ�" ) ;
					#endif
					return WSB_XML_FAIL ;
				}
				#if WSB_XML_PRINT_DEBUG
				Print( wkname ) ;
				#endif
				
				/*
				 *	�v�f���󂩂ǂ����𔻒�
				 *	�������擾�����ゾ�Ƃ����ƂƂ�Ȃ������̂ł��̎��_��
				 *	��v�f���ǂ����̔�������
				 */
				int wkisempty = xmlTextReaderIsEmptyElement( _reader ) ;

				/*
				 *	�O��̃^�C�v�ɂ���ċ������ω�
				 */
				switch ( _prevtype ) {
						
					/*
					 *	�O�񂪃^�O�̊J�n�ł���΁Achild �𐶐�
					 *	_prevxml �� parent
					 */
					case XML_READER_TYPE_ELEMENT :
						{
							wkxml = CWsbXmlSP( new CWsbXml ) ;
							wkxml->m_this_week = CWsbXmlWP( wkxml ) ;
//							wkxml->m_tag_name = toString( wkname ) ;
							wkxml->m_tag_name = string( (const char*)wkname );

							wkxml->m_tag_parent = CWsbXmlWP( _prevxml ) ;
							_prevxml->m_tag_child = wkxml ;
						}
						break ;
						
					/*
					 *	�O�񂪃^�O�̏I���ł���΁Anext �𐶐�
					 *	_prevxml �� brother
					 */
					case XML_READER_TYPE_END_ELEMENT :
						{
							// next �̍Ō�������o
							while ( true ) {
								if ( _prevxml->m_tag_next == NULL ) break ;
								_prevxml = _prevxml->m_tag_next ;
							}
							
							// next �𐶐�
							wkxml = CWsbXmlSP( new CWsbXml ) ;
							wkxml->m_this_week = CWsbXmlWP( wkxml ) ;
//							wkxml->m_tag_name = toString( wkname ) ;
							wkxml->m_tag_name = string( (const char*)wkname ) ;
							wkxml->m_tag_parent = CWsbXmlWP( _prevxml->m_tag_parent ) ;
							_prevxml->m_tag_next = wkxml ;
						}
						break ;
						
					/*
					 *	�n�߂̈�񂾂�������ʂ郋�[�g
					 *	���[�g�f�[�^�̐ݒ�
					 *	_prevxml �� root
					 */
					case XML_READER_TYPE_ROOT :
						{
							wkxml = _prevxml ;
//							wkxml->m_tag_name = toString( wkname ) ;
							wkxml->m_tag_name = string( (const char*)wkname ) ;
							wkxml->m_string = "wsb_root_xml" ;
							wkxml->m_tag_parent = CWsbXmlWP( wkxml ) ;
							
							#if WSB_XML_PRINT_DEBUG
							Print( "root �ł���" ) ;
							Print( wkxml->m_string ) ;
							#endif
						}
						break ;
						
					default :
							return WSB_XML_FAIL ;
						break ;
				}
				
				
				// �����̎擾
				int wkresult = xmlTextReaderMoveToNextAttribute( _reader ) ;
				
				if ( wkresult == WSB_XML_TRUE ) {
					
					
					wk_attr_xml = wkxml ;

					// ���������݂����ꍇ�͑������ׂĎ��o��
					while ( true ) {
						
						// �������̎擾
						if ( ( wkname = xmlTextReaderConstName( _reader ) ) == NULL ) {
							#if WSB_XML_PRINT_DEBUG
							Print( "err : ���O�̎擾�Ɏ��s" ) ;
							#endif
							return WSB_XML_FAIL ;
						}
						Print( wkname ) ;
						
						// �����f�[�^�̎擾
						if ( ( wkvalue = xmlTextReaderConstValue( _reader ) ) == NULL ) {
							#if WSB_XML_PRINT_DEBUG
							Print( "err : �l�̎擾�Ɏ��s" ) ;
							#endif
							return WSB_XML_FAIL ;
						}
						
						#if WSB_XML_PRINT_DEBUG
						Print( wkvalue ) ;
						#endif
						
						// �����̐���
						wk_add = CWsbXmlSP( new CWsbXml ) ;
						wk_add->m_this_week = CWsbXmlWP( wk_add ) ;
//						wk_add->m_tag_name	= toString( wkname ) ;
//						wk_add->m_string	= toString( wkvalue ) ;
						wk_add->m_tag_name = string( (const char*)wkname ) ;
						wk_add->m_string = string( (const char*)wkvalue ) ;

						wk_add->m_s32		= strtol( (const char*)wkvalue, NULL, 10 ) ;
						wk_add->m_f32		= (float)strtod( (const char*)wkvalue, NULL ) ;
						
						wk_attr_xml->m_attr = wk_add ;
						wk_attr_xml = wk_attr_xml->m_attr ;
						
						// ���̑����̎擾
						wkresult = xmlTextReaderMoveToNextAttribute( _reader ) ;
						if ( wkresult == WSB_XML_TRUE ) {
						}
						else if ( wkresult == WSB_XML_FALSE ) {
							break ;
						}
						else if ( wkresult == WSB_XML_FAIL ) {
							#if WSB_XML_PRINT_DEBUG
							Print( "err : �����̎擾�Ɏ��s (1)" ) ;
							#endif
							return WSB_XML_FAIL ;
						}
					}
					
					/*
					 *	��v�f���ǂ����ł̋����̕ω��͂����ōs��
					 */
					if ( wkisempty == WSB_XML_TRUE ) {
						// �����L��̋�v�f
						wknexttype	= XML_READER_TYPE_END_ELEMENT ; 
					}
					else if ( wkisempty == WSB_XML_FALSE ) {
						// �����L��̒ʏ�v�f
						wknexttype	= wknowtype ;
					}
					else if ( wkisempty == WSB_XML_FAIL ) {
						#if WSB_XML_PRINT_DEBUG
						Print( "err : �v�f���󂩂ǂ����̎擾�Ɏ��s" ) ;
						#endif
						return WSB_XML_FAIL ;
					}
					
				}
				else if ( wkresult == WSB_XML_FALSE ) {
					// ���������ʏ�v�f
					wknexttype = wknowtype ;
				}
				else if ( wkresult == WSB_XML_FAIL ) {
					#if WSB_XML_PRINT_DEBUG
					Print( "err : �����̎擾�Ɏ��s" ) ;
					#endif
					return WSB_XML_FAIL ;
				}
			}
			break ;
			
		/*
		 *	����
		 *
		 *	�����ɂ͓����Ă��Ă���̂��ǂ����킩��Ȃ�
		 */
		case XML_READER_TYPE_ATTRIBUTE :
			{
				// �������̎擾
				if ( ( wkname = xmlTextReaderConstName( _reader ) ) == NULL ) {
					#if WSB_XML_PRINT_DEBUG
					Print( "err : ���O�̎擾�Ɏ��s (1)" ) ;
					#endif
					return WSB_XML_FAIL ;
				}
				#if WSB_XML_PRINT_DEBUG
				Print( wkname ) ;
				#endif
				
				// �����f�[�^�̎擾
				if ( ( wkvalue = xmlTextReaderConstValue( _reader ) ) == NULL ) {
					#if WSB_XML_PRINT_DEBUG
					Print( "err : �l�̎擾�Ɏ��s (1)" ) ;
					#endif
					return WSB_XML_FAIL ;
				}
				#if WSB_XML_PRINT_DEBUG
				Print( wkvalue ) ;
				Print( "�����ł���" ) ;
				#endif
				wkxml		= _prevxml ;
				wknexttype	= _prevtype ;
			}
			break ;
			
		/*
		 *	�X�y�[�X
		 *	�󔒃f�[�^�̏ꍇ�͑O��̃f�[�^�����̂܂ܓn��
		 */
		case XML_READER_TYPE_WHITESPACE :
		case XML_READER_TYPE_SIGNIFICANT_WHITESPACE :
			{
				// �l�̎擾
				if ( ( wkvalue = xmlTextReaderConstValue( _reader ) ) == NULL ) {
					#if WSB_XML_PRINT_DEBUG
					Print( "err : �l�̎擾�Ɏ��s (2)" ) ;
					#endif
					return WSB_XML_FAIL ;
				}
				
				#if WSB_XML_PRINT_DEBUG
				Print( "�X�y�[�X" ) ;
				Print( wkvalue ) ;
				#endif
				
				wkxml		= _prevxml ;
				wknexttype	= _prevtype ;
			}
			break ;
			
		/*
		 *	������f�[�^
		 *	_prevxml ��������f�[�^��}������ xml �ɂȂ�
		 */
		case XML_READER_TYPE_TEXT :
			{
				// �l�̎擾
				if ( (wkvalue = xmlTextReaderConstValue( _reader ) ) == NULL ) {
					#if WSB_XML_PRINT_DEBUG
					Print( "err : �l�̎擾�Ɏ��s (3)" ) ;
					#endif
					return WSB_XML_FAIL ;
				}
				
				#if WSB_XML_PRINT_DEBUG
				Print( "������f�[�^�̎擾" ) ;
				Print( wkvalue ) ;
				#endif
				
				wkxml			= _prevxml ;
//				wkxml->m_string	= toString( wkvalue ) ;
				wkxml->m_string = string( (const char*)wkvalue ) ;

				wkxml->m_s32	= strtol( (const char*)wkvalue, NULL, 10 ) ;
				wkxml->m_f32	= (float)strtod( (const char*)wkvalue, NULL ) ;
				
				wknexttype	= wknowtype ;
			}	
			break ;
			
		/*
		 *	�I���v�f
		 *	�O����v�f�̏I���ł������ꍇ�� parent ��Ԃ�
		 */
		case XML_READER_TYPE_END_ELEMENT :
			{
				if ( _prevtype == XML_READER_TYPE_END_ELEMENT )
					wkxml = CWsbXmlSP( _prevxml->m_tag_parent ) ;
				else
					wkxml = _prevxml ;
				
				wknexttype = wknowtype ;
			}
			break ;
			
		/*
		 *	�h�L�������g
		 */
		case XML_READER_TYPE_DOCUMENT :
			{
				#if WSB_XML_PRINT_DEBUG
				Print( "�h�L�������g" ) ;
				#endif
			}
			break ;
			
		/*
		 *	���̑��̃^�C�v�̏ꍇ�͑O��̃f�[�^�����̂܂܈����p��
		 */
		default :
			{
				wkxml		= _prevxml ;
				wknexttype	= _prevtype ;
			}
			break ;
	}
	
	// �����f�[�^�̏ꍇ�̏���
	if ( wknowtype == XML_READER_TYPE_ATTRIBUTE )
		return xmlTextReaderMoveToNextAttribute( _reader ) ;
	
	// ���̃f�[�^��ǂݍ���
	int wkcompflag = xmlTextReaderRead( _reader ) ;
	if ( wkcompflag == WSB_XML_TRUE )
		return CWsbXml::ParseProcess( _reader, wkxml, wknexttype ) ;
	else if ( wkcompflag == WSB_XML_FAIL )
		return WSB_XML_FAIL ;
	
	return WSB_XML_FALSE ;

}

//=========================================================
// name... CreateXml
// work... XML ���쐬
// arg1... �^�O��
// ret.... XML �ւ̃X�}�[�g�|�C���^
// tips... none
//=========================================================
CWsbXmlSP CWsbXml::CreateXml( std::string _root_name )
{
	CWsbXmlSP wkxml ;
	wkxml = CWsbXmlSP( new CWsbXml ) ;
	wkxml->m_this_week = CWsbXmlWP( wkxml ) ;
	wkxml->m_tag_name = _root_name ;
	wkxml->m_string = "wsb_root_xml" ;
	return wkxml ;
}

//=========================================================
// work... XML���Z�[�u
// arg1... �Z�[�u�t�@�C����
//=========================================================
void CWsbXml::SaveXmlFile( std::string _filename )
{
	std::string xml_str ;
	GetXmlString( &xml_str ) ;
	std::ofstream ofs( _filename ) ;
	ofs << xml_str << std::endl ;
}

//=====================================================
// �e�L�X�g�x�[�X�� XML���擾
// arg1... �o�͌���
// arg2... �w�肵�Ȃ���OK
//=====================================================
void CWsbXml::GetXmlString( string *_string, bool start )
{
	
	if( start ){
		*_string = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" ;
		*_string += "\n" ;
	}
	
	string esc = "\n" ;
	CWsbXmlSP sarch ;
	
	*_string += "<" + this->m_tag_name + ">" ;
	if( this->m_tag_child != NULL ){
		*_string += esc ;
		sarch = this->m_tag_child ;
		sarch->GetXmlString( _string, false ) ;
		
		// �q���ɌZ�킪����ꍇ�͐e����������
		// �Z��ɌZ������������Ă͂���
		if( this->m_tag_child->m_tag_next != NULL ){
			sarch = this->m_tag_child ;
			while( sarch->m_tag_next != NULL ){
				sarch = sarch->m_tag_next ;
				sarch->GetXmlString( _string, false ) ;
			}
		}
		
	}else{
		*_string += this->m_string ;
	}
	*_string += "</" + this->m_tag_name + ">" + esc ;

	return ;
}


//=========================================================
//=========================================================
void CWsbXml::Set( int _v )
{
	char str[64] ;
	memset( str, 0, sizeof(str) ) ;
	sprintf_s( str, "%d", _v ) ;
	this->m_string = str ;
	this->m_s32	= _v ;
	this->m_f32	= (float)_v ;
}

//=========================================================
//=========================================================
void CWsbXml::Set( float _v )
{

	char str[64] ;
	memset( str, 0, sizeof(str) ) ;
	sprintf_s( str, "%f", _v ) ;
	this->m_string = str ;
	this->m_s32	= (int)_v ;
	this->m_f32	= _v ;
}

//=========================================================
//=========================================================
void CWsbXml::Set( std::string _string )
{
	this->m_string = _string ;
	this->m_s32		= strtol( (const char*)_string.c_str(), NULL, 10 ) ;
	this->m_f32	= (float)strtod( (const char*)_string.c_str(), NULL ) ;
}

//=========================================================
// name... GetElementNum
// work.... �G�������g�̐����擾����
// arg1.... �G�������g�� ( �w��Ȃ��̏ꍇ�͑S�Ă̎q���̃G�������g )
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
int	CWsbXml::GetElementNum( std::string _tag_name )
{
	int element_count = 0 ;
	bool all_ok = false ;
	CWsbXmlSP sarch = this->m_tag_child ;
	
	if( _tag_name == "all_element" ){
		all_ok = true ;
	}
	
	while( sarch != NULL ){
		if( all_ok ){
			element_count++ ;
		}else if( sarch->m_tag_name == _tag_name ){
			element_count++ ;
		}
		sarch = sarch->m_tag_next ;
	}
	
	return element_count ;
	
}

//=========================================================
// name... GetElement
// work.... �G�������g���擾����
// arg1.... �G�������g��
// arg2.... ���Ԗڂ��擾���邩
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
CWsbXmlSP CWsbXml::GetElement( std::string _tag_name, int _idx )
{
	int element_count = 0 ;
	CWsbXmlSP null_obj ;
	CWsbXmlSP sarch = this->m_tag_child ;
	
	while( sarch != NULL ){
		if( sarch->m_tag_name == _tag_name ){
			if( element_count == _idx ) return sarch ;
			element_count++ ;
		}
		sarch = sarch->m_tag_next ;
	}
	
	return null_obj ;
}


//=========================================================
// name... GetElement
// work.... �G�������g���擾����
// arg1.... ���Ԗڂ��擾���邩
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
CWsbXmlSP CWsbXml::GetElement( int _idx )
{
	CWsbXmlSP null_obj ;
	CWsbXmlSP sarch = this->m_tag_child ;
	
	for( int i = 0 ; i < _idx ; i++ ){
		if( sarch == NULL ) return null_obj ;
		sarch = sarch->m_tag_next ;
	}
	return sarch ;
	
}


//=========================================================
// name... GetElementTop
// work.... �ŏ�ʂ̃G�������g���擾����
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
CWsbXmlSP CWsbXml::GetElementTop()
{
	CWsbXmlSP parent = GetParentElement() ;
	while( 1 ){
		if( parent->GetString() == "wsb_root_xml" ) return parent ;
		parent = parent->GetParentElement() ;
	}
	return parent ;
}


//=========================================================
// name... GetAttrNum
// work.... �����̐����擾����
// arg1.... ������ ( �w��Ȃ��̏ꍇ�͑S�Ă̑���)
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
int	CWsbXml::GetAttrNum( std::string _tag_name )
{
	int attr_count = 0 ;
	bool all_ok = false ;
	CWsbXmlSP sarch = this->m_attr ;
	
	if( _tag_name == "all_attribute" ){
		all_ok = true ;
	}
	
	while( sarch != NULL ){
		if( all_ok ){
			attr_count++ ;
		}else if( sarch->m_tag_name == _tag_name ){
			attr_count++ ;
		}
		sarch = sarch->m_attr ;
	}
	
	return attr_count ;
	
}


//=========================================================
// name... GetAttr
// work.... �������擾����
// arg1.... ������
// arg2.... ���Ԗڂ��擾���邩
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
CWsbXmlSP CWsbXml::GetAttr( std::string _tag_name, int _idx )
{
	int attr_count = 0 ;
	CWsbXmlSP null_obj ;
	CWsbXmlSP sarch = this->m_attr ;
	
	while( sarch != NULL ){
		if( sarch->m_tag_name == _tag_name ){
			if( attr_count == _idx ){
				return sarch ;
			}
			attr_count++ ;
		}
		sarch = sarch->m_attr ;
	}
	
	return null_obj ;
}

//=========================================================
// name... GetAttr
// work.... �������擾����
// arg1.... ���Ԗڂ��擾���邩
// ret....... [ ���� : XML �ւ̃X�}�[�g�|�C���^ ] [ ���s : NULL �I�u�W�F�N�g ]
// tips...... none
//=========================================================
CWsbXmlSP CWsbXml::GetAttr( int _idx )
{
	CWsbXmlSP null_obj ;
	CWsbXmlSP sarch = this->m_attr ;
	
	for( int i = 0 ; i < _idx ; i++ ){
		if( sarch == NULL ) return null_obj ;
		sarch = sarch->m_attr ;
	}
	return sarch ;
	
}






#pragma warning( pop )









