#include "DXUT.h"
#include "Shader.h"
#include "../GraphicsManager.h"

#include "../../Support/wsb_xml.h"
#include "../../Extension.h"
#include "../../System/Debug.h"
#include "../Renderer/GraphicBehavior.h"

namespace KMT {

	// static Object
	std::hash_map<std::string, CShaderSP>	CShader::Shaders;
	
	//-----------------------------------------------------------------------------------------------------------
	// CShader
	//-----------------------------------------------------------------------------------------------------------

	CShader::CShader() : Ambient(0), Specular(0), SpecularPower(0), Type(0) { }

	CShader::CShader(std::string _xmlpath)
	{	
		CWsbXmlSP xml = CWsbXml::LoadXmlFile(_xmlpath);
		std::string sdr_path = xml->GetElement( "path" )->GetString();

		FilePath = sdr_path;

		WCHAR buff_name[256] = {0};
		DXconvAnsiToWide( buff_name, sdr_path.c_str(), (sdr_path.length()+1) );
		
		// �V�F�[�_ �t�@�C���̃��[�h
		LPD3DXBUFFER pCompilationErrors = NULL;

		HRESULT hr = D3DXCreateEffectFromFile( 
					CGraphicsManager::pd3dDevice, 
					buff_name, 
					NULL, 
					NULL, 
					D3DXSHADER_DEBUG, 
					NULL, 
					&pd3dEffect, 
					&pCompilationErrors
					);

		// ���[�h�Ɏ��s�����ꍇ
		if(FAILED(hr))
		{
			if(pCompilationErrors)	
				DXUTOutputDebugStringA((LPCSTR)pCompilationErrors->GetBufferPointer());
			
			SAFE_RELEASE(pCompilationErrors);
			return;
		}
		// �n���h���̓ǂݍ���
		pTechnique = pd3dEffect->GetTechniqueByName(xml->GetElement("technique")->GetString().c_str());
		pWVP = pd3dEffect->GetParameterByName(NULL, xml->GetElement("wvp")->GetString().c_str());
		pColor = pd3dEffect->GetParameterByName(NULL, xml->GetElement("color")->GetString().c_str());
		pSrcTex = pd3dEffect->GetParameterByName(NULL, xml->GetElement("srctex")->GetString().c_str());

		// ���A���[�h
		for(int i = 0; i < xml->GetElementNum("handle"); i++)
		{
			// XML����Key��ǂݍ��݃��[�h����
			D3DXHANDLE sdr_temp 
				= pd3dEffect->GetParameterByName(NULL, xml->GetElement("handle", i)->GetString().c_str());
			handles.insert(std::make_pair(xml->GetElement("handle", i)->GetString() , sdr_temp));
		}
	}

	CShader::~CShader()
	{
		SAFE_RELEASE(pd3dEffect);
	}
	
	void CShader::Destroy(std::string _name)
	{
		// �C�e���[�^��p��
		// �C�e���[�^���n�b�V���}�b�v�̐擪�ɃZ�b�g
		stdext::hash_map< std::string, CShaderSP >::iterator it = Shaders.begin();

		// �S�����
		if(_name == "all")
		{
			while(it != Shaders.end())
			{
				(*it).second.reset();
				Shaders.erase(it++);
			}
		}
		// �e�N�X�`�����P�������
		else
		{
			it = Shaders.find(_name);
			if(it != Shaders.end())
			{
				(*it).second.reset();
				Shaders.erase(it);
			}
		}
	}

	void CShader::setTechnique() const
	{
		pd3dEffect->SetTechnique(pTechnique);
	}

	void CShader::setWVPMatrix(const CMatrix& wvp) const
	{
		pd3dEffect->SetMatrix(pWVP, (D3DXMATRIX*)&wvp);
	}

	void CShader::setColor(const CVector4& color) const
	{
		pd3dEffect->SetVector(pColor, (D3DXVECTOR4*)&color);
	}

	void CShader::setTexture(const LPDIRECT3DTEXTURE9 texture) const
	{
		pd3dEffect->SetTexture(pSrcTex, texture);
	}

	void CShader::BeginShader() const
	{
		pd3dEffect->Begin(NULL, 0);
	}

	void CShader::EndShader() const
	{
		pd3dEffect->End();
	}

	void CShader::BeginPass(const bool isAddBlend)
	{
		pd3dEffect->BeginPass(isAddBlend);
	}

	void CShader::EndPass()
	{
		pd3dEffect->EndPass();
	}

	D3DXHANDLE* CShader::getpHandle(const std::string &_path) 
	{
		// �C�e���[�^��p��
		std::hash_map<std::string, D3DXHANDLE>::iterator it = handles.find(_path);

		if(it != handles.end())
			return &(*it).second;
		// ������Ȃ��ꍇ(�����ɗ����ꍇ�G���[����)
		return NULL;
	}

	//-----------------------------------------------------------------------------------------------------------
	// CShaderNormal
	//-----------------------------------------------------------------------------------------------------------
	CShaderNormal::CShaderNormal() : CShader("Resource/HLSL/Normal.xml")
	{ }

	CShaderSP CShaderNormal::CreateShader()
	{
		std::string _xmlpath("Resource/HLSL/Normal.xml");
		
		CWsbXmlSP xml = CWsbXml::LoadXmlFile(_xmlpath);
		std::string sdr_path = xml->GetElement("path")->GetString();
		
		hash_map<std::string, CShaderSP>::iterator it = Shaders.find(sdr_path);
		CShaderSP psdr;
		// ���݂�������v�f��Ԃ�
		if(it != Shaders.end())
		{
			psdr = (*it).second;
			return psdr;
		}
		// ���݂��Ȃ���ΐV�������[�h
		psdr = CShaderSP(new CShaderNormal());
		// �n�b�V���}�b�v�ɑ}��
		Shaders.insert(std::make_pair(sdr_path, psdr));
		return psdr;
	}

	void CShaderNormal::applyEffect(const CMatrix& _rotmtx, const CVector4& _campos)
	{
		return;
	}

}