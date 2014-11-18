#pragma once

#include "../../Library/Library.h"
using namespace KMT ;

#include <string>

const int TRANSPOSITION_X = 320 ;
const int TRANSPOSITION_Y = 240 ;
const float TRANS_ALPHA = 0.02f ;
const int WATE_TIME = 30 ;

class CTransition
{
public :
	// �������֐�
	static void initializeTransition();
	// ����֐�
	static void Destroy();
	// �g�����W�V���������֐�����1
	// tips... ������̊֐����g���ƁA���[�h�����摜�̓f�t�H���g�̂��̂ƂȂ�
	static void CreateTransition();
	// �g�����W�V��������֐�
	static void DestroyTransition();
	// �g�����W�V��������������Ă��邩�ǂ����̃t���O��Ԃ��֐�
	// �߂�l�͐�������
	static const bool IsExistTransition();
	// �t�F�[�h�A�E�g�֐�
	// ret.... [ false : �t�F�[�h�A�E�g�� ] [ true : �t�F�[�h�A�E�g���� ]
	static const bool FadeOut();
	// �t�F�[�h�C���֐�
	// ret.... [ false : �t�F�[�h�C���� ] [ true : �t�F�[�h�C������ ]
	static const bool FadeIn();
	// �`��֐�
	inline static void Render(){ if((spriteImage != NULL) ^ (boardImage != NULL)) spriteImage->Render(); }

private :
	// �����x�̕ϓ��l
	static float fAlpha;
	// RGB�l
	static float colR, colG, colB;
	// �f�t�H���g�̃g�����W�V�����摜�̃t�@�C����
	static std::string Path;
	// ���W
	static float posX, posY;
	// �T�C�Y
	static float Size;
	// ---------------------------------------------------------------------------------
	// �g�����W�V�����摜
	static CSpriteSP spriteImage;	// Sprite
	static CGPlaneSP boardImage; // 3Dboardpoly
	// �ҋ@�^�C�}�[
	static CTimerSP pWaitTimer;
	// �ҋ@�t���O
	static bool isWait;					

	// �R���X�g���N�^
	CTransition(){}
	// �f�X�g���N�^
	~CTransition(){}

};