//*********************************************
// DirectX�e�N�X�`�����\�[�X�Ǘ��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#include <string>
#include <memory>
#include <hash_map>

namespace KMT {

	//--------------------------------------------------------------------
	// CTexture

	class CTexture;

	typedef std::shared_ptr<CTexture> CTextureSP;
	typedef std::weak_ptr<CTexture> CTextureWP;

	class CTexture sealed
	{
	private :
		// �e�N�X�`���̃}�b�v
		static stdext::hash_map<std::string, CTextureWP> Textures;
		// �����e�N�X�`���}�b�v
		static stdext::hash_map<std::string, CTextureWP> stringTextures;
		// �t�@�C���p�X
		std::string FilePath;
		// �e�N�X�`���f�[�^
		LPDIRECT3DTEXTURE9 pd3dTexture;
		// �摜���
		D3DXIMAGE_INFO d3dImageInfo;
		// �e�N�X�`���[�̔ԍ�
		static size_t TexCount;

		// �R���X�g���N�^
		CTexture();

	public :
		// �f�X�g���N�^
		~CTexture();
		// ��̃e�N�X�`������
		// _name : �n�b�V���}�b�v�o�^��
		// nWidth : �������̃e�N�X�`���̕�
		// nHeight : �������̃e�N�X�`���̍���
		static CTextureSP CreateEmpty(const size_t Width, const size_t Height);
		// �������������܂ꂽ�e�N�X�`���̐���
		// nWidth : �e�N�X�`���̕�
		// nHeight : �e�N�X�`���̍���
		// nFromRGB : �t�H���g�̃O���f�[�V�����̊J�n�F( ARGB�̘_���a�w�� )
		// nToRGB : �t�H���g�̃O���f�[�V�����̏I���F( ARGB�̘_���a�w�� )
		// cFont : �g�p����t�H���g
		// cChar : �������镶��
		// ���l : �}�b�v�o�^�L�[�̓t�H���g���{��������
		static CTextureSP CreateToFont(int nWidth, int nHeight, int nFromRGB, int nToRGB, const std::string Font, const std::string Char);
		// ���\�[�X����̃e�N�X�`������
		// _path : �t�@�C���p�X
		static CTextureSP CreateFromFile(const std::string &_path, const DWORD dwFilter = D3DX_FILTER_NONE);
		// �j��
		// m_name : �j������I�u�W�F�N�g�̖��O
		// tips : �f�t�H���g������all�őS�Ă̔z����I�u�W�F�N�g��j��
		static void Destroy(std::string _name = "all");

		// �擾 : �t�@�C���p�X
		inline std::string getFilePath() { return FilePath; }
		// �擾 : DirectX�e�N�X�`�����
		inline LPDIRECT3DTEXTURE9 getpd3dTexture() { return pd3dTexture; }
		// �擾 : �C���[�W���擾
		inline D3DXIMAGE_INFO getd3dImageInfo() { return d3dImageInfo; }

	} ;

}