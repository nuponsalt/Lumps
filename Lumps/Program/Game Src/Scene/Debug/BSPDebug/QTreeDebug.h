#pragma once

#include "../../Scene.h"
#include <memory>
#include "../../../../Library/Library.h"

//* �萔�Q *//
// �����m�̔����W��
const float gCircleReflection = 0.5f;
// ���ƕǂ̔����W��
const float WallReflection = 0.99f;
// ��������~�̐�
const int gCircleNum = 350;
// ��ԕ������x��
const int gPartitionLebel = 6;
// �d��
const float gGravity = 5.0f;

extern void getNextCirclePosition(Circle &circle);
extern void collisionCircleProc(Circle *c1, Circle *c2);

class QTreeDebug : public CScene
{
public :
	// �f�X�g���N�^
	~QTreeDebug() { }
	
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
	// �~�̕`��p�X�v���C�g
	CSpriteSP spriteCircle;	// ��Փˎ�
	CSpriteSP spriteCollision;	// �Փˎ�
	// �~�I�u�W�F�N�g
	Circle CircAry[gCircleNum];
	// �~�I�u�W�F�N�g���ރc���[�I�u�W�F�N�g
	std::shared_ptr<CTreeObject<Circle>> spTreeObjAry[gCircleNum];
	// ���`���؃I�u�W�F�N�g
	CLinerQuadTreeManager<Circle> LTree;
	// �Փ˔����
	DWORD CollisionNumber;
	// �ՓˑΏۃ��X�g
	CCollisionList<Circle> *ColVector;

	// �R���X�g���N�^
	QTreeDebug();

protected :
	// �R�}���h�̐���
	CCommand CreateCommand();

};

// ��L�f�o�b�O�N���X�̉��ǔ�(���Ǌ�����͂����炪������)
class QTreeDebug_ : public CScene
{
public :
	// �f�X�g���N�^
	~QTreeDebug_() { }
	
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
	// �t���[�����[�g
	CFrameRateCounter updateFPSCount, renderFPSCount;
	float updateFPS, renderFPS;
	// �~�̕`��p�X�v���C�g
	CSpriteSP spriteCircle;	// ��Փˎ�
	CSpriteSP spriteCollision;	// �Փˎ�
	// �~�I�u�W�F�N�g
	std::list<Circle> CircList;
	// �~�I�u�W�F�N�g���ރc���[�I�u�W�F�N�g
	std::vector<std::shared_ptr<CTreeObject<Circle>>> spTrees;
	// ���`���؃I�u�W�F�N�g
	CLinerQuadTreeManager<Circle> LTree;
	// �Փ˔����
	DWORD CollisionNumber;
	// �ՓˑΏۃ��X�g
	CCollisionList<Circle> *ColVector;

	// �R���X�g���N�^
	QTreeDebug_();

protected :
	// �R�}���h�̐���
	CCommand CreateCommand();

};