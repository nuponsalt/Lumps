#pragma once

#include "../../Scene.h"

class CTerrainDebug : public CScene
{
public :
	// デストラクタ
	~CTerrainDebug() { }

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
	// 地形モデル
	CGRendererSP Terrain;
	// 衝突判定テストモデル
	CGRendererSP Object;
	// 最下段の地面
	float deadline;
	// 重力
	float gravity;

	// コンストラクタ
	CTerrainDebug();

protected :
	// コマンド生成
	CCommand CreateCommand();

};