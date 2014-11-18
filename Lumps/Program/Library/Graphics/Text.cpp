//*********************************************************************
// �e�L�X�g�\���N���X
// Last Update : 2013.12.5
// Yuta Komatsu
//*********************************************************************
#include "DXUT.h"
#include "Text.h"

namespace KMT {

	CDebugText::CDebugText() : bitColor(0xFFFFFFFF) { }
	
	CDebugText::~CDebugText() 
	{
		SAFE_RELEASE(pd3dfont);
	}

	CDebugTextSP CDebugText::CreateText(size_t nSize, const LPCWCHAR wFont) 
	{
		CDebugTextSP ptext  = CDebugTextSP(new CDebugText);
		// �t�H���g�̏���ݒ�
		D3DXFONT_DESC _d3dfontDesc;
		// �t�H���g�̍���
		_d3dfontDesc.Height = nSize;
		// �t�H���g�̕�
		_d3dfontDesc.Width = nSize / 2;
		_d3dfontDesc.Weight = 0;
		_d3dfontDesc.MipLevels = 0;
		_d3dfontDesc.Italic = FALSE;
		_d3dfontDesc.CharSet = SHIFTJIS_CHARSET;
		_d3dfontDesc.OutputPrecision = OUT_TT_ONLY_PRECIS;
		_d3dfontDesc.Quality = DEFAULT_QUALITY;
		_d3dfontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
		lstrcpy(_d3dfontDesc.FaceName, wFont);
		// �t�H���g����
		D3DXCreateFontIndirect(DXUTGetD3D9Device(), &_d3dfontDesc, &ptext->pd3dfont);
		// ���ʂ̃I�u�W�F�N�g���߂�
		return ptext;
	}

	void CDebugText::drawText(const int _Left, const int _Top, const DWORD _bitColor, LPCWSTR _Text, ...)
	{
		// �`��ʒu�̐ݒ�
		RECT _rect = { _Left, _Top, 0, 0 };
		// �J���[�ۑ�
		bitColor = _bitColor;
		// �ϒ��������當����ɕϊ�
		va_list va;
		va_start(va, _Text);
		WCHAR _Buffer[255] = { 0 };
		vswprintf_s(_Buffer, _Text, va);
		va_end(va);

		HRESULT hr;
		if(SUCCEEDED(DXUTGetD3D9Device()->BeginScene()))
		{
			// �e�L�X�g�`��
			// _Text : �`�悷�镶���� (WCHAR �w��)
			// _rect : �`��͈͎w��
			// nColor : �F�w��
			pd3dfont->DrawText(NULL, _Buffer,	-1, &_rect,	DT_LEFT | DT_NOCLIP, _bitColor);
			// �`��I��
			V(DXUTGetD3D9Device()->EndScene());
		}
	}

}