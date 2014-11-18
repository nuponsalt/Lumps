#pragma once

#include <string>
#include <memory>
#include "../Graphics/Renderer/Sprite.h"

namespace KMT {

	class CCounter ;
	typedef std::shared_ptr<CCounter> CCounterSP ;

	class CCounter
	{
	public :
		// �񂹃^�C�v
		enum ALIGN_TYPE{
			// ����
			LEFT_ALI,	
			// �E��
			RIGHT_ALI	
		};

		// �R���X�g���N�^
		CCounter();
		// �f�X�g���N�^
		~CCounter(){ Image.reset(); }
		// ����
		static CCounterSP CreateCounter() ;
		static CCounterSP CreateCounter(const std::string &_path);
		/* �擾 */
		// ��_���W�̎擾�֐�
		inline const CVector3 getPosition() const { return Position; }
		
		inline CSpriteSP getImage() const { return Image; }
		/* �ݒ� */
		// ���W
		inline void setPosition(const CVector3& _position){ Position = _position; }
		inline void setPosition(const float &_x, const float &_y, const float &_z) { Position = CVector3(_x, _y, _z); }
		// �`�抴�o
		inline void setInterval(const float _interval){ Interval = _interval; }
		// �`��֐�
		void Render(const ALIGN_TYPE &_type, const int &_num);
		

	private :
		// �����ɑ΂��镪����
		static const int DIV_X_NUM = 10;
		// �����ɑ΂��镪����
		static const int DIV_Y_NUM = 1;
		// �\���ł��錅��
		static const int MAX_NUM = 10;

		// �����摜
		CSpriteSP Image;
		// �`�悷��ۂ̊�_���W
		CVector3 Position;
		// �`��Ԋu
		float Interval;

		// �����摜�̃��[�h�֐�
		// _path : �g�p���鐔���摜�̃t�@�C����
		void LoadFromFile(const std::string& _path);
		
	};

}