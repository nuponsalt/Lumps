#include "DXUT.h"
#include "GraphicalRegularPolygonPlane.h"

#include "../../GraphicsManager.h"
#include "../../Shader/Shader.h"

namespace KMT {

	CGraphicalRegularPolygonPlane::CGraphicalRegularPolygonPlane() : TextureSize(1.0f, 1.0f, 0.0f)
	{}

	//CGRendererSP CGraphicalRegularPolygonPlane::Create(const int &_radius, const int &_facenum, 
	//	const FACE_GENERATE_TYPE &_type, const CTextureSP &_texture) 
	//{
	//	CGraphicalRegularPolygonPlane *_obj;
	//	return CGRendererSP(_obj);
	//}

	//bool CGraphicalRegularPolygonPlane::GenerateRegularPolygonBoard(const int &_radius, const int &_facenum, 
	//	const FACE_GENERATE_TYPE &_type, const CTextureSP &_texture) 
	//{
	//	// �L�[�l�[���ݒ�
	//	std::stringstream ss("");
	//	ss << _radius << _facenum;
	//	std::string name = ss.str();
	//	// ���b�V���C���X�^���X�̐���
	//	Mesh = CMesh::Create(name);
	//	// �T�C�Y���L��
	//	Size.x = _radius * 2.0f;
	//	Size.y = _radius * 2.0f;
	//	Size.z = 0.0f;
	//	// �e�N�X�`���w�肪����ꍇ�e�N�X�`���[�̃T�C�Y���擾
	//	if(_texture != NULL)
	//	{
	//		while(UINT(TextureSize.x) < _texture->getd3dImageInfo().Width)
	//		{
	//			TextureSize.x *= 2;
	//		}
	//		while(UINT(TextureSize.y) < _texture->getd3dImageInfo().Height)
	//		{
	//			TextureSize.y *= 2;
	//		}
	//	}
	//	// �V�F�[�_�[�ݒ�
	//	Shader = CShader::Create();
	//	// ���b�V�����ǂݍ���
	//	LPD3DXMESH _mesh;
	//	// ���_���͖ʐ�+���S���_�łł���
	//	//if (FAILED(D3DXCreateMeshFVF(_facenum, (_type == )(_facenum+1), D3DXMESH_MANAGED, CVertex::FVF, CGraphicsManager::pd3dDevice, &_mesh)))
	//	//{
	//	//	return false;
	//	//}
	//	// �萔
	//	static const float TWO = 2.0f;
	//	// ���_�f�[�^�̍쐬
	//	CVertex* pV;
	//	_mesh->LockVertexBuffer(0, (void**)&pV);
	//	//�C���f�b�N�X�f�[�^�̍쐬
	//	WORD *pIndex;
	//	_mesh->LockIndexBuffer( 0, (void **)&pIndex );
	//	pV[0].position = CVector3();
	//	pV[0].normal = CVector3(0.0f, 0.0f, 1.0f);
	//	for (int i = 0; i < _facenum; i++) 
	//	{
	//		if (_type == POLYNUM_VTX)
	//		{
	//			float x = _radius * cos(TWO * D3DX_PI * ((float)i / (float)_facenum) - D3DXToRadian(90));
	//			float y = _radius * sin(TWO * D3DX_PI * ((float)i / (float)_facenum) - D3DXToRadian(90));
	//			pV[i + 1].position = CVector3(x, y, 0);
	//			pV[i + 1].normal = CVector3(0, 0, 1);
	//			if(_texture == NULL)
	//			{
	//				//pV[i].uv.x = (float)x * 1.0f ;
	//				//pV[i].uv.y = 1.0f -((float)y * 1.0f) ;
	//			}
	//			pIndex[i * 3]  = 0;
	//			pIndex[i * 3 + 1] = (i !=_facenum - 1) ? i + 2 : 1;
	//			pIndex[i * 3 + 2] = i + 1;
	//			// �����𔲂���
	//			continue;
	//		}
	//	}
	//	_mesh->UnlockVertexBuffer();
	//	_mesh->UnlockIndexBuffer();
	//	// ���b�V���ɐݒ�
	//	Mesh->setpd3dMesh( _mesh ) ;
	//	// �쐬����
	//	return true;
	//}
}