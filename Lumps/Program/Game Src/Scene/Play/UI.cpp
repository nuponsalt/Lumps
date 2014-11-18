#include "DXUT.h"
#include "ScenePlay.h"
#include "../../Define.h"

void CScenePlay::initializeUI()
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/UI.xml");
	// UI�摜
	std::string _path = xml->GetElement("UI")->GetElement("path")->GetString();
	float posX = xml->GetElement("UI")->GetElement("Position")->GetElement("X")->GetFloat();
	float posY = xml->GetElement("UI")->GetElement("Position")->GetElement("Y")->GetFloat();
	UI = CSprite::CreateFromFile(_path);
	UI->Position = CVector3(posX, posY, 0);
	_path = xml->GetElement("SizeUI")->GetElement("path")->GetString();
	posX = xml->GetElement("SizeUI")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("SizeUI")->GetElement("Position")->GetElement("Y")->GetFloat();
	ScoreUI = CSprite::CreateFromFile(_path);
	ScoreUI->Position = CVector3(posX, posY, 0);
	ScoreUI->Scale = ZERO_VECTOR3;
	// ��������
	TimeLimit = xml->GetElement("TimeLimit")->GetInt();
	// �^�C�}�[������
	int _timecount = xml->GetElement("TimeCount")->GetElement("Count")->GetInt();
	CompTimer = CTimerSP(new CTimer(_timecount));
	// �^�C���`�搔��
	float colR = xml->GetElement("TimeCount")->GetElement("Color")->GetElement("R")->GetFloat();
	float colG = xml->GetElement("TimeCount")->GetElement("Color")->GetElement("G")->GetFloat();
	float colB = xml->GetElement("TimeCount")->GetElement("Color")->GetElement("B")->GetFloat();
	posX = xml->GetElement("TimeCount")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("TimeCount")->GetElement("Position")->GetElement("Y")->GetFloat();
	float _interval = xml->GetElement("Interval")->GetFloat();
	TimeCounter = CCounter::CreateCounter();
	TimeCounter->getImage()->setColorRGBA(colR, colG, colB, 1.0f);
	TimeCounter->setPosition(posX, posY, 0.0f);
	TimeCounter->setInterval(_interval);
	// �T�C�Y�`�搔��
	colR = xml->GetElement("SizeCount")->GetElement("Color")->GetElement("R")->GetFloat();
	colG = xml->GetElement("SizeCount")->GetElement("Color")->GetElement("G")->GetFloat();
	colB = xml->GetElement("SizeCount")->GetElement("Color")->GetElement("B")->GetFloat();
	posX = xml->GetElement("SizeCount")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("SizeCount")->GetElement("Position")->GetElement("Y")->GetFloat();
	SizeCounter = CCounter::CreateCounter();
	SizeCounter->getImage()->setColorRGBA(colR, colG, colB, 1.0f);
	SizeCounter->setPosition(posX, posY, 0.0f);
	SizeCounter->setInterval(_interval);
	// �ÓI�p�����[�^������
	ScoreVolume = TotalScoreVolume = 0;
}

void CScenePlay::updateUI()
{
	Score = Interpolate(Score, ScoreVolume, INTERPOLATE_LOW);

	float __size = (float)(ScoreVolume / Player->getExpNext());

	ScoreUI->Scale = Interpolate(ScoreUI->Scale, CVector3(__size, __size, __size), INTERPOLATE_LOW);

	// �������Ԃ̃J�E���g�_�E��
	if(TimeLimit > 0 && CompTimer->TimeCount())
		--TimeLimit;
}

void CScenePlay::renderUI()
{
	// UI���n�摜�`��
	ScoreUI->Render();
	UI->Render();
	// �������ԕ`��p�J�E���^�[
	TimeCounter->Render(CCounter::RIGHT_ALI, TimeLimit);	
	// �T�C�Y�`��p�J�E���^�[
	SizeCounter->Render(CCounter::RIGHT_ALI, (int)Score);
}