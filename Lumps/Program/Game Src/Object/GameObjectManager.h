#pragma once

#include <list>
#include "GameObject.h"
#include "Sphere/Sphere.h"

// �Q�[���I�u�W�F�N�g�}�l�[�W���[
//class CGameObjectManager
//{
//public :
//	// �Q�[���I�u�W�F�N�g����
//	static CGameObjectSP createGameObject(const GameObjectType& type);
//	// ������
//	static void initializeGameObject();
//	// �j��
//	static void destroyGameObject();
//	// �I�u�W�F�N�g�̒ǉ�
//	static void AddObject(const CSphereSP object, const GameObjectType& type);
//
//	// �i�[�����I�u�W�F�N�g�̈ꊇ�A�b�v�f�[�g
//	static void updateGameObject();
//
//	// ������J�����O�ɂ��`��ݒ�
//	static void isVisibleViewFrustum(const CCamera* camera);
//
//private :
//	// ���I�u�W�F�N�g���X�g(std::list)
//	static std::list<CSphereSP> objectSphereList;
//	// �쐶�̃I�u�W�F�N�g���X�g
//	static std::list<CGameObjectWP> NativeList;
//	// ��ɂȂ��Ă���I�u�W�F�N�g���X�g
//	static std::vector<CGameObjectWP> Links;
//};