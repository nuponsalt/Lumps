#pragma once

#include "../Scene.h"
#include <memory>
#include "../../Object/Sphere/Sphere.h"
#include "../../Object/Sphere/Player/Player.h"

typedef std::shared_ptr<CTreeObject<Sphere>> SphereTreeObjSP;
typedef std::weak_ptr<CTreeObject<Sphere>> SphereTreeObjWP;

// �v���C�V�[���N���X
class CScenePlay : public CScene
{
public :
	// �f�X�g���N�^
	~CScenePlay() { }

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
	
	// �擾 : �X�R�A
	static inline float getScore() { return ScoreVolume; }
	static inline float getTotalScore() { return TotalScoreVolume; }

private :
	// �|�[�Y���j���[�̎��
	enum PauseMenuType {
		// �Q�[���𑱂���
		PAUSE_CONTINUE,
		// ���C�����j���[�ɖ߂�
		PAUSE_MAINMENU,
		// ���j���[�̐�
		PAUSE_MAX
	};
	// �V�[�P���X
	enum SEQ_TYPE {
		SEQ_BEGIN,
		SEQ_MAIN,
		SEQ_PAUSE,
		SEQ_END,
		SEQ_MAX
	};
	// �V�[�P���X���
	SEQ_TYPE SequenceState;

	// �I���J�E���g
	int EndCounter;
	// �I�����鎞��
	int EndCount;

	// �~�j�}�b�v���C���[
	CLayerSP minimapLayer;

	// �|�[�Y�摜
	CGPlaneSP PauseImage;
	// �X�J�C�h�[��
	CGRendererSP SkyDome;
	// �n�ʍŉ��i
	CGRendererSP UnderGround;
	// ��
	CGRendererSP Wall;
	// �����Փ˔���(std::vector)
	std::vector<Segment> segs;
	// �~�j�}�b�v�w�i
	CGPlaneSP minimapBack;

	// �X�^�[�g, �^�C���A�b�v���S
	CGRendererSP StartLogo, TimeupLogo;
	// ���E��
	float BorderLine;
	// �A���t�@���Z�l
	float AddAlpha;
	// �i�s����
	CVector3 Direct;

	// ���̏o������
	CTimerSP PopTimer;
	// �v���C���[
	CPlayerSP Player;
	// �e�X�g�p
	std::list<CSphereSP> FallList;
	// �쐶�̃I�u�W�F�N�g���X�g
	std::list<CSphereWP> NativeList;
	// ��ɂȂ��Ă���I�u�W�F�N�g���X�g
	std::vector<CSphereWP> Links;

	// �`�搔
	int renderNum;

	// ��������
	int TimeLimit;
	// �������Ԍv�Z�p�^�C�}�[
	CTimerSP CompTimer;
	// �������ԕ`��p�J�E���^�[
	CCounterSP TimeCounter;
	// �X�R�A(���������̐�)
	float Score;
	static float ScoreVolume;
	// �X�R�A(�����̐�)
	static float TotalScoreVolume;
	// �T�C�Y�\�L�`��p�J�E���^�[
	CCounterSP SizeCounter;
	// UI�摜
	CSpriteSP UI, ScoreUI;
	
	// SE
	std::string pathBackTitleSE, pathGoodSE, pathBadSE;
	bool isPlay; // �Đ��t���O
	CTimerSP resetTimer; // �t���O���Z�b�g�p�^�C�}�[

	// �R���X�g���N�^
	CScenePlay() ;

	//* UI *//
	// ���[�U�[�C���^�[�t�F�[�X�̏�����
	void initializeUI();
	// ���[�U�[�C���^�[�t�F�[�X�̍X�V
	void updateUI();
	// ���[�U�[�C���^�[�t�F�[�X�̕`��
	void renderUI();

	// �f�o�b�O�`��
	void renderDebug();

	//* �I�u�W�F�N�g *//
	// �������̐���
	void CreateFall(CSphereSP _obj);
	// ��������(���Ԍo��) : �����_�����W(ZX)
	void PopObjectRandom();
	// ��̍X�V
	void subupdateLinks();
	// �ǏՓˎ��̕␳
	void correctWall();

	// xml����̃p�����[�^�[�ǂݍ���
	void initializeObjects();
	// �I�u�W�F�N�g�̍X�V
	void updateObjects();

	//* �V�[�����V�[�P���X�Ǘ� *//
	// �V�[�P���X�֐��|�C���^�z��
	bool (CScenePlay::*Sequence[SEQ_MAX])(CCommand &command);
	// �V�[�P���X : �J�n
	bool SequenceBegin(CCommand &command);
	// �V�[�P���X : �v���C
	bool SequenceMain(CCommand &command);
	// �V�[�P���X : �|�[�Y
	bool SequencePause(CCommand &command);
	// �V�[�P���X : �I��
	bool SequenceEnd(CCommand &command);

protected :
	// �R�}���h�̐���
	CCommand CreateCommand();

} ;