#pragma once

#include "../Scene.h"
#include "../../../Library/Library.h"

// リザルトシーンクラス
class CSceneResult : public CScene
{
public :
	// デストラクタ
	~CSceneResult() { }

	// 生成
	static CSceneSP CreateScene();
	// 初期化処理
	void initializeScene();
	// 終了処理
	void destroyScene();
	// 更新処理
	void updateScene();
	// 描画処理
	void renderScene();
	// BGM再生関数
	void PlayBGM();
	// BGM停止関数
	void StopBGM();

private :
	enum RESULT_STATE {
		// スコア表示
		SCORE,
		RANKING,
		STATE_MAX
	};
	// 回転
	CQuaternion rotationSkyDome;
	// 背景
	CGRendererSP SkyDome;
	// プレイングスコア(ロゴ)
	CGRendererSP ScoreLogo;
	// プレイングスコア
	int Score;
	int TotalScore;
	// プレイ時スコア描画カウンター
	CCounterSP ScoreCounter;
	// ランキング画像
	CGRendererSP RankingLogo;
	CGRendererSP Ranking1st;
	CGRendererSP Ranking2nd;
	CGRendererSP Ranking3rd;
	CGRendererSP Ranking4th;
	CGRendererSP Ranking5th;
	// ランキングスコア
	std::vector<int> rankScores;
	// ランキングスコア描画カウンター
	CCounterSP rank1Counter;
	CCounterSP rank2Counter;
	CCounterSP rank3Counter;
	CCounterSP rank4Counter;
	CCounterSP rank5Counter;

	// コンストラクタ
	CSceneResult();

protected :
	// コマンドの生成
	CCommand CreateCommand();

};