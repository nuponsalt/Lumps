#pragma once

namespace KMT {

	class CGraphicsManager
	{
	private :
		
		// �R���X�g���N�^
		CGraphicsManager() {}

		// �f�X�g���N�^
		~CGraphicsManager() {}
	public :
		
		// �摜�����ɕK�v�ȃf�o�C�X�̃|�C���^
		static IDirect3DDevice9* pd3dDevice ;

		// �o�b�N�u�b�t�@�̃T�[�t�F�C�X
		static LPDIRECT3DSURFACE9 pd3dBackBufferSurface ;

		// �o�b�N�o�b�t�@�̐[�x�o�b�t�@�̃T�[�t�F�C�X
		static LPDIRECT3DSURFACE9 pd3dBackDepthSurface ;

		// ������
		static void Initialize( IDirect3DDevice9* _pd3dDevice ) ;

		// ���
		static void Destroy() ;

		static void setRenderTargetToBackBuffer() ;
	} ;

}