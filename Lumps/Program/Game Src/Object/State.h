#pragma once

// 状態を管理する
class CState
{
private :

	// 値 ( ビットフラグ )
	int Value ;

public :

	// 状態の種類
	enum 
	{
		GROUNDING	= 0x01		// 接地してるか否か
	} ;

	// コンストラクタ
	CState( int state = 0 ) : Value( state ) {}

	// デストラクタ
	~CState() {}

	// 状態を追加
	void Add( int state ) { Value |= state ; }

	// 指定した状態のフラグチェック
	bool Check( int state ) { return ( Value & state ) == state ; }

} ;