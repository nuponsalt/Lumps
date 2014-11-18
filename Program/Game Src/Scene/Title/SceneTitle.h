#pragma once

#include "../Scene.h"
#include <memory>
#include "../../Object/Sphere/Sphere.h"

// タイトルシーンクラス
class CSceneTitle : public CScene
{
public :
	// デストラクタ
	~CSceneTitle() { }

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
	// メニュータイプ
	enum MENU_TYPE{
		// プレイ選択
		MENU_PLAY,
		// 終了選択
		MENU_EXIT,
		// メニュー最大数
		MENU_MAX
	};
	// メニュー表示フラグ
	bool isBrowseMenu;
	// 選択状態
	int stateMenu;
	// カメラ注視座標
	CVector3 Target[MENU_MAX+1];
	int TargetState;
	// 回転
	CQuaternion RotationAxisY, RotationAxisX;
	CQuaternion rotationSkyDome;
	// 背景
	CGRendererSP BackGround;
	// タイトルロゴ(3Dモデル, 一文字ずつ個別にコントロールする)
	CGRendererSP titleL;
	CGRendererSP titleU;
	CGRendererSP titleM;
	CGRendererSP titleP;
	CGRendererSP titleS;
	// 選択モデル : プレイ
	CGRendererSP UnPress;
	CGRendererSP playModel;
	CGPlaneSP playLogo;
	CGRendererSP exitModel;
	CGPlaneSP exitLogo;

	// SE
	std::string pathSelectSE;
	std::string pathDecideSE;
	std::string pathCancelSE;

	// コンストラクタ
	CSceneTitle();
	// パラメータの反映
	void appllyParameter();

protected :
	// コマンドの生成
	CCommand CreateCommand();

};