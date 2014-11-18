#pragma once

#include "../../Scene.h"
#include <memory>
#include "../../../../Library/Library.h"

//* 定数群 *//
// 球同士の反発係数
const float gCircleReflection = 0.5f;
// 球と壁の反発係数
const float WallReflection = 0.99f;
// 生成する円の数
const int gCircleNum = 350;
// 空間分割レベル
const int gPartitionLebel = 6;
// 重力
const float gGravity = 5.0f;

extern void getNextCirclePosition(Circle &circle);
extern void collisionCircleProc(Circle *c1, Circle *c2);

class QTreeDebug : public CScene
{
public :
	// デストラクタ
	~QTreeDebug() { }
	
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
	// 円の描画用スプライト
	CSpriteSP spriteCircle;	// 非衝突時
	CSpriteSP spriteCollision;	// 衝突時
	// 円オブジェクト
	Circle CircAry[gCircleNum];
	// 円オブジェクトを包むツリーオブジェクト
	std::shared_ptr<CTreeObject<Circle>> spTreeObjAry[gCircleNum];
	// 線形分木オブジェクト
	CLinerQuadTreeManager<Circle> LTree;
	// 衝突判定回数
	DWORD CollisionNumber;
	// 衝突対象リスト
	CCollisionList<Circle> *ColVector;

	// コンストラクタ
	QTreeDebug();

protected :
	// コマンドの生成
	CCommand CreateCommand();

};

// 上記デバッグクラスの改良版(改良完了後はこちらが正式版)
class QTreeDebug_ : public CScene
{
public :
	// デストラクタ
	~QTreeDebug_() { }
	
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
	// フレームレート
	CFrameRateCounter updateFPSCount, renderFPSCount;
	float updateFPS, renderFPS;
	// 円の描画用スプライト
	CSpriteSP spriteCircle;	// 非衝突時
	CSpriteSP spriteCollision;	// 衝突時
	// 円オブジェクト
	std::list<Circle> CircList;
	// 円オブジェクトを包むツリーオブジェクト
	std::vector<std::shared_ptr<CTreeObject<Circle>>> spTrees;
	// 線形分木オブジェクト
	CLinerQuadTreeManager<Circle> LTree;
	// 衝突判定回数
	DWORD CollisionNumber;
	// 衝突対象リスト
	CCollisionList<Circle> *ColVector;

	// コンストラクタ
	QTreeDebug_();

protected :
	// コマンドの生成
	CCommand CreateCommand();

};