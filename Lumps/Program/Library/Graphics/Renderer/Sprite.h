//*********************************************
// �X�v���C�g�`��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#pragma warning ( disable:4238 )

#include "GraphicBehavior.h"
#include "../Animation.h"
#include <memory>

namespace KMT {

	class CSprite ;
	typedef std::shared_ptr<CSprite> CSpriteSP ;
	typedef std::weak_ptr<CSprite> CSpriteWP ;

	class CSprite : public CGraphicBehavior, public CAnimation
	{
	public :
		// �摜�̂ǂ͈̔͂�`�悷�邩
		RECT rect;
		
		// �f�X�g���N�^
		~CSprite();

		// �e�N�X�`���̐ݒ�
		void setTexture(const CTextureSP &_texture);
		//* ���� *//
		static CSpriteSP CreateSprite();
		// �ꖇ�e�N�X�`��
		// _path : �e�N�X�`���[�̃t�@�C���p�X
		static CSpriteSP CreateFromFile(const std::string &_path);
		// �A�j���[�V�����e�N�X�`��
		// _path : �e�N�X�`���[�̃t�@�C���p�X
		// _w_num : ������
		// _h_num : �c����
		static CSpriteSP CreateFromFile(const std::string &_path, const int &_w_num, const int &_h_num);
		//* �`�� *//
		void Render(const CCamera* camera = NULL);
		
	private :
		// DirectX3D�X�v���C�g
		LPD3DXSPRITE pd3dSprite;
		// ���]�p�񎟌��x�N�g��
		CVector2 vTurn;
		
		// �R���X�g���N�^
		CSprite();

	};

}