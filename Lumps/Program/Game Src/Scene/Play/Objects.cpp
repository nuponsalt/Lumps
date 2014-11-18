#include "DXUT.h"
#include "ScenePlay.h"
#include "../../Object/Sphere/Player/Player.h"
#include "../../Object/Sphere/Drop/Drop.h"

#include "../../Effect/AnimationEffect.h"

//* �O���[�o���X�R�[�v *//
// �Փˌ�̋����m�̕␳
bool CollidedSpheres(CVector3 &vA, CVector3 &vB, float rA, float rB)
{
	if(!getCollideSpheres(vA, vB, rA, rB))
		return false;

	CVector3 center = (vA + vB) * 0.5f;

	//// �Z���^�[����P�ւ̃x�N�g��
	CVector3 centertoA = vA - center;
	//// �Z���^�[����Q�x�N�g��
	CVector3 centertoB = vB - center;

	centertoA.Normalize();
	centertoB.Normalize();

	vA = center + (centertoA * 0.5);
	vB = center + (centertoB * 0.5);
	return true;
}

void CScenePlay::correctWall()
{
	// �������_, ���a, �����ɂ�����I�_
	CVector3 Strength, epos, IntersectPt, NearPt;
	// �l�ӂ̏����͓����Ȃ̂�for���[�v
	for (size_t i = 0; i < segs.size(); i++)
	{
		// ������̍ŋߓ_�̎Z�o
		NearPt = NearOnLine(CVector3(Player->Transform.Position.x, 0.0f, Player->Transform.Position.z), segs[i].s, segs[i].e);
		// �ŋߓ_����ɖ@���x�N�g�����Z�o
		Strength = Normalize(NearPt - CVector3(Player->Transform.Position.x, 0.0f, Player->Transform.Position.z)) * Player->realSphere.Radius;
		// �I�_�̌v�Z
		epos = Player->Transform.Position + Strength;
		// ����
		if(getCollideSegments(&IntersectPt, 
			CVector3(Player->Transform.Position.x, Player->Transform.Position.z, 0), CVector3(epos.x, epos.z,0), 
			CVector3(segs[i].s.x, segs[i].s.z, 0), CVector3(segs[i].e.x, segs[i].e.z, 0)
			))
			// �␳
			Player->Transform.Position = NearPt - Strength;
	}
}

void CScenePlay::CreateFall(CSphereSP _obj)
{
	FallList.push_back(_obj);
	// �쐶�̃I�u�W�F�N�g
	NativeList.push_back(_obj);
	// �����_�[�^�[�Q�b�g
	mainLayer->AddObject(_obj->Model, RENDER_NORMAL);
	//mainLayer->AddObject(_obj->Shadow, RENDER_ALPHA);
}

void CScenePlay::PopObjectRandom()
{
	int _time = TimeLimit;
	// �����ɐ������鐔
#if _DEBUG
	const int CREATENUM = 1;
#else
	const int CREATENUM = 2;
#endif
	if(_time > 0 && PopTimer->TimeCount() && FallList.size() < 500)
	{
		CSphereSP _obj[CREATENUM];
		CVector3 _position[CREATENUM]; 
		for (int i = 0; i < CREATENUM; i++) {
			_position[i].y = 50.0f;
			_position[i].x = (float)GetRandom(-500, 500);
			_position[i].z = (float)GetRandom(-500, 500);
			_obj[i] = CDrop::Create();
			_obj[i]->Transform.Position = _position[i];
			CreateFall(_obj[i]);
		}
	}
}

void CScenePlay::initializeObjects()
{
	// xml�t�@�C���̓ǂݍ���
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Play/ScenePlay.xml");
	
	// �f�o�b�O�e�L�X�g�`��I�u�W�F�N�g
	Text = CDebugText::CreateText(xml->GetElement("FontSize")->GetInt(), L"���C���I");
	
	// �I�����鎞��(����3�b)
	EndCount = xml->GetElement("EndCount")->GetInt();

	// ���E��(Z)���W
	BorderLine = xml->GetElement("Border")->GetFloat();

	// �o������
	int _time = xml->GetElement("PopTimer")->GetInt();
	PopTimer = CTimerSP(new CTimer(_time));

	//* ���C�����C���[ *//
	// ���C�����C���[������
	mainLayer = CLayer::CreateLayer(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainLayer->board->Position.y = xml->GetElement("MainLayer")->GetElement("Position")->GetElement("Y")->GetFloat();
	
	// �|�[�Y�摜
	std::string _path = xml->GetElement("pauseImage")->GetElement("path")->GetString();
	float posX = xml->GetElement("pauseImage")->GetElement("Position")->GetElement("X")->GetFloat();
	float posY = xml->GetElement("pauseImage")->GetElement("Position")->GetElement("Y")->GetFloat();
	float posZ = xml->GetElement("pauseImage")->GetElement("Position")->GetElement("Z")->GetFloat();
	PauseImage = CGPlane::CreateFromTexture(_path);
	PauseImage->Position = CVector3(posX, posY, posZ);
	PauseImage->isRender = false;
	
	// �X�J�C�h�[��
	_path = xml->GetElement("SkyDome")->GetElement("path")->GetString();
	posX = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("SkyDome")->GetElement("Position")->GetElement("Z")->GetFloat();
	SkyDome = CGRenderer::CreateFromX(_path, CShaderNormal::CreateShader());
	SkyDome->Position = CVector3(posX, posY, posZ);
	
	// �n�ʃ��f��
	_path = xml->GetElement("UnderGround")->GetElement("path")->GetString();
	posX = xml->GetElement("UnderGround")->GetElement("Position")->GetElement("X")->GetFloat(); 
	posY = xml->GetElement("UnderGround")->GetElement("Position")->GetElement("Y")->GetFloat(); 
	posZ = xml->GetElement("UnderGround")->GetElement("Position")->GetElement("Z")->GetFloat();
	UnderGround = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	UnderGround->Position = CVector3(posX, posY, posZ);
	UnderGround->Scale = CVector3(
		xml->GetElement("UnderGround")->GetElement("Scale")->GetElement("X")->GetFloat(), 
		xml->GetElement("UnderGround")->GetElement("Scale")->GetElement("Y")->GetFloat(), 
		xml->GetElement("UnderGround")->GetElement("Scale")->GetElement("Z")->GetFloat()
		);
	
	// ��
	_path = xml->GetElement("Wall")->GetElement("path")->GetString();
	posX = xml->GetElement("Wall")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("Wall")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("Wall")->GetElement("Position")->GetElement("Z")->GetFloat();
	float scale = xml->GetElement("Wall")->GetElement("scale")->GetFloat();
	float scaleY = xml->GetElement("Wall")->GetElement("scaleY")->GetFloat();
	Wall = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	Wall->setisAddBlend(true);
	Wall->Position = CVector3(posX, posY, posZ);
	Wall->Scale = CVector3(scale, scaleY, scale);
	Wall->setColorRGBA(1,1,1,1);

	for(int i = 0; i < xml->GetElement("SegmentNum")->GetInt(); i++)
	{
		Segment seg;
		seg.s.x = xml->GetElement("Segment", i)->GetElement("Start")->GetElement("X")->GetFloat();
		seg.s.y = xml->GetElement("Segment", i)->GetElement("Start")->GetElement("Y")->GetFloat();
		seg.s.z = xml->GetElement("Segment", i)->GetElement("Start")->GetElement("Z")->GetFloat();
		seg.e.x = xml->GetElement("Segment", i)->GetElement("End")->GetElement("X")->GetFloat();
		seg.e.y = xml->GetElement("Segment", i)->GetElement("End")->GetElement("Y")->GetFloat();
		seg.e.z = xml->GetElement("Segment", i)->GetElement("End")->GetElement("Z")->GetFloat();
		segs.push_back(seg);
	}

	// �X�^�[�g���S
	_path = xml->GetElement("StartLogo")->GetElement("path")->GetString();
	posX = xml->GetElement("StartLogo")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("StartLogo")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("StartLogo")->GetElement("Position")->GetElement("Z")->GetFloat();
	scale = xml->GetElement("StartLogo")->GetElement("Scale")->GetFloat();
	StartLogo = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	StartLogo->Position = CVector3(posX, posY, posZ);
	StartLogo->Scale = CVector3(scale, scale, scale);
	StartLogo->vColorRGBA.w = 0;

	// �^�C���A�b�v���S
	_path = xml->GetElement("EndLogo")->GetElement("path")->GetString();
	posX = xml->GetElement("EndLogo")->GetElement("Position")->GetElement("X")->GetFloat();
	posY = xml->GetElement("EndLogo")->GetElement("Position")->GetElement("Y")->GetFloat();
	posZ = xml->GetElement("EndLogo")->GetElement("Position")->GetElement("Z")->GetFloat();
	scale = xml->GetElement("EndLogo")->GetElement("Scale")->GetFloat();
	TimeupLogo = CGRenderer::CreateFromX(_path, CShaderLambert::CreateShader());
	TimeupLogo->Position = CVector3(posX, posY, posZ);
	TimeupLogo->Scale = CVector3(scale, scale, scale);
	TimeupLogo->isRender = false;

	// �A���t�@���Z�l
	AddAlpha = xml->GetElement("AddAlphaRate")->GetFloat();

	// BGM
	pathBGM = xml->GetElement("BGM")->GetString();
	CSoundManager::Load(pathBGM);
	// SE
	pathBackTitleSE = xml->GetElement("SE")->GetElement("backtitle")->GetString();
	CSoundManager::Load(pathBackTitleSE);
	pathGoodSE = xml->GetElement("SE")->GetElement("good")->GetString();
	CSoundManager::Load(pathGoodSE);
	pathBadSE = xml->GetElement("SE")->GetElement("bad")->GetString();
	CSoundManager::Load(pathBadSE);
	// ���Z�b�g�^�C�}�[
	_time = xml->GetElement("ResetTimer")->GetInt();
	resetTimer = CTimerSP(new CTimer(_time));
	
	// �v���C���[
	Player = CPlayer::Create();
	//* �Q�[���I�u�W�F�N�g�����ꂼ��̃��X�g�ɑ}�� *//
	// �v���C���[�����삵�Ă����
	Links.push_back(Player);
	
	// ���C�����C���[�̃J�������v���C���[�̃J�����ɐݒ�
	mainLayer->Camera3D = Player->getCamera();

	// ���C�����C���[�̃����_�[���X�g�ɒǉ�
	mainLayer->AddObject(SkyDome, RENDER_NORMAL);
	mainLayer->AddObject(UnderGround, RENDER_NORMAL);
	mainLayer->AddObject(Wall, RENDER_ALPHA);
	mainLayer->AddObject(Player->Model, RENDER_NORMAL);
	mainLayer->AddObject(Player->Shadow, RENDER_ALPHA);
	mainLayer->AddObject(PauseImage, RENDER_FRONT2D);
	mainLayer->AddObject(StartLogo, RENDER_ALPHA);
	mainLayer->AddObject(TimeupLogo, RENDER_NORMAL);

	//* �~�j�}�b�v���C���[ *//
	// �~�j�}�b�v���C���[������
	minimapLayer = CLayer::CreateLayer(
		xml->GetElement("MinimapLayer")->GetElement("Size")->GetElement("Width")->GetInt(), 
		xml->GetElement("MinimapLayer")->GetElement("Size")->GetElement("Height")->GetInt()
		);
	minimapLayer->board->Position = CVector3(
		xml->GetElement("MinimapLayer")->GetElement("Position")->GetElement("X")->GetFloat(),
		xml->GetElement("MinimapLayer")->GetElement("Position")->GetElement("Y")->GetFloat(),
		xml->GetElement("MinimapLayer")->GetElement("Position")->GetElement("Z")->GetFloat()
		);
	// �~�j�}�b�v���C���[�̃J�����ݒ�
	minimapLayer->Camera3D->setEye(0, xml->GetElement("EyeY")->GetFloat(), 0);
	minimapLayer->Camera3D->setLookAt(0, 0, 0);
	minimapLayer->Camera3D->setUp(0, 0, 1);

	// �~�j�}�b�v�w�i

}

void CScenePlay::subupdateLinks()
{
	// �C�e���[�^��p��(���X�g�̓�����)
	auto native_it = NativeList.begin() ;
	while(native_it != NativeList.end())
	{
		// �t���O	
		bool inc = true;
		for(int i = 0; i < Links.size(); i++)
		{
			// ���W
			CVector3 a = (*native_it).lock()->bvSphere.Position;
			CVector3 b = Player->bvSphere.Position;
			// ���a(�Փ˔���ł݂̂̎g�p)
			float ra = (*native_it).lock()->bvSphere.Radius;
			float rb = Player->bvSphere.Radius;
			// �����m�̔���Ȃ̂Ŕ��a���m�ŏՓ˔�����s��(�Փ˂��Ȃ���΂����艺�̏������΂�)or �T�C�Y�����ݍő�T�C�Y�̏ꍇ������
			if(!getCollideSpheres(a, b, ra, rb) || (*native_it).lock()->getSize() >= (*native_it).lock()->getSizeMax() * 0.009f * CPlayer::getStSize()) 
				continue;
			
			// SE�Đ�
			CSoundManager::Play(pathGoodSE, CSoundManager::MODE_ONCE);
			// [ ���������I�u�W�F�N�g ]�̌����𔍒D
			(*native_it).lock()->isActive = false;
			Player->Volume += (*native_it).lock()->Volume;
			ScoreVolume += (*native_it).lock()->Volume;
			TotalScoreVolume = Player->Volume;
			// ���΍��W�Z�o
			D3DXVECTOR3 ab = b - a; // a ���� b �ւ̑��΍��W
			D3DXVECTOR3 ba = a - b; // b ���� a �ւ̑��΍��W
			// [ ������ɍs�����I�u�W�F�N�g ] �̃����N�f�[�^�� [ ���������I�u�W�F�N�g ] �̃f�[�^��ǉ�
			Links[i].lock()->Links.push_back((*native_it).lock());
			Links[i].lock()->LocalPositions.push_back(ba);
			Links[i].lock()->BaseRotations.push_back(Links[i].lock()->Transform.qRotation);
			// [ ���������� ] �̃����N�f�[�^�� [ ������ɍs�����I�u�W�F�N�g ] �̃f�[�^��ǉ�
			(*native_it).lock()->Links.push_back(Links[i].lock());
			(*native_it).lock()->LocalPositions.push_back(ab);
			(*native_it).lock()->BaseRotations.push_back((*native_it).lock()->Transform.qRotation);
			// �򃊃X�g�� [ ���������I�u�W�F�N�g ] ��ǉ�
			Links.push_back((*native_it).lock());
			// �쐶���X�g���� [ ���������I�u�W�F�N�g ] ���폜
			native_it = NativeList.erase(native_it);

			inc = false;
			break;
		}
		// ���̌��m
		if(inc){
			native_it++;
		}
	}
}

void CScenePlay::updateObjects()
{
	renderNum = 0;

	auto fall_it = FallList.begin();
	while(fall_it != FallList.end())
	{
		if((*fall_it)->getisRender())
			++renderNum;
		// ���łɃf���[�g����Ă����ꍇ���邢�̓��C�t��0�̏ꍇ���X�g���珜�O���ăX�L�b�v
		if((*fall_it) == NULL || (*fall_it)->getLife() == 0)
		{
			if((*fall_it)->getisRender())
			{
				CAnimationEffectSP eff = CAnimationEffect::CreateEffect("Resource/XML/Effect/Smoke.xml", (*fall_it)->Transform.Position);
				mainLayer->AddObject(eff->Board, RENDER_ALPHA);
			}
			fall_it = FallList.erase(fall_it);
			continue;
		}
		// NPC�̍X�V
		(*fall_it)->Update();
		(*fall_it)->isVisible(Player->getCamera().get());
		// ���̃C�e���[�^
		fall_it++;
	}

	// �v���C���[�ȊO�̗����I�u�W�F�N�g�ɑ΂���␳
	auto native_it = NativeList.begin();
	while(native_it != NativeList.end())
	{
		if((*native_it).lock() == NULL || (*native_it).lock()->getLife() == 0)
		{
			native_it = NativeList.erase(native_it);
			continue;
		}
		float ra = Player->bvSphere.Radius;
		float rb = (*native_it).lock()->bvSphere.Radius;
		float sa = (*native_it).lock()->getSize();
		float sb = (*native_it).lock()->getSizeMax() * 0.009f * CPlayer::getStSize();
		if(sa >= sb)
			if(CollidedSpheres(Player->Transform.Position, (*native_it).lock()->Transform.Position, ra, rb))
				if(isPlay)
				{ 
					CSoundManager::Play(pathBadSE, CSoundManager::MODE_ONCE);
					isPlay = false;
				}
		native_it++;
	}
	if(!isPlay && resetTimer->TimeCount())
		isPlay = true;

	// �v���C���[�X�V
	Player->Update();

	// ���@�̕ǂɑ΂���␳
	correctWall();
	// ��̍X�V
	subupdateLinks();
	// �G�t�F�N�g�̍X�V
	CAnimationEffect::updateAllEffect();
}