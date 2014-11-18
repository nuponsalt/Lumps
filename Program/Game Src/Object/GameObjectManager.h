#pragma once

#include <list>
#include "GameObject.h"
#include "Sphere/Sphere.h"

// ゲームオブジェクトマネージャー
//class CGameObjectManager
//{
//public :
//	// ゲームオブジェクト生成
//	static CGameObjectSP createGameObject(const GameObjectType& type);
//	// 初期化
//	static void initializeGameObject();
//	// 破棄
//	static void destroyGameObject();
//	// オブジェクトの追加
//	static void AddObject(const CSphereSP object, const GameObjectType& type);
//
//	// 格納したオブジェクトの一括アップデート
//	static void updateGameObject();
//
//	// 視錐台カリングによる描画設定
//	static void isVisibleViewFrustum(const CCamera* camera);
//
//private :
//	// 球オブジェクトリスト(std::list)
//	static std::list<CSphereSP> objectSphereList;
//	// 野生のオブジェクトリスト
//	static std::list<CGameObjectWP> NativeList;
//	// 塊になっているオブジェクトリスト
//	static std::vector<CGameObjectWP> Links;
//};