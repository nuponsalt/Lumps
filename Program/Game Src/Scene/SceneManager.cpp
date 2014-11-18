#include "DXUT.h"
#include "SceneManager.h"

#include "Transition.h"
#include "Title/SceneTitle.h"
#include "Play/ScenePlay.h"
#include "Result/SceneResult.h"
#include "Debug/BSPDebug/QTreeDebug.h"
#include "Debug/ShaderDebug/ShaderDebug.h"
#include "Debug/TerrainDebug/TerrainDebug.h"

CSceneSP CSceneManager::Scene;
CSceneSP CSceneManager::NextScene;

bool CSceneManager::isKeyLock;
bool CSceneManager::isPause;

void CSceneManager::Initialize_()
{
	Scene = CreateScene(SceneType::Play);
	//Scene = CreateDebugScene(DebugSceneType::Shader);
	// 最初のシーンの初期化
	Scene->initializeScene();
	// 次のシーンは空に
	NextScene = NULL;
	// 自由に操作可能
	isKeyLock = false;
	// 非ポーズ状態
	isPause = false;

// リリースビルド時
#if !_DEBUG
	// BGM再生
	Scene->PlayBGM();
#endif

	// トランジション初期化
	CTransition::initializeTransition();
}

void CSceneManager::Destroy_()
{
	// トランジションマネージャーの解放
	CTransition::Destroy();
	// 現在のシーンのパラメータ破棄
	Scene->destroyScene();
	// 現在のシーンの解放
	Scene.reset();
	// 次のシーンがセットされていた場合、それも解放する
	if(NextScene != NULL) NextScene.reset();
}

void CSceneManager::Update_()
{
	// トランジションが生成されていれば、シーン遷移関数を呼ぶ
	if(CTransition::IsExistTransition()) TransitionScene();
	// 現在のシーンの更新呼び出し
	Scene->updateScene();
}

void CSceneManager::Render_()
{
	// 全シーン用のカメラの更新
	if(CScene::Camera3D != NULL) CScene::Camera3D->updateView();
	if(CScene::Camera2D != NULL) CScene::Camera2D->updateView();
	// 現在のシーンの描画呼び出し
	Scene->renderScene();
	// トランジションの描画呼び出し
	CTransition::Render();
}

void CSceneManager::setNextScene_(const CSceneSP _scene)
{
	// 次のシーンを設定
	NextScene = _scene;
	// トランジション生成
	CTransition::CreateTransition();
}

CSceneSP CSceneManager::CreateScene(const SceneType& elem)
{
	// 対応するシーンが生成される
	return (elem == SceneType::Title) ? CSceneTitle::CreateScene() : (elem == SceneType::Play) ? CScenePlay::CreateScene() : CSceneResult::CreateScene();
}

CSceneSP CSceneManager::CreateDebugScene(const DebugSceneType& elem)
{
	// 対応するシーンが生成される
	return (elem == DebugSceneType::BSP) ? QTreeDebug::CreateScene() 
		: (elem == DebugSceneType::BSPlink) ? QTreeDebug_::CreateScene()
		: (elem == DebugSceneType::Shader) ? CShaderDebug::CreateScene()
		: CTerrainDebug::CreateScene();
}

void CSceneManager::ChangeScene()
{
	// BGMを停止
	Scene->StopBGM();	
	// 現在のシーンを破棄
	Scene->destroyScene();
	// シーンの入れ替え
	Scene = NextScene;
	// 入れ替わったシーンの初期化
	Scene->initializeScene();

// リリースビルド時
#if !_DEBUG
	// BGMを再生
	Scene->PlayBGM();
#endif

	// 設定していた遷移先を空にする
	NextScene = NULL;
}

void CSceneManager::TransitionScene()
{
	// キー操作制限
	LockKey();
	// フェードアウト開始
	// 次のシーンがセットされていて、なおかつフェードアウトが完了していれば、シーン入れ替え関数を呼ぶ
	if(NextScene != NULL && CTransition::FadeOut()) ChangeScene();
	// フェードイン開始
	// フェードインが完了したら、トランジションを解放する
	if(NULL == NextScene && CTransition::FadeIn()){
		CTransition::DestroyTransition();
		UnLockKey();
		UnPause_();
	}
}