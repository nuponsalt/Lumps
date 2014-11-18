// プリコンパイル済みヘッダー読み込み
#include "DXUT.h"
#include "ScenePlay.h"

#include "../../Object/Sphere/Player/Player.h"
#include "../../Define.h"
#include "../Transition.h"
#include "../../../Library/Library.h"
#include "../SceneManager.h"
#include "../Title/SceneTitle.h"
#include "../Result/SceneResult.h"
#include "../../Effect/AnimationEffect.h"

float CScenePlay::ScoreVolume = 0;
float CScenePlay::TotalScoreVolume = 0;

CScenePlay::CScenePlay() : Score(0), isPlay(true), EndCounter(0), renderNum(0) { }

CSceneSP CScenePlay::CreateScene()
{
	return CSceneSP(new CScenePlay());
}

void CScenePlay::destroyScene()
{
	PauseImage.reset();
	SkyDome.reset();
	UnderGround.reset();
	Wall.reset();
	StartLogo.reset();
	TimeupLogo.reset();
	PopTimer.reset();
	Player.reset();
	CompTimer.reset();
	TimeCounter.reset();
	SizeCounter.reset();
	UI.reset();
	FallList.clear();
	NativeList.clear();
	Links.clear();
	mainLayer.reset();
	minimapLayer.reset();
	CAnimationEffect::DestroyEffect();
}

CCommand CScenePlay::CreateCommand()
{
	CCommand command;
	// 入力制限時は入力受付なし
	if(CSceneManager::getisKeyLock_()) 
		return command;
	// STARTキー
	if(DXUTWasKeyPressed('P')
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::PAD_BTN_10))
		command.Add(CCommand::START);
	// 非ポーズ時はこれより下の入力は受け付けない
	if(!CSceneManager::getisPause_())	
		return command;
	// 上キー
	int move = 0;
	if (DXUTIsKeyDown(VK_UP) || DXUTIsKeyDown('W')
		||CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_UP) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_LEFT_UP) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_UP_RIGHT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::STICK_UP))	
		move |= CCommand::UP;
	// 下キー
	if (DXUTIsKeyDown(VK_DOWN) || DXUTIsKeyDown('S')
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_DOWN) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_DOWN_LEFT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_RIGHT_DOWN) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::STICK_DOWN))
		move |= CCommand::DOWN;
	// コマンドの追加
	command.Add(move);
	// ○キー
	if(DXUTWasKeyPressed('Z') || DXUTWasKeyPressed(VK_RETURN)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::PAD_BTN_2))
		command.Add(CCommand::CIRCLE);
	// ✕キー
	if(DXUTWasKeyPressed('X')
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::PAD_BTN_3))
		command.Add(CCommand::CROSS);

	return command;
}

void CScenePlay::initializeScene()
{
	// シーケンスを関数ポインタで管理
	Sequence[SEQ_BEGIN] = &CScenePlay::SequenceBegin;
	Sequence[SEQ_MAIN] = &CScenePlay::SequenceMain;
	Sequence[SEQ_PAUSE] = &CScenePlay::SequencePause;
	Sequence[SEQ_END] = &CScenePlay::SequenceEnd;
	
	// 最初のシーケンス
	SequenceState = SEQ_BEGIN;

	// 各パラメーター初期化
	initializeObjects();
	
	// ユーザーインターフェース初期化
	initializeUI();
}

bool CScenePlay::SequenceBegin(CCommand &command)
{
	// トランジションが終了したら
	if(!CTransition::IsExistTransition())
	{
		if(!CSceneManager::getisKeyLock_())
			CSceneManager::LockKey();

		++Count;
	}
	// ゲームオブジェクト更新
	updateObjects();
	
	if(Count > 60 && StartLogo->vColorRGBA.w < 1)
		StartLogo->vColorRGBA.w += AddAlpha / 255;

	// ゲームカウントが一定値に到達した場合
	if(Count > 180)
		--StartLogo->Position.z;

	if(StartLogo->Position.z < BorderLine)
	{
		CSceneManager::UnLockKey();
		StartLogo->isRender = false;
		// メインシーケンス移行
		SequenceState = SEQ_MAIN;
	}

	// 正常終了
	return false ;
}

bool CScenePlay::SequenceMain(CCommand &command)
{
	CVector3 pos = Player->getCamera()->getEye();
	TimeupLogo->Position = CVector3(pos.x * 1.5f, pos.y, pos.z * 1.5f);
	TimeupLogo->qRotation = Player->getFrontRotation();
	
	// ゲームオブジェクト更新
	updateObjects();
	// UIの更新
	updateUI();
	// ランダムな生成
	PopObjectRandom();
	if(command.Check(CCommand::START))
		CSceneManager::Pause_();
	// ポーズ画像の描画
	PauseImage->isRender = (CSceneManager::getisPause_()) ? true : false;		

	if(CSceneManager::getisPause_())
		SequenceState = SEQ_PAUSE;

	if(TimeLimit <= 0)
	{
		CSceneManager::LockKey();
		Direct = Normalize(CVector3((TimeupLogo->Position - Player->Transform.Position).x, 0, (TimeupLogo->Position - Player->Transform.Position).z));
		TimeupLogo->isRender = true;
		SequenceState = SEQ_END;
	}

	Count++;

	// 正常動作
	return false;
}

bool CScenePlay::SequencePause(CCommand &command)
{
	// スタート入力検知
	if(command.Check(CCommand::START))
		CSceneManager::UnPause_();
	// ○ボタン入力検知
	if(command.Check(CCommand::CIRCLE))
	{
		CSoundManager::Play(pathBackTitleSE, CSoundManager::MODE_ONCE);
		CSceneManager::setNextScene_(CSceneTitle::CreateScene());
	}

	if(!CSceneManager::getisPause_())
		SequenceState = SEQ_MAIN;

	Count++;

	return false;
}

bool CScenePlay::SequenceEnd(CCommand &command)
{
	// ゲームオブジェクト更新
	updateObjects();
	
	TimeupLogo->Position -= Direct;

	if(EndCounter == EndCount)
		CSceneManager::setNextScene_(CSceneResult::CreateScene());

	Count++;
	EndCounter++;

	return false;
}

void CScenePlay::updateScene()
{
	// コマンド生成
	CCommand command = CreateCommand();
	// 正常に動作してるか判定を受け取る
	bool success = (this->*Sequence[SequenceState])(command);
	// 異常動作発生で強制終了
	if(success) PostQuitMessage(WM_QUIT);	
	// フレームレートの取得
	updateFPS = updateFPSCount.getFrameRate_();
}

void CScenePlay::renderDebug()
{
	Text->drawText(10, 10, D3DCOLOR_ARGB(255,255,0,0), L"GameTime = %d", Count);
	Text->drawText(10, 30, D3DCOLOR_ARGB(255,255,0,0), L"UpdateFPS : %2.5f", updateFPS);
	Text->drawText(10, 50, D3DCOLOR_ARGB(255,255,0,0), L"RenderFPS : %2.5f", renderFPS);
	Text->drawText(10, 70, D3DCOLOR_ARGB(255,255,0,0), L"FallsNumber : %d", FallList.size());
	Text->drawText(10, 90, D3DCOLOR_ARGB(255,255,0,0), L"RenderNumber : %d", renderNum);
}

void CScenePlay::renderScene()
{
	// レイヤーの描画
	mainLayer->Render();
	minimapLayer->Render();
	// バックバッファにレンダーターゲットを設定
	CGraphicsManager::setRenderTargetToBackBuffer();
	// レイヤーテクスチャーの貼られた板ポリの描画
	mainLayer->board->Render(Camera2D.get());
	minimapLayer->board->Render(Camera2D.get());
	// UIの描画
	renderUI();
#ifdef _DEBUG
	// デバッグ描画
	renderDebug();
#endif
	renderFPS = renderFPSCount.getFrameRate_();
}

void CScenePlay::PlayBGM()
{
	(bgm == 0) ? bgm = CSoundManager::Play(pathBGM, CSoundManager::MODE_LOOP) : CSoundManager::Play(bgm);
}

void CScenePlay::StopBGM()
{
	CSoundManager::Stop(bgm);
}