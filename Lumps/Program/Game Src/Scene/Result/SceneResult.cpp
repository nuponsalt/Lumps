#include "DXUT.h"
#include "SceneResult.h"

#include "../../Camera/CameraThirdPerson.h"
#include <algorithm>
#include "../Title/SceneTitle.h"
#include "../Play/ScenePlay.h"
#include "../SceneManager.h"

CSceneResult::CSceneResult() : Score(0), TotalScore(0) { }

CSceneSP CSceneResult::CreateScene()
{
	return CSceneSP(new CSceneResult());
}

CCommand CSceneResult::CreateCommand()
{
	CCommand command;
	// 入力制限時は入力受付なし
	if(CSceneManager::getisKeyLock_())
		return command;
	// ○キー
	if(DXUTWasKeyPressed('Z') || DXUTWasKeyPressed(VK_RETURN)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::PAD_BTN_2))
		command.Add(CCommand::CIRCLE);

	return command;
}

void CSceneResult::initializeScene()
{
	// オフスクリーンレンダリング
	mainLayer = CLayer::CreateLayer(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainLayer->board->Position.y = 0.0f;
	
	// XMLデータ取得
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Result/SceneResult.xml");
	// 深度スケールは別に設定
	float zscl = xml->GetElement("DepthScale")->GetFloat();
	// 背景スカイドーム
	std::string _path = xml->GetElement("SkyDome")->GetElement("path")->GetString();
	float posX = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("X")->GetFloat();
	float posY = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("Y")->GetFloat();
	float posZ = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("Z")->GetFloat();
	SkyDome = CGRenderer::CreateFromX(_path, CShaderNormal::CreateShader());
	SkyDome->Position = CVector3(posX, posY, posZ);
	// プレイングスコア(ロゴ)
	_path = xml->GetElement("Score")->GetElement("path")->GetString();
	posX = xml->GetElement("Score")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Score")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Score")->GetElement("Position")->GetElement("Z")->GetFloat();
	float scl = xml->GetElement("Score")->GetElement("Scale")->GetFloat();
	float alpha = xml->GetElement("Score")->GetElement("Alpha")->GetFloat();
	ScoreLogo = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	ScoreLogo->Position = CVector3(posX, posY, posZ);
	ScoreLogo->Scale = CVector3(scl, scl, scl * zscl);
	ScoreLogo->setColorRGBA(255, 255, 255, alpha);
	// ランキング(ロゴ)
	_path = xml->GetElement("Ranking")->GetElement("path")->GetString();
	posX = xml->GetElement("Ranking")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Ranking")->GetElement("Position")->GetElement("Z")->GetFloat();
	scl = xml->GetElement("Ranking")->GetElement("Scale")->GetFloat();
	alpha = xml->GetElement("Ranking")->GetElement("Alpha")->GetFloat();
	RankingLogo = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	RankingLogo->Position = CVector3(posX, posY, posZ);
	RankingLogo->Scale = CVector3(scl, scl, scl * zscl);
	RankingLogo->setColorRGBA(255, 255, 255, alpha);
	// ランキング1位(ロゴ)
	_path = xml->GetElement("Ranking1st")->GetElement("path")->GetString();
	posX = xml->GetElement("Ranking1st")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking1st")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Ranking1st")->GetElement("Position")->GetElement("Z")->GetFloat();
	scl = xml->GetElement("Ranking1st")->GetElement("Scale")->GetFloat();
	Ranking1st = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Ranking1st->Position = CVector3(posX, posY, posZ);
	Ranking1st->Scale = CVector3(scl, scl, scl * zscl);
	// ランキング2位(ロゴ)
	_path = xml->GetElement("Ranking2nd")->GetElement("path")->GetString();
	posX = xml->GetElement("Ranking2nd")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking2nd")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Ranking2nd")->GetElement("Position")->GetElement("Z")->GetFloat();
	scl = xml->GetElement("Ranking2nd")->GetElement("Scale")->GetFloat();
	Ranking2nd = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Ranking2nd->Position = CVector3(posX, posY, posZ);
	Ranking2nd->Scale = CVector3(scl, scl, scl * zscl);
	// ランキング3位(ロゴ)
	_path = xml->GetElement("Ranking3rd")->GetElement("path")->GetString();
	posX = xml->GetElement("Ranking3rd")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking3rd")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Ranking3rd")->GetElement("Position")->GetElement("Z")->GetFloat();
	scl = xml->GetElement("Ranking3rd")->GetElement("Scale")->GetFloat();
	Ranking3rd = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Ranking3rd->Position = CVector3(posX, posY, posZ);
	Ranking3rd->Scale = CVector3(scl, scl, scl * zscl);
	// ランキング4位(ロゴ)
	_path = xml->GetElement("Ranking4th")->GetElement("path")->GetString();
	posX = xml->GetElement("Ranking4th")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking4th")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Ranking4th")->GetElement("Position")->GetElement("Z")->GetFloat();
	scl = xml->GetElement("Ranking4th")->GetElement("Scale")->GetFloat();
	Ranking4th = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Ranking4th->Position = CVector3(posX, posY, posZ);
	Ranking4th->Scale = CVector3(scl, scl, scl * zscl);
	// ランキング5位(ロゴ)
	_path = xml->GetElement("Ranking5th")->GetElement("path")->GetString();
	posX = xml->GetElement("Ranking5th")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking5th")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Ranking5th")->GetElement("Position")->GetElement("Z")->GetFloat();
	scl = xml->GetElement("Ranking5th")->GetElement("Scale")->GetFloat();
	Ranking5th = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Ranking5th->Position = CVector3(posX, posY, posZ);
	Ranking5th->Scale = CVector3(scl, scl, scl * zscl);

	// 描画リストに追加
	mainLayer->AddObject(SkyDome, RENDER_NORMAL);
	mainLayer->AddObject(ScoreLogo, RENDER_ALPHA);
	mainLayer->AddObject(RankingLogo, RENDER_ALPHA);
	mainLayer->AddObject(Ranking1st, RENDER_ALPHA);
	mainLayer->AddObject(Ranking2nd, RENDER_ALPHA);
	mainLayer->AddObject(Ranking3rd, RENDER_ALPHA);
	mainLayer->AddObject(Ranking4th, RENDER_ALPHA);
	mainLayer->AddObject(Ranking5th, RENDER_ALPHA);

	// カウンター初期化
	// 全てのカウンターに反映する値
	float interval = xml->GetElement("AllCounter")->GetElement("Interval")->GetFloat();
	float allscl = xml->GetElement("AllCounter")->GetElement("Scale")->GetFloat();
	// プレイング
	posX = xml->GetElement("Score")->GetElement("CounterPosition")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Score")->GetElement("CounterPosition")->GetElement("Y")->GetFloat();
	ScoreCounter = CCounter::CreateCounter();
	ScoreCounter->setPosition(posX, posY, 0);
	ScoreCounter->setInterval(interval);
	ScoreCounter->getImage()->Scale = CVector3(allscl, allscl, 0);
	// 1位
	posX = xml->GetElement("Ranking1st")->GetElement("CounterPosition")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking1st")->GetElement("CounterPosition")->GetElement("Y")->GetFloat();
	rank1Counter = CCounter::CreateCounter();
	rank1Counter->setPosition(posX, posY, 0);
	rank1Counter->setInterval(interval);
	rank1Counter->getImage()->Scale = CVector3(allscl, allscl, 0);
	// 2位
	posX = xml->GetElement("Ranking2nd")->GetElement("CounterPosition")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking2nd")->GetElement("CounterPosition")->GetElement("Y")->GetFloat();
	rank2Counter = CCounter::CreateCounter();
	rank2Counter->setPosition(posX, posY, 0);
	rank2Counter->setInterval(interval);
	rank2Counter->getImage()->Scale = CVector3(allscl, allscl, 0);
	// 3位
	posX = xml->GetElement("Ranking3rd")->GetElement("CounterPosition")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking3rd")->GetElement("CounterPosition")->GetElement("Y")->GetFloat();
	rank3Counter = CCounter::CreateCounter();
	rank3Counter->setPosition(posX, posY, 0);
	rank3Counter->setInterval(interval);
	rank3Counter->getImage()->Scale = CVector3(allscl, allscl, 0);
	// 4位
	posX = xml->GetElement("Ranking4th")->GetElement("CounterPosition")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking4th")->GetElement("CounterPosition")->GetElement("Y")->GetFloat();
	rank4Counter = CCounter::CreateCounter();
	rank4Counter->setPosition(posX, posY, 0);
	rank4Counter->setInterval(interval);
	rank4Counter->getImage()->Scale = CVector3(allscl, allscl, 0);
	// 5位
	posX = xml->GetElement("Ranking5th")->GetElement("CounterPosition")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Ranking5th")->GetElement("CounterPosition")->GetElement("Y")->GetFloat();
	rank5Counter = CCounter::CreateCounter();
	rank5Counter->setPosition(posX, posY, 0);
	rank5Counter->setInterval(interval);
	rank5Counter->getImage()->Scale = CVector3(allscl, allscl, 0);

	// カメラの設定
	posX = xml->GetElement("Camera")->GetElement("Offset")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Camera")->GetElement("Offset")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Camera")->GetElement("Offset")->GetElement("Z")->GetFloat();
	float _dist = xml->GetElement("Camera")->GetElement("Distance")->GetFloat();
	float _overhead = xml->GetElement("Camera")->GetElement("Overhead")->GetFloat();
	float _speed = xml->GetElement("Camera")->GetElement("Speed")->GetFloat();
	posZ *= _dist;
	CCameraThirdPersonSP tps = CCameraThirdPerson::Create();
	tps->setOffset(posX, posY, posZ);
	tps->setOverhead(_overhead);
	tps->setSpeed(_speed);
	posX = xml->GetElement("Camera")->GetElement("Target")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Camera")->GetElement("Target")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Camera")->GetElement("Target")->GetElement("Z")->GetFloat();
	tps->setLookAt(posX, posY, posZ);

	// カメラの同期
	Camera2D = mainLayer->Camera2D;
	Camera3D = mainLayer->Camera3D = tps;

	// スカイドームローラー
	float speed = xml->GetElement("SkyDome")->GetElement("RotateSpeed")->GetFloat();
	rotationSkyDome = CQuaternion(AXIS_Y, D3DXToRadian(speed));

	// BGM
	pathBGM = xml->GetElement("BGM")->GetString();
	CSoundManager::Load(pathBGM);

	xml = CWsbXml::LoadXmlFile("Resource/XML/RankData.xml");

	// プレイングスコア
	Score = CScenePlay::getScore();
	TotalScore = CScenePlay::getTotalScore();
	// ランキングスコアのロード
	for(int i = 0 ; i < xml->GetElement("Size")->GetInt(); i++)
		rankScores.push_back(xml->GetElement("Score", i )->GetInt());
	// 配列要素のソート
	std::sort(rankScores.begin(), rankScores.end());

	// プレイングスコアがランキングの最低スコアを上回っていた場合、最低スコアを上書き後ソート
	if(Score > rankScores[0])
		rankScores[0] = Score;
	std::sort(rankScores.begin(), rankScores.end());

	// ランキングスコアのセーブ
	CWsbXmlSP p = CWsbXml::CreateXml("root") ;
	int max = xml->GetElement("Size")->GetInt() ;
	for(int i = 0; i < max; i++)
		p->AddChild("Score", rankScores[max - i - 1]);
	
	p->AddChild("Size", max);
	p->SaveXmlFile("Resource/XML/RankData.xml");
}

void CSceneResult::destroyScene()
{
	SkyDome.reset();
	ScoreLogo.reset();
	RankingLogo.reset();
	Ranking1st.reset();
	Ranking2nd.reset();
	Ranking3rd.reset();
	Ranking4th.reset();
	Ranking5th.reset();
	mainLayer.reset();
}

void CSceneResult::updateScene()
{
	CCommand command = CreateCommand();
	// ○キー入力でタイトルに戻る
	if(command.Check(CCommand::CIRCLE))
		CSceneManager::setNextScene_(CSceneTitle::CreateScene());

	SkyDome->qRotation *= rotationSkyDome;
	Camera3D->Calculate();
}

void CSceneResult::renderScene()
{
	// 
	mainLayer->Render();
	// 描画先をバックバッファに戻す
	CGraphicsManager::setRenderTargetToBackBuffer();
	// 板ポリの描画
	mainLayer->board->Render(Camera2D.get());
	
	// カウンターの描画
	ScoreCounter->Render(CCounter::RIGHT_ALI, Score);
	rank1Counter->Render(CCounter::RIGHT_ALI, rankScores[4]);
	rank2Counter->Render(CCounter::RIGHT_ALI, rankScores[3]);
	rank3Counter->Render(CCounter::RIGHT_ALI, rankScores[2]);
	rank4Counter->Render(CCounter::RIGHT_ALI, rankScores[1]);
	rank5Counter->Render(CCounter::RIGHT_ALI, rankScores[0]);
}

void CSceneResult::PlayBGM()
{
	(bgm == 0) ? bgm = CSoundManager::Play(pathBGM, CSoundManager::MODE_LOOP) : CSoundManager::Play(bgm) ;
}

void CSceneResult::StopBGM()
{
	CSoundManager::Stop(bgm);
}