#include "DXUT.h"
//#include "HeightField.h"
//
//CHeightField::CHeightField()
//{
//	numWidth = 200;
//	numDepth = 200;
//	const int HEIGHT_MAX = 8;
//
//	numVTX = 0;
//	numIDX = 0;
//
//	// シェーダー設定
//	Shader = CShaderPhong::Create();
//
//	// テクスチャのロード
//	Texture = CTexture::CreateFromFile("tex3.png", D3DX_FILTER_NONE);
//
//	auto texheight = CTexture::CreateFromFile("height.png", D3DX_DEFAULT);
//	auto pd3dHeightTexture = texheight->getpd3dTexture();
//
//	D3DSURFACE_DESC surface;
//	pd3dHeightTexture->GetLevelDesc(0, &surface);
//
//	float twidth = (float)surface.Width;
//	float theight = (float)surface.Height;
//
//	// 色を引っ張ってくるのでテクスチャをロック
//	D3DLOCKED_RECT LockedRect;
//	pd3dHeightTexture->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD);
//
//	numVTX = numWidth * numDepth;
//	numIDX = 3 * (numWidth * numDepth) * 2;
//
//	CVertex* pVertex = new CVertex[numVTX];
//	WORD* pIndexes = new WORD[numIDX];
//
//	std::vector<int> sum_num;
//	for(int i = 0; i< numVTX; i++)
//	{
//		sum_num.push_back(0);
//	}
//
//	vSize.x = 70.0f ;
//	vSize.z = 70.0f ;
//	float sx = -(vSize.x * 0.5f);
//	float sz = (vSize.z * 0.5f);
//	float wx = vSize.x / (float)numWidth;
//	float wz = vSize.z / (float)numDepth;
//	//float wu = 1.0f / (float)VTX_X ;
//	//float wv = 1.0f / (float)VTX_Z ;
//
//	// 頂点データを生成
//	for(int i = 0; i < numDepth; i++) 
//	{
//		float v = i / ((float)numDepth);
//		for(int k = 0 ; k < numWidth; k++)
//		{
//			float px = sx + (wx * (float)k);
//			float pz = sz - (wz * (float)i);
//			float u = k / float(numWidth);
//
//			int tx = (int)(u * twidth);
//			int ty = (int)(v * theight);
//
//			// UV に適応したテクスチャの色データげっと( 1ピクセル分の色 )
//			DWORD* pColor = (DWORD*)((BYTE*)LockedRect.pBits + LockedRect.Pitch*ty + 4*tx);
//
//			int R = (*pColor & 0x00ff0000) >> 16;
//			int G = (*pColor & 0x0000ff00) >> 8;
//			int B = (*pColor & 0x000000ff) >> 0;
//
//			float col = (R + G + B) / 3.0f;
//			float height = (col / 255.0f) * HEIGHT_MAX;
//			float py = height;
//
//			pVertex[(i * numWidth) + k].Position = CVector3(px, py, pz);
//			pVertex[(i * numWidth) + k].Normal = CVector3(0.0f, 1.0f, 0.0f);
//			pVertex[(i * numWidth) + k].UV = CVector2(u, v);
//		}
//	}
//
//	// テクスチャアンロック
//	pd3dHeightTexture->UnlockRect(0);
//
//	// インデックスデータを生成
//	WORD* index = pIndexes;
//	for(int k = 0; k < numDepth - 1; k++)
//	{
//		int base = k * (numWidth);
//		std::vector<CTerrainSP> colls;
//
//		for(int i = 0; i < numWidth - 1; i++) {
//			*index++ = (WORD)(base + i);
//			*index++ = (WORD)(base + i + 1) ;
//			*index++ = (WORD)(base + i + (numWidth));
//			*index++ = (WORD)(base + i + (numWidth));
//			*index++ = (WORD)(base + i + 1);
//			*index++ = (WORD)(base + i + 1 + (numWidth));
//
//			// 当たり判定用の三角形ポリゴンデータを生成
//			CTerrain* collision = new CTerrain();
//			// 頂点座標の計算
//			collision->Positions.push_back(pVertex[base + i].Position);
//			collision->Positions.push_back(pVertex[base + i + 1].Position);
//			collision->Positions.push_back(pVertex[base + i + (numWidth)].Position);
//			collision->Positions.push_back(pVertex[base + i + 1 + (numWidth)].Position);
//			// 法線ベクトルを計算
//			CVector3 vec1 = collision->Positions[1] - collision->Positions[0];
//			CVector3 vec2 = collision->Positions[0] - collision->Positions[2];
//			//D3DXVec3Cross( &coll->m_nml[0], &vec1, &vec2 ) ;
//			collision->Normal[0] = vec2.Cross(vec1);
//			collision->Normal[0].Normalize();
//			// 頂点データに法線ベクトルをセット
//			pVertex[base + i].Normal += collision->Normal[0];
//			sum_num[base + i]++;
//			pVertex[base + i + 1].Normal += collision->Normal[0];
//			sum_num[base + i + 1]++;
//			pVertex[base + i + (numWidth)].Normal += collision->Normal[0];
//			sum_num[base + i + (numWidth)]++;
//
//			// 法線ベクトルを計算
//			CVector3 vec3 = collision->Positions[1] - collision->Positions[2];
//			CVector3 vec4 = collision->Positions[2] - collision->Positions[3];
//			//D3DXVec3Cross( &coll->m_nml[1], &vec3, &vec4 ) ;
//			collision->Normal[1] = vec4.Cross(vec3);
//			collision->Normal[1].Normalize();
//			// 頂点データに法線ベクトルをセット
//			pVertex[base + i + (numWidth)].Normal += collision->Normal[1];
//			sum_num[base + i + (numWidth)]++;
//			pVertex[base + i + 1].Normal += collision->Normal[1];
//			sum_num[base + i + 1] ++ ;
//			pVertex[base + i + (numWidth) + 1 ].Normal += collision->Normal[1];
//			sum_num[base + i + (numWidth) + 1]++;
//			// ベクターに登録
//			colls.push_back(CTerrainSP(collision));
//		}
//		Collisions.push_back(colls);
//	}
//
//	for(size_t i = 0; i < sum_num.size(); i++)
//	{
//		pVertex[i].Normal /= (float)sum_num[i]; 
//	}
//
//	//-------------------------------------------------------------------------------------------------------------
//	// 頂点バッファ作成
//	CGraphicsManager::pd3dDevice->CreateVertexBuffer(
//		// バッファサイズ
//		numVTX * sizeof(CVertex),
//		// 描画専用
//		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
//		// 頂点フォーマット
//		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1),
//		D3DPOOL_DEFAULT,
//		// 受け取り
//		&pd3dVertexBuffer,
//		NULL
//		);
//
//	// 頂点バッファに自前のポリゴンデータを設定
//	void* pVertices;
//	pd3dVertexBuffer->Lock(0, numVTX * sizeof(CVertex), (void**)&pVertices, 0);
//	memcpy(pVertices, pVertex, numVTX * sizeof(CVertex));
//	pd3dVertexBuffer->Unlock();
//
//	//----------------------------------------------------------------------------------------------------------	 /
//	// 頂点インデックスバッファ作成
//	CGraphicsManager::pd3dDevice->CreateIndexBuffer(
//		// バッファサイズ
//		numIDX * sizeof(WORD),
//		// VRAM 上に確保して高速描画(CPU からは読めない)
//		D3DUSAGE_WRITEONLY,
//		// インデックスバッファ16bit
//		D3DFMT_INDEX16,
//		// CPU からは読めない
//		D3DPOOL_DEFAULT,
//		// 受け取り用
//		&pd3dIndexBuffer,
//		NULL
//		);										
//
//	// インデックスバッファに適用するインデックスバッファの内容を設定
//	BYTE* pIndex;
//	pd3dIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_NOSYSLOCK);
//	memcpy(pIndex, pIndexes, numIDX * sizeof(WORD));
//	pd3dIndexBuffer->Unlock() ;
//
//	SAFE_RELEASE(pd3dHeightTexture);
//
//	delete[] pIndexes;
//	delete[] pVertex;
//}
//
//CHeightFieldSP CHeightField::CreateHeightField()
//{
//	return CHeightFieldSP(new CHeightField());
//}
//
//float CTerrain::calculateDistance(CVector3 pos, float dist, int polynum)
//{
//	for(int i=0; i<3; i++)
//	{
//		CVector3 tri_vec = Positions[Index[PolygonNumber][(1 + i) % 3]] - Positions[Index[PolygonNumber][(0 + i) % 3]];
//		CVector3 judge_vec = pos - Positions[Index[PolygonNumber][(0 + i) % 3]];
//		CVector3 nml_vec = Cross(tri_vec, judge_vec);
//		if(nml_vec.y < 0)
//		{
//			float dist_ = nml_vec.Length() / tri_vec.Length();
//			return dist * dist + dist_ * dist_;
//		}
//	}
//	return dist * dist;
//}
//
//bool CTerrain::getCollide(const CVector3& pos, float radius)
//{
//	// 二つある三角形のどちらと判定を取るか
//	PolygonNumber = 0;
//	CVector2 boundary_s = CVector2(Positions[2].x, Positions[2].z);
//	CVector2 boundary_e = CVector2(Positions[1].x, Positions[1].z);
//
//	float judge = pos.x * (boundary_s.y - boundary_e.y) + boundary_s.x * (boundary_e.y - pos.z) + boundary_e.x * (pos.z - boundary_s.y);
//
//	if(judge < 0)
//		PolygonNumber = 1;
//
//	//------------------------------------------
//
//	CVector3 nml_vec_s = Positions[Index[PolygonNumber][0]];
//	CVector3 nml_vec_d = Normal[PolygonNumber];
//
//	CVector3 vec1 = pos - nml_vec_s;
//
//	float dist_ = fabs(Dot(nml_vec_d, vec1)) /  fabs(nml_vec_d.Length());
//
//	CVector3 vec2 = -Normal[PolygonNumber];
//	vec2.Normalize();
//	vec2 *= dist_;
//	CVector3 pos1 = pos + vec2;
//
//	float judge_dist = calculateDistance(pos1, dist_, PolygonNumber);
//
//	if((radius * radius) >= judge_dist) 
//		return true;
//
//	return false;
//}
//
//void CHeightField::Render(const CCamera* camera)
//{
//	if(!isRender)
//		return;
//	// ワールド行列設定
//	CMatrix SclMtx, RotMtx, PosMtx, WldMtx, WVPMtx;
//	// 拡縮
//	D3DXMatrixScaling(&SclMtx, Scale.x, Scale.y, Scale.z );
//	// 回転 : switch-case…クォータニオンか回転行列かXYZ指定か
//	switch(CurrentRotateType)
//	{
//	case ROTATE_TYPE::QUATERNION :
//		D3DXMatrixRotationQuaternion(&RotMtx, &qRotation);
//		break;
//
//	case ROTATE_TYPE::MATRIX :
//		mRotationWorld = mRotationX * mRotationY * mRotationZ;
//		RotMtx = mRotationWorld;
//		break;
//
//	case ROTATE_TYPE::XYZ :
//		D3DXMatrixRotationYawPitchRoll(&RotMtx, vRotation.y, vRotation.x, vRotation.z);
//		break;
//	}
//	// 位置
//	D3DXMatrixTranslation(&PosMtx, Position.x, Position.y, Position.z);
//	CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_CULLMODE, d3dCull);
//	// デバッグ用
//	//CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//	// シェーダを使用する場合カメラのビュー行列(0)、プロジェクション行列(1)をワールド行列に合成
//	WldMtx = SclMtx * RotMtx * PosMtx;
//	WVPMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW) * camera->getMatrix(CViewBehavior::PROJECTION);
//	// カメラの座標をシェーダに使用するための行列変換
//	CMatrix CamMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW);
//	D3DXMatrixInverse(&CamMtx, NULL, &CamMtx);
//	CVector4 EyePos = CVector4(
//		camera->getEye().x,
//		camera->getEye().y,
//		camera->getEye().z,
//		1
//		);
//	EyePos.Transform(CamMtx);
//	D3DXVec4Normalize((D3DXVECTOR4*)&EyePos, (D3DXVECTOR4*)&EyePos);
//	// シェーダ設定
//	Shader->setTechnique();
//	// シェーダにワールド行列を渡す
//	Shader->getpd3dEffect()->SetMatrix(*Shader->getpWVP(), &WVPMtx);
//	// シェーダーでする作業
//	Shader->applyEffect(RotMtx, EyePos);
//}