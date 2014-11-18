#include "DXUT.h"
#include "Sprite.h"
#include "../GraphicsManager.h"

namespace KMT {

	CSprite::CSprite() : vTurn(1, 1)
	{
		// �X�v���C�g�̐���
		D3DXCreateSprite(CGraphicsManager::pd3dDevice, &pd3dSprite) ;
	}

	CSprite::~CSprite()
	{
		Texture.reset() ;
		SAFE_RELEASE( pd3dSprite ) ;
	}

	void CSprite::setTexture(const CTextureSP &_ptexture) 
	{
		Texture = _ptexture ;
	}

	CSpriteSP CSprite::CreateFromFile(const std::string &_path)
	{
		CSpriteSP _obj(new CSprite()) ;
		// �e�N�X�`����ݒ�
		_obj->LoadTextureAndAnimation(_path) ;

		return _obj ;
	}

	CSpriteSP CSprite::CreateFromFile(const std::string &_path, const int &_w_num, const int &_h_num) 
	{
		CSpriteSP _obj(new CSprite()) ;
		// �e�N�X�`���̐ݒ�
		_obj->LoadTextureAndAnimation(_path, _w_num, _h_num) ;

		return _obj ;
	}

	void CSprite::Render(const CCamera* camera)
	{
		// �`�悷�邩
		if(!isRender)
			return;
		//---------------------------------------------------------------------------------
		//
		// ���[���h�s��Ɋւ�����
		//
		D3DXMATRIX WldMtx, PosMtx, SclMtx, RotMtx; // ���[���h�s��A�g�����X���[�V�����s��i���W�j�A�X�P�[���s��A��]�s��
		// �g�����X���[�V����( ���s�ړ� ) �s��̍쐬
		D3DXMatrixTranslation(&PosMtx, Position.x, Position.y, Position.z);
		// �X�P�[��( �g�k ) �s��̍쐬
		D3DXMatrixScaling(&SclMtx, vTurn.x * Scale.x, vTurn.y * Scale.y, 1.0f);
		// ���[�e�[�V����( ��] ) �s��̍쐬 
		// �� ����� 2D�Ȃ̂� Z��]�̂�
		D3DXMatrixRotationZ(&RotMtx, D3DXToRadian(vRotation.z));
		//�y !�d�v! �z���[���h�s��̎Z�o 
		// DirectX �ł� ���[���h�s��̎Z�o��
		// �X�P�[�� * ���[�e�[�V���� * �g�����X���[�V���� �̏��ōs��
		WldMtx = SclMtx * RotMtx * PosMtx;
		// �X�v���C�g�Ƀ��[���h�s���ݒ�
		pd3dSprite->SetTransform(&WldMtx);

		HRESULT hr;
		// Render the scene
		if(SUCCEEDED( DXUTGetD3D9Device()->BeginScene()))
		{		
			// �X�v���C�g�̕`�揀��
			pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND); // �������A�s�����̂Ƃ��͂O��n��
			//----------------------------------------------------------------------------------
			//
			// ���Z�u�����h�̐ݒ�
			//
			if(isAddBlend)
			{
				DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
				DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				DXUTGetD3D9Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}/*else{
				CGraphicsManager::pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE ) ;
			}*/

			// �X�v���C�g�̕`�施��
			pd3dSprite->Draw(
				// �`��Ɏg�p����e�N�X�`��
				Texture->getpd3dTexture(),
				// �摜�̕`��͈�
				&Rects[Number],	
				// �T�[�t�F�C�X�̒��S
				(D3DXVECTOR3*)&CenterPosition,
				// �`����W(�s��Ő��䂷��̂�0, 0, 0��OK)
				&D3DXVECTOR3(0,0,0),
				// �F
				D3DCOLOR_ARGB((int)(vColorRGBA.w * 255), (int)(vColorRGBA.x * 255), (int)(vColorRGBA.y * 255), (int)(vColorRGBA.z * 255)));

			// ���Z�؂�ւ�
			pd3dSprite->End();
			// �`��I��
			V(CGraphicsManager::pd3dDevice->EndScene());
		}
	}

}