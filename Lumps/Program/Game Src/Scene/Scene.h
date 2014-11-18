#pragma once

// �V�[���֘A�I�u�W�F�N�g

#include "../../Library/Library.h"
#include <memory>
using namespace KMT;

class CCommand;

class CScene;
typedef std::shared_ptr<CScene> CSceneSP;

// �V�[���^�C�v�̗񋓌^
enum SceneType
{
	Title,
	Play,
	Result,
	SceneTypeMax
};

// �f�o�b�O��p�V�[���^�C�v�̗񋓌^
enum DebugSceneType
{
	BSP,
	BSPlink,
	Shader,
	Terrain,
	Shadow,
	DebugSceneTypeMax
};

class CScene
{
public :
	// �Q�[���S�̂Ŏg���J�����i�o�b�N�o�b�t�@�`��p�j
	static CCameraSP Camera3D;
	static CCameraSP Camera2D;

	// �R���X�g���N�^
	CScene();
	// �f�X�g���N�^
	virtual ~CScene();

	// �I��
	virtual void destroyScene() = 0;
	// ������
	virtual void initializeScene() = 0;
	// �V�[�����̍X�V����
	virtual void updateScene() = 0;
	// �V�[�����̕`�揈��
	virtual void renderScene() = 0;
	// BGM�Đ��֐�
	virtual void PlayBGM() = 0;
	// BGM��~�֐�
	virtual void StopBGM() = 0;

protected :
	// ���C���`��̃��C���[
	CLayerSP mainLayer;
	// �I�����
	int State;
	// ���݃V�[���˓����Ă���̑�����
	size_t Count;
	// �f�o�b�O�\���e�L�X�g(�����g���񂵉\)
	CDebugTextSP Text;
	// BGM
	std::string pathBGM;
	int bgm;
	// �t���[�����[�g
	CFrameRateCounter updateFPSCount, renderFPSCount;
	float updateFPS, renderFPS;

	// �R�}���h�̐���
	virtual CCommand CreateCommand() = 0;

};