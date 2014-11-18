//
//  wsb_xml.h
//
//  Created by ��� �O on 12/02/05.
//  Copyright (c) 2011 t.tsuneki All rights reserved.
//


#ifndef __WSB_XML__
#define __WSB_XML__

#include <iostream>
#include <string>

#include <libxml/xmlversion.h>
#include <libxml/xmlreader.h>
#include <libxml/tree.h>
#include <memory>

using namespace std ;
class CWsbXml ;
typedef std::shared_ptr< CWsbXml > CWsbXmlSP ;
typedef std::weak_ptr< CWsbXml > CWsbXmlWP ;

//-------------------------------------------------------------------------
//
// XML �N���X
//
class CWsbXml {
	
private:

	// ���[�U�ɂ��R���X�g���N�^�Ăяo���֎~
	CWsbXml() {
	/*
		m_tag_child = NULL ;
		m_tag_next = NULL ;
		m_tag_parent = NULL ;
		m_attr = NULL ;
	*/
	}
	
	std::string		m_file_name ;	// �t�@�C����
	std::string		m_tag_name ;	// �^�O��
	std::string		m_string ;		// �v�f�̕�����
	int				m_s32 ;			// �v�f�̐���
	float			m_f32 ;			// �v�f�̏���
	
	CWsbXmlSP		m_tag_child ;
	CWsbXmlSP		m_tag_next ;
	CWsbXmlWP		m_this_week ;
	CWsbXmlWP		m_tag_parent ;
	CWsbXmlSP		m_attr ;
	
	static int ParseProcess( xmlTextReaderPtr _reader, CWsbXmlSP _parent, int _prevtype ) ;
	
public:
	
	//=====================================================
	// �v�f���̎擾
	//=====================================================
    inline std::string GetFileName(){ return GetElementTop()->m_file_name ; }
	inline std::string GetTagName(){ return m_tag_name ; }
	inline std::string GetString(){ return m_string ; }
	inline int GetInt(){ return m_s32 ; }
	inline float GetFloat(){ return m_f32 ; }
	inline CWsbXmlSP GetParentElement(){ return CWsbXmlSP( m_tag_parent ) ; }
	
	//=====================================================
	// �v�f�̎擾
	//=====================================================
	int	GetElementNum( std::string _tag_name = "all_element" ) ;
	CWsbXmlSP GetElement( std::string _tag_name, int _idx = 0 ) ;
	CWsbXmlSP GetElement( int _idx ) ;
	CWsbXmlSP GetElementTop() ;
	
	//=====================================================
	// �����̎擾
	//=====================================================
	int GetAttrNum( std::string _attr_name = "all_attribute" ) ;
	CWsbXmlSP GetAttr( std::string _attr_name, int _idx = 0 ) ;
	CWsbXmlSP GetAttr( int _idx ) ;

	//=====================================================
	// �e�L�X�g�x�[�X�� XML���擾
	// arg1... �o�͌���
	// arg2... �w�肵�Ȃ���OK
	//=====================================================
	void GetXmlString( std::string *_string, bool start = true ) ;
	
	//=====================================================
	// �v�f�̐ݒ�
	//=====================================================
	void Set( int _v ) ;
	void Set( float _v ) ;
	void Set( std::string _string ) ;
	
	//=====================================================
	// �q���̒ǉ�
	// arg1... �^�O��
	// arg2... string, s32, f32 �̂ǂꂩ
	//=====================================================
	template<class T> void AddChild( string _string, const T& _v )
	{
		CWsbXmlSP sarch = CWsbXmlSP( this->m_this_week ) ;
		
		if( sarch->m_tag_child == NULL ){
			sarch->m_tag_child = CWsbXmlSP( new CWsbXml ) ;
			sarch = sarch->m_tag_child ;
		}else{
			sarch = sarch->m_tag_child ;
			while( sarch->m_tag_next != NULL ){
				sarch = sarch->m_tag_next ;
			}
			sarch->m_tag_next = CWsbXmlSP( new CWsbXml ) ;
			sarch = sarch->m_tag_next ;
		}
		
		sarch->m_tag_parent = this->m_this_week ;
		sarch->m_this_week = CWsbXmlWP( sarch ) ;
		sarch->Set( _v ) ;
		sarch->m_tag_name = _string ;
	}
	
	//=====================================================
	// �Z��̒ǉ�
	// arg1... �^�O��
	// arg2... string, s32, f32 �̂ǂꂩ
	//=====================================================
	template<class T> bool AddNext( string _string, const T& _v )
	{
		if( this->m_string == "wsb_root_xml" ) return false ;
		
		CWsbXmlSP sarch = CWsbXmlSP( this->m_this_week ) ;
		while( sarch->m_tag_next != NULL ){
			sarch = sarch->m_tag_next ;
		}
		sarch->m_tag_next = CWsbXmlSP( new CWsbXml ) ;
		sarch->m_tag_parent = this->m_tag_parent ;
		sarch = sarch->m_tag_next ;
		sarch->m_this_week = CWsbXmlWP( sarch ) ;
		sarch->Set( _v ) ;
		sarch->m_tag_name = _string ;
		return true ;
	}
	
	
public:
	
	static CWsbXmlSP CreateXml( std::string _root_name ) ;
	static CWsbXmlSP LoadXmlFile( std::string _filename ) ;
	static CWsbXmlSP LoadXmlString( std::string _xmlstring ) ;
	void SaveXmlFile( std::string _filename ) ;

	//=====================================================
	// ���g�̃R�s�[
	//=====================================================
	CWsbXml GetInstance() { return (*this) ; }	
	
	//=====================================================
	// �v�f�̎擾
	//=====================================================
	CWsbXml operator[]( std::string index ) {
		CWsbXmlSP wkxml = this->GetElement( index ) ;
		return (*wkxml.get()) ;
	}
	
	CWsbXml operator[]( int index ) {
		CWsbXmlSP wkparent = this->GetParentElement() ;
		CWsbXmlSP wkxml = wkparent->GetElement( this->m_tag_name, index ) ;
		return (*wkxml.get()) ;
	}
	
	//=====================================================
	// �����̎擾
	//=====================================================
	CWsbXml operator()( std::string index ) {
		CWsbXmlSP wkxml = this->GetAttr( index ) ;
		return (*wkxml.get()) ;
	}
	
	//=====================================================
	// ������f�[�^�̎擾
	//=====================================================
	std::string operator()() {
		return this->GetString() ;
	}
	
} ;

#endif
