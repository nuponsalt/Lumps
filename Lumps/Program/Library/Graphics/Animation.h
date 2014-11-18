#pragma once 

#include "Texture.h"
#include "../Math/Vector.h"

namespace KMT 
{

	// �A�j���[�V�����Đ����[�h
	enum PLAYMODE{
		// �t���[���w��
		SELECT_FRAME,			
		// ��x�����Đ�
		PLAY_ONCE,
		// ���[�v�Đ�
		PLAY_LOOP	
	};

	class CAnimation 
	{
	public :
		// �R���X�g���N�^
		CAnimation();
		// �f�X�g���N�^
		virtual ~CAnimation();

		// �e�N�X�`�����摜�t�@�C������ǂݍ���
		// _path : �摜�̃t�@�C���p�X
		// _x_num : ������
		// _y_num : �c����
		void LoadTextureAndAnimation(const std::string &_path, const int &_x_num = 1, const int &_y_num = 1, const DWORD &dwFilter = D3DX_FILTER_NONE);
		
		//* �擾 *//
		// ���݂̃A�j���[�V�����ԍ����擾����
		inline int GetAnimationNumber() const { return Number; }
		//* �ݒ� *//
		// ������
		inline void setDivideW(const int &_num) { DivideWidth = _num; }
		inline void setDivideH(const int &_num) { DivideHeight = _num; }
		// �Đ����x
		inline void setAnimationSpeed(int _speed) { Speed = _speed; }
		// �Đ����[�h
		inline void setPlayMode(PLAYMODE mode) { CurrentPlayMode = mode; }

		// �A�j���[�V��������
		// _mode : �Đ����[�h
		// frame : �t���[����
		// �߂�l : �Đ������ۂ�(false�͍Đ����Atrue�͍Đ��I��)
		// ���l : �t���[���w�胂�[�h�̏ꍇ�͑������Ƀt���[���ԍ����A����ȊO�̃��[�h�ł͉��t���[�����ɃA�j���[�V���������邩��n��
		const bool UpdateAnimation(const int &frame = 0);

	protected :
		// �e�N�X�`���[
		CTextureSP Texture;
		// ������(Width:��, Height:�c)
		int DivideWidth, DivideHeight;
		// �`��͈�
		std::vector<RECT> Rects;
		// �摜������̃T�C�Y
		CVector3 ImageSize;
		// �`�撆�S���W
		CVector3 CenterPosition;
		// �A�j���[�V�����̑���
		int Speed;
		// �\������A�j���[�V�����ԍ�
		int Number;
		// �A�j���[�V�����p�̃J�E���^
		int Count;

		// �Đ����[�h
		PLAYMODE CurrentPlayMode;
		
	};
}