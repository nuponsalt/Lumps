#include "DXUT.h"
#include "TerrainDebug.h"

CTerrainDebug::CTerrainDebug()
{ }

CSceneSP CTerrainDebug::CreateScene()
{
	return CSceneSP(new CTerrainDebug());
}

void CTerrainDebug::destroyScene()
{
	Terrain.reset();
	Object.reset();
	mainLayer.reset();
}

CCommand CTerrainDebug::CreateCommand()
{
	CCommand command;

	return command;
}

void CTerrainDebug::initializeScene()
{
	// オフスクリーンレンダリング
	mainLayer = CLayer::CreateLayer(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainLayer->board->Position.y = 0.0f;
	
	// xmlファイルの読み込み
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Debug/Terrain/TerrainDebug.xml");

	// 地形モデル
	std::string path = xml->GetElement("Terrain")->GetElement("Path")->GetString();
	Terrain = CGRenderer::CreateFromX(path, CShaderPhong::CreateShader());
	// 判定用オブジェクト
	path = xml->GetElement("Object")->GetElement("Path")->GetString();
	float Size = xml->GetElement("Object")->GetElement("Size")->GetFloat();
	CVector3 pos = CVector3(
		xml->GetElement("Object")->GetElement("Position")->GetElement("X")->GetFloat(),
		xml->GetElement("Object")->GetElement("Position")->GetElement("Y")->GetFloat(),
		xml->GetElement("Object")->GetElement("Position")->GetElement("Z")->GetFloat()
		);
	Object = CGRenderer::CreateFromX(path, CShaderToon::CreateShader());
	Object->Position = pos;
	Object->Scale *= Size;

	deadline = xml->GetElement("DeadLine")->GetFloat();

	// 描画リストに追加
	mainLayer->AddObject(Terrain, RENDER_NORMAL);
	mainLayer->AddObject(Object, RENDER_NORMAL);

	Camera3D = mainLayer->Camera3D;
	Camera2D = mainLayer->Camera2D;
	// カメラの座標を全体を俯瞰できるように設定
	Camera3D->setEye(
		xml->GetElement("CameraPos")->GetElement("X")->GetFloat(),
		xml->GetElement("CameraPos")->GetElement("Y")->GetFloat(),
		xml->GetElement("CameraPos")->GetElement("Z")->GetFloat()
		);
}

void CTerrainDebug::updateScene()
{
	CCommand command = CreateCommand();



	CorrectInfinitePlane(deadline, Object->Position.y, 50);
}

void CTerrainDebug::renderScene()
{
	mainLayer->Render();

	CGraphicsManager::setRenderTargetToBackBuffer();

	mainLayer->board->Render(Camera2D.get());
}

void CTerrainDebug::PlayBGM()
{

}

void CTerrainDebug::StopBGM()
{

}