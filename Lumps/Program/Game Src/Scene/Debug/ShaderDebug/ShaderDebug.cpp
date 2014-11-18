#include "DXUT.h"
#include "ShaderDebug.h"

#include "../../../Effect/AnimationEffect.h"

CShaderDebug::CShaderDebug() : speed(0)
{ }

CSceneSP CShaderDebug::CreateScene()
{
	return CSceneSP(new CShaderDebug());
}

void CShaderDebug::destroyScene()
{
	Back.reset();
	Object.reset();
	mainLayer.reset();
	CAnimationEffect::DestroyEffect();
}

CCommand CShaderDebug::CreateCommand()
{
	CCommand command;

	if(DXUTIsKeyDown(VK_LEFT))
		command.Add(CCommand::LEFT);

	if(DXUTIsKeyDown(VK_RIGHT))
		command.Add(CCommand::RIGHT);

	if(DXUTIsKeyDown(VK_UP))
		command.Add(CCommand::UP);

	if(DXUTIsKeyDown(VK_DOWN))
		command.Add(CCommand::DOWN);

	if(DXUTWasKeyPressed(VK_RETURN))
		command.Add(CCommand::CIRCLE);

	if(DXUTWasKeyPressed(VK_SPACE))
		command.Add(CCommand::TRIANGLE);

	return command;
}

void CShaderDebug::initializeScene()
{
	// オフスクリーンレンダリング
	mainLayer = CLayer::CreateLayer(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainLayer->board->Position.y = 0.0f;

	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Debug/Shader/ShaderDebug.xml");
	// 背景
	//Back = CGRenderer::CreateFromX(xml->GetElement("Back")->GetString(), CShaderNormal::Create());
	// モデル
	//Object = CGRenderer::CreateFromX(xml->GetElement("Object")->GetElement("path")->GetString(), CShaderPhong::Create());
	//Object->Position = CVector3(xml->GetElement("Object")->GetElement("Position")->GetElement("X")->GetFloat(), 
	//	xml->GetElement("Object")->GetElement("Position")->GetElement("Y")->GetFloat(), 
	//	xml->GetElement("Object")->GetElement("Position")->GetElement("Z")->GetFloat()
	//	);

	//Object->Scale = CVector3(xml->GetElement("Object")->GetElement("Scale")->GetFloat(),xml->GetElement("Object")->GetElement("Scale")->GetFloat(),xml->GetElement("Object")->GetElement("Scale")->GetFloat());

	//speed = xml->GetElement("Object")->GetElement("speed")->GetFloat();

	//
	//RenderTarget->AddObject(Back, RENDER_NORMAL);
	//RenderTarget->AddObject(Object, RENDER_NORMAL);

	Camera3D = mainLayer->Camera3D;
	Camera2D = mainLayer->Camera2D;
}

void CShaderDebug::updateScene()
{
	CCommand command = CreateCommand();

	if(command.Check(CCommand::LEFT))
	{
		CQuaternion rot(AXIS_Y, D3DXToRadian(speed));
		Object->qRotation *= rot;
	}
	if(command.Check(CCommand::RIGHT))
	{
		CQuaternion rot(AXIS_Y, D3DXToRadian(-speed));
		Object->qRotation *= rot;
	}
	if(command.Check(CCommand::DOWN))
	{
		Object->Position.z --;
	}
	if(command.Check(CCommand::UP))
	{
		Object->Position.z ++;
	}

	if(command.Check(CCommand::CIRCLE))
	{
		CAnimationEffectSP eff = CAnimationEffect::CreateEffect("Resource/XML/Effect/Smoke.xml", CVector3(0, 0, 0));
		mainLayer->AddObject(eff->Board, RENDER_ALPHA);
	}

	if(command.Check(CCommand::TRIANGLE))
	{
		particle = CPointSprite::CreatePointSprite("Resource/Texture/Effect/Perticle.png", 40, 20);
		particle->Position = CVector3(0, 0, 0);
		particle->setisAddBlend(true);
		mainLayer->AddObject(particle, RENDER_NORMAL);
	}

	CAnimationEffect::updateAllEffect();
}

void CShaderDebug::renderScene()
{
	mainLayer->Render();

	CGraphicsManager::setRenderTargetToBackBuffer();

	mainLayer->board->Render(Camera2D.get());
}

void CShaderDebug::PlayBGM()
{
}

void CShaderDebug::StopBGM()
{
}