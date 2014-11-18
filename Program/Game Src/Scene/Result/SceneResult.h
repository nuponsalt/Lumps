#pragma once

#include "../Scene.h"
#include "../../../Library/Library.h"

// ���U���g�V�[���N���X
class CSceneResult : public CScene
{
public :
	// �f�X�g���N�^
	~CSceneResult() { }

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
	enum RESULT_STATE {
		// �X�R�A�\��
		SCORE,
		RANKING,
		STATE_MAX
	};
	// ��]
	CQuaternion rotationSkyDome;
	// �w�i
	CGRendererSP SkyDome;
	// �v���C���O�X�R�A(���S)
	CGRendererSP ScoreLogo;
	// �v���C���O�X�R�A
	int Score;
	int TotalScore;
	// �v���C���X�R�A�`��J�E���^�[
	CCounterSP ScoreCounter;
	// �����L���O�摜
	CGRendererSP RankingLogo;
	CGRendererSP Ranking1st;
	CGRendererSP Ranking2nd;
	CGRendererSP Ranking3rd;
	CGRendererSP Ranking4th;
	CGRendererSP Ranking5th;
	// �����L���O�X�R�A
	std::vector<int> rankScores;
	// �����L���O�X�R�A�`��J�E���^�[
	CCounterSP rank1Counter;
	CCounterSP rank2Counter;
	CCounterSP rank3Counter;
	CCounterSP rank4Counter;
	CCounterSP rank5Counter;

	// �R���X�g���N�^
	CSceneResult();

protected :
	// �R�}���h�̐���
	CCommand CreateCommand();

};