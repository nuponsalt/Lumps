#include "DXUT.h"
#include "SceneManager.h"

#include "Transition.h"
#include "Title/SceneTitle.h"
#include "Play/ScenePlay.h"
#include "Result/SceneResult.h"
#include "Debug/BSPDebug/QTreeDebug.h"
#include "Debug/ShaderDebug/ShaderDebug.h"
#include "Debug/TerrainDebug/TerrainDebug.h"

CSceneSP CSceneManager::Scene;
CSceneSP CSceneManager::NextScene;

bool CSceneManager::isKeyLock;
bool CSceneManager::isPause;

void CSceneManager::Initialize_()
{
	Scene = CreateScene(SceneType::Play);
	//Scene = CreateDebugScene(DebugSceneType::Shader);
	// �ŏ��̃V�[���̏�����
	Scene->initializeScene();
	// ���̃V�[���͋��
	NextScene = NULL;
	// ���R�ɑ���\
	isKeyLock = false;
	// ��|�[�Y���
	isPause = false;

// �����[�X�r���h��
#if !_DEBUG
	// BGM�Đ�
	Scene->PlayBGM();
#endif

	// �g�����W�V����������
	CTransition::initializeTransition();
}

void CSceneManager::Destroy_()
{
	// �g�����W�V�����}�l�[�W���[�̉��
	CTransition::Destroy();
	// ���݂̃V�[���̃p�����[�^�j��
	Scene->destroyScene();
	// ���݂̃V�[���̉��
	Scene.reset();
	// ���̃V�[�����Z�b�g����Ă����ꍇ�A������������
	if(NextScene != NULL) NextScene.reset();
}

void CSceneManager::Update_()
{
	// �g�����W�V��������������Ă���΁A�V�[���J�ڊ֐����Ă�
	if(CTransition::IsExistTransition()) TransitionScene();
	// ���݂̃V�[���̍X�V�Ăяo��
	Scene->updateScene();
}

void CSceneManager::Render_()
{
	// �S�V�[���p�̃J�����̍X�V
	if(CScene::Camera3D != NULL) CScene::Camera3D->updateView();
	if(CScene::Camera2D != NULL) CScene::Camera2D->updateView();
	// ���݂̃V�[���̕`��Ăяo��
	Scene->renderScene();
	// �g�����W�V�����̕`��Ăяo��
	CTransition::Render();
}

void CSceneManager::setNextScene_(const CSceneSP _scene)
{
	// ���̃V�[����ݒ�
	NextScene = _scene;
	// �g�����W�V��������
	CTransition::CreateTransition();
}

CSceneSP CSceneManager::CreateScene(const SceneType& elem)
{
	// �Ή�����V�[�������������
	return (elem == SceneType::Title) ? CSceneTitle::CreateScene() : (elem == SceneType::Play) ? CScenePlay::CreateScene() : CSceneResult::CreateScene();
}

CSceneSP CSceneManager::CreateDebugScene(const DebugSceneType& elem)
{
	// �Ή�����V�[�������������
	return (elem == DebugSceneType::BSP) ? QTreeDebug::CreateScene() 
		: (elem == DebugSceneType::BSPlink) ? QTreeDebug_::CreateScene()
		: (elem == DebugSceneType::Shader) ? CShaderDebug::CreateScene()
		: CTerrainDebug::CreateScene();
}

void CSceneManager::ChangeScene()
{
	// BGM���~
	Scene->StopBGM();	
	// ���݂̃V�[����j��
	Scene->destroyScene();
	// �V�[���̓���ւ�
	Scene = NextScene;
	// ����ւ�����V�[���̏�����
	Scene->initializeScene();

// �����[�X�r���h��
#if !_DEBUG
	// BGM���Đ�
	Scene->PlayBGM();
#endif

	// �ݒ肵�Ă����J�ڐ����ɂ���
	NextScene = NULL;
}

void CSceneManager::TransitionScene()
{
	// �L�[���쐧��
	LockKey();
	// �t�F�[�h�A�E�g�J�n
	// ���̃V�[�����Z�b�g����Ă��āA�Ȃ����t�F�[�h�A�E�g���������Ă���΁A�V�[������ւ��֐����Ă�
	if(NextScene != NULL && CTransition::FadeOut()) ChangeScene();
	// �t�F�[�h�C���J�n
	// �t�F�[�h�C��������������A�g�����W�V�������������
	if(NULL == NextScene && CTransition::FadeIn()){
		CTransition::DestroyTransition();
		UnLockKey();
		UnPause_();
	}
}