#pragma once

#include "../../Scene.h"

class CTerrainDebug : public CScene
{
public :
	// �f�X�g���N�^
	~CTerrainDebug() { }

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
	// �n�`���f��
	CGRendererSP Terrain;
	// �Փ˔���e�X�g���f��
	CGRendererSP Object;
	// �ŉ��i�̒n��
	float deadline;
	// �d��
	float gravity;

	// �R���X�g���N�^
	CTerrainDebug();

protected :
	// �R�}���h����
	CCommand CreateCommand();

};