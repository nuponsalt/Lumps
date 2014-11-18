#include "DXUT.h"
#include "Mesh.h"

#include "../Extension.h"

namespace KMT {

	stdext::hash_map<std::string, CMeshWP> CMesh::Meshs;

	CMesh::CMesh() : pd3dMesh(NULL), pd3dMeterialBuffer(NULL), MaterialNumber(1), pVertex(NULL)
	{}

	CMesh::~CMesh()
	{
		// �C�e���[�^�̏���
		// �t�@�C���p�X�Ō���
		std::hash_map<std::string, CMeshWP>::iterator it = Meshs.find(FilePath);

		if(it != Meshs.end())
		{
			Meshs.erase( it ) ;
		}
		SAFE_RELEASE(pd3dMesh);
		SAFE_RELEASE(pd3dMeterialBuffer);
#if _DEBUG
		OutputDebugString(L"Release Mesh\n");
#endif
	}

	CMeshSP CMesh::Create(const std::string& _path)
	{
		std::hash_map<std::string, CMeshWP>::iterator it = Meshs.find(_path);
		// ���݂���ΕԂ�
		if(it != Meshs.end()){
			return it->second.lock();
		}
		CMeshSP pmesh = CMeshSP(new CMesh);
		pmesh->FilePath = _path;
		Meshs.insert(make_pair(_path, pmesh));

		return pmesh;
	}

	CMeshSP CMesh::CreateFromX(const std::string& _path)
	{
		stdext::hash_map<std::string, CMeshWP>::iterator it = Meshs.find(_path);

		if(it != Meshs.end()) 
			return CMeshSP((*it).second.lock());
		// ���݂��Ȃ���ΐV�������[�h
		CMeshSP pmesh = CMeshSP(new CMesh);
		// �t�@�C���p�X���擾
		pmesh->FilePath = _path;
		// ������ϊ�
		WCHAR wcbuff[255] = {0};
		DXconvAnsiToWide(wcbuff, _path.c_str(), 255);
		// ���b�V���̃��[�h
		D3DXLoadMeshFromX(wcbuff,
			D3DXMESH_MANAGED,
			DXUTGetD3D9Device(),
			NULL,
			&pmesh->pd3dMeterialBuffer,
			NULL,
			&pmesh->MaterialNumber,
			&pmesh->pd3dMesh);
		// �}�b�v�ɒǉ�
		Meshs.insert(std::make_pair(_path, CMeshWP(pmesh)));

		return pmesh ;
	}

	void CMesh::Destroy(std::string _name) 
	{
		// �C�e���[�^��p��
		// �C�e���[�^���n�b�V���}�b�v�̐擪�ɃZ�b�g
		stdext::hash_map<std::string, CMeshWP>::iterator it = Meshs.begin(); 
		// �S�����
		if(_name == "all"){
			while(it != Meshs.end()){
				(*it).second.reset();
				Meshs.erase(it++);
			}
		}
		else
			// �e�N�X�`�����P�������
		{
			it = Meshs.find(_name);
			if(it != Meshs.end()){
				(*it).second.reset();
				Meshs.erase(it);
			}
		}
	}

	void CMesh::setpd3dMeshVertexIndexBuffer(const WORD* _idx)
	{
		WORD *pI;
		pd3dMesh->LockIndexBuffer(0, (void **)&pI);
		memcpy(pI, _idx, sizeof(WORD) * IndexNumber);
		pd3dMesh->UnlockIndexBuffer();
	}

	void CMesh::setpd3dMeshVertexBuffer(const CVertex* _info, const size_t _memsize)
	{
		pd3dMesh->LockVertexBuffer(0, (void**)&pVertex);
		memcpy(pVertex, _info, _memsize * VertexNumber);
		pd3dMesh->UnlockVertexBuffer();
	}
}