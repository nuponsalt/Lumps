#include "DXUT.h"
#include "GameObject.h"

#include "../Define.h"
#include "../Scene/SceneManager.h"

CGameObject::CGameObject() : isActive(true), Volume(0), Gravity(0), Speed(0), Size(ONE), Life(0), MaxLife(0), isRender(false)
{ }

CCommand CGameObject::CreateCommand()
{
	CCommand command;
	if(CSceneManager::getisKeyLock_() || CSceneManager::getisPause_())
		return command;
	// 移動
	int move = 0;
	// 上方向入力
	if (DXUTIsKeyDown(VK_UP)
		||CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_UP) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_LEFT_UP) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_UP_RIGHT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::STICK_UP))	
		move |= CCommand::UP;
	// 下方向入力
	if (DXUTIsKeyDown(VK_DOWN)
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_DOWN) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_DOWN_LEFT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_RIGHT_DOWN) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::STICK_DOWN))
		move |= CCommand::DOWN;
	// 左方向入力
	if (DXUTIsKeyDown(VK_LEFT)
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_LEFT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_LEFT_UP) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_DOWN_LEFT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::STICK_LEFT))
		move |= CCommand::LEFT;
	// 右方向入力
	if (DXUTIsKeyDown(VK_RIGHT)
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_RIGHT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_UP_RIGHT) 
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::CROSS_RIGHT_DOWN)
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::STICK_RIGHT))
		move |= CCommand::RIGHT;
	
	command.Add(move);
	
	// △キー入力
	if(DXUTIsKeyDown('W')
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::PAD_BTN_1))
		command.Add(CCommand::TRIANGLE);
	// ✕キー入力
	if(DXUTIsKeyDown('S')
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::PAD_BTN_3))
		command.Add(CCommand::CROSS);
	// □キー入力
	if(DXUTIsKeyDown('A')
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::PAD_BTN_4))
		command.Add(CCommand::SQUARE);
	// ○キー入力
	if(DXUTIsKeyDown('D')
		|| CJoyPadManager::IsKeyKeep(0, CJoyPadManager::PAD_BTN_2))
		command.Add(CCommand::CIRCLE);

	return command;
}

void CGameObject::UpdateLink(const CGameObjectSP parent, CQuaternion &parent_rotation, CQuaternion &base_rotation, CVector3 local_position)
{
	Transform.qRotation *= parent_rotation;
	CQuaternion _q = base_rotation.Delta(parent->Transform.qRotation);
	//D3DXVECTOR3 p =  QuaternionTransformCoord(_local_position,  _parent->Transform.qRotation);

	//Transform.Position = _local_position * _q;
	Transform.Position = local_position * parent->Transform.qRotation;
	Transform.Position += parent->Transform.Position;

	for(int i = 0; i < Links.size(); i++) {
		if(Links[i].lock() == parent) continue;
		Links[i].lock()->UpdateLink(shared_from_this(), parent_rotation, BaseRotations[i], LocalPositions[i]);
	}
}