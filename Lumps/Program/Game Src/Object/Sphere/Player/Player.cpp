// プリコンパイル済みヘッダー読み込み
#include "DXUT.h"

#include "Player.h"
#include "../../../Camera/CameraThirdPerson.h"
#include "../../../Define.h"
#include "../../../Scene/Play/ScenePlay.h"
#define _USE_MATH_DEFINES
#include <math.h>

float CPlayer::StatusSize;

CPlayer::CPlayer() : Direction(), prevLevelExp(0)
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/Player.xml");
	std::string _path = xml->GetElement("Model")->GetString();
	float _posX = xml->GetElement("Position")->GetElement("X")->GetFloat();
	float _posY = xml->GetElement("Position")->GetElement("Y")->GetFloat();
	float _posZ = xml->GetElement("Position")->GetElement("Z")->GetFloat();
	StatusSize = Size = xml->GetElement("Size")->GetFloat();
	
	// モデル読み込み
	Model = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Life = xml->GetElement("Life")->GetInt();
	
	// 影モデルの読み込み
	_path = xml->GetElement("Shadow")->GetElement("Path")->GetString();
	positionYShadow = xml->GetElement("Shadow")->GetElement("Y")->GetFloat();
	Shadow = CGPlane::CreateFromTexture(_path, 1, 1, realSphere.Radius * 2, realSphere.Radius * 2);
	Shadow->vColorRGBA = CVector4(1, 1, 1, xml->GetElement("Shadow")->GetElement("Alpha")->GetFloat());

	// 変形情報
	Transform.Position = CVector3(_posX, _posY, _posZ);
	Transform.Scale = CVector3(Size, Size, Size);
	// 体積計算
	float _rad = realSphere.Radius * Size;
	Volume = calculateSphereVolume(_rad);
	// 半径
	bvSphere.Radius = xml->GetElement("gRadius")->GetFloat();
	MaxSpeed = xml->GetElement("Speed")->GetFloat();
	Model->CurrentRotateType = ROTATE_TYPE::QUATERNION;
	// カメラ
	float _ofsX = xml->GetElement("Camera")->GetElement("Offset")->GetElement("X")->GetFloat();
	float _ofsY = xml->GetElement("Camera")->GetElement("Offset")->GetElement("Y")->GetFloat();
	float _ofsZ = xml->GetElement("Camera")->GetElement("Offset")->GetElement("Z")->GetFloat();
	float _dist = xml->GetElement("Camera")->GetElement("Distance")->GetFloat();
	float _speed = xml->GetElement("Camera")->GetElement("Speed")->GetFloat();
	// 
	Overhead = xml->GetElement("Overhead")->GetFloat();
	_ofsZ *= _dist;
	Camera = CCameraThirdPerson::Create();
	Camera->setOffset(_ofsX, _ofsY, _ofsZ);
	Camera->setOverhead(Overhead);
	Camera->setSpeed(_speed);
	// レベル
	Level = xml->GetElement("Level")->GetInt();
	nextLevelExp = xml->GetElement("NextLvExp")->GetInt();
	// SE
	pathLvUpSE = xml->GetElement("SE")->GetElement("lvup")->GetString();
	CSoundManager::Load(pathLvUpSE);
	// 
	isRender = true;
}

CPlayer::~CPlayer()
{
	Camera.reset() ;
}

CPlayerSP CPlayer::Create()
{		
	return CPlayerSP(new CPlayer()) ;
}

CVector3 CPlayer::getZXVector(CCommand &command)
{
	CVector3 v;
	// 入力方向に単位ベクトル(XZ平面で考える)が入る
	float value = ONE;
	if (command.Check(CCommand::UP))
		v.z = value;
	if (command.Check(CCommand::DOWN))
		v.z = -value;
	if (command.Check(CCommand::LEFT))
		v.x = -value;
	if (command.Check(CCommand::RIGHT))
		v.x = value;
	// 正規化を行う
	return (v.Length() > ZERO) ? v.Normalize() : ZERO_VECTOR3;
}

void CPlayer::calculateVelocity(CCommand &command)
{
	// 入力があった場合
	if(CCommand::CheckMoveCommand(command))
	{
		// 入力方向からローカルな移動方向を取得
		Direction = getZXVector(command);
		// カメラの前方向を表す回転を取得
		frontRotation = Camera->getRotation(AXISY);
	}
	// 移動方向が確定
	float _speed = ((bvSphere.Radius * TWO * PI) / ANGLE_360) * Speed ;
	CVector3 vel = (Direction * frontRotation) * _speed;
	// 反映
	Velocity.x = vel.x;
	Velocity.z = vel.z;
}

CQuaternion CPlayer::getFrontRotation() const
{
	return Camera->getRotation(AXISY);
}

void CPlayer::calculateRotation(CCommand &command)
{
	CVector3 vel = Velocity;
	// 移動に回転を合わせる
	CVector3 AxisXZ = vel.Cross(-AXIS_Y);
	CQuaternion _rotation = CQuaternion(AxisXZ, D3DXToRadian(Speed));
	ImpactRotation = _rotation;
}

void CPlayer::calculateLevel()
{
	//（初期値×（１＋（１÷（１＋（現在レベル＋（１÷引数Ａ））×引数Ｂ）））＾（現在レベル－１）× 現在レベル
	if(CScenePlay::getScore() >= nextLevelExp) 
	{
		CSoundManager::Play(pathLvUpSE, CSoundManager::MODE_ONCE);
		Level ++;
		StatusSize += 0.2f;
		Size = StatusSize;
		Transform.Scale = CVector3(StatusSize, StatusSize, StatusSize);
		realSphere.Radius += realSphere.Radius * 0.2f;
		bvSphere.Radius += bvSphere.Radius * 0.2f;
		prevLevelExp = nextLevelExp;

		float a = (1.0f + (1.0f / (1.0f + (Level + (1 / 0.1f)) * 0.05f)));
		float b = (float)pow(a, Level - 1);
		float c = 10.0f * b * Level;

		nextLevelExp = (int)c;
	}
}

void CPlayer::updateAction(CCommand &command, CState &state)
{
	// 速さの計算
	if (CCommand::CheckMoveCommand(command))
	{
		Speed = Interpolate(Speed, MaxSpeed, INTERPOLATE_LOW);
	}
	// 移動計算
	calculateVelocity(command);
	// 姿勢計算
	calculateRotation(command);
}

void CPlayer::subUpdate(CCommand& command, CState& state)
{
	updateAction(command, state);
	Camera->setCommand(command);
}

void CPlayer::subApplyParameter()
{
	// リンクしているオブジェクトの更新
	for(int i = 0; i < Links.size(); i++)
		Links[i].lock()->UpdateLink(shared_from_this(), ImpactRotation, BaseRotations[i], LocalPositions[i]);
	
	// レベル計算
	calculateLevel();

	// カメラ
	Camera->setLookAt(Transform.Position.x, Transform.Position.y + Overhead, Transform.Position.z);
	Camera->setSizeIPO(StatusSize);
	Camera->Calculate();
	Camera->calculateViewFructum();
}