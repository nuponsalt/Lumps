#include "DXUT.h"
#include "QTreeDebug.h"
#include "../../SceneManager.h"

//#include <tchar.h>
#include <time.h>

//* メンバ関数定義 *//
QTreeDebug_::QTreeDebug_() : updateFPS(0.0f), renderFPS(0.0f), CollisionNumber(0), ColVector(NULL) { }

CSceneSP QTreeDebug_::CreateScene()
{
	return CSceneSP(new QTreeDebug_());
}

void QTreeDebug_::destroyScene()
{
	Text.reset();
	spriteCircle.reset();
	spriteCollision.reset();
	ColVector->refresh();
}

CCommand QTreeDebug_::CreateCommand()
{
	CCommand command;
	// 入力制限時は入力受付なし
	if(CSceneManager::getisKeyLock_())
		return command;

	// スペースキー
	if(DXUTWasKeyPressed(VK_SPACE))
		command.Add(CCommand::DEBUG_);
	// Enter
	if(DXUTWasKeyPressed(VK_RETURN))
		command.Add(CCommand::CIRCLE);

	// 全てのコマンドが入る
	return command;
}

void QTreeDebug_::initializeScene()
{
	srand((unsigned)time(NULL));
	// XMLファイル内データ取得
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Debug/QTree/QTreeDebug.xml");
	// テキストオブジェクト
	Text = CDebugText::CreateText(xml->GetElement("Text")->GetElement("Size")->GetInt(), L"メイリオ");
	// スプライトの生成
	spriteCircle = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("Circle")->GetString());
	spriteCollision = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("ColCircle")->GetString());

	//* 円オブジェクトの初期位置・速度の設定 *//
	// 初期量としてgCircleNumだけ円を生成
	for(int i = 0; i < gCircleNum; i++) {
		Circle *circ = new Circle;
		// 円の番号
		circ->ID = i;
		// 円の半径(2~5までランダム)
		circ->Radius = 2 + 3 * (float)rand() / RAND_MAX;
		// 細長い初期配置
		circ->Position.x = (float)i / gCircleNum * 120 + 30 * (float)rand() / RAND_MAX;
		// 
		circ->Position.y = -400 + 700 * (float)i / gCircleNum;
		// 初速
		circ->Velocity.x = 0.5f;
		circ->Velocity.y = 0;
		//
		circ->Scale = circ->Radius / 32.0f;
		// 質量は半径 * 半径 * 半径に比例するとする
		circ->Mass = circ->Radius * circ->Radius * circ->Radius;
		CircList.push_back(*circ);
		// TreeObjectに登録
		CTreeObject<Circle> *p = new CTreeObject<Circle>(circ->ID);
		// 登録
		auto it = CircList.begin();
		while(it != CircList.end())
		{
			if(it->ID != circ->ID)
			{
				it++;
				continue;
			}
			p->pObject = &(*it);
			break;
		}
		spTrees.push_back(std::shared_ptr<CTreeObject<Circle>>(p));
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

void QTreeDebug_::updateScene()
{
	Count++;
	
	CCommand command = CreateCommand();

	// 円の位置を更新してツリーに再登録
	std::vector<std::shared_ptr<CTreeObject<Circle>>>::iterator it = spTrees.begin();
	while(it != spTrees.end()) {
		Circle *pTmp = (*it)->pObject;
		// 次の移動位置を仮決定
		getNextCirclePosition(*pTmp);
		// 一度リストから外れる
		(*it)->Remove();
		// 再登録
		LTree.Register(pTmp->Position.x - pTmp->Radius, pTmp->Position.y - pTmp->Radius, pTmp->Position.x + pTmp->Radius, pTmp->Position.y + pTmp->Radius, it->get());
		it++;
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

void QTreeDebug_::renderScene()
{
	// 円の描画
	for(std::list<Circle>::iterator it = CircList.begin(); it != CircList.end(); it++) {
		spriteCircle->Scale = CVector3(it->Scale, it->Scale, 0.0f);
		spriteCircle->Position = it->Position;
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

void QTreeDebug_::PlayBGM()
{
}

void QTreeDebug_::StopBGM()
{
}