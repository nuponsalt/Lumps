// プリコンパイル済みヘッダー読み込み
#include "DXUT.h"

#include "Drop.h"
#include "../Player/Player.h"
#include "../../../Define.h"

CDrop::CDrop() : rotateSpeed(0)
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/Drop.xml");
	std::string _path = xml->GetElement("Model")->GetString();
	
	float max = MaxSize * CPlayer::getStSize();
	Size = (float)(GetRandom(MinSize, max) * 0.01f);
	// 体積計算
	float _rad = realSphere.Radius * Size;
	Volume = calculateSphereVolume(_rad);
	// 半径
	bvSphere.Radius *= Size;
	realSphere.Radius = bvSphere.Radius;
	// モデル読み込み
	Model = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	Transform.Scale = CVector3(Size, Size, Size);
	MaxLife = xml->GetElement("Life")->GetInt();
	Life = MaxLife;
	Model->CurrentRotateType = ROTATE_TYPE::QUATERNION;
	positionYShadow = xml->GetElement("Shadow")->GetElement("Y")->GetFloat();
	// 色の設定
	int val = GetRandom(0, 2);
	Model->vColorRGBA = 
		(val == 0) ? CVector4(1, 0.5f, 0.5f, 1) :
		(val == 1) ? CVector4(0.5f, 1, 0.5f, 1) :
		(val == 2) ? CVector4(0.5f, 0.5f, 1, 1) :
		CVector4(0.5f, 0.5f, 0.5f, 1);
}

CDropSP CDrop::Create()
{
	return CDropSP(new CDrop());
}

CQuaternion CDrop::getFrontRotation() const 
{
	return Transform.qRotation;
}

void CDrop::updateAction(CCommand &command, CState &state)
{
	
}

void CDrop::manageLife(CState& state)
{
	if(Life > 0 && state.Check(CState::GROUNDING)) 
	{ 
		--Life;
		++rotateSpeed;
	}
}

void CDrop::subUpdate(CCommand& command, CState& state)
{
	if(isActive)
	{
		// 行動管理
		updateAction(command, state);
		// ライフ管理
		manageLife(state);
	}
	else
	{
		Life = MaxLife;
		Velocity = ZERO_VECTOR3;
		rotateSpeed = 0;
	}
}

void CDrop::subApplyParameter()
{
	float _size = (float)((float)Life / (float)MaxLife) * Size;
	
	Transform.Scale = CVector3(_size, _size, _size);
	Transform.qRotation *= CQuaternion(AXIS_Y, D3DXToRadian(rotateSpeed));
}