#include "DXUT.h"
#include "QTreeDebug.h"

#include "../../SceneManager.h"
//#include <tchar.h>
#include <time.h>

//* グローバル関数 *//
// 次の円の位置を算出
void getNextCirclePosition(Circle &circle)
{
	// 反射後の速度ベクトル
	CVector3 refV;
	// 衝突位置
	CVector3 ColPos;
	// 衝突後の移動可能時間
	float resTime = 0.0f;
	// 重力を掛けて落とす
	// 1フレームで9.8/60(m/s)加速
	circle.Velocity.y += gGravity / 60;	

	// 今の速度で位置を更新
	// 前の位置を保存
	circle.PreviousPosition = circle.Position;
	// 位置更新
	circle.Position += circle.Velocity;

	// 壁との衝突をチェック
	// 左壁
	if(circle.Position.x < 0)
	{
		// 反射後の速度ベクトルを取得
		getReflectVelocity(&refV, CVector3(1, 0 ,0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		// 残り時間算出
		resTime = circle.Position.x / circle.Velocity.x;
		// 反射後の位置を算出
		getReflectedPosition(resTime, circle, refV);
	}
	// 右壁
	else if(circle.Position.x > 960)
	{
		getReflectVelocity(&refV, CVector3(-1, 0, 0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		resTime = (circle.Position.x - 960) / circle.Velocity.x;
		getReflectedPosition(resTime, circle, refV);
	}
	// 上壁
	else if(circle.Position.y < -1200)
	{
		getReflectVelocity(&refV, CVector3(0, 1, 0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		resTime = (circle.Position.y + 1200) / circle.Velocity.y;
		getReflectedPosition(resTime, circle, refV);
	}
	// 下壁
	else if(circle.Position.y > 540){
		getReflectVelocity(&refV, CVector3(0, -1, 0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		resTime = (circle.Position.y - 540) / circle.Velocity.y;
		getReflectedPosition(resTime, circle, refV);
	}
}

// 2円衝突処理
void collisionCircleProc(Circle *c1, Circle *c2)
{
	float time = 0;
	CVector3 C1Position, C2Position, C1Velocity, C2Velocity;

	// 衝突している2円の衝突位置を検出
	if(!calculateParticleCollision(c1->Radius, c2->Radius,
		&CVector3(c1->PreviousPosition.x, c1->PreviousPosition.y, 0),
		&CVector3(c1->Position.x, c1->Position.y, 0),
		&CVector3(c2->PreviousPosition.x, c2->PreviousPosition.y, 0),
		&CVector3(c2->Position.x, c2->Position.y, 0),
		&time,
		&C1Position,
		&C2Position))
		return;	// 衝突していないようです

	// 衝突位置を前位置として保存
	c1->Position = C1Position;
	c2->Position = C2Position;
	c1->PreviousPosition = C1Position;
	c2->PreviousPosition = C2Position;

	// 衝突後の速度を算出
	if(!calculateParticlePositionAfterCollision(
		&C1Position, &CVector3(c1->Velocity.x, c1->Velocity.y, 0),
		&C2Position, &CVector3(c2->Velocity.x, c2->Velocity.y, 0),
		c1->Mass, c2->Mass,
		// 球の反発係数
		gCircleReflection, gCircleReflection,
		time,
		&C1Position, &C1Velocity,
		&C2Position, &C2Velocity))
		return; // 何か失敗したようです

	// 衝突後位置に移動
	c1->Velocity = C1Velocity;
	c2->Velocity = C2Velocity;
	c1->Position += c1->Velocity;
	c2->Position += c2->Velocity;
}

//* メンバ関数定義 *//
QTreeDebug::QTreeDebug() : CollisionNumber(0), ColVector(NULL) { }

CSceneSP QTreeDebug::CreateScene()
{
	return CSceneSP(new QTreeDebug());
}

void QTreeDebug::destroyScene()
{
	Text.reset();
	spriteCircle.reset();
	spriteCollision.reset();
	ColVector->refresh();
}

CCommand QTreeDebug::CreateCommand()
{
	CCommand command;
	// 入力制限時は入力受付なし
	if(CSceneManager::getisKeyLock_())
		return command;
	if(DXUTWasKeyPressed(VK_RETURN))
		command.Add(CCommand::CIRCLE);
	
	// 全てのコマンドが入る
	return command;
}

void QTreeDebug::initializeScene()
{
	srand((unsigned int)time(NULL)) ;
	// XMLファイル内データ取得
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Debug/QTree/QTreeDebug.xml");
	// テキストオブジェクト
	Text = CDebugText::CreateText(xml->GetElement("Text")->GetElement("Size")->GetInt(), L"メイリオ");
	// スプライトの生成
	spriteCircle = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("Circle")->GetString());
	spriteCollision = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("ColCircle")->GetString());

	//* 円オブジェクトの初期位置・速度の設定 *//
	// g_CircleNumだけ円を生成
	for(int i = 0; i < gCircleNum; i++) {
		CircAry[i].ID = i;
		// 円の半径(2～5までランダム)
		CircAry[i].Radius = 2 + 3 * (float)rand() / RAND_MAX;
		// 細長い初期位置
		CircAry[i].Position.x = (float)i / gCircleNum * 120 + 30 * (float)rand() / RAND_MAX;
		// 結構高いところから落とします
		CircAry[i].Position.y = -400 + 700 * (float)i / gCircleNum;
		// 初速（適当)
		CircAry[i].Velocity.x = 0.5;
		CircAry[i].Velocity.y = 0;
		// 画像が64×64なのでスケール値はこうなるんです！
		CircAry[i].Scale = CircAry[i].Radius / 32.0f;
		// 質量は半径の3乗に比例とします
		CircAry[i].Mass = CircAry[i].Radius * CircAry[i].Radius * CircAry[i].Radius;
		// TreeObjectに登録
		CTreeObject<Circle> *p = new CTreeObject<Circle>(i);
		// 登録
		p->pObject = &CircAry[i];
		spTreeObjAry[i].reset(p);
	}

	//* 線形4分木マネージャ *//
	//  空間範囲をX=-60～720; Y=-1200～520に設定
	//  円が飛び出さない範囲を指定すれば良いので
	//  アバウトです
	if(!LTree.Initialize(gPartitionLebel, 0.0f, -1200.0f, 960.0f, 540.0f))
	{
		//MessageBox(NULL, _T("線形4分木空間の初期化に失敗しました。"), NULL, NULL);
		return;
	}

}

void QTreeDebug::updateScene()
{
	Count++;
	
	CCommand command = CreateCommand();

	// 円の位置を更新してツリーに再登録
	for(int i = 0; i < gCircleNum; i++)
	{
		int id = i;
		//
		Circle *pTmp = spTreeObjAry[id]->pObject;
		// 次の移動位置を仮決定
		getNextCirclePosition(*pTmp);
		// 一度リストから外れる
		spTreeObjAry[id]->Remove();
		// 再登録
		CTreeObject<Circle> *_pTree = spTreeObjAry[id].get();
		LTree.Register(pTmp->Position.x - pTmp->Radius, pTmp->Position.y - pTmp->Radius, pTmp->Position.x + pTmp->Radius, pTmp->Position.y + pTmp->Radius, _pTree);
	}
	// 衝突対応リストを取得
	CollisionNumber = LTree.getAllCollisionList(&ColVector);
	// 衝突判定
	// 2で割るのはペアになっているので
	CollisionNumber /= 2;
	Circle** pRoot = ColVector->getRootPtr();
	for(DWORD c = 0; c < CollisionNumber; c++) {
		float r2 = (pRoot[c * 2]->Radius + pRoot[c * 2 + 1]->Radius) * (pRoot[c * 2]->Radius+pRoot[c * 2 + 1]->Radius);
		float x = (pRoot[c * 2]->Position.x - pRoot[c * 2 + 1]->Position.x);
		float y = (pRoot[c * 2]->Position.y - pRoot[c * 2 + 1]->Position.y);
		if(r2 >= (x * x) + (y * y))
		{
			// ぶつかった物同士のテクスチャをオレンジに変更
			// 

			// 2円衝突処理をする
			collisionCircleProc(pRoot[c * 2], pRoot[c * 2 + 1]);
		}
	}

	// 論理処理フレームレートの再計算
	updateFPS = updateFPSCount.getFrameRate_();
}

void QTreeDebug::renderScene()
{
	for(int i = 0; i < gCircleNum; i++) {
		spriteCircle->Scale = CVector3(CircAry[i].Scale, CircAry[i].Scale, 0.0f);
		spriteCircle->Position = CircAry[i].Position;
		spriteCircle->Render();
	}
	// ツリー情報表示
	Text->drawText(10, 10, D3DCOLOR_ARGB(255, 255, 0, 0), L"UpdateFrameRate : %2.5f", updateFPS);
	Text->drawText(10, 30, D3DCOLOR_ARGB(255, 255, 0, 0), L"RenderFrameRate : %2.5f", renderFPS);
	// 円の数
	Text->drawText(10, 50, D3DCOLOR_ARGB(255, 255, 0, 0), L"Circle Number : %d", gCircleNum);
	// 衝突判定数
	Text->drawText(10, 70, D3DCOLOR_ARGB(255, 255, 0, 0), L"Collision Check Number : %d", CollisionNumber);
	// 最適化
	Text->drawText(10, 90, D3DCOLOR_ARGB(255, 255, 0, 0), L"Optimization : %2.5f ％", 100.0 * (float)(CollisionNumber / 2) / (gCircleNum / 2 * (gCircleNum + 1)));
	// カウント
	Text->drawText(10, 110, D3DCOLOR_ARGB(255, 255, 0, 0), L"Counter = %d", Count);
	
	// 描画フレームレートの再計算
	renderFPS = (float)renderFPSCount.getFrameRate_();
}

void QTreeDebug::PlayBGM()
{
}

void QTreeDebug::StopBGM()
{
}