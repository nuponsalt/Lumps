#pragma once

#include <memory>
#include "../Sphere.h"

class CDrop;
typedef std::shared_ptr<CDrop> CDropSP;

// 落下物オブジェクト
class CDrop : public CSphere
{
public :
	// デストラクタ
	~CDrop() { }
	// 生成
	static CDropSP Create();
	// 取得 : 正面回転
	CQuaternion getFrontRotation() const;

private :
	// 回転速度
	int rotateSpeed;

	// コンストラクタ
	CDrop();
	// 行動の更新
	void updateAction(CCommand &command, CState &state);
	// ライフ増減管理
	void manageLife(CState& state);

protected:
	// 派生クラス固有の更新処理
	void subUpdate(CCommand &command, CState &state);
	// 情報の反映
	void subApplyParameter();

} ;