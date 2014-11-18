#include "DXUT.h"
#include "QTreeDebug.h"
#include "../../SceneManager.h"

//#include <tchar.h>
#include <time.h>

//* �����o�֐���` *//
QTreeDebug_::QTreeDebug_() : updateFPS(0.0f), renderFPS(0.0f), CollisionNumber(0), ColVector(NULL) { }

CSceneSP QTreeDebug_::CreateScene()
{
	return CSceneSP(new QTreeDebug_());
}

void QTreeDebug_::destroyScene()
{
	Text.reset();
	spriteCircle.reset();
	spriteCollision.reset();
	ColVector->refresh();
}

CCommand QTreeDebug_::CreateCommand()
{
	CCommand command;
	// ���͐������͓��͎�t�Ȃ�
	if(CSceneManager::getisKeyLock_())
		return command;

	// �X�y�[�X�L�[
	if(DXUTWasKeyPressed(VK_SPACE))
		command.Add(CCommand::DEBUG_);
	// Enter
	if(DXUTWasKeyPressed(VK_RETURN))
		command.Add(CCommand::CIRCLE);

	// �S�ẴR�}���h������
	return command;
}

void QTreeDebug_::initializeScene()
{
	srand((unsigned)time(NULL));
	// XML�t�@�C�����f�[�^�擾
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Debug/QTree/QTreeDebug.xml");
	// �e�L�X�g�I�u�W�F�N�g
	Text = CDebugText::CreateText(xml->GetElement("Text")->GetElement("Size")->GetInt(), L"���C���I");
	// �X�v���C�g�̐���
	spriteCircle = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("Circle")->GetString());
	spriteCollision = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("ColCircle")->GetString());

	//* �~�I�u�W�F�N�g�̏����ʒu�E���x�̐ݒ� *//
	// �����ʂƂ���gCircleNum�����~�𐶐�
	for(int i = 0; i < gCircleNum; i++) {
		Circle *circ = new Circle;
		// �~�̔ԍ�
		circ->ID = i;
		// �~�̔��a(2~5�܂Ń����_��)
		circ->Radius = 2 + 3 * (float)rand() / RAND_MAX;
		// �ג��������z�u
		circ->Position.x = (float)i / gCircleNum * 120 + 30 * (float)rand() / RAND_MAX;
		// 
		circ->Position.y = -400 + 700 * (float)i / gCircleNum;
		// ����
		circ->Velocity.x = 0.5f;
		circ->Velocity.y = 0;
		//
		circ->Scale = circ->Radius / 32.0f;
		// ���ʂ͔��a * ���a * ���a�ɔ�Ⴗ��Ƃ���
		circ->Mass = circ->Radius * circ->Radius * circ->Radius;
		CircList.push_back(*circ);
		// TreeObject�ɓo�^
		CTreeObject<Circle> *p = new CTreeObject<Circle>(circ->ID);
		// �o�^
		auto it = CircList.begin();
		while(it != CircList.end())
		{
			if(it->ID != circ->ID)
			{
				it++;
				continue;
			}
			p->pObject = &(*it);
			break;
		}
		spTrees.push_back(std::shared_ptr<CTreeObject<Circle>>(p));
	}

	//* ���`4���؃}�l�[�W�� *//
	//  ��Ԕ͈͂�X=-60�`720; Y=-1200�`520�ɐݒ�
	//  �~����яo���Ȃ��͈͂��w�肷��Ηǂ��̂�
	//  �A�o�E�g�ł�
	if(!LTree.Initialize(gPartitionLebel, 0.0f, -1200.0f, 960.0f, 540.0f))
	{
		//MessageBox(NULL, _T("���`4���؋�Ԃ̏������Ɏ��s���܂����B"), NULL, NULL);
		return;
	}

}

void QTreeDebug_::updateScene()
{
	Count++;
	
	CCommand command = CreateCommand();

	// �~�̈ʒu���X�V���ăc���[�ɍēo�^
	std::vector<std::shared_ptr<CTreeObject<Circle>>>::iterator it = spTrees.begin();
	while(it != spTrees.end()) {
		Circle *pTmp = (*it)->pObject;
		// ���̈ړ��ʒu��������
		getNextCirclePosition(*pTmp);
		// ��x���X�g����O���
		(*it)->Remove();
		// �ēo�^
		LTree.Register(pTmp->Position.x - pTmp->Radius, pTmp->Position.y - pTmp->Radius, pTmp->Position.x + pTmp->Radius, pTmp->Position.y + pTmp->Radius, it->get());
		it++;
	}
	// �ՓˑΉ����X�g���擾
	CollisionNumber = LTree.getAllCollisionList(&ColVector);
	// �Փ˔���
	// 2�Ŋ���̂̓y�A�ɂȂ��Ă���̂�
	CollisionNumber /= 2;
	Circle** pRoot = ColVector->getRootPtr();
	for(DWORD c = 0; c < CollisionNumber; c++) {
		float r2 = (pRoot[c * 2]->Radius + pRoot[c * 2 + 1]->Radius) * (pRoot[c * 2]->Radius+pRoot[c * 2 + 1]->Radius);
		float x = (pRoot[c * 2]->Position.x - pRoot[c * 2 + 1]->Position.x);
		float y = (pRoot[c * 2]->Position.y - pRoot[c * 2 + 1]->Position.y);
		if(r2 >= (x * x) + (y * y))
		{
			// �Ԃ����������m�̃e�N�X�`�����I�����W�ɕύX
			// 

			// 2�~�Փˏ���������
			collisionCircleProc(pRoot[c * 2], pRoot[c * 2 + 1]);
		}
	}

	// �_�������t���[�����[�g�̍Čv�Z
	updateFPS = updateFPSCount.getFrameRate_();
}

void QTreeDebug_::renderScene()
{
	// �~�̕`��
	for(std::list<Circle>::iterator it = CircList.begin(); it != CircList.end(); it++) {
		spriteCircle->Scale = CVector3(it->Scale, it->Scale, 0.0f);
		spriteCircle->Position = it->Position;
		spriteCircle->Render();
	}
	// �c���[���\��
	Text->drawText(10, 10, D3DCOLOR_ARGB(255, 255, 0, 0), L"UpdateFrameRate : %2.5f", updateFPS);
	Text->drawText(10, 30, D3DCOLOR_ARGB(255, 255, 0, 0), L"RenderFrameRate : %2.5f", renderFPS);
	// �~�̐�
	Text->drawText(10, 50, D3DCOLOR_ARGB(255, 255, 0, 0), L"Circle Number : %d", gCircleNum);
	// �Փ˔��萔
	Text->drawText(10, 70, D3DCOLOR_ARGB(255, 255, 0, 0), L"Collision Check Number : %d", CollisionNumber);
	// �œK��
	Text->drawText(10, 90, D3DCOLOR_ARGB(255, 255, 0, 0), L"Optimization : %2.5f ��", 100.0 * (float)(CollisionNumber / 2) / (gCircleNum / 2 * (gCircleNum + 1)));
	// �J�E���g
	Text->drawText(10, 110, D3DCOLOR_ARGB(255, 255, 0, 0), L"Counter = %d", Count);
	
	// �`��t���[�����[�g�̍Čv�Z
	renderFPS = (float)renderFPSCount.getFrameRate_();
}

void QTreeDebug_::PlayBGM()
{
}

void QTreeDebug_::StopBGM()
{
}