#include "DXUT.h"
#include "GameObjectManager.h"
//
//#include "Sphere/Player/Player.h"
//#include "Sphere/Drop/Drop.h"
//
//std::list<CSphereSP> CGameObjectManager::objectSphereList;
//std::list<CGameObjectWP> CGameObjectManager::NativeList;
//std::vector<CGameObjectWP> CGameObjectManager::Links;
//
//CGameObjectSP CGameObjectManager::createGameObject(const GameObjectType& type)
//{
//	 //ƒvƒŒƒCƒ„[
//	if(type == PLAYER) 
//		return CPlayer::Create();
//	 //—Ž‰º•¨(‹…)
//	if(type == DROP)
//		return CDrop::Create();
//}
//
//void CGameObjectManager::initializeGameObject()
//{
//	objectSphereList.clear();
//}
//
//void CGameObjectManager::destroyGameObject()
//{
//
//}
//
//void CGameObjectManager::AddObject(const CSphereSP object, const GameObjectType& type)
//{
//	if(type != PLAYER)
//	{
//		objectSphereList.push_back(object);
//		NativeList.push_back(object);
//		return;
//	}
//	Links.
//}
//
//void CGameObjectManager::updateGameObject()
//{
//
//}
//
//void CGameObjectManager::isVisibleViewFrustum(const CCamera* camera)
//{
//	auto obj_it = objectSphereList.begin();
//	while(obj_it != objectSphereList.end())
//	{
//		if(camera->isIntersectViewFrustum((*obj_it)->realSphere))
//			(*obj_it)->setisRender(true);
//		else
//			(*obj_it)->setisRender(false);
//
//		++obj_it;
//	}
//}