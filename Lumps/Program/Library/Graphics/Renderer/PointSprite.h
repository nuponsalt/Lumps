#pragma once

#include "DXUT.h"

#include "GraphicBehavior.h"

namespace KMT {

	// �|�C���g�X�v���C�g���_�f�[�^
	typedef struct tag_POINTSPRITE
	{
		// ���_���W
		CVector3 Position;
		// �|�C���g�X�v���C�g�T�C�Y
		float PSize;
		// ���_�J���[
		DWORD Color;

		// ���_�t�H�[�}�b�g��`
		static const WORD FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE);

	}POINTSPRITE, *pPOINTSPRITE;

	// �G�~�b�^�[
	class CEmitter
	{
	public :
		// ���W
		CVector3 Position;
		// ���o�����x�N�g��
		std::vector<CVector3> Directions;
		// ���x
		std::vector<float> Speeds;
		// �����x
		float acceleration;

		// �p�[�e�B�N���̎���
		int Span;

		// �`��t���O
		bool isRender;

		// �R���X�g���N�^
		CEmitter() : Span(0), isRender(false) { }
		// �f�X�g���N�^
		~CEmitter() { } 

	};

	class CPointSprite;
	typedef std::shared_ptr<CPointSprite> CPointSpriteSP;

	// �|�C���g�X�v���C�g(�p�[�e�B�N��)
	class CPointSprite : public CGraphicBehavior
	{
	public :
		// �f�X�g���N�^
		virtual ~CPointSprite();

		// �|�C���g�X�v���C�g����
		static CPointSpriteSP CreatePointSprite(const std::string& path, const WORD numPoint, const float size = 1);
		// �`��
		void Render(const CCamera* camera);

	private :
		// ���_�o�b�t�@
		LPDIRECT3DVERTEXBUFFER9 pd3dVertexBuffer;
		// �e�N�X�`��
		CTextureSP Texture;
		// �G�~�b�^�[�z��(std::vector)
		CEmitter* EmitterData;

		// ���_1�̑傫��
		float pointSize;
		// ���_��
		WORD pointNumber;

		// �R���X�g���N�^
		// path : �\��t����e�N�X�`���p�X
		// numPoint : �|�C���g��
		// size : �|�C���g�T�C�Y
		CPointSprite(const std::string& path, const WORD numPoint, const float size = 1);

	};

}