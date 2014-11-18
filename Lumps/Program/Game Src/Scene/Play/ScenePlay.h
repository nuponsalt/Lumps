#pragma once

#include "../Scene.h"
#include <memory>
#include "../../Object/Sphere/Sphere.h"
#include "../../Object/Sphere/Player/Player.h"

typedef std::shared_ptr<CTreeObject<Sphere>> SphereTreeObjSP;
typedef std::weak_ptr<CTreeObject<Sphere>> SphereTreeObjWP;

// プレイシーンクラス
class CScenePlay : public CScene
{
public :
	// デストラクタ
	~CScenePlay() { }

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
	
	// 取得 : スコア
	static inline float getScore() { return ScoreVolume; }
	static inline float getTotalScore() { return TotalScoreVolume; }

private :
	// ポーズメニューの種類
	enum PauseMenuType {
		// ゲームを続ける
		PAUSE_CONTINUE,
		// メインメニューに戻る
		PAUSE_MAINMENU,
		// メニューの数
		PAUSE_MAX
	};
	// シーケンス
	enum SEQ_TYPE {
		SEQ_BEGIN,
		SEQ_MAIN,
		SEQ_PAUSE,
		SEQ_END,
		SEQ_MAX
	};
	// シーケンス状態
	SEQ_TYPE SequenceState;

	// 終了カウント
	int EndCounter;
	// 終了する時間
	int EndCount;

	// ミニマップレイヤー
	CLayerSP minimapLayer;

	// ポーズ画像
	CGPlaneSP PauseImage;
	// スカイドーム
	CGRendererSP SkyDome;
	// 地面最下段
	CGRendererSP UnderGround;
	// 壁
	CGRendererSP Wall;
	// 線分衝突判定(std::vector)
	std::vector<Segment> segs;
	// ミニマップ背景
	CGPlaneSP minimapBack;

	// スタート, タイムアップロゴ
	CGRendererSP StartLogo, TimeupLogo;
	// 境界線
	float BorderLine;
	// アルファ加算値
	float AddAlpha;
	// 進行方向
	CVector3 Direct;

	// 物体出現時間
	CTimerSP PopTimer;
	// プレイヤー
	CPlayerSP Player;
	// テスト用
	std::list<CSphereSP> FallList;
	// 野生のオブジェクトリスト
	std::list<CSphereWP> NativeList;
	// 塊になっているオブジェクトリスト
	std::vector<CSphereWP> Links;

	// 描画数
	int renderNum;

	// 制限時間
	int TimeLimit;
	// 制限時間計算用タイマー
	CTimerSP CompTimer;
	// 制限時間描画用カウンター
	CCounterSP TimeCounter;
	// スコア(くっつけた体積)
	float Score;
	static float ScoreVolume;
	// スコア(総合体積)
	static float TotalScoreVolume;
	// サイズ表記描画用カウンター
	CCounterSP SizeCounter;
	// UI画像
	CSpriteSP UI, ScoreUI;
	
	// SE
	std::string pathBackTitleSE, pathGoodSE, pathBadSE;
	bool isPlay; // 再生フラグ
	CTimerSP resetTimer; // フラグリセット用タイマー

	// コンストラクタ
	CScenePlay() ;

	//* UI *//
	// ユーザーインターフェースの初期化
	void initializeUI();
	// ユーザーインターフェースの更新
	void updateUI();
	// ユーザーインターフェースの描画
	void renderUI();

	// デバッグ描画
	void renderDebug();

	//* オブジェクト *//
	// 落下物の生成
	void CreateFall(CSphereSP _obj);
	// 自動生成(時間経過) : ランダム座標(ZX)
	void PopObjectRandom();
	// 塊の更新
	void subupdateLinks();
	// 壁衝突時の補正
	void correctWall();

	// xmlからのパラメーター読み込み
	void initializeObjects();
	// オブジェクトの更新
	void updateObjects();

	//* シーン内シーケンス管理 *//
	// シーケンス関数ポインタ配列
	bool (CScenePlay::*Sequence[SEQ_MAX])(CCommand &command);
	// シーケンス : 開始
	bool SequenceBegin(CCommand &command);
	// シーケンス : プレイ
	bool SequenceMain(CCommand &command);
	// シーケンス : ポーズ
	bool SequencePause(CCommand &command);
	// シーケンス : 終了
	bool SequenceEnd(CCommand &command);

protected :
	// コマンドの生成
	CCommand CreateCommand();

} ;