#include "DXUT.h"
#include "Scene.h"

#include "../../Library/Library.h"

//----------------------------------------------------------------------------
// CScene

CCameraSP CScene::Camera3D;
CCameraSP CScene::Camera2D;

CScene::CScene() : State(0), Count(0), bgm(0), updateFPS(0.0f), renderFPS(0.0f)
{
	Camera3D = CCamera::Create();
	Camera2D = CCamera::Create();

	float angle = Camera2D->getAngle();
	Camera2D->setEye(0, 0, -(SCREEN_HEIGHT / (2.0f * tan(angle / 2.0f))));
}

CScene::~CScene()
{
	Camera3D.reset();
	Camera2D.reset();
}