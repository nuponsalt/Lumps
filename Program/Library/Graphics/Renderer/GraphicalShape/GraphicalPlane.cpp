#include "DXUT.h"
#include "GraphicalPlane.h"

#include "../../Shader/Shader.h"
#include "../../GraphicsManager.h"
#include "../../Mesh.h"
#include "../../View/Camera.h"

#include <sstream>

using namespace KMT;
static void getBillBoardRotation(CVector3* _BillPos, CVector3* _TargetPos, CMatrix* _Rot )
{
	D3DXMatrixIdentity((D3DXMATRIX*)_Rot);
	D3DXMatrixLookAtLH(_Rot, (D3DXVECTOR3*)_TargetPos, (D3DXVECTOR3*)_BillPos, &D3DXVECTOR3(0, 1, 0));

	_Rot->_41 = 0;
	_Rot->_42 = 0;
	_Rot->_43 = 0;

	D3DXMatrixInverse(_Rot, NULL, _Rot);
}

namespace KMT
{
	// static parameters
	size_t CGraphicalPlane::CreateCount = 0;

	CGraphicalPlane::CGraphicalPlane() : TextureSize(1.0f, 1.0f, 0.0f), PreviousNumber(0)
	{}

	bool CGraphicalPlane::GenerateBoard(const std::string& _path, const int &_width, const int &_height, const CTextureSP &_texture)
	{
		// �L�[�l�[���ݒ�
		std::stringstream ss("");
		// �t�@�C���p�X�������ԍ����������̏��Œǉ�
		ss << _path << ++CreateCount << _width << _height;
		std::string name = ss.str();
		// ���b�V���C���X�^���X�̐���
		Mesh = CMesh::Create(name);
		// �T�C�Y���L�^
		Size.x = (float)_width ;
		Size.y = (float)_height ;
		//Size.z = 0 ;
		// �e�N�X�`���w�肪����ꍇ���̃T�C�Y���擾
		if(_texture != NULL)
		{
			while(UINT(TextureSize.x) < Texture->getd3dImageInfo().Width)
			{
				TextureSize.x *= 2;
			}
			while(UINT(TextureSize.y) < Texture->getd3dImageInfo().Height)
			{
				TextureSize.y *= 2;
			}
		}
		// �V�F�[�_�[�ݒ�
		Shader = CShaderNormal::CreateShader();
		// ���b�V���𐶐�����
		LPD3DXMESH _mesh;
		if (FAILED(D3DXCreateMeshFVF(2, 4, D3DXMESH_MANAGED, CVertex::FVF, CGraphicsManager::pd3dDevice, &_mesh)))
			return false;

		//���_�f�[�^�̍쐬
		CVertex* pV;
		_mesh->LockVertexBuffer(0, (void**)&pV);
		for (int y = 0 ; y < 2 ; y++) {
			for (int x = 0 ; x < 2 ; x++) {
				float x1 = (float)(x * _width - ((float)_width / 2));
				float y1 = (float)(y * _height - ((float)_height / 2));
				int idx = y * 2 + x;
				pV[idx].Position.x = x1;
				pV[idx].Position.y = y1;
				pV[idx].Position.z = 0;
				pV[idx].Normal.x = 0;
				pV[idx].Normal.y = 0;
				pV[idx].Normal.z = 1;
				if( _texture == NULL )
				{
					pV[idx].UV.x = (float)x * 1.0f;
					pV[idx].UV.y = 1.0f - ((float)y * 1.0f);
				}
			}
		}
		if(_texture)
		{
			pV[0].UV.x = (float)Rects[Number].left / Texture->getd3dImageInfo().Width;
			pV[0].UV.y = (float)Rects[Number].bottom / Texture->getd3dImageInfo().Height;
			pV[1].UV.x = (float)Rects[Number].right / Texture->getd3dImageInfo().Width;
			pV[1].UV.y = (float)Rects[Number].bottom / Texture->getd3dImageInfo().Height;
			pV[2].UV.x = (float)Rects[Number].left / Texture->getd3dImageInfo().Width;
			pV[2].UV.y = (float)Rects[Number].top / Texture->getd3dImageInfo().Height;
			pV[3].UV.x = (float)Rects[Number].right / Texture->getd3dImageInfo().Width;
			pV[3].UV.y = (float)Rects[Number].top / Texture->getd3dImageInfo().Height;
		}
		_mesh->UnlockVertexBuffer();
		//�C���f�b�N�X�f�[�^�̍쐬
		WORD *pIndex;
		_mesh->LockIndexBuffer(0, (void **)&pIndex);
		pIndex[0] = 0;
		pIndex[1] = 2;
		pIndex[2] = 1;
		pIndex[3] = 1;
		pIndex[4] = 2;
		pIndex[5] = 3;
		_mesh->UnlockIndexBuffer();
	    Mesh->setpd3dMesh(_mesh);

		return true;
	}

	CGraphicalPlaneSP CGraphicalPlane::Create(const int &_width, const int &_height, const CTextureSP &_texture)
	{
		CGraphicalPlane *_obj = new CGraphicalPlane();
		++CreateCount;
		std::stringstream ss;
		ss.str("");
		ss << CreateCount;
		std::string str = ss.str().c_str();

		_obj->GenerateBoard(str, _width, _height, _texture);
		return CGraphicalPlaneSP(_obj);
	}

	void CGraphicalPlane::LoadTexture(const std::string &_path, const int &x_num, const int &y_num, const int &size_x, const int &size_y)
	{
		// ���\�[�X����e�N�X�`���𐶐�
		LoadTextureAndAnimation(_path, x_num, y_num, D3DX_DEFAULT);
		// �C���[�W�T�C�Y�ɍ��킹�Ĕ|���S���𐶐�
		(size_x == 0 && size_y == 0) ? GenerateBoard(_path, (int)ImageSize.x, (int)ImageSize.y, Texture) : GenerateBoard(_path, size_x, size_y, Texture);
		// �e�N�X�`���[��}��
		setTexture(Texture);
	}

	void CGraphicalPlane::LoadTexture (const CTextureSP& _tex,const int& x_num, const int &y_num, const int &size_x, const int &size_y)
	{
		Texture = _tex;
		(size_x == 0 && size_y == 0) ? GenerateBoard(_tex->getFilePath(), (int)ImageSize.x, (int)ImageSize.y, Texture) : GenerateBoard(_tex->getFilePath(), size_x, size_y, Texture);
		setTexture(Texture);
	}

	CGraphicalPlaneSP CGraphicalPlane::CreateFromTexture(const std::string &_path, const int &x_num, const int &y_num, const int &size_x, const int &size_y)
	{
		// �C���[�W�T�C�Y�ɍ��킹�Ĕ|���𐶐�
		CGraphicalPlane *_obj = new CGraphicalPlane();
		// �e�N�X�`������
		_obj->LoadTexture(_path, x_num, y_num, size_x, size_y);
		// �쐬�����I�u�W�F�N�g��Ԃ�
		return CGraphicalPlaneSP(_obj);
	}

	CGraphicalPlaneSP CGraphicalPlane::CreateFromTexture(const CTextureSP &_tex, const int &x_num, const int &y_num, const int &size_x, const int &size_y)
	{
		CGraphicalPlane* _obj = new CGraphicalPlane();
		_obj->LoadTexture(_tex, x_num, y_num, size_x, size_y);
		// 
		return CGraphicalPlaneSP(_obj);
	}

	void CGraphicalPlane::Render(const CCamera* camera) 
	{
		// �`�悵�Ȃ��Ȃ炱���Ŋ֐��I��
		if(!isRender)
			return;
		// �����ǂݍ��݂����ꍇ�̉摜�͈͑I��
		if(PreviousNumber != Number)
		{
			CVertex* pV;
			Mesh->getpd3dMesh()->LockVertexBuffer( 0, (void**)&pV );
			pV[0].UV.x = (float)Rects[Number].left / Textures[0]->getd3dImageInfo().Width;
			pV[0].UV.y = (float)Rects[Number].bottom / Textures[0]->getd3dImageInfo().Height;
			pV[1].UV.x = (float)Rects[Number].right / Textures[0]->getd3dImageInfo().Width;
			pV[1].UV.y = (float)Rects[Number].bottom / Textures[0]->getd3dImageInfo().Height;
			pV[2].UV.x = (float)Rects[Number].left / Textures[0]->getd3dImageInfo().Width;
			pV[2].UV.y = (float)Rects[Number].top / Textures[0]->getd3dImageInfo().Height;
			pV[3].UV.x = (float)Rects[Number].right / Textures[0]->getd3dImageInfo().Width;
			pV[3].UV.y = (float)Rects[Number].top / Textures[0]->getd3dImageInfo().Height;
			Mesh->getpd3dMesh()->UnlockIndexBuffer();
			PreviousNumber = Number;
		}
		// ���[���h�s��ݒ�
		CMatrix SclMtx, RotMtx, PosMtx, WldMtx, WVPMtx;
		// �g�k
		D3DXMatrixScaling(&SclMtx, Scale.x, Scale.y, Scale.z);
		// ��]
		// �N�H�[�^�j�I������]�s��XYZ�w�肩
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
			D3DXMatrixRotationYawPitchRoll( &RotMtx, vRotation.y, vRotation.x, vRotation.z );
			break;
		}
		// �r���{�[�h�̏ꍇ
		if(isBillBoard)
		{
			CVector3 campos = camera->getEye() ;
			getBillBoardRotation(&Position, &campos, &RotMtx);
		}
		// �ʒu
		D3DXMatrixTranslation(&PosMtx, Position.x, Position.y, Position.z);
		// �J�����O��ݒ�
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_CULLMODE, d3dCull);
		// �f�o�b�O�p
		//CGraphicsManager::pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
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