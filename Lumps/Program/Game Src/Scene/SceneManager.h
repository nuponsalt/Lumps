#pragma once

#include "Scene.h"

// シーン管理マネージャー
class CSceneManager
{
public :
	// 初期化
	static void Initialize_();
	// 全てのロジック処理
	static void Update_();
	// 全ての描画処理
	static void Render_();
	// 終了
	static void Destroy_();
	// キー操作制限フラグ取得関数
	static const bool getisKeyLock_() { return isKeyLock; }
	// 取得 : ポーズフラグ
	static const bool getisPause_() { return isPause; }
	// キー操作制限関数
	static void LockKey() { isKeyLock = true; }
	// キー操作制限解除関数
	static void UnLockKey() { isKeyLock = false; }
	// ポーズ
	static void Pause_() { isPause = true; }
	// ポーズ解除
	static void UnPause_() { isPause = false; }
	// 次のシーンをセットする関数
	// arg1..次のシーンのインスタンス
	static void setNextScene_(const CSceneSP _scene);

private :
	// 現在のシーン
	static CSceneSP Scene;
	// 次のシーン
	static CSceneSP NextScene;
	// キー操作制限用
	static bool isKeyLock;
	// ポーズ
	static bool isPause;
	
	// コンストラクタ
	CSceneManager() { } 
	// デストラクタ
	~CSceneManager() { }

	// シーン遷移
	static void ChangeScene();
	// シーン遷移処理関数
	static void TransitionScene();

protected :
	// シーン生成
	static CSceneSP CreateScene(const SceneType& _element);
	// シーン生成(デバッグ用シーン)
	static CSceneSP CreateDebugScene(const DebugSceneType& _element);


};