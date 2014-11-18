//*********************************************
// DirectX�e�N�X�`�����\�[�X�Ǘ��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#include "DXUT.h"

#include "Texture.h"
#include "../System/Debug.h"
#include "../Extension.h"

#include <sstream>

namespace KMT {

	//-----------------------------------------------------------
	// CTexture

	// static parameters
	stdext::hash_map<std::string, CTextureWP> CTexture::Textures;
	stdext::hash_map<std::string, CTextureWP> CTexture::stringTextures;
	size_t CTexture::TexCount = 0;

	CTexture::CTexture() : pd3dTexture( NULL )
	{}

	CTexture::~CTexture()
	{
		// �C�e���[�^������
		// �t�@�C���p�X�Ō���
		std::hash_map<std::string, CTextureWP>::iterator it = Textures.find(FilePath);
		// �Y�����肾�����ꍇ
		if(it != Textures.end())
			// map�������
			Textures.erase(it);

		SAFE_RELEASE(pd3dTexture);
#if _DEBUG
		OutputDebugString(L"Release Texture\n");
#endif
	}

	CTextureSP CTexture::CreateEmpty( const size_t nWidth, const size_t nHeight )
	{
			
		// �e�N�X�`���N���X�̃|�C���^��p��
		// �V�����e�N�X�`���N���X���쐻
		CTextureSP ptexture = CTextureSP( new CTexture() ) ;

		// width��height�̑傫���ق�����Ƃ���
		int size = nWidth > nHeight ? nWidth : nHeight ;
		int tex_size = 1 ;
		while( tex_size < size )
		{
			tex_size *= 2 ;
		}

		if ( FAILED( D3DXCreateTexture( DXUTGetD3D9Device(), 
			tex_size, 
			tex_size, 
			0, 
			D3DUSAGE_RENDERTARGET, 
			D3DFMT_A8R8G8B8, 
			D3DPOOL_DEFAULT, 
			&ptexture->pd3dTexture ) ) )
		{
			// �e�N�X�`���̍쐬�Ɏ��s
			// �G���[�ɑΉ�����R�[�h�������ɏ���
			//CDebug::AddString("Error : Failed to Create Texture\n"); 
		}
		// �e�N�X�`���̃T�C�Y���L�^
		ptexture->d3dImageInfo.Width = tex_size ;
		ptexture->d3dImageInfo.Height = tex_size ;
		// �e�N�X�`���̑������X�V
		TexCount ++ ;
		// �e�N�X�`��No���t�@�C���p�X�̑���ɃL�[�ɂ��ă}�b�v�ɓo�^
		std::stringstream ss ;
		ss.str("");
		ss << TexCount << ":" << nWidth << nHeight ;
		std::string str = ss.str().c_str() ;
		// �t�@�C���p�X��ێ�
		ptexture->FilePath = str;
		// �}�b�v�ɓo�^
		Textures.insert( std::make_pair( str, CTextureWP( ptexture ) ) ) ;

		return ptexture ;
	}


	CTextureSP CTexture::CreateToFont( int nWidth, int nHeight, int nFromRGB, int nToRGB, const std::string cFont, const std::string cChar ) 
	{
		std::stringstream ss("") ;
		ss << cFont << cChar ;
		// ���ɂ��̃e�N�X�`���[�����݂���ꍇ�A�Ԃ�
		std::hash_map<std::string, CTextureWP>::iterator it = Textures.find( ss.str() ) ;
		if(it != Textures.end())
			return it->second.lock();
		//-------------------------------------------------------------------------------
		// �t�H���g�T�C�Y�̓|���S���ˑ�
		int fontsize = ((nWidth + nHeight) >> 1);
		fontsize = (fontsize <= 32) ? 32 : fontsize;
		int Len = 0;

		WCHAR font_buff[LF_FACESIZE] = {0};
		DXconvAnsiToWide(font_buff, cFont.c_str(), (cFont.length()+1));
		// �t�H���g���ݒ�
		LOGFONT logfont = {fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, 0};
		
		memcpy(logfont.lfFaceName, font_buff, sizeof(WCHAR)*LF_FACESIZE);

		HFONT hFont = CreateFontIndirect(&logfont);
		if(!(hFont))
			MessageBox(NULL, TEXT("Error : Failed to create string texture"), NULL, MB_OK | MB_ICONSTOP);

		WCHAR char_buff[256] = {0};
		DXconvAnsiToWide(char_buff, cChar.c_str(), (cChar.length() + 1));

		TCHAR *c = char_buff;
		Len = (int)wcslen(c);
		//-------------------------------------------------------------------------------
		// �f�o�C�X�R���e�L�X�g�擾
		// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
		HDC hdc = GetDC(NULL);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
		//-----------------------------------------------------------------------------------------------
		LPDIRECT3DTEXTURE9 pWkTex = NULL;
		CTextureSP ptexture = CTextureSP(new CTexture());
		//-----------------------------------------------------------------------------------------------
		for(int i = 0; i < 1; i++){
			//-------------------------------------------------------------------------------
			// 1 �����R�[�h�擾
			size_t code = 0;
#if _UNICODE
			// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
			code = (UINT)*c;
#else
			// �}���`�o�C�g�����̏ꍇ�A
			// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
			// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
			if( IsDBCSLeadByte( *c ) ){
				code = (BYTE)c[0]<<8 | (BYTE)c[1];
				c += 2;
			}else{
				code = c[0];
				c++;
			}
#endif	
			//-------------------------------------------------------------------------------
			// �t�H���g�r�b�g�}�b�v�擾
			TEXTMETRIC TM;
			GetTextMetrics(hdc, &TM);
			GLYPHMETRICS GM;
			CONST MAT2 Mat = {{0,1}, {0,0}, {0,0}, {0,1}};

			//DWORD size = GetGlyphOutline( hdc, code, GGO_BITMAP, &GM, 0, NULL, &Mat ) ;			
			//DWORD size = GetGlyphOutline( hdc, code, GGO_GRAY2_BITMAP, &GM, 0, NULL, &Mat ) ;
			//DWORD size = GetGlyphOutline( hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat ) ;
			DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY8_BITMAP, &GM, 0, NULL, &Mat);

			BYTE *ptr = new BYTE[size];

			//BYTE *ptr = ( BYTE* )T2Malloc( sizeof( BYTE ) * size ) ;
			//GetGlyphOutline( hdc, code, GGO_BITMAP, &GM, size, ptr, &Mat ) ;
			//GetGlyphOutline( hdc, code, GGO_GRAY2_BITMAP, &GM, size, ptr, &Mat ) ;
			//GetGlyphOutline( hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat ) ;
			GetGlyphOutline(hdc, code, GGO_GRAY8_BITMAP, &GM, size, ptr, &Mat);
			//---------------------------------------------------------------
			// �e�N�X�`���쐬
			D3DLOCKED_RECT LockedRect;

			if(FAILED(DXUTGetD3D9Device()->CreateTexture(GM.gmCellIncX,
				TM.tmHeight,
				1,
				D3DUSAGE_DYNAMIC,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&pWkTex,
				NULL))){
					MessageBox(NULL, TEXT(" !! Font Create Err 02 !! "), NULL, MB_OK | MB_ICONSTOP);
			}

			if(FAILED(pWkTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD))){
				MessageBox(NULL, TEXT(" !! Font Create Err 03 !! "), NULL, MB_OK | MB_ICONSTOP);
			}
			//---------------------------------------------------------------
			// �t�H���g���̏�������
			// iOfs_x, iOfs_y : �����o���ʒu(����)
			// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
			// Level : ���l�̒i�K (GGO_GRAY4_BITMAP��17�i�K�AGGO_GRAY8_BITMAP��65�i�K)
			int iOfs_x = GM.gmptGlyphOrigin.x;
			int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
			int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4)) % 4;
			int iBmp_h = GM.gmBlackBoxY;
			int Level = 65;
			int x, y;
			DWORD Alpha, Color;

			FillMemory(LockedRect.pBits , LockedRect.Pitch * TM.tmHeight, 0);

			for(y = iOfs_y; y < iOfs_y+iBmp_h; y++){
				for(x = iOfs_x; x < iOfs_x+iBmp_w; x++){
					//--------------------------------------------------------------
					// �m�[�}���t�H���g
					//if( T2FONT_ANTIALIAS & FLG ){
					//	Alpha = ( 255 * ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] ) / ( Level-1 ) ;
					//}else{
					//	Alpha = ( 0 == ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] )? 0 : 255 ;
					//}

					Alpha = (DWORD)ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] ;
					Alpha = Alpha * ( 256 / ( Level - 1 ) ) ;
					if( Alpha > 255 )
						Alpha = 255 ;
					//Alpha = ( 0 == ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] )? 0 : 255 ;
					{
						int wkY = ( iOfs_y + iBmp_h ) ;
						int wkStR = ( nFromRGB & 0x00ff0000 )>>16 ;
						int wkStG = ( nFromRGB & 0x0000ff00 )>>8 ;
						int wkStB = ( nFromRGB & 0x000000ff ) ;

						int wkEnR = ( nToRGB & 0x00ff0000 )>>16 ;
						int wkEnG = ( nToRGB & 0x0000ff00 )>>8 ;
						int wkEnB = ( nToRGB & 0x000000ff ) ;

						int wkSubR = wkStR - wkEnR ;
						int wkSubG = wkStG - wkEnG ;
						int wkSubB = wkStB - wkEnB ;

						float wkAddR = ( (float)wkSubR / (float)wkY ) ;
						float wkAddG = ( (float)wkSubG / (float)wkY ) ;
						float wkAddB = ( (float)wkSubB / (float)wkY ) ;

						int wkR = wkStR - (int)( y * wkAddR ) ;
						int wkG = wkStG - (int)( y * wkAddG ) ;
						int wkB = wkStB - (int)( y * wkAddB ) ;
						Color = D3DCOLOR_ARGB( 0, wkR, wkG, wkB ) | ( Alpha << 24 ) ;
						memcpy( ( BYTE* )LockedRect.pBits + LockedRect.Pitch*y + 4*x, &Color, sizeof(DWORD) ) ;
					}
				}
			}

			pWkTex->UnlockRect( 0 ) ;

			delete[] ptr;		

		}

		D3DXVECTOR3 v1( -( nWidth * 0.5f ),  ( nHeight * 0.5f ), 0.0f ) ;
		D3DXVECTOR3 v2(  ( nWidth * 0.5f ),  ( nHeight * 0.5f ), 0.0f ) ;
		D3DXVECTOR3 v3(  ( nWidth * 0.5f ), -( nHeight * 0.5f ), 0.0f ) ;
		D3DXVECTOR3 v4( -( nWidth * 0.5f ), -( nHeight * 0.5f ), 0.0f ) ;
		//CreateSprite( v1, v2, v3, v4, NULL ) ;

		//-------------------------------------------------------------------------------
		// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
		SelectObject( hdc, oldFont ) ;
		DeleteObject( hFont ) ;
		ReleaseDC( NULL, hdc ) ;	

		//*ppFont = pWkFont ;
		//pWkFont->Init( pStr ) ;

		ptexture->pd3dTexture = pWkTex ;
		ptexture->d3dImageInfo.Width = fontsize ;

		stringTextures.insert(make_pair(ss.str(), CTextureWP(ptexture)));

		return ptexture ;

	}

	CTextureSP CTexture::CreateFromFile(const std::string &_path, const DWORD dwFilter)
	{
		CTextureSP ptexture;
		std::stringstream ss;
		ss.str("");
		ss << _path << "Filter : " << dwFilter;
		std::string str = ss.str().c_str();

		stdext::hash_map<std::string, CTextureWP>::iterator it = Textures.find(str);
		// �Y�������������ꍇ
		if(it == Textures.end())
		{
			ptexture = CTextureSP(new CTexture());

			ptexture->FilePath = str;
			// �t�@�C���p�X�����C�h�����ɕϊ�����
			WCHAR buff_path[256] = {0} ;
			DXconvAnsiToWide( buff_path, _path.c_str(), ( _path.length() + 1 ) ) ;

			// �e�N�X�`���̃��[�h
			D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(),
				// �t�@�C���p�X
				buff_path,			
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DPOOL_DEFAULT,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				// �t�B���^�[
				dwFilter,
				D3DX_DEFAULT,
				// �����F�̎w�� �S��0�w��ŃJ���[�L�[�Ȃ�
				D3DXCOLOR(0,0,0,0),	
				// �摜���̎擾
				&ptexture->d3dImageInfo,		
				NULL,
				// �e�N�X�`���̎󂯎��
				&ptexture->pd3dTexture			
				);

			// �}�b�v�ɓo�^
			Textures.insert(std::make_pair(str, CTextureWP(ptexture)));
		// �Y�����肾�����ꍇ
		}
		else
			// �쐬�ς݂̃e�N�X�`���N���X�̃|�C���^���擾
			ptexture = CTextureSP((*it).second);	

		return ptexture;
	}

	void CTexture::Destroy(std::string _name) 
	{
		// �C�e���[�^��p��
		// �C�e���[�^���n�b�V���}�b�v�̐擪�ɃZ�b�g
		stdext::hash_map<std::string, CTextureWP>::iterator it = Textures.begin() ; 
		// �S�����
		if( _name == "all" ){
			while(it != Textures.end())
			{
				(*it).second.reset();
				Textures.erase(it++);
			}
		}
		else
			// �e�N�X�`�����P�������
		{
			it = Textures.find(_name);
			if(it != Textures.end())
			{
				(*it).second.reset();
				Textures.erase(it);
			}
		}
	}

}