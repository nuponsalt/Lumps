#include "DXUT.h"
#include "ScenePlay.h"
#include "../../Define.h"

void CScenePlay::initializeUI()
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/UI.xml");
	// UI画像
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
	// 制限時間
	TimeLimit = xml->GetElement("TimeLimit")->GetInt();
	// タイマー初期化
	int _timecount = xml->GetElement("TimeCount")->GetElement("Count")->GetInt();
	CompTimer = CTimerSP(new CTimer(_timecount));
	// タイム描画数字
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
	// サイズ描画数字
	colR = xml->GetElement("SizeCount")->GetElement("Color")->GetElement("R")->GetFloat();
	colG = xml->GetElement("SizeCount")->GetElement("Color")->GetElement("G")->GetFloat();
	colB = xml->GetElement("SizeCount")->GetElement("Color")->GetElement("B")->GetFloat();
	posX = xml->GetElement("SizeCount")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("SizeCount")->GetElement("Position")->GetElement("Y")->GetFloat();
	SizeCounter = CCounter::CreateCounter();
	SizeCounter->getImage()->setColorRGBA(colR, colG, colB, 1.0f);
	SizeCounter->setPosition(posX, posY, 0.0f);
	SizeCounter->setInterval(_interval);
	// 静的パラメータ初期化
	ScoreVolume = TotalScoreVolume = 0;
}

void CScenePlay::updateUI()
{
	Score = Interpolate(Score, ScoreVolume, INTERPOLATE_LOW);

	float __size = (float)(ScoreVolume / Player->getExpNext());

	ScoreUI->Scale = Interpolate(ScoreUI->Scale, CVector3(__size, __size, __size), INTERPOLATE_LOW);

	// 制限時間のカウントダウン
	if(TimeLimit > 0 && CompTimer->TimeCount())
		--TimeLimit;
}

void CScenePlay::renderUI()
{
	// UI下地画像描画
	ScoreUI->Render();
	UI->Render();
	// 制限時間描画用カウンター
	TimeCounter->Render(CCounter::RIGHT_ALI, TimeLimit);	
	// サイズ描画用カウンター
	SizeCounter->Render(CCounter::RIGHT_ALI, (int)Score);
}