#pragma once

#include <string>
#include <memory>
#include <hash_map>

#include "Vertex.h"

namespace KMT {

	class CMesh ;
	typedef std::shared_ptr<CMesh> CMeshSP;
	typedef std::weak_ptr<CMesh> CMeshWP;

	class CMesh
	{
	public :
		// �f�X�g���N�^
		~CMesh() ;
		// �󐶐�
		static CMeshSP Create(const std::string& _path);
		// X�t�@�C����ǂݍ���Ő���
		static CMeshSP CreateFromX(const std::string& _path);
		// �j��
		static void Destroy(std::string _name = "all");
		// �擾
		inline LPD3DXMESH getpd3dMesh() { return pd3dMesh; }
		inline LPD3DXBUFFER getpd3dMaterialBuffer() { return pd3dMeterialBuffer; }
		inline DWORD getMaterialNum() const { return MaterialNumber; }
		// �ݒ�
		inline void setpd3dMesh(LPD3DXMESH const _p) { pd3dMesh = _p; }
		inline void setVertexNum(const WORD _num) { VertexNumber = _num; }
		inline void setVertexIndexNum(const WORD _num) { IndexNumber = _num; }
		void setpd3dMeshVertexIndexBuffer(const WORD* _idx);
		void setpd3dMeshVertexBuffer(const CVertex* _info, const size_t _memsize);

	private :
		// �p�X
		std::string FilePath;
		// ���b�V��
		LPD3DXMESH pd3dMesh;
		// �}�e���A���o�b�t�@�[
		LPD3DXBUFFER pd3dMeterialBuffer;
		// ���_��
		WORD VertexNumber;
		// ���_�C���f�b�N�X
		BYTE* pIndex;
		// ���_�C���f�b�N�X��
		WORD IndexNumber;
		// �ʐ�
		WORD PrimitiveNumber;
		// �}�e���A���̐�
		DWORD MaterialNumber;
		// ���_���
		CVertex* pVertex;
		// �n�b�V���}�b�v
		static stdext::hash_map<std::string, CMeshWP> Meshs;

		// �R���X�g���N�^
		CMesh();
	
	};
}