#include "DXUT.h"
#include "Layer.h"
#include "../GraphicsManager.h"

#include "GraphicalShape/GraphicalPlane.h"

namespace KMT {

	CLayer::CLayer() : pd3dTextureSurface(NULL), pd3dDepthSurface(NULL) { }

	CLayer::~CLayer()
	{
		// �T�[�t�F�C�X�̊J��
		SAFE_RELEASE(pd3dTextureSurface);
		// �X�e���V���p�b�t�@
		SAFE_RELEASE(pd3dDepthSurface);
		// �|���̉��
		board.reset();
		// �J�����̉��
		Camera3D.reset();
		Camera2D.reset();

		// �����_�����O���X�g�����
		//-----------------------------------------
		for(int i = 0; i < RENDER_STATE_MAX; i++)
		{
			render_lists[i]->clear();
		}
		for(size_t i = 0; i < render_lists.size(); i++)
		{
			SAFE_DELETE(render_lists[i]);
		}
		render_lists.clear();
	}

	CLayerSP CLayer::CreateLayer(size_t width, size_t height)
	{
		CLayerSP pRenderTag = CLayerSP(new CLayer);

		// �e�N�X�`���̐���
		pRenderTag->Texture = CTexture::CreateEmpty(width, height);

		// �T�[�t�F�C�X�̎擾
		if (FAILED(pRenderTag->Texture->getpd3dTexture()->GetSurfaceLevel(0, &pRenderTag->pd3dTextureSurface)))
		{
			// �T�[�t�F�C�X�擾���s
			// �G���[�ɑΉ�����R�[�h
		}

		// �X�e���V���o�b�t�@�̍쐬
		if (FAILED(CGraphicsManager::pd3dDevice->CreateDepthStencilSurface( 
			pRenderTag->Texture->getd3dImageInfo().Width,
			pRenderTag->Texture->getd3dImageInfo().Height,
			D3DFMT_D16, 
			D3DMULTISAMPLE_NONE, 
			0, 
			TRUE, 
			&pRenderTag->pd3dDepthSurface, 
			NULL)))
		{
			// �X�e���V���o�b�t�@�̍쐬�Ɏ��s
			// �G���[�ɑΉ�����R�[�h�������ɏ���
		}

		pRenderTag->Camera3D = CCamera::Create();
		pRenderTag->Camera3D->setEye(0, 0, -10.0f);

		pRenderTag->Camera2D = CCamera::Create();
		float angle = pRenderTag->Camera2D->getAngle();
		pRenderTag->Camera2D->setEye(0, 0, -(SCREEN_HEIGHT / (2.0f * tan(angle / 2.0f))));
		// �|������
		pRenderTag->board = CGraphicalPlane::Create(width, height);
		float aspect = (float)width / height;
		pRenderTag->Camera3D->setAspect(aspect);
		pRenderTag->Camera2D->setAspect(aspect);
		// �|���Ƀe�N�X�`�����Z�b�g
		if(pRenderTag->board->getptextures().size() < 1)
			pRenderTag->board->setTexture(pRenderTag->Texture);
		// �����_�����O���X�g�̍쐬
		for(int i = 0; i < RENDER_STATE_MAX; i++)
		{
			std::list<CGraphicBehaviorWP> *list = new std::list<CGraphicBehaviorWP>();
			pRenderTag->render_lists.push_back(list);
		}

		return pRenderTag;
	}

	void CLayer::Render()
	{
		// �X�e���V���o�b�t�@���Z�b�g
		CGraphicsManager::pd3dDevice->SetDepthStencilSurface(pd3dDepthSurface);

		// �����_�����O�^�[�Q�b�g���Z�b�g
		CGraphicsManager::pd3dDevice->SetRenderTarget(0, pd3dTextureSurface);

		// �T�[�t�F�C�X���N���A
		CGraphicsManager::pd3dDevice->Clear(0,
			NULL, 
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_ARGB(255, 100, 149, 237),
			1.0f,
			0);


		// �J�����̍X�V
		Camera3D->updateView();
		Camera2D->updateView();

		std::hash_map<size_t, std::list<CGraphicBehaviorWP>*>::iterator hmit;

		// 2D�\�[�g
		render_lists[RENDER_BACK2D]->sort(CGraphicBehavior::comp2D);
		render_lists[RENDER_FRONT2D]->sort(CGraphicBehavior::comp2D);

		// ���X�g�A�N�Z�X�p�C�e���[�^
		std::list<CGraphicBehaviorWP>::iterator it;

		// 3D�\�[�g
		//-------------------------------------------------
		for(int i = 0; i < 2; i++)
		{
			it = render_lists[RENDER_NORMAL + i]->begin();

			while(it != render_lists[RENDER_NORMAL + i]->end())
			{
				// ���łɃf���[�g����Ă����ꍇ���X�g���珜�O���ăX�L�b�v
				if((*it).lock() == NULL)
				{
					it = render_lists[RENDER_NORMAL + i]->erase(it);
					continue;
				}

				// �J��������̋������v�Z
				CVector3 campos = Camera3D->getEye();
				CVector3 vec = (*it).lock()->Position - campos;
				(*it).lock()->CameraDistance = vec.Length();

				++it;
			}
		}

		// �\�[�g
		render_lists[RENDER_NORMAL]->sort(CGraphicBehavior::comp);
		render_lists[RENDER_ALPHA]->sort(CGraphicBehavior::compBack);
		//-------------------------------------------------------

		// �����_�����O�[���X�g�̒��g�����ׂĕ`��
		//-------------------------------------------------------
		for(int i = RENDER_BACK2D; i < RENDER_STATE_MAX; i++)
		{
			if(i != RENDER_ALPHA)
			{
				// Z�o�b�t�@�̃N���A
				CGraphicsManager::pd3dDevice->Clear(0, 
					NULL, 
					D3DCLEAR_ZBUFFER,
					D3DCOLOR_ARGB(255, 0, 191, 255),
					1.0f,
					0);
			}

			// Z�o�b�t�@�؂�ւ�
			(i == RENDER_NORMAL || i == RENDER_ALPHA) 
				? CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE)
				: CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

			it = render_lists[i]->begin();
			
			while(it != render_lists[i]->end())
			{
				// ���łɃf���[�g����Ă����ꍇ���X�g���珜�O���ăX�L�b�v
				if((*it).lock() == NULL)
				{
					it = render_lists[i]->erase(it);
					continue ;
				}
				// �J�����I��
				CCameraSP camera = (i == RENDER_BACK2D || i == RENDER_FRONT2D) ? Camera2D : Camera3D;
				// �`��
				(*it).lock()->Render(camera.get());
				// ���̃C�e���[�^��
				it ++;
			}
		}
	}
}