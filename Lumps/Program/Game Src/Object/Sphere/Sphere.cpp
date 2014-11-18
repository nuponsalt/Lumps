#include "DXUT.h"
#include "Sphere.h"

#include "../../Define.h"

CSphere::CSphere() : Overhead(0), positionYShadow(0)
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/Sphere.xml");
	// 全オブジェクトの初期Y座標
	Transform.Position.y = xml->GetElement("Position")->GetElement("Y")->GetFloat();
	// プレイヤー以外の全オブジェクトの最小サイズ
	MinSize = xml->GetElement("SizeMin")->GetFloat();
	// プレイヤー以外の全オブジェクトの最大サイズ
	MaxSize = xml->GetElement("SizeMax")->GetFloat();
	// 見た目通りの衝突判定の設定
	realSphere.Radius = xml->GetElement("Radius")->GetFloat();
	// 現実を無視した衝突判定の設定(自機以外は基本的に見た目通り)
	bvSphere.Radius = xml->GetElement("gRadius")->GetFloat();
	// 全オブジェクトに対する重力を設定
	Gravity = xml->GetElement("Gravity")->GetFloat();
}

CSphere::~CSphere() { }

CState CSphere::CreateState()
{
	float ground_pos = GROUND_POSITION;
	// ステージとの当たり判定
	const float PLAYER_BOUND = -0.2f;	// 地面との反発係数
	const float FRICTION_RATE = 0.985f;		// 地面との摩擦係数
	bool isHitGround = 
		(isActive) ? CorrectInfinitePlane(ground_pos, Transform.Position.y, realSphere.Radius) : false;
	
	// 衝突時は地上状態
	if (isHitGround)
	{
		State.Add(CState::GROUNDING);
		Velocity.y *= PLAYER_BOUND;
		Speed *= FRICTION_RATE;
	}
	// 重力
	Velocity.y += Gravity;
	
	return State;
}

void CSphere::applyParameter()
{
	// 1フレーム前の座標を保存
	PreviousPosition = Transform.Position;
	// 移動量を加算(アクティブでない場合加算しない)
	Transform.Position += (isActive) ? Velocity : ZERO_VECTOR3;
	
	// 派生クラスでの情報反映
	subApplyParameter();
	
	// 衝突判定の座標
	realSphere.Position = bvSphere.Position = Transform.Position;
	// 描画座標合わせる
	RenderPosition = Transform.Position;
	// 回転を反映
	Transform.qRotation *= ImpactRotation;
	// 描画確認
	if(isRender)
	{
		Model->isRender = true;
	//	Shadow->isRender = true;
	}
	else 
	{
		Model->isRender = false;
	//	Shadow->isRender = false;
	}

	// モデル
	Model->Position = RenderPosition;
	Model->Scale = Transform.Scale;
	Model->qRotation = Transform.qRotation;
	// 影モデル
	if(Shadow == NULL)
		return;
	Shadow->Position = CVector3(RenderPosition.x, positionYShadow, RenderPosition.z);
	Shadow->Scale = Transform.Scale;
	Shadow->qRotation = CQuaternion(AXIS_X, D3DXToRadian(90));
}

void CSphere::Update()
{
	State = CreateState();
	CCommand command = CreateCommand();

	// 派生クラスでの情報更新
	subUpdate(command, State);
	// 情報反映
	applyParameter();
}

void CSphere::isVisible(const CCamera* camera)
{
	if(camera->isCullingFrustum(realSphere))
		isRender = false;
	else 
		isRender = true;
}