#include "DXUT.h"
#include "Transition.h"

#include "../../Library/Library.h"

// CTransitionManagerの静的メンバ実体
float CTransition::fAlpha = 0.0f;
float CTransition::colR = 0.0f, CTransition::colG = 0.0f, CTransition::colB = 0.0f;
std::string CTransition::Path = "";
float CTransition::posX, CTransition::posY = 0.0f;
float CTransition::Size = 0.0;
CSpriteSP CTransition::spriteImage = NULL;
CGPlaneSP CTransition::boardImage = NULL;
CTimerSP CTransition::pWaitTimer = NULL;
bool CTransition::isWait = false;

void CTransition::initializeTransition()
{
	CWsbXmlSP xml = CWsbXml::LoadXmlFile("Resource/XML/Transition.xml");
	// 画像ファイルパス
	Path = xml->GetElement("Path")->GetString();
	// トランジション画像の描画座標
	posX = xml->GetElement("spriteImage")->GetElement("Position")->GetElement("X")->GetFloat();	
	posY = xml->GetElement("spriteImage")->GetElement("Position")->GetElement("Y")->GetFloat();
	// サイズの変更
	Size = xml->GetElement("Size")->GetFloat();
	// 透明度の変動値
	fAlpha = xml->GetElement("Alpha")->GetFloat();
	// RGB値
	colR = xml->GetElement("Color")->GetElement("R")->GetFloat();
	colG = xml->GetElement("Color")->GetElement("G")->GetFloat();
	colB = xml->GetElement("Color")->GetElement("B")->GetFloat();
	// フェードアウトとインの間の待機時間
	int WaitTime = xml->GetElement("WaitTime")->GetInt();
	// タイマーの生成
	// 待機タイマー
	pWaitTimer = CTimerSP(new CTimer(WaitTime));
}

void CTransition::Destroy()
{
	// 画像の解放
	// トランジション画像
	spriteImage.reset();	
	// タイマーの解放
	// 待機タイマー
	pWaitTimer.reset();	
}

void CTransition::CreateTransition()
{
	// 画像生成
	spriteImage = CSprite::CreateFromFile(Path);
	spriteImage->Position= CVector3(posX, posY, 0);
	spriteImage->Scale *= Size;
	// 各値の初期化
	// 透明度
	spriteImage->setColorRGBA(colR, colG, colB, 0.0f);
	// 待機タイマー
	pWaitTimer->ResetCount();
	// 待機フラグ
	isWait	 = false;
}

void CTransition::DestroyTransition() 
{ 
	spriteImage.reset(); 
	boardImage.reset();
}

const bool CTransition::IsExistTransition()
{
	return (spriteImage != NULL) ? true : false;
}

const bool CTransition::FadeOut()
{
	// 透明度が最大でなければ、トランジション画像の透明度を加算していく
	if(spriteImage->vColorRGBA.w >= 1.0f){
		spriteImage->vColorRGBA.w = 1.0f;
		isWait = true;
		return true;
	}
	spriteImage->vColorRGBA.w += fAlpha;
	return false;
}

// フェードイン関数
const bool CTransition::FadeIn()
{
	// 待機が終わるまでフェードインは行わない
	if(isWait && !pWaitTimer->TimeCount())
		return false;
	else
		isWait = false;
	// 透明度が最小でなければ、トランジション画像の透明度を減算していく
	if(spriteImage->vColorRGBA.w <= 0.0f){
		spriteImage->vColorRGBA.w = 0.0f;
		return true;
	}
	spriteImage->vColorRGBA.w -= fAlpha;
	return false;
}