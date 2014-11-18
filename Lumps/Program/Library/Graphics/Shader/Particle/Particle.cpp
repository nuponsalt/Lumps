#include "DXUT.h"
#include "Particle.h"

#include "../../../Support/wsb_xml.h"

namespace KMT {

	CShaderParticle::CShaderParticle() : CShader("Resource/HLSL/Particle.xml")
	{ }

	CShaderSP CShaderParticle::CreateShader()
	{
		std::string _xmlpath("Resource/HLSL/Particle.xml");

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
		psdr = CShaderSP(new CShaderParticle());
		// �n�b�V���}�b�v�ɑ}��
		Shaders.insert(std::make_pair(sdr_path, psdr));
		return psdr;
	}

	void CShaderParticle::applyEffect(const CMatrix& _rotmtx, const CVector4& _campos)
	{
		return;
	}

}