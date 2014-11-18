#include "DXUT.h"
#include "ScenePlay.h"
#include "../../Object/Sphere/Player/Player.h"
#include "../../Object/Sphere/Drop/Drop.h"

#include "../../Effect/AnimationEffect.h"

//* グローバルスコープ *//
// 衝突後の球同士の補正
bool CollidedSpheres(CVector3 &vA, CVector3 &vB, float rA, float rB)
{
	if(!getCollideSpheres(vA, vB, rA, rB))
		return false;

	CVector3 center = (vA + vB) * 0.5f;

	//// センターから１へのベクトル
	CVector3 centertoA = vA - center;
	//// センターから２ベクトル
	CVector3 centertoB = vB - center;

	centertoA.Normalize();
	centertoB.Normalize();

	vA = center + (centertoA * 0.5);
	vB = center + (centertoB * 0.5);
	return true;
}

void CScenePlay::correctWall()
{
	// 左から交点, 半径, 線分における終点
	CVector3 Strength, epos, IntersectPt, NearPt;
	// 四辺の処理は同じなのでforループ
	for (size_t i = 0; i < segs.size(); i++)
	{
		// 線分上の最近点の算出
		NearPt = NearOnLine(CVector3(Player->Transform.Position.x, 0.0f, Player->Transform.Position.z), segs[i].s, segs[i].e);
		// 最近点を基に法線ベクトルを算出
		Strength = Normalize(NearPt - CVector3(Player->Transform.Position.x, 0.0f, Player->Transform.Position.z)) * Player->realSphere.Radius;
		// 終点の計算
		epos = Player->Transform.Position + Strength;
		// 判定
		if(getCollideSegments(&IntersectPt, 
			CVector3(Player->Transform.Position.x, Player->Transform.Position.z, 0), CVector3(epos.x, epos.z,0), 
			CVector3(segs[i].s.x, segs[i].s.z, 0), CVector3(segs[i].e.x, segs[i].e.z, 0)
			))
			// 補正
			Player->Transform.Position = NearPt - Strength;
	}
}

void CScenePlay::CreateFall(CSphereSP _obj)
{
	FallList.push_back(_obj);
	// 野生のオブジェクト
	NativeList.push_back(_obj);
	// レンダーターゲット
	mainLayer->AddObject(_obj->Model, RENDER_NORMAL);
	//mainLayer->AddObject(_obj->Shadow, RENDER_ALPHA);
}

void CScenePlay::PopObjectRandom()
{
	int _time = TimeLimit;
	// 同時に生成する数
#if _DEBUG
	const int CREATENUM = 1;
#else
	const int CREATENUM = 2;
#endif
	if(_time > 0 && PopTimer->TimeCount() && FallList.size() < 500)
	{
		CSphereSP _obj[CREATENUM];
		CVector3 _position[CREATENUM]; 
		for (int i = 0; i < CREATENUM; i++) {
			_position[i].y = 50.0f;
			_position[i].x = (float)GetRandom(-500, 500);
			_position[i].z = (float)GetRandom(-500, 500);
			_obj[i] = CDrop::Create();
			_obj[i]->Transform.Position = _position[i];
			CreateFall(_obj[i]);
		}
	}
}

void CScenePlay::initializeObjects()
{
	// xmlファイルの読み込み
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/ScenePlay.xml");
	
	// デバッグテキスト描画オブジェクト
	Text = CDebugText::CreateText(xml->GetElement("FontSize")->GetInt(), L"メイリオ");
	
	// 終了する時間(推定3秒)
	EndCount = xml->GetElement("EndCount")->GetInt();

	// 境界線(Z)座標
	BorderLine = xml->GetElement("Border")->GetFloat();

	// 出現時間
	int _time = xml->GetElement("PopTimer")->GetInt();
	PopTimer = CTimerSP(new CTimer(_time));

	//* メインレイヤー *//
	// メインレイヤー初期化
	mainLayer = CLayer::CreateLayer(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainLayer->board->Position.y = xml->GetElement("MainLayer")->GetElement("Position")->GetElement("Y")->GetFloat();
	
	// ポーズ画像
	std::string _path = xml->GetElement("pauseImage")->GetElement("path")->GetString();
	float posX = xml->GetElement("pauseImage")->GetElement("Position")->GetElement("X")->GetFloat();
	float posY = xml->GetElement("pauseImage")->GetElement("Position")->GetElement("Y")->GetFloat();
	float posZ = xml->GetElement("pauseImage")->GetElement("Position")->GetElement("Z")->GetFloat();
	PauseImage = CGPlane::CreateFromTexture(_path);
	PauseImage->Position = CVector3(posX, posY, posZ);
	PauseImage->isRender = false;
	
	// スカイドーム
	_path = xml->GetElement("SkyDome")->GetElement("path")->GetString();
	posX = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("Z")->GetFloat();
	SkyDome = CGRenderer::CreateFromX(_path, CShaderNormal::CreateShader());
	SkyDome->Position = CVector3(posX, posY, posZ);
	
	// 地面モデル
	_path = xml->GetElement("UnderGround")->GetElement("path")->GetString();
	posX = xml->GetElement("UnderGround")->GetElement("Position")->GetElement("X")->GetFloat(); 
	posY = xml->GetElement("UnderGround")->GetElement("Position")->GetElement("Y")->GetFloat(); 
	posZ = xml->GetElement("UnderGround")->GetElement("Position")->GetElement("Z")->GetFloat();
	UnderGround = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	UnderGround->Position = CVector3(posX, posY, posZ);
	UnderGround->Scale = CVector3(
		xml->GetElement("UnderGround")->GetElement("Scale")->GetElement("X")->GetFloat(), 
		xml->GetElement("UnderGround")->GetElement("Scale")->GetElement("Y")->GetFloat(), 
		xml->GetElement("UnderGround")->GetElement("Scale")->GetElement("Z")->GetFloat()
		);
	
	// 壁
	_path = xml->GetElement("Wall")->GetElement("path")->GetString();
	posX = xml->GetElement("Wall")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Wall")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Wall")->GetElement("Position")->GetElement("Z")->GetFloat();
	float scale = xml->GetElement("Wall")->GetElement("scale")->GetFloat();
	float scaleY = xml->GetElement("Wall")->GetElement("scaleY")->GetFloat();
	Wall = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	Wall->setisAddBlend(true);
	Wall->Position = CVector3(posX, posY, posZ);
	Wall->Scale = CVector3(scale, scaleY, scale);
	Wall->setColorRGBA(1,1,1,1);

	for(int i = 0; i < xml->GetElement("SegmentNum")->GetInt(); i++)
	{
		Segment seg;
		seg.s.x = xml->GetElement("Segment", i)->GetElement("Start")->GetElement("X")->GetFloat();
		seg.s.y = xml->GetElement("Segment", i)->GetElement("Start")->GetElement("Y")->GetFloat();
		seg.s.z = xml->GetElement("Segment", i)->GetElement("Start")->GetElement("Z")->GetFloat();
		seg.e.x = xml->GetElement("Segment", i)->GetElement("End")->GetElement("X")->GetFloat();
		seg.e.y = xml->GetElement("Segment", i)->GetElement("End")->GetElement("Y")->GetFloat();
		seg.e.z = xml->GetElement("Segment", i)->GetElement("End")->GetElement("Z")->GetFloat();
		segs.push_back(seg);
	}

	// スタートロゴ
	_path = xml->GetElement("StartLogo")->GetElement("path")->GetString();
	posX = xml->GetElement("StartLogo")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("StartLogo")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("StartLogo")->GetElement("Position")->GetElement("Z")->GetFloat();
	scale = xml->GetElement("StartLogo")->GetElement("Scale")->GetFloat();
	StartLogo = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	StartLogo->Position = CVector3(posX, posY, posZ);
	StartLogo->Scale = CVector3(scale, scale, scale);
	StartLogo->vColorRGBA.w = 0;

	// タイムアップロゴ
	_path = xml->GetElement("EndLogo")->GetElement("path")->GetString();
	posX = xml->GetElement("EndLogo")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("EndLogo")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("EndLogo")->GetElement("Position")->GetElement("Z")->GetFloat();
	scale = xml->GetElement("EndLogo")->GetElement("Scale")->GetFloat();
	TimeupLogo = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	TimeupLogo->Position = CVector3(posX, posY, posZ);
	TimeupLogo->Scale = CVector3(scale, scale, scale);
	TimeupLogo->isRender = false;

	// アルファ加算値
	AddAlpha = xml->GetElement("AddAlphaRate")->GetFloat();

	// BGM
	pathBGM = xml->GetElement("BGM")->GetString();
	CSoundManager::Load(pathBGM);
	// SE
	pathBackTitleSE = xml->GetElement("SE")->GetElement("backtitle")->GetString();
	CSoundManager::Load(pathBackTitleSE);
	pathGoodSE = xml->GetElement("SE")->GetElement("good")->GetString();
	CSoundManager::Load(pathGoodSE);
	pathBadSE = xml->GetElement("SE")->GetElement("bad")->GetString();
	CSoundManager::Load(pathBadSE);
	// リセットタイマー
	_time = xml->GetElement("ResetTimer")->GetInt();
	resetTimer = CTimerSP(new CTimer(_time));
	
	// プレイヤー
	Player = CPlayer::Create();
	//* ゲームオブジェクトをそれぞれのリストに挿入 *//
	// プレイヤーが操作している塊
	Links.push_back(Player);
	
	// メインレイヤーのカメラをプレイヤーのカメラに設定
	mainLayer->Camera3D = Player->getCamera();

	// メインレイヤーのレンダーリストに追加
	mainLayer->AddObject(SkyDome, RENDER_NORMAL);
	mainLayer->AddObject(UnderGround, RENDER_NORMAL);
	mainLayer->AddObject(Wall, RENDER_ALPHA);
	mainLayer->AddObject(Player->Model, RENDER_NORMAL);
	mainLayer->AddObject(Player->Shadow, RENDER_ALPHA);
	mainLayer->AddObject(PauseImage, RENDER_FRONT2D);
	mainLayer->AddObject(StartLogo, RENDER_ALPHA);
	mainLayer->AddObject(TimeupLogo, RENDER_NORMAL);

	//* ミニマップレイヤー *//
	// ミニマップレイヤー初期化
	minimapLayer = CLayer::CreateLayer(
		xml->GetElement("MinimapLayer")->GetElement("Size")->GetElement("Width")->GetInt(), 
		xml->GetElement("MinimapLayer")->GetElement("Size")->GetElement("Height")->GetInt()
		);
	minimapLayer->board->Position = CVector3(
		xml->GetElement("MinimapLayer")->GetElement("Position")->GetElement("X")->GetFloat(),
		xml->GetElement("MinimapLayer")->GetElement("Position")->GetElement("Y")->GetFloat(),
		xml->GetElement("MinimapLayer")->GetElement("Position")->GetElement("Z")->GetFloat()
		);
	// ミニマップレイヤーのカメラ設定
	minimapLayer->Camera3D->setEye(0, xml->GetElement("EyeY")->GetFloat(), 0);
	minimapLayer->Camera3D->setLookAt(0, 0, 0);
	minimapLayer->Camera3D->setUp(0, 0, 1);

	// ミニマップ背景

}

void CScenePlay::subupdateLinks()
{
	// イテレータを用意(リストの頭を代入)
	auto native_it = NativeList.begin() ;
	while(native_it != NativeList.end())
	{
		// フラグ	
		bool inc = true;
		for(int i = 0; i < Links.size(); i++)
		{
			// 座標
			CVector3 a = (*native_it).lock()->bvSphere.Position;
			CVector3 b = Player->bvSphere.Position;
			// 半径(衝突判定でのみの使用)
			float ra = (*native_it).lock()->bvSphere.Radius;
			float rb = Player->bvSphere.Radius;
			// 球同士の判定なので半径同士で衝突判定を行う(衝突がなければこれより下の処理を飛ばす)or サイズが現在最大サイズの場合抜ける
			if(!getCollideSpheres(a, b, ra, rb) || (*native_it).lock()->getSize() >= (*native_it).lock()->getSizeMax() * 0.009f * CPlayer::getStSize()) 
				continue;
			
			// SE再生
			CSoundManager::Play(pathGoodSE, CSoundManager::MODE_ONCE);
			// [ 当たったオブジェクト ]の権利を剥奪
			(*native_it).lock()->isActive = false;
			Player->Volume += (*native_it).lock()->Volume;
			ScoreVolume += (*native_it).lock()->Volume;
			TotalScoreVolume = Player->Volume;
			// 相対座標算出
			D3DXVECTOR3 ab = b - a; // a から b への相対座標
			D3DXVECTOR3 ba = a - b; // b から a への相対座標
			// [ 当たりに行ったオブジェクト ] のリンクデータに [ 当たったオブジェクト ] のデータを追加
			Links[i].lock()->Links.push_back((*native_it).lock());
			Links[i].lock()->LocalPositions.push_back(ba);
			Links[i].lock()->BaseRotations.push_back(Links[i].lock()->Transform.qRotation);
			// [ 当たった球 ] のリンクデータに [ 当たりに行ったオブジェクト ] のデータを追加
			(*native_it).lock()->Links.push_back(Links[i].lock());
			(*native_it).lock()->LocalPositions.push_back(ab);
			(*native_it).lock()->BaseRotations.push_back((*native_it).lock()->Transform.qRotation);
			// 塊リストに [ 当たったオブジェクト ] を追加
			Links.push_back((*native_it).lock());
			// 野生リストから [ 当たったオブジェクト ] を削除
			native_it = NativeList.erase(native_it);

			inc = false;
			break;
		}
		// 次の検知
		if(inc){
			native_it++;
		}
	}
}

void CScenePlay::updateObjects()
{
	renderNum = 0;

	auto fall_it = FallList.begin();
	while(fall_it != FallList.end())
	{
		if((*fall_it)->getisRender())
			++renderNum;
		// すでにデリートされていた場合あるいはライフが0の場合リストから除外してスキップ
		if((*fall_it) == NULL || (*fall_it)->getLife() == 0)
		{
			if((*fall_it)->getisRender())
			{
				CAnimationEffectSP eff = CAnimationEffect::CreateEffect("Resource/XML/Effect/Smoke.xml", (*fall_it)->Transform.Position);
				mainLayer->AddObject(eff->Board, RENDER_ALPHA);
			}
			fall_it = FallList.erase(fall_it);
			continue;
		}
		// NPCの更新
		(*fall_it)->Update();
		(*fall_it)->isVisible(Player->getCamera().get());
		// 次のイテレータ
		fall_it++;
	}

	// プレイヤー以外の落下オブジェクトに対する補正
	auto native_it = NativeList.begin();
	while(native_it != NativeList.end())
	{
		if((*native_it).lock() == NULL || (*native_it).lock()->getLife() == 0)
		{
			native_it = NativeList.erase(native_it);
			continue;
		}
		float ra = Player->bvSphere.Radius;
		float rb = (*native_it).lock()->bvSphere.Radius;
		float sa = (*native_it).lock()->getSize();
		float sb = (*native_it).lock()->getSizeMax() * 0.009f * CPlayer::getStSize();
		if(sa >= sb)
			if(CollidedSpheres(Player->Transform.Position, (*native_it).lock()->Transform.Position, ra, rb))
				if(isPlay)
				{ 
					CSoundManager::Play(pathBadSE, CSoundManager::MODE_ONCE);
					isPlay = false;
				}
		native_it++;
	}
	if(!isPlay && resetTimer->TimeCount())
		isPlay = true;

	// プレイヤー更新
	Player->Update();

	// 自機の壁に対する補正
	correctWall();
	// 塊の更新
	subupdateLinks();
	// エフェクトの更新
	CAnimationEffect::updateAllEffect();
}