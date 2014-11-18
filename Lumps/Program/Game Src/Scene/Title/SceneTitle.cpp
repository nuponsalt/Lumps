// プリコンパイル済みヘッダー読み込み
#include "DXUT.h"
#include "SceneTitle.h"
#include "../Play/ScenePlay.h"
#include "../Result/SceneResult.h"
#include "../SceneManager.h"
//
#include "../Transition.h"
#include "../../Camera/CameraThirdPerson.h"
#include "../../Define.h"

CSceneTitle::CSceneTitle()
{}

CSceneSP CSceneTitle::CreateScene()
{
	return CSceneSP(new CSceneTitle());
}

CCommand CSceneTitle::CreateCommand()
{
	CCommand command;
	if(CSceneManager::getisKeyLock_())
		return command;
	int move = 0;
	// 左方向入力
	if (DXUTWasKeyPressed(VK_LEFT)
		||CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::CROSS_LEFT)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::CROSS_LEFT_UP)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::CROSS_DOWN_LEFT)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::STICK_LEFT))
		move |= CCommand::LEFT;
	// 右方向入力
	if (DXUTWasKeyPressed(VK_RIGHT)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::CROSS_RIGHT)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::CROSS_RIGHT_DOWN)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::CROSS_UP_RIGHT)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::STICK_RIGHT))
		move |= CCommand::RIGHT;
	// 移動コマンド追加
	command.Add(move);
	// ○キー入力
	if(DXUTWasKeyPressed('Z') || DXUTWasKeyPressed(VK_RETURN)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::PAD_BTN_2))
		command.Add(CCommand::CIRCLE);
	// ✕キー入力
	if(DXUTWasKeyPressed('X') || DXUTWasKeyPressed(VK_BACK)
		|| CJoyPadManager::IsKeyTrigger(0, CJoyPadManager::PAD_BTN_3))
		command.Add(CCommand::CROSS);

	return command;
}

void CSceneTitle::initializeScene()
{
	// XMLファイル読み込み
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Title/SceneTitle.xml");
	
	// オフスクリーンレンダリング
	mainLayer = CLayer::CreateLayer(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainLayer->board->Position.y = 0.0f;
	
	// 背景(スカイドーム)
	std::string _path = xml->GetElement("BackGround")->GetElement("Path")->GetString();
	float posX = xml->GetElement("BackGround")->GetElement("Position")->GetElement("X")->GetFloat();
	float posY = xml->GetElement("BackGround")->GetElement("Position")->GetElement("Y")->GetFloat();
	float posZ = xml->GetElement("BackGround")->GetElement("Position")->GetElement("Z")->GetFloat();
	BackGround = CGRenderer::CreateFromX(_path, CShaderNormal::CreateShader());
	BackGround->Position = CVector3(posX, posY, posZ);
	// タイトルロゴ
	// L
	_path = xml->GetElement("TitleLogo")->GetElement("L")->GetElement("Path")->GetString();
	posX = xml->GetElement("TitleLogo")->GetElement("L")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("TitleLogo")->GetElement("L")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("TitleLogo")->GetElement("L")->GetElement("Position")->GetElement("Z")->GetFloat();
	float Size = xml->GetElement("TitleLogo")->GetElement("Size")->GetFloat();
	titleL = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	titleL->Position = CVector3(posX, posY, posZ);
	// u
	_path = xml->GetElement("TitleLogo")->GetElement("u")->GetElement("Path")->GetString();
	posX = xml->GetElement("TitleLogo")->GetElement("u")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("TitleLogo")->GetElement("u")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("TitleLogo")->GetElement("u")->GetElement("Position")->GetElement("Z")->GetFloat();
	titleU = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	titleU->Position = CVector3(posX, posY, posZ);
	// m
	_path = xml->GetElement("TitleLogo")->GetElement("m")->GetElement("Path")->GetString();
	posX = xml->GetElement("TitleLogo")->GetElement("m")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("TitleLogo")->GetElement("m")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("TitleLogo")->GetElement("m")->GetElement("Position")->GetElement("Z")->GetFloat();
	titleM = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	titleM->Position = CVector3(posX, posY, posZ);
	// p
	_path = xml->GetElement("TitleLogo")->GetElement("p")->GetElement("Path")->GetString();
	posX = xml->GetElement("TitleLogo")->GetElement("p")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("TitleLogo")->GetElement("p")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("TitleLogo")->GetElement("p")->GetElement("Position")->GetElement("Z")->GetFloat();
	titleP = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	titleP->Position = CVector3(posX, posY, posZ);
	// s
	_path = xml->GetElement("TitleLogo")->GetElement("s")->GetElement("Path")->GetString();
	posX = xml->GetElement("TitleLogo")->GetElement("s")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("TitleLogo")->GetElement("s")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("TitleLogo")->GetElement("s")->GetElement("Position")->GetElement("Z")->GetFloat();
	titleS = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	titleS->Position = CVector3(posX, posY, posZ);
	// タイトルロゴのサイズ統一
	titleL->Scale = titleU->Scale = titleM->Scale = titleP->Scale = titleS->Scale *= Size;
	// 無入力状態時表示モデル
	_path = xml->GetElement("UnPress")->GetElement("Path")->GetString();
	posX = xml->GetElement("UnPress")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("UnPress")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("UnPress")->GetElement("Position")->GetElement("Z")->GetFloat();
	Size = xml->GetElement("UnPress")->GetElement("Size")->GetFloat();
	UnPress = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	UnPress->Position = CVector3(posX, posY, posZ);
	UnPress->Scale *= Size;
	// 選択モデル : プレイ
	/*モデル*/
	_path = xml->GetElement("PlaySelect")->GetElement("Model")->GetElement("Path")->GetString();
	posX = xml->GetElement("PlaySelect")->GetElement("Model")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("PlaySelect")->GetElement("Model")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("PlaySelect")->GetElement("Model")->GetElement("Position")->GetElement("Z")->GetFloat();
	Size = xml->GetElement("PlaySelect")->GetElement("Model")->GetElement("Size")->GetFloat();
	playModel = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	playModel->Position = CVector3(posX, posY, posZ);
	playModel->Scale *= Size;
	/*ロゴ*/
	_path = xml->GetElement("PlaySelect")->GetElement("Logo")->GetElement("Path")->GetString();
	posX = xml->GetElement("PlaySelect")->GetElement("Logo")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("PlaySelect")->GetElement("Logo")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("PlaySelect")->GetElement("Logo")->GetElement("Position")->GetElement("Z")->GetFloat();
	Size = xml->GetElement("PlaySelect")->GetElement("Logo")->GetElement("Size")->GetFloat();
	playLogo = CGPlane::CreateFromTexture(_path);
	playLogo->Position = CVector3(posX, posY, posZ);
	playLogo->Scale *= Size;
	playLogo->isBillBoard = true;
	// 選択モデル : 終了
	/*モデル*/
	_path = xml->GetElement("ExitSelect")->GetElement("Model")->GetElement("Path")->GetString();
	posX = xml->GetElement("ExitSelect")->GetElement("Model")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("ExitSelect")->GetElement("Model")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("ExitSelect")->GetElement("Model")->GetElement("Position")->GetElement("Z")->GetFloat();
	Size = xml->GetElement("ExitSelect")->GetElement("Model")->GetElement("Size")->GetFloat();
	exitModel = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	exitModel->Position = CVector3(posX, posY, posZ);
	exitModel->Scale *= Size;
	/*ロゴ*/
	_path = xml->GetElement("ExitSelect")->GetElement("Logo")->GetElement("Path")->GetString();
	posX = xml->GetElement("ExitSelect")->GetElement("Logo")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("ExitSelect")->GetElement("Logo")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("ExitSelect")->GetElement("Logo")->GetElement("Position")->GetElement("Z")->GetFloat();
	Size = xml->GetElement("ExitSelect")->GetElement("Logo")->GetElement("Size")->GetFloat();
	exitLogo = CGPlane::CreateFromTexture(_path);
	exitLogo->Position = CVector3(posX, posY, posZ);
	exitLogo->Scale *= Size;
	exitLogo->isBillBoard = true;

	// レンダーリストに追加
	mainLayer->AddObject(BackGround, RENDER_NORMAL);
	mainLayer->AddObject(titleL, RENDER_NORMAL);
	mainLayer->AddObject(titleU, RENDER_NORMAL);
	mainLayer->AddObject(titleM, RENDER_NORMAL);
	mainLayer->AddObject(titleP, RENDER_NORMAL);
	mainLayer->AddObject(titleS, RENDER_NORMAL);
	mainLayer->AddObject(UnPress, RENDER_NORMAL);
	mainLayer->AddObject(playModel, RENDER_NORMAL);
	mainLayer->AddObject(playLogo, RENDER_ALPHA);
	mainLayer->AddObject(exitModel, RENDER_NORMAL);
	mainLayer->AddObject(exitLogo, RENDER_ALPHA);
	
	// カメラ座標
	posX = xml->GetElement("Camera3D")->GetElement("Offset")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Camera3D")->GetElement("Offset")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Camera3D")->GetElement("Offset")->GetElement("Z")->GetFloat();
	float _dist = xml->GetElement("Camera3D")->GetElement("Distance")->GetFloat();
	float _overhead = xml->GetElement("Camera3D")->GetElement("Overhead")->GetFloat();
	float _speed = xml->GetElement("Camera3D")->GetElement("Speed")->GetFloat();
	posZ *= _dist;
	CCameraThirdPersonSP tpscam = CCameraThirdPerson::Create();
	tpscam->setOffset(posX, posY, posZ);
	tpscam->setOverhead(_overhead);
	tpscam->setSpeed(_speed);
	// 注視座標
	for(int i = 0; i < 3; i++){
		Target[i].x = xml->GetElement("Target")->GetElement("Position", i)->GetElement("X")->GetFloat();
		Target[i].y = xml->GetElement("Target")->GetElement("Position", i)->GetElement("Y")->GetFloat();
		Target[i].z = xml->GetElement("Target")->GetElement("Position", i)->GetElement("Z")->GetFloat();
	}
	
	TargetState = xml->GetElement("FirstState")->GetInt();

	// 共通ローラー
	// Y軸
	_speed = xml->GetElement("RotateSpeed")->GetFloat();
	RotationAxisY = CQuaternion(AXIS_Y, D3DXToRadian(_speed));
	// X軸
	// 背景スカイドームローラー
	_speed = xml->GetElement("BackGround")->GetElement("rotSpeed")->GetFloat();
	rotationSkyDome = CQuaternion(AXIS_Y, D3DXToRadian(_speed)) * CQuaternion(AXIS_X, D3DXToRadian(_speed));
	
	// メニュー表示フラグ
	isBrowseMenu = false;
	// 選択状態
	stateMenu = xml->GetElement("SelectState")->GetInt();
	
	// BGMファイルの読み込み
	pathBGM = xml->GetElement("BGM")->GetString();
	CSoundManager::Load(pathBGM);
	// SEファイルの読み込み
	pathSelectSE = xml->GetElement("SE")->GetElement("select")->GetString();
	CSoundManager::Load(pathSelectSE);
	pathDecideSE = xml->GetElement("SE")->GetElement("decide")->GetString();
	CSoundManager::Load(pathDecideSE);
	pathCancelSE = xml->GetElement("SE")->GetElement("cancel")->GetString();
	CSoundManager::Load(pathCancelSE);

	// カメラの同期
	Camera3D = mainLayer->Camera3D = tpscam;
	Camera2D = mainLayer->Camera2D;
}

void CSceneTitle::destroyScene()
{
	BackGround.reset();
	titleL.reset();
	titleU.reset();
	titleM.reset();
	titleP.reset();
	titleS.reset();
	UnPress.reset();
	playModel.reset();
	playLogo.reset();
	exitModel.reset();
	exitLogo.reset();
	mainLayer.reset();
}

void CSceneTitle::updateScene()
{
	if (!CTransition::IsExistTransition())
	{
		// コマンド生成
		CCommand command = CreateCommand();
		/// デバッグ時
#if _DEBUG
		if(DXUTWasKeyPressed('D'))
			CSceneManager::setNextScene_(CScenePlay::CreateScene());
		if(DXUTWasKeyPressed('S'))
			CSceneManager::setNextScene_(CSceneResult::CreateScene());
#endif
		// メニュー表示状態で
		if(isBrowseMenu)
		{
			if(command.Check(CCommand::LEFT))
			{
				CSoundManager::Play(pathSelectSE, CSoundManager::MODE_ONCE);
				if(MENU_PLAY == stateMenu)
					stateMenu = MENU_EXIT;
				else
					--stateMenu;
			}
			if(command.Check(CCommand::RIGHT))
			{
				CSoundManager::Play(pathSelectSE, CSoundManager::MODE_ONCE);
				if(MENU_EXIT == stateMenu)
					stateMenu = MENU_PLAY;
				else
					++stateMenu;
			}
			// ○操作
			if(command.Check(CCommand::CIRCLE))
			{
				switch(stateMenu)
				{
					// ゲームスタート
				case MENU_PLAY :
					CSoundManager::Play(pathDecideSE, CSoundManager::MODE_ONCE);
					CSceneManager::setNextScene_(CScenePlay::CreateScene());
					break;
					// 終了
				case MENU_EXIT :
					CSoundManager::Play(pathDecideSE, CSoundManager::MODE_ONCE);
					PostQuitMessage(WM_QUIT);
					break;

				default :
					break ;
				}
			}
			// ✕操作
			if(command.Check(CCommand::CROSS))
			{
				CSoundManager::Play(pathCancelSE, CSoundManager::MODE_ONCE);
				isBrowseMenu = false;
			}
			// 座標
			switch(stateMenu)
			{
				// プレイ選択時
			case MENU_PLAY :
				TargetState = MENU_PLAY;
				break ;
				// 終了選択時
			case MENU_EXIT :
				TargetState = MENU_EXIT;
				break ;

			default :
				break;
			}
		}
		// メニュー非表示時
		if(!isBrowseMenu){
			TargetState = 2;
			if(command.Check(CCommand::CIRCLE))
			{
				CSoundManager::Play(pathDecideSE, CSoundManager::MODE_ONCE);
				isBrowseMenu = true;
			}
			//if(command.Check(CCommand::CROSS))
			//	PostQuitMessage(WM_QUIT);
		}
		Count++;
	}
	BackGround->qRotation *= rotationSkyDome;
	UnPress->qRotation = playModel->qRotation = exitModel->qRotation *= RotationAxisY;
	Camera3D->setLookAt(Interpolate(Camera3D->getLookAt(), Target[TargetState], INTERPOLATE_LOW));
	Camera3D->Calculate();
}

void CSceneTitle::renderScene()
{
	// レンダーターゲット内の全オブジェクトの描画
	mainLayer->Render();
	// 描画先をバックバッファに戻す
	CGraphicsManager::setRenderTargetToBackBuffer();
	// オフスクリーンの描画
	mainLayer->board->Render(Camera2D.get());
}

void CSceneTitle::PlayBGM()
{
	(0 == bgm) ? bgm = CSoundManager::Play(pathBGM, CSoundManager::MODE_LOOP) : CSoundManager::Play(bgm);
}

void CSceneTitle::StopBGM()
{
	CSoundManager::Stop(bgm);
}