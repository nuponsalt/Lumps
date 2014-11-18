#pragma once
//
//#include "../../Library/Library.h"
//using namespace KMT;
//
//class CTerrain;
//class CHeightField;
//
//typedef std::shared_ptr<CTerrain> CTerrainSP;
//typedef std::shared_ptr<CHeightField> CHeightFieldSP;
//
//typedef std::weak_ptr<CTerrain> CTerrainWP;
//typedef std::weak_ptr<CHeightField> CHeightFieldWP;
//
//// �n�`�Փ˔���
//typedef class CTerrain
//{
//public :
//	// ���_���W�x�N�^�[�z��
//	std::vector<CVector3> Positions;
//	// ���_�C���f�b�N�X
//	size_t Index[2][3];
//	// �@���x�N�g��
//	CVector3 Normal[2];
//	// �|���S������Ώۃt���O
//	size_t PolygonNumber;
//
//	// �R���X�g���N�^
//	CTerrain() : PolygonNumber(0) 
//	{
//		Index[0][0] = 0;
//		Index[0][1] = 1;
//		Index[0][2] = 2;
//		Index[1][0] = 2;
//		Index[1][1] = 1;
//		Index[1][2] = 3;
//	}
//
//	// �Փ˔���̎擾
//	bool getCollide(const CVector3& pos, float radius);
//
//private :
//	// �_�Ƃ̋����̌v�Z
//	float calculateDistance(CVector3 pos, float dist, int polynum);
//
//}ModelVolume, *PModel, *PModelVolume;
//
//// �n�C�g�}�b�v�n�`���f��
//class CHeightField : public CGraphicBehavior
//{
//public :
//	// �f�X�g���N�^
//	~CHeightField() { }
//
//	// ����
//	static CHeightFieldSP CreateHeightField();
//	// �Փ˔���
//	//bool getCollide(CVector3* ppos, float size);
//	// �`��
//	void Render(const CCamera* camera);
//
//private :
//	// �e�N�X�`��
//	CTextureSP Texture;
//	// ���_�o�b�t�@
//	LPDIRECT3DVERTEXBUFFER9 pd3dVertexBuffer;
//	// �C���f�b�N�X�o�b�t�@
//	LPDIRECT3DINDEXBUFFER9  pd3dIndexBuffer;
//	// �n�C�g�t�B�[���h�̏Փ˔���
//	std::vector<std::vector<CTerrainSP>> Collisions;
//	// �t�B�[���h�̃T�C�Y
//	CVector3 vSize;
//
//	// �����̕�����
//	int numWidth;
//	int numDepth;
//	// ���_����
//	int numVTX;
//	// �C���f�b�N�X��
//	int numIDX;
//
//	// �R���X�g���N�^
//	CHeightField();
//
//};