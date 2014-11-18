#pragma once

// シーン関連オブジェクト

#include "../../Library/Library.h"
#include <memory>
using namespace KMT;

class CCommand;

class CScene;
typedef std::shared_ptr<CScene> CSceneSP;

// シーンタイプの列挙型
enum SceneType
{
	Title,
	Play,
	Result,
	SceneTypeMax
};

// デバッグ専用シーンタイプの列挙型
enum DebugSceneType
{
	BSP,
	BSPlink,
	Shader,
	Terrain,
	Shadow,
	DebugSceneTypeMax
};

class CScene
{
public :
	// ゲーム全体で使うカメラ（バックバッファ描画用）
	static CCameraSP Camera3D;
	static CCameraSP Camera2D;

	// コンストラクタ
	CScene();
	// デストラクタ
	virtual ~CScene();

	// 終了
	virtual void destroyScene() = 0;
	// 初期化
	virtual void initializeScene() = 0;
	// シーン毎の更新処理
	virtual void updateScene() = 0;
	// シーン毎の描画処理
	virtual void renderScene() = 0;
	// BGM再生関数
	virtual void PlayBGM() = 0;
	// BGM停止関数
	virtual void StopBGM() = 0;

protected :
	// メイン描画のレイヤー
	CLayerSP mainLayer;
	// 選択状態
	int State;
	// 現在シーン突入してからの総時間
	size_t Count;
	// デバッグ表示テキスト(複数使い回し可能)
	CDebugTextSP Text;
	// BGM
	std::string pathBGM;
	int bgm;
	// フレームレート
	CFrameRateCounter updateFPSCount, renderFPSCount;
	float updateFPS, renderFPS;

	// コマンドの生成
	virtual CCommand CreateCommand() = 0;

};