#include "DXUT.h"
#include "QTreeDebug.h"

#include "../../SceneManager.h"
//#include <tchar.h>
#include <time.h>

//* �O���[�o���֐� *//
// ���̉~�̈ʒu���Z�o
void getNextCirclePosition(Circle &circle)
{
	// ���ˌ�̑��x�x�N�g��
	CVector3 refV;
	// �Փˈʒu
	CVector3 ColPos;
	// �Փˌ�̈ړ��\����
	float resTime = 0.0f;
	// �d�͂��|���ė��Ƃ�
	// 1�t���[����9.8/60(m/s)����
	circle.Velocity.y += gGravity / 60;	

	// ���̑��x�ňʒu���X�V
	// �O�̈ʒu��ۑ�
	circle.PreviousPosition = circle.Position;
	// �ʒu�X�V
	circle.Position += circle.Velocity;

	// �ǂƂ̏Փ˂��`�F�b�N
	// ����
	if(circle.Position.x < 0)
	{
		// ���ˌ�̑��x�x�N�g�����擾
		getReflectVelocity(&refV, CVector3(1, 0 ,0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		// �c�莞�ԎZ�o
		resTime = circle.Position.x / circle.Velocity.x;
		// ���ˌ�̈ʒu���Z�o
		getReflectedPosition(resTime, circle, refV);
	}
	// �E��
	else if(circle.Position.x > 960)
	{
		getReflectVelocity(&refV, CVector3(-1, 0, 0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		resTime = (circle.Position.x - 960) / circle.Velocity.x;
		getReflectedPosition(resTime, circle, refV);
	}
	// ���
	else if(circle.Position.y < -1200)
	{
		getReflectVelocity(&refV, CVector3(0, 1, 0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		resTime = (circle.Position.y + 1200) / circle.Velocity.y;
		getReflectedPosition(resTime, circle, refV);
	}
	// ����
	else if(circle.Position.y > 540){
		getReflectVelocity(&refV, CVector3(0, -1, 0), CVector3(circle.Velocity.x, circle.Velocity.y, 0), WallReflection);
		resTime = (circle.Position.y - 540) / circle.Velocity.y;
		getReflectedPosition(resTime, circle, refV);
	}
}

// 2�~�Փˏ���
void collisionCircleProc(Circle *c1, Circle *c2)
{
	float time = 0;
	CVector3 C1Position, C2Position, C1Velocity, C2Velocity;

	// �Փ˂��Ă���2�~�̏Փˈʒu�����o
	if(!calculateParticleCollision(c1->Radius, c2->Radius,
		&CVector3(c1->PreviousPosition.x, c1->PreviousPosition.y, 0),
		&CVector3(c1->Position.x, c1->Position.y, 0),
		&CVector3(c2->PreviousPosition.x, c2->PreviousPosition.y, 0),
		&CVector3(c2->Position.x, c2->Position.y, 0),
		&time,
		&C1Position,
		&C2Position))
		return;	// �Փ˂��Ă��Ȃ��悤�ł�

	// �Փˈʒu��O�ʒu�Ƃ��ĕۑ�
	c1->Position = C1Position;
	c2->Position = C2Position;
	c1->PreviousPosition = C1Position;
	c2->PreviousPosition = C2Position;

	// �Փˌ�̑��x���Z�o
	if(!calculateParticlePositionAfterCollision(
		&C1Position, &CVector3(c1->Velocity.x, c1->Velocity.y, 0),
		&C2Position, &CVector3(c2->Velocity.x, c2->Velocity.y, 0),
		c1->Mass, c2->Mass,
		// ���̔����W��
		gCircleReflection, gCircleReflection,
		time,
		&C1Position, &C1Velocity,
		&C2Position, &C2Velocity))
		return; // �������s�����悤�ł�

	// �Փˌ�ʒu�Ɉړ�
	c1->Velocity = C1Velocity;
	c2->Velocity = C2Velocity;
	c1->Position += c1->Velocity;
	c2->Position += c2->Velocity;
}

//* �����o�֐���` *//
QTreeDebug::QTreeDebug() : CollisionNumber(0), ColVector(NULL) { }

CSceneSP QTreeDebug::CreateScene()
{
	return CSceneSP(new QTreeDebug());
}

void QTreeDebug::destroyScene()
{
	Text.reset();
	spriteCircle.reset();
	spriteCollision.reset();
	ColVector->refresh();
}

CCommand QTreeDebug::CreateCommand()
{
	CCommand command;
	// ���͐������͓��͎�t�Ȃ�
	if(CSceneManager::getisKeyLock_())
		return command;
	if(DXUTWasKeyPressed(VK_RETURN))
		command.Add(CCommand::CIRCLE);
	
	// �S�ẴR�}���h������
	return command;
}

void QTreeDebug::initializeScene()
{
	srand((unsigned int)time(NULL)) ;
	// XML�t�@�C�����f�[�^�擾
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Debug/QTree/QTreeDebug.xml");
	// �e�L�X�g�I�u�W�F�N�g
	Text = CDebugText::CreateText(xml->GetElement("Text")->GetElement("Size")->GetInt(), L"���C���I");
	// �X�v���C�g�̐���
	spriteCircle = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("Circle")->GetString());
	spriteCollision = CSprite::CreateFromFile(xml->GetElement("Image")->GetElement("ColCircle")->GetString());

	//* �~�I�u�W�F�N�g�̏����ʒu�E���x�̐ݒ� *//
	// g_CircleNum�����~�𐶐�
	for(int i = 0; i < gCircleNum; i++) {
		CircAry[i].ID = i;
		// �~�̔��a(2�`5�܂Ń����_��)
		CircAry[i].Radius = 2 + 3 * (float)rand() / RAND_MAX;
		// �ג��������ʒu
		CircAry[i].Position.x = (float)i / gCircleNum * 120 + 30 * (float)rand() / RAND_MAX;
		// ���\�����Ƃ��납�痎�Ƃ��܂�
		CircAry[i].Position.y = -400 + 700 * (float)i / gCircleNum;
		// �����i�K��)
		CircAry[i].Velocity.x = 0.5;
		CircAry[i].Velocity.y = 0;
		// �摜��64�~64�Ȃ̂ŃX�P�[���l�͂����Ȃ��ł��I
		CircAry[i].Scale = CircAry[i].Radius / 32.0f;
		// ���ʂ͔��a��3��ɔ��Ƃ��܂�
		CircAry[i].Mass = CircAry[i].Radius * CircAry[i].Radius * CircAry[i].Radius;
		// TreeObject�ɓo�^
		CTreeObject<Circle> *p = new CTreeObject<Circle>(i);
		// �o�^
		p->pObject = &CircAry[i];
		spTreeObjAry[i].reset(p);
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

void QTreeDebug::updateScene()
{
	Count++;
	
	CCommand command = CreateCommand();

	// �~�̈ʒu���X�V���ăc���[�ɍēo�^
	for(int i = 0; i < gCircleNum; i++)
	{
		int id = i;
		//
		Circle *pTmp = spTreeObjAry[id]->pObject;
		// ���̈ړ��ʒu��������
		getNextCirclePosition(*pTmp);
		// ��x���X�g����O���
		spTreeObjAry[id]->Remove();
		// �ēo�^
		CTreeObject<Circle> *_pTree = spTreeObjAry[id].get();
		LTree.Register(pTmp->Position.x - pTmp->Radius, pTmp->Position.y - pTmp->Radius, pTmp->Position.x + pTmp->Radius, pTmp->Position.y + pTmp->Radius, _pTree);
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

void QTreeDebug::renderScene()
{
	for(int i = 0; i < gCircleNum; i++) {
		spriteCircle->Scale = CVector3(CircAry[i].Scale, CircAry[i].Scale, 0.0f);
		spriteCircle->Position = CircAry[i].Position;
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

void QTreeDebug::PlayBGM()
{
}

void QTreeDebug::StopBGM()
{
}