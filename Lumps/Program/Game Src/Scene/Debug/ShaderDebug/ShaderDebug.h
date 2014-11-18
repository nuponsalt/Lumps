#pragma once

#include "../../Scene.h"

#include "../../../Camera/CameraThirdPerson.h"

class CShaderDebug : public CScene
{
public :
	// デストラクタ
	~CShaderDebug() { }

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
	CCameraThirdPersonSP camera;
	CGRendererSP Back;
	CGRendererSP Object;
	CPointSpriteSP particle;
	float speed;

	// コンストラクタ
	CShaderDebug();

protected :
	// コマンド生成
	CCommand CreateCommand();

};