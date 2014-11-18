//*********************************************
// �e�L�X�g�\���N���X
// Last Update : 2013.12.5
// Yuta Komatsu
//*********************************************
#pragma once

#include <string>
#include <memory>
#include "../Math/Vector.h"

namespace KMT {
	// �O���錾
	class CDebugText;
	typedef std::shared_ptr<CDebugText> CDebugTextSP;
	typedef std::weak_ptr<CDebugText> CDebugTextWP;
	
	//**�f�o�b�O��p�e�L�X�g�`��N���X**//
	class CDebugText
	{
	private:
		// �t�H���g
		LPD3DXFONT pd3dfont;
		// �F���(�r�b�g)
		DWORD bitColor;

		// �R���X�g���N�^
		CDebugText();

	public:
		// �f�X�g���N�^
		~CDebugText();

		// �t�H���g�̐���
		// nSizeX : �����T�C�Y
		// wFont : �g�p�t�H���g
		static CDebugTextSP CreateText(size_t _Size, const LPCWCHAR wFont);
		// ������̕`��
		// �����@�`�悷�镶����
		void drawText(const int _Left, const int _Top, const DWORD _bitColor, LPCWSTR _Text, ...);
	};

}