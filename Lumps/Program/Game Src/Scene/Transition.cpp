#include "DXUT.h"
#include "Transition.h"

#include "../../Library/Library.h"

// CTransitionManager�̐ÓI�����o����
float CTransition::fAlpha = 0.0f;
float CTransition::colR = 0.0f, CTransition::colG = 0.0f, CTransition::colB = 0.0f;
std::string CTransition::Path = "";
float CTransition::posX, CTransition::posY = 0.0f;
float CTransition::Size = 0.0;
CSpriteSP CTransition::spriteImage = NULL;
CGPlaneSP CTransition::boardImage = NULL;
CTimerSP CTransition::pWaitTimer = NULL;
bool CTransition::isWait = false;

void CTransition::initializeTransition()
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Transition.xml");
	// �摜�t�@�C���p�X
	Path = xml->GetElement("Path")->GetString();
	// �g�����W�V�����摜�̕`����W
	posX = xml->GetElement("spriteImage")->GetElement("Position")->GetElement("X")->GetFloat();	
	posY = xml->GetElement("spriteImage")->GetElement("Position")->GetElement("Y")->GetFloat();
	// �T�C�Y�̕ύX
	Size = xml->GetElement("Size")->GetFloat();
	// �����x�̕ϓ��l
	fAlpha = xml->GetElement("Alpha")->GetFloat();
	// RGB�l
	colR = xml->GetElement("Color")->GetElement("R")->GetFloat();
	colG = xml->GetElement("Color")->GetElement("G")->GetFloat();
	colB = xml->GetElement("Color")->GetElement("B")->GetFloat();
	// �t�F�[�h�A�E�g�ƃC���̊Ԃ̑ҋ@����
	int WaitTime = xml->GetElement("WaitTime")->GetInt();
	// �^�C�}�[�̐���
	// �ҋ@�^�C�}�[
	pWaitTimer = CTimerSP(new CTimer(WaitTime));
}

void CTransition::Destroy()
{
	// �摜�̉��
	// �g�����W�V�����摜
	spriteImage.reset();	
	// �^�C�}�[�̉��
	// �ҋ@�^�C�}�[
	pWaitTimer.reset();	
}

void CTransition::CreateTransition()
{
	// �摜����
	spriteImage = CSprite::CreateFromFile(Path);
	spriteImage->Position= CVector3(posX, posY, 0);
	spriteImage->Scale *= Size;
	// �e�l�̏�����
	// �����x
	spriteImage->setColorRGBA(colR, colG, colB, 0.0f);
	// �ҋ@�^�C�}�[
	pWaitTimer->ResetCount();
	// �ҋ@�t���O
	isWait	 = false;
}

void CTransition::DestroyTransition() 
{ 
	spriteImage.reset(); 
	boardImage.reset();
}

const bool CTransition::IsExistTransition()
{
	return (spriteImage != NULL) ? true : false;
}

const bool CTransition::FadeOut()
{
	// �����x���ő�łȂ���΁A�g�����W�V�����摜�̓����x�����Z���Ă���
	if(spriteImage->vColorRGBA.w >= 1.0f){
		spriteImage->vColorRGBA.w = 1.0f;
		isWait = true;
		return true;
	}
	spriteImage->vColorRGBA.w += fAlpha;
	return false;
}

// �t�F�[�h�C���֐�
const bool CTransition::FadeIn()
{
	// �ҋ@���I���܂Ńt�F�[�h�C���͍s��Ȃ�
	if(isWait && !pWaitTimer->TimeCount())
		return false;
	else
		isWait = false;
	// �����x���ŏ��łȂ���΁A�g�����W�V�����摜�̓����x�����Z���Ă���
	if(spriteImage->vColorRGBA.w <= 0.0f){
		spriteImage->vColorRGBA.w = 0.0f;
		return true;
	}
	spriteImage->vColorRGBA.w -= fAlpha;
	return false;
}