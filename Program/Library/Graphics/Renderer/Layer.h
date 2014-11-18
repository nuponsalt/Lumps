//*********************************************************************
// �I�t�X�N���[�������_�����O�N���X
// Last Update : 2014.2.5
// Yuta Komatsu
//*********************************************************************
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>

#include "GraphicBehavior.h"
#include "GraphicalShape/GraphicalPlane.h"
#include "../View/Camera.h"

#include "../../Extension.h"

namespace KMT {

	enum RenderState
	{
		RENDER_BACK2D,
		RENDER_NORMAL,
		RENDER_ALPHA,
		RENDER_FRONT2D,
		RENDER_STATE_MAX
	};

	class CLayer;
	typedef std::shared_ptr<CLayer> CLayerSP;
	typedef std::weak_ptr<CLayer> CLayerWP;

	class CLayer
	{
	public :
		// �J����
		CCameraSP Camera3D;
		CCameraSP Camera2D;
		// �|�����f��
		CGPlaneSP board;

		// �f�X�g���N�^
		~CLayer();

		// ����
		static CLayerSP CreateLayer(size_t width, size_t height);
		// �����_�����O���X�g�̒��g�����ׂĕ`��
		void Render();
		// �����_�����O���X�g�ɃI�u�W�F�N�g��ǉ�����
		// _obj �ǉ�����I�u�W�F�N�g
		// _list �ǂ̃����_�����O���X�g�ɒǉ����邩
		inline void AddObject(CGraphicBehaviorWP obj, RenderState list)
		{
			render_lists[list]->push_back(obj);
		}

	private :
		// �����_�����O���X�g(�`�惊�X�g�̃n�b�V���}�b�v)
		std::vector<std::list<CGraphicBehaviorWP>*> render_lists;
		// �����_�����O�Ώۂ̃e�N�X�`��
		CTextureSP Texture;
		// ��L�����_�����O�Ώۂ̃e�N�X�`���̃T�[�t�F�C�X
		LPDIRECT3DSURFACE9 pd3dTextureSurface;
		// �����_�����O�Ώۂ̃e�N�X�`���p�[�x�o�b�t�@
		LPDIRECT3DSURFACE9 pd3dDepthSurface;

		// �R���X�g���N�^
		CLayer();

	};

} 