#pragma once

#include "../../Scene.h"

#include "../../../Camera/CameraThirdPerson.h"

class CShaderDebug : public CScene
{
public :
	// �f�X�g���N�^
	~CShaderDebug() { }

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
	CCameraThirdPersonSP camera;
	CGRendererSP Back;
	CGRendererSP Object;
	CPointSpriteSP particle;
	float speed;

	// �R���X�g���N�^
	CShaderDebug();

protected :
	// �R�}���h����
	CCommand CreateCommand();

};