#pragma once

#include "../Scene.h"
#include <memory>
#include "../../Object/Sphere/Sphere.h"

// �^�C�g���V�[���N���X
class CSceneTitle : public CScene
{
public :
	// �f�X�g���N�^
	~CSceneTitle() { }

	// ����
	static CSceneSP CreateScene();
	// ����������
	void initializeScene();
	// �I������
	void destroyScene();
	// �X�V����
	void updateScene();
	// �`�揈��
	void renderScene();
	// BGM�Đ��֐�
	void PlayBGM();
	// BGM��~�֐�
	void StopBGM();

private :
	// ���j���[�^�C�v
	enum MENU_TYPE{
		// �v���C�I��
		MENU_PLAY,
		// �I���I��
		MENU_EXIT,
		// ���j���[�ő吔
		MENU_MAX
	};
	// ���j���[�\���t���O
	bool isBrowseMenu;
	// �I�����
	int stateMenu;
	// �J�����������W
	CVector3 Target[MENU_MAX+1];
	int TargetState;
	// ��]
	CQuaternion RotationAxisY, RotationAxisX;
	CQuaternion rotationSkyDome;
	// �w�i
	CGRendererSP BackGround;
	// �^�C�g�����S(3D���f��, �ꕶ�����ʂɃR���g���[������)
	CGRendererSP titleL;
	CGRendererSP titleU;
	CGRendererSP titleM;
	CGRendererSP titleP;
	CGRendererSP titleS;
	// �I�����f�� : �v���C
	CGRendererSP UnPress;
	CGRendererSP playModel;
	CGPlaneSP playLogo;
	CGRendererSP exitModel;
	CGPlaneSP exitLogo;

	// SE
	std::string pathSelectSE;
	std::string pathDecideSE;
	std::string pathCancelSE;

	// �R���X�g���N�^
	CSceneTitle();
	// �p�����[�^�̔��f
	void appllyParameter();

protected :
	// �R�}���h�̐���
	CCommand CreateCommand();

};