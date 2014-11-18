// �v���R���p�C���ς݃w�b�_�[�ǂݍ���
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
	
	// ���f���ǂݍ���
	Model = CGRenderer::CreateFromX(_path, CShaderPhong::CreateShader());
	Life = xml->GetElement("Life")->GetInt();
	
	// �e���f���̓ǂݍ���
	_path = xml->GetElement("Shadow")->GetElement("Path")->GetString();
	positionYShadow = xml->GetElement("Shadow")->GetElement("Y")->GetFloat();
	Shadow = CGPlane::CreateFromTexture(_path, 1, 1, realSphere.Radius * 2, realSphere.Radius * 2);
	Shadow->vColorRGBA = CVector4(1, 1, 1, xml->GetElement("Shadow")->GetElement("Alpha")->GetFloat());

	// �ό`���
	Transform.Position = CVector3(_posX, _posY, _posZ);
	Transform.Scale = CVector3(Size, Size, Size);
	// �̐όv�Z
	float _rad = realSphere.Radius * Size;
	Volume = calculateSphereVolume(_rad);
	// ���a
	bvSphere.Radius = xml->GetElement("gRadius")->GetFloat();
	MaxSpeed = xml->GetElement("Speed")->GetFloat();
	Model->CurrentRotateType = ROTATE_TYPE::QUATERNION;
	// �J����
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
	// ���x��
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
	// ���͕����ɒP�ʃx�N�g��(XZ���ʂōl����)������
	float value = ONE;
	if (command.Check(CCommand::UP))
		v.z = value;
	if (command.Check(CCommand::DOWN))
		v.z = -value;
	if (command.Check(CCommand::LEFT))
		v.x = -value;
	if (command.Check(CCommand::RIGHT))
		v.x = value;
	// ���K�����s��
	return (v.Length() > ZERO) ? v.Normalize() : ZERO_VECTOR3;
}

void CPlayer::calculateVelocity(CCommand &command)
{
	// ���͂��������ꍇ
	if(CCommand::CheckMoveCommand(command))
	{
		// ���͕������烍�[�J���Ȉړ��������擾
		Direction = getZXVector(command);
		// �J�����̑O������\����]���擾
		frontRotation = Camera->getRotation(AXISY);
	}
	// �ړ��������m��
	float _speed = ((bvSphere.Radius * TWO * PI) / ANGLE_360) * Speed ;
	CVector3 vel = (Direction * frontRotation) * _speed;
	// ���f
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
	// �ړ��ɉ�]�����킹��
	CVector3 AxisXZ = vel.Cross(-AXIS_Y);
	CQuaternion _rotation = CQuaternion(AxisXZ, D3DXToRadian(Speed));
	ImpactRotation = _rotation;
}

void CPlayer::calculateLevel()
{
	//�i�����l�~�i�P�{�i�P���i�P�{�i���݃��x���{�i�P�������`�j�j�~�����a�j�j�j�O�i���݃��x���|�P�j�~ ���݃��x��
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
	// �����̌v�Z
	if (CCommand::CheckMoveCommand(command))
	{
		Speed = Interpolate(Speed, MaxSpeed, INTERPOLATE_LOW);
	}
	// �ړ��v�Z
	calculateVelocity(command);
	// �p���v�Z
	calculateRotation(command);
}

void CPlayer::subUpdate(CCommand& command, CState& state)
{
	updateAction(command, state);
	Camera->setCommand(command);
}

void CPlayer::subApplyParameter()
{
	// �����N���Ă���I�u�W�F�N�g�̍X�V
	for(int i = 0; i < Links.size(); i++)
		Links[i].lock()->UpdateLink(shared_from_this(), ImpactRotation, BaseRotations[i], LocalPositions[i]);
	
	// ���x���v�Z
	calculateLevel();

	// �J����
	Camera->setLookAt(Transform.Position.x, Transform.Position.y + Overhead, Transform.Position.z);
	Camera->setSizeIPO(StatusSize);
	Camera->Calculate();
	Camera->calculateViewFructum();
}