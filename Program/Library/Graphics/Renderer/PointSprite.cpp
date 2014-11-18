#include "DXUT.h"
#include "PointSprite.h"

#include "../Shader/Particle/Particle.h"
#include "../GraphicsManager.h"
#include "../View/Camera.h"
#include "../../Extension.h"

namespace KMT {

#define FRAND()	((float)rand() / 32768.0f)

	CPointSprite::CPointSprite(const std::string& path, const WORD numPoint, const float size) : pointNumber(numPoint), pointSize(size)
	{
		Path = path;

		d3dCull = D3DCULL_NONE;

		// ���_�o�b�t�@�̍쐬
		if(FAILED(CGraphicsManager::pd3dDevice->CreateVertexBuffer(
			sizeof(POINTSPRITE) * pointNumber, 
			D3DUSAGE_NPATCHES | D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC, 
			POINTSPRITE::FVF,
			D3DPOOL_DEFAULT,
			&pd3dVertexBuffer,
			NULL
			)))
			MessageBox(NULL, TEXT("POINTSPRITE's VertexBuffer Create Err"), NULL, MB_OK | MB_ICONSTOP);

		// ���_���̏�����
		pPOINTSPRITE pPS;
		if(FAILED(pd3dVertexBuffer->Lock(sizeof(POINTSPRITE), sizeof(POINTSPRITE) * pointNumber, (void**)&pPS, D3DLOCK_DISCARD)))
			MessageBox(NULL, TEXT("POINTSPRITE's VertexBuffer Lock Err"), NULL, MB_OK | MB_ICONSTOP);

		for(int i = 0; i < pointNumber - 1; i++)
		{
			pPS[i].Position = CVector3(0, 0, 0);
			pPS[i].PSize = size;
			pPS[i].Color = 0;
		}

		pd3dVertexBuffer->Unlock();

		// �G�~�b�^�[�f�[�^�̐���
		EmitterData = new CEmitter();

		// �e�N�X�`���̃��[�h
		Texture = CTexture::CreateFromFile(path, D3DX_FILTER_NONE);
		// �V�F�[�_�[��ݒ�
		Shader = CShaderParticle::CreateShader();
	}

	CPointSprite::~CPointSprite()
	{
		SAFE_RELEASE(pd3dVertexBuffer);
		Texture.reset();

		// �G�~�b�^�[�f�[�^�̉��
		SAFE_DELETE(EmitterData);
		
	}

	CPointSpriteSP CPointSprite::CreatePointSprite(const std::string& path, const WORD numPoint, const float size)
	{
		return CPointSpriteSP(new CPointSprite(path, numPoint, size));
	}

	void CPointSprite::Render(const CCamera* camera)
	{
		// �`�悷�邩�ۂ�
		if(!isRender)
			return;

		// ���[���h�s��ݒ�
		CMatrix SclMtx, RotMtx, PosMtx, WldMtx, WVPMtx;
		// �g�k
		D3DXMatrixScaling(&SclMtx, Scale.x, Scale.y, Scale.z);
		// ��] : switch-case�c�N�H�[�^�j�I������]�s��XYZ�w�肩
		switch(CurrentRotateType)
		{
		case ROTATE_TYPE::QUATERNION :
			D3DXMatrixRotationQuaternion(&RotMtx, &qRotation);
			break;

		case ROTATE_TYPE::MATRIX :
			mRotationWorld = mRotationX * mRotationY * mRotationZ;
			RotMtx = mRotationWorld;
			break;

		case ROTATE_TYPE::XYZ :
			D3DXMatrixRotationYawPitchRoll(&RotMtx, vRotation.y, vRotation.x, vRotation.z);
			break;
		}
		// �ʒu
		D3DXMatrixTranslation(&PosMtx, Position.x, Position.y, Position.z);
		// �V�F�[�_���g�p����ꍇ�J�����̃r���[�s��(0)�A�v���W�F�N�V�����s��(1)�����[���h�s��ɍ���
		WldMtx = SclMtx * RotMtx * PosMtx;
		WVPMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW) * camera->getMatrix(CViewBehavior::PROJECTION);
		// �J�����̍��W���V�F�[�_�Ɏg�p���邽�߂̍s��ϊ�
		CMatrix CamMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW);
		D3DXMatrixInverse(&CamMtx, NULL, &CamMtx);
		CVector4 EyePos = CVector4(
			camera->getEye().x, 
			camera->getEye().y, 
			camera->getEye().z, 
			1
			);
		EyePos.Transform(CamMtx);
		D3DXVec4Normalize((D3DXVECTOR4*)&EyePos, (D3DXVECTOR4*)&EyePos);
		// �V�F�[�_�[�ݒ�
		Shader->setTechnique();
		// �V�F�[�_�[�Ƀ��[���h*�r���[*�v���W�F�N�V�����s��ɓn��
		Shader->setWVPMatrix(WVPMtx);
		// �V�F�[�_�[���L�̒l�n��
		Shader->applyEffect(RotMtx, EyePos);

		HRESULT hr;
		// �`�揈��
		// �V�F�[�_�[�ɃJ���[��n��
		Shader->setColor(vColorRGBA);
		// �e�N�X�`����n��
		if(NULL != Texture)
			Shader->setTexture(Texture->getpd3dTexture());
		// �V�F�[�_�[�̎g�p�J�n
		Shader->BeginShader();
		// �V�F�[�_�[�̃p�X�J�n
		Shader->BeginPass(isAddBlend);
		// �p�[�e�B�N���̎g�p��L���ɂ���
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
		// �|�C���g�̍ŏ��T�C�Y
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_POINTSIZE_MIN, 0);
		// Z�o�b�t�@(�p�[�e�B�N���̂݁AZ�l�̏������݂��s��Ȃ�)
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		// ���_�̐ݒ�
		CGraphicsManager::pd3dDevice->SetStreamSource(0, pd3dVertexBuffer, 0, sizeof(POINTSPRITE));
		CGraphicsManager::pd3dDevice->SetFVF(POINTSPRITE::FVF);
		// �J�����O��ݒ�
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_CULLMODE, d3dCull);

		if(SUCCEEDED(CGraphicsManager::pd3dDevice->BeginScene()))
		{
			CGraphicsManager::pd3dDevice->DrawPrimitive(D3DPT_POINTLIST, 0, pointNumber);
			V(CGraphicsManager::pd3dDevice->EndScene());
		}
		// �p�X�I��
		Shader->EndPass();
		// Z�o�b�t�@�ݒ�̃��Z�b�g
		CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		// �V�F�[�_�[�I��
		Shader->EndShader();
	}

}