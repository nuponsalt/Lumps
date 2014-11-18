#pragma once
//
//#include "../../Library/Library.h"
//using namespace KMT;
//
//class CTerrain;
//class CHeightField;
//
//typedef std::shared_ptr<CTerrain> CTerrainSP;
//typedef std::shared_ptr<CHeightField> CHeightFieldSP;
//
//typedef std::weak_ptr<CTerrain> CTerrainWP;
//typedef std::weak_ptr<CHeightField> CHeightFieldWP;
//
//// 地形衝突判定
//typedef class CTerrain
//{
//public :
//	// 頂点座標ベクター配列
//	std::vector<CVector3> Positions;
//	// 頂点インデックス
//	size_t Index[2][3];
//	// 法線ベクトル
//	CVector3 Normal[2];
//	// ポリゴン判定対象フラグ
//	size_t PolygonNumber;
//
//	// コンストラクタ
//	CTerrain() : PolygonNumber(0) 
//	{
//		Index[0][0] = 0;
//		Index[0][1] = 1;
//		Index[0][2] = 2;
//		Index[1][0] = 2;
//		Index[1][1] = 1;
//		Index[1][2] = 3;
//	}
//
//	// 衝突判定の取得
//	bool getCollide(const CVector3& pos, float radius);
//
//private :
//	// 点との距離の計算
//	float calculateDistance(CVector3 pos, float dist, int polynum);
//
//}ModelVolume, *PModel, *PModelVolume;
//
//// ハイトマップ地形モデル
//class CHeightField : public CGraphicBehavior
//{
//public :
//	// デストラクタ
//	~CHeightField() { }
//
//	// 生成
//	static CHeightFieldSP CreateHeightField();
//	// 衝突判定
//	//bool getCollide(CVector3* ppos, float size);
//	// 描画
//	void Render(const CCamera* camera);
//
//private :
//	// テクスチャ
//	CTextureSP Texture;
//	// 頂点バッファ
//	LPDIRECT3DVERTEXBUFFER9 pd3dVertexBuffer;
//	// インデックスバッファ
//	LPDIRECT3DINDEXBUFFER9  pd3dIndexBuffer;
//	// ハイトフィールドの衝突判定
//	std::vector<std::vector<CTerrainSP>> Collisions;
//	// フィールドのサイズ
//	CVector3 vSize;
//
//	// 奥横の分割数
//	int numWidth;
//	int numDepth;
//	// 頂点総数
//	int numVTX;
//	// インデックス数
//	int numIDX;
//
//	// コンストラクタ
//	CHeightField();
//
//};