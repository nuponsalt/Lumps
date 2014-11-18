#pragma once

#include "../../Library/Library.h"
using namespace KMT ;

#include <string>

const int TRANSPOSITION_X = 320 ;
const int TRANSPOSITION_Y = 240 ;
const float TRANS_ALPHA = 0.02f ;
const int WATE_TIME = 30 ;

class CTransition
{
public :
	// 初期化関数
	static void initializeTransition();
	// 解放関数
	static void Destroy();
	// トランジション生成関数その1
	// tips... こちらの関数を使うと、ロードされる画像はデフォルトのものとなる
	static void CreateTransition();
	// トランジション解放関数
	static void DestroyTransition();
	// トランジションが生成されているかどうかのフラグを返す関数
	// 戻り値は生成是非
	static const bool IsExistTransition();
	// フェードアウト関数
	// ret.... [ false : フェードアウト中 ] [ true : フェードアウト完了 ]
	static const bool FadeOut();
	// フェードイン関数
	// ret.... [ false : フェードイン中 ] [ true : フェードイン完了 ]
	static const bool FadeIn();
	// 描画関数
	inline static void Render(){ if((spriteImage != NULL) ^ (boardImage != NULL)) spriteImage->Render(); }

private :
	// 透明度の変動値
	static float fAlpha;
	// RGB値
	static float colR, colG, colB;
	// デフォルトのトランジション画像のファイル名
	static std::string Path;
	// 座標
	static float posX, posY;
	// サイズ
	static float Size;
	// ---------------------------------------------------------------------------------
	// トランジション画像
	static CSpriteSP spriteImage;	// Sprite
	static CGPlaneSP boardImage; // 3Dboardpoly
	// 待機タイマー
	static CTimerSP pWaitTimer;
	// 待機フラグ
	static bool isWait;					

	// コンストラクタ
	CTransition(){}
	// デストラクタ
	~CTransition(){}

};