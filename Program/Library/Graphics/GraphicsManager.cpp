#include "DXUT.h"
#include "GraphicsManager.h"

#include "Shader/Shader.h"
#include "Shader/Lambert/ShaderLambert.h"
#include "Shader/HalfLambert/ShaderHalfLambert.h"
#include "Shader/Phong/ShaderPhong.h"
#include "Shader/Toon/ShaderToon.h"
#include "Texture.h"

namespace KMT {

	IDirect3DDevice9* CGraphicsManager::pd3dDevice;

	LPDIRECT3DSURFACE9 CGraphicsManager::pd3dBackBufferSurface;

	LPDIRECT3DSURFACE9 CGraphicsManager::pd3dBackDepthSurface;

	void CGraphicsManager::Initialize(IDirect3DDevice9 *_pd3dDevice)
	{
		// �f�o�C�X�|�C���^�̎擾
		pd3dDevice = _pd3dDevice;

		// �o�b�N�o�b�t�@�̃T�[�t�F�C�X���擾
		pd3dDevice->GetRenderTarget(0, &pd3dBackBufferSurface);
		
		// �[�x�o�b�t�@�̃T�[�t�F�C�X���擾
		pd3dDevice->GetDepthStencilSurface(&pd3dBackDepthSurface);

		//-------------------------------------------------------------
		// �V�F�[�_�[�̏����ǂݍ���

		//* �V�F�[�f�B���O���ݒ� *//
		CShaderNormal::CreateShader();
		//* �����o�[�g�g�U���˃V�F�[�f�B���O *//
		CShaderLambert::CreateShader();
		//* �n�[�t�����o�[�g�V�F�[�_�[ *//
		CShaderHalfLambert::CreateShader();
		//* �t�H���V�F�[�_�[ *//
		CShaderPhong::CreateShader();
		//* �g�D�[���V�F�[�_�[ *//
		CShaderToon::CreateShader();
	}
	
	void CGraphicsManager::Destroy()
	{
		// �o�b�N�o�b�t�@�̃T�[�t�F�C�X�����
		SAFE_RELEASE(pd3dBackBufferSurface);
		// �[�x�o�b�t�@�̃T�[�t�F�C�X�����
		SAFE_RELEASE(pd3dBackDepthSurface);
		// �V�F�[�_�[�̊J��
		CShader::Destroy();
		// �e�N�X�`���̊J��
		CTexture::Destroy();
	}

	void CGraphicsManager::setRenderTargetToBackBuffer()
	{
		// �X�e���V���o�b�t�@���Z�b�g
		pd3dDevice->SetDepthStencilSurface(pd3dBackDepthSurface);
		// �����_�����O�^�[�Q�b�g���Z�b�g
		pd3dDevice->SetRenderTarget(0, pd3dBackBufferSurface);
		// �T�[�t�F�C�X���N���A
		pd3dDevice->Clear(0, 
			NULL, 
			D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
			D3DCOLOR_ARGB(0, 20, 40, 50),
			1.0f,
			0);
	}

}