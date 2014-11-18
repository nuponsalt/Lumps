#include "DXUT.h"
#include "ModelRenderer.h"
#include "../GraphicsManager.h"

#include "../Shader/Shader.h"
#include "../View/Camera.h"

namespace KMT {

	CModelRenderer::CModelRenderer() { }

	void CModelRenderer::LoadFromX(const std::string &_path)
	{
		//-------------------------------------------------------------------------
		// X �t�@�C�� �ƃe�N�X�`���̃��[�h
		Mesh = CMesh::CreateFromX(_path);
		// �}�e���A�����̎擾
		D3DXMATERIAL *p_materials = (D3DXMATERIAL*)(Mesh->getpd3dMaterialBuffer()->GetBufferPointer());
		// �e�N�X�`���̃��[�h
		std::stringstream ss;
		WCHAR wc_buff[255] = { 0 };
		CTextureSP tex;
		for(size_t i = 0; i < Mesh->getMaterialNum(); i++){
			memset(wc_buff, 0, sizeof(WCHAR)*255);
			ss.str("");
			// ����̕����Ńe�N�X�`�������݂��Ȃ��ꍇ
			if(NULL == p_materials[i].pTextureFilename){
				tex = NULL;
				Textures.push_back(tex);
				D3DCOLORVALUE v = p_materials[i].MatD3D.Diffuse;
				// �}�e���A������F�����擾
				D3DXVECTOR4 col = D3DXVECTOR4(v.r, v.g, v.b, v.a);
				DiffuseColors.push_back(col);
				continue;
			}
			//
			DiffuseColors.push_back(D3DXVECTOR4(0,0,0,0));
			// �e�N�X�`���̃p�X�������I�ɐ���
			//------------------------------------------------

			// �t�@�C���p�X�̑O�������i�[����
			std::string b_path;
			// X�t�@�C���̃p�X����K�v�������������o��

			// "/" "\\"���������p�X�̋�؂�̍Ō�̕�������������
			// X�t�@�C���ƃe�N�X�`���͓����t�H���_�ɂ���Ƃ��A
			// X�t�@�C���̂���t�H���_�̃p�X�܂ł𔲂����

			// �p�X�̍Ō��"/"������
			std::size_t index = _path.find_last_of("/");
			if(index != std::string::npos)
			{
				b_path = _path.substr(0, index + 1);
			}
			// �Y���Ȃ��Ȃ�"\\"�ōČ���
			else
			{
				index = _path.find_last_of("\\");
				if(index != std::string::npos)
				{
					// �p�X�̋�؂肪"\\"�̂Ƃ���"\\"�̕������͂���������"/"������
					b_path = _path.substr(0, index);
					b_path += "/";
				}
			}

			// X�t�@�C���ɋL�q����Ă���e�N�X�`���̃p�X�̍Ō�̕��������𔲂��o���O�����ɒǉ�
			//----------------------------------------------------
			std::string temp_str;
			temp_str = p_materials[i].pTextureFilename;
			// �p�X�̍Ō��"/"������
			index = temp_str.find_last_of("/");
			if(index != std::string::npos)
			{
				std::string str1;
				str1 = temp_str.substr(index + 1);
				b_path += str1;
			}
			// �Y���Ȃ��Ȃ�"\\"�ōČ���
			else{
				index = temp_str.find_last_of("\\");
				if(index != std::string::npos)
				{
					std::string str1;
					str1 = temp_str.substr(index + 1);
					b_path += str1;
				}
				// �Y���Ȃ��Ȃ炻�̂܂ܒǉ�
				else{
					b_path += temp_str;
				}
			}
			// �Ǝ��e�N�X�`���N���X�Ƃ��Đ���
			tex = CTexture::CreateFromFile(b_path, D3DX_DEFAULT);

			Textures.push_back(tex);
		}
	}

	CGRendererSP CModelRenderer::CreateFromX(const std::string &_path, const CShaderSP &_shader)
	{
		CGRendererSP pgraph(new CModelRenderer());
		// �V�F�[�_�[�ݒ�
		pgraph->setShader(_shader);
		pgraph->LoadFromX(_path);

		return CGRendererSP(pgraph);
	}

	void CModelRenderer::Render(const CCamera* camera)
	{
		if(!isRender)
			return;
		// ���[���h�s��ݒ�
		CMatrix SclMtx, RotMtx, PosMtx, WldMtx, WVPMtx;
		// �g�k
		D3DXMatrixScaling(&SclMtx, Scale.x, Scale.y, Scale.z);
		// ��] : switch-case�c�N�H�[�^�j�I������]�s��XYZ�w�肩
		switch(CurrentRotateType)
		{
		case ROTATE_TYPE::QUATERNION :
			D3DXMatrixRotationQuaternion(&RotMtx, &qRotation);
			break;

		case ROTATE_TYPE::MATRIX :
			mRotationWorld = mRotationX * mRotationY * mRotationZ;
			RotMtx = mRotationWorld;
			break;

		case ROTATE_TYPE::XYZ :
			D3DXMatrixRotationYawPitchRoll(&RotMtx, vRotation.y, vRotation.x, vRotation.z);
			break;
		}
		// �ʒu
		D3DXMatrixTranslation(&PosMtx, Position.x, Position.y, Position.z);
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_CULLMODE, d3dCull);
		// �f�o�b�O�p
		//CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		// �V�F�[�_���g�p����ꍇ�J�����̃r���[�s��(0)�A�v���W�F�N�V�����s��(1)�����[���h�s��ɍ���
		WldMtx = SclMtx * RotMtx * PosMtx;
		WVPMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW) * camera->getMatrix(CViewBehavior::PROJECTION);
		// �J�����̍��W���V�F�[�_�Ɏg�p���邽�߂̍s��ϊ�
		CMatrix CamMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW);
		D3DXMatrixInverse(&CamMtx, NULL, &CamMtx);
		CVector4 EyePos = CVector4(
			camera->getEye().x, 
			camera->getEye().y, 
			camera->getEye().z, 
			1
			);
		EyePos.Transform(CamMtx);
		D3DXVec4Normalize((D3DXVECTOR4*)&EyePos, (D3DXVECTOR4*)&EyePos);
		// �V�F�[�_�ݒ�
		Shader->setTechnique();
		// �V�F�[�_�Ƀ��[���h * �r���[ * �v���W�F�N�V�����s���n��
		Shader->setWVPMatrix(WVPMtx);
		// �V�F�[�_�[���L�̒l�̐ݒ�
		Shader->applyEffect(RotMtx, EyePos);
		
		HRESULT hr;
		// 3D ���f���̃p�[�c�����[�v���ĕ`��
		for(size_t i = 0 ; i < Mesh->getMaterialNum(); i++)
		{
			// �e�N�X�`�������݂��Ȃ��ꍇ�̃J���[
			D3DXVECTOR4 vec4 = D3DXVECTOR4(1.0,1.0,1.0,1.0);
			// �i�p�[�c�ɑΉ�����e�N�X�`����ݒ�
			// �V�F�[�_�Ƀe�N�X�`����n��
			if(NULL != Textures[i])
			{
				LPDIRECT3DTEXTURE9 p_tex = Textures[i]->getpd3dTexture();
				// �V�F�[�_�ɃJ���[��n��
				Shader->setColor(vColorRGBA);
				Shader->setTexture(p_tex);
			} else 
			{
				Shader->setColor(vec4);
			}
			// �V�F�[�_�̎g�p�J�n
			Shader->BeginShader();
			// �V�F�[�_�̃p�X�ݒ�
			Shader->BeginPass(isAddBlend);
			// �p�[�c�̕`��	
			if(SUCCEEDED(CGraphicsManager::pd3dDevice->BeginScene()))
			{
				Mesh->getpd3dMesh()->DrawSubset(i); 
				V(CGraphicsManager::pd3dDevice->EndScene());
			}
			// �p�X�I��
			Shader->EndPass();
			// �V�F�[�_�I��
			Shader->EndShader();
		}
	}
	
}