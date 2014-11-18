#pragma once

#include "Scene.h"

// �V�[���Ǘ��}�l�[�W���[
class CSceneManager
{
public :
	// ������
	static void Initialize_();
	// �S�Ẵ��W�b�N����
	static void Update_();
	// �S�Ă̕`�揈��
	static void Render_();
	// �I��
	static void Destroy_();
	// �L�[���쐧���t���O�擾�֐�
	static const bool getisKeyLock_() { return isKeyLock; }
	// �擾 : �|�[�Y�t���O
	static const bool getisPause_() { return isPause; }
	// �L�[���쐧���֐�
	static void LockKey() { isKeyLock = true; }
	// �L�[���쐧�������֐�
	static void UnLockKey() { isKeyLock = false; }
	// �|�[�Y
	static void Pause_() { isPause = true; }
	// �|�[�Y����
	static void UnPause_() { isPause = false; }
	// ���̃V�[�����Z�b�g����֐�
	// arg1..���̃V�[���̃C���X�^���X
	static void setNextScene_(const CSceneSP _scene);

private :
	// ���݂̃V�[��
	static CSceneSP Scene;
	// ���̃V�[��
	static CSceneSP NextScene;
	// �L�[���쐧���p
	static bool isKeyLock;
	// �|�[�Y
	static bool isPause;
	
	// �R���X�g���N�^
	CSceneManager() { } 
	// �f�X�g���N�^
	~CSceneManager() { }

	// �V�[���J��
	static void ChangeScene();
	// �V�[���J�ڏ����֐�
	static void TransitionScene();

protected :
	// �V�[������
	static CSceneSP CreateScene(const SceneType& _element);
	// �V�[������(�f�o�b�O�p�V�[��)
	static CSceneSP CreateDebugScene(const DebugSceneType& _element);


};