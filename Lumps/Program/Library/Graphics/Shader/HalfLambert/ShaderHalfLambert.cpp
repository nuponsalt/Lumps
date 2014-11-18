#include "DXUT.h"
#include "ShaderHalfLambert.h"

#include "../../GraphicsManager.h"

#include "../../../Support/wsb_xml.h"
#include "../../../Extension.h"
#include "../../../System/Debug.h"
#include "../../Renderer/GraphicBehavior.h"

namespace KMT {

	//------------------------------------------------------------------------------------------------------------------------------------
	// CShaderHalfLambert
	//------------------------------------------------------------------------------------------------------------------------------------
	CShaderHalfLambert::CShaderHalfLambert() : CShader("Resource/HLSL/HalfLambert.xml")
	{}

	CShaderSP CShaderHalfLambert::CreateShader()
	{
		std::string _xmlpath("Resource/HLSL/HalfLambert.xml") ;
		
		CWsbXmlSP xml = CWsbXml::LoadXmlFile(_xmlpath);
		std::string sdr_path = xml->GetElement("path")->GetString();
		CShaderSP psdr ;
		hash_map<std::string, CShaderSP>::iterator it = Shaders.find(sdr_path);
		
		// ���݂�������v�f��Ԃ�
		if(it != Shaders.end())
		{
			psdr = (*it).second ;
			return psdr ;
		}
		// ���݂��Ȃ���ΐV�������[�h
		psdr = CShaderSP(new CShaderHalfLambert());
		
		float dirX = xml->GetElement("LightDirection")->GetElement("X")->GetFloat();
		float dirY = xml->GetElement("LightDirection")->GetElement("Y")->GetFloat();
		float dirZ = xml->GetElement("LightDirection")->GetElement("Z")->GetFloat();
		
		psdr->setLightDirection(dirX, dirY, dirZ);

		// �n�b�V���}�b�v�ɑ}��
		Shaders.insert(std::make_pair(sdr_path, psdr));

		return psdr;
	}

	void CShaderHalfLambert::applyEffect(const CMatrix &_rotmtx, const CVector4& _campos)
	{
		// ���C�g�v�Z�p�ɉ�]�s���n��
		pd3dEffect->SetMatrix(*getpHandle("ROT"), &_rotmtx);
		// ���C�g�ݒ�(���s����)
		pd3dEffect->SetVector(*getpHandle("LightDir"), (D3DXVECTOR4*)&LightDirection);
	}

}