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
//	// �V�F�[�_�[�ݒ�
//	Shader = CShaderPhong::Create();
//
//	// �e�N�X�`���̃��[�h
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
//	// �F�����������Ă���̂Ńe�N�X�`�������b�N
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
//	// ���_�f�[�^�𐶐�
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
//			// UV �ɓK�������e�N�X�`���̐F�f�[�^������( 1�s�N�Z�����̐F )
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
//	// �e�N�X�`���A�����b�N
//	pd3dHeightTexture->UnlockRect(0);
//
//	// �C���f�b�N�X�f�[�^�𐶐�
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
//			// �����蔻��p�̎O�p�`�|���S���f�[�^�𐶐�
//			CTerrain* collision = new CTerrain();
//			// ���_���W�̌v�Z
//			collision->Positions.push_back(pVertex[base + i].Position);
//			collision->Positions.push_back(pVertex[base + i + 1].Position);
//			collision->Positions.push_back(pVertex[base + i + (numWidth)].Position);
//			collision->Positions.push_back(pVertex[base + i + 1 + (numWidth)].Position);
//			// �@���x�N�g�����v�Z
//			CVector3 vec1 = collision->Positions[1] - collision->Positions[0];
//			CVector3 vec2 = collision->Positions[0] - collision->Positions[2];
//			//D3DXVec3Cross( &coll->m_nml[0], &vec1, &vec2 ) ;
//			collision->Normal[0] = vec2.Cross(vec1);
//			collision->Normal[0].Normalize();
//			// ���_�f�[�^�ɖ@���x�N�g�����Z�b�g
//			pVertex[base + i].Normal += collision->Normal[0];
//			sum_num[base + i]++;
//			pVertex[base + i + 1].Normal += collision->Normal[0];
//			sum_num[base + i + 1]++;
//			pVertex[base + i + (numWidth)].Normal += collision->Normal[0];
//			sum_num[base + i + (numWidth)]++;
//
//			// �@���x�N�g�����v�Z
//			CVector3 vec3 = collision->Positions[1] - collision->Positions[2];
//			CVector3 vec4 = collision->Positions[2] - collision->Positions[3];
//			//D3DXVec3Cross( &coll->m_nml[1], &vec3, &vec4 ) ;
//			collision->Normal[1] = vec4.Cross(vec3);
//			collision->Normal[1].Normalize();
//			// ���_�f�[�^�ɖ@���x�N�g�����Z�b�g
//			pVertex[base + i + (numWidth)].Normal += collision->Normal[1];
//			sum_num[base + i + (numWidth)]++;
//			pVertex[base + i + 1].Normal += collision->Normal[1];
//			sum_num[base + i + 1] ++ ;
//			pVertex[base + i + (numWidth) + 1 ].Normal += collision->Normal[1];
//			sum_num[base + i + (numWidth) + 1]++;
//			// �x�N�^�[�ɓo�^
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
//	// ���_�o�b�t�@�쐬
//	CGraphicsManager::pd3dDevice->CreateVertexBuffer(
//		// �o�b�t�@�T�C�Y
//		numVTX * sizeof(CVertex),
//		// �`���p
//		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
//		// ���_�t�H�[�}�b�g
//		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1),
//		D3DPOOL_DEFAULT,
//		// �󂯎��
//		&pd3dVertexBuffer,
//		NULL
//		);
//
//	// ���_�o�b�t�@�Ɏ��O�̃|���S���f�[�^��ݒ�
//	void* pVertices;
//	pd3dVertexBuffer->Lock(0, numVTX * sizeof(CVertex), (void**)&pVertices, 0);
//	memcpy(pVertices, pVertex, numVTX * sizeof(CVertex));
//	pd3dVertexBuffer->Unlock();
//
//	//----------------------------------------------------------------------------------------------------------	 /
//	// ���_�C���f�b�N�X�o�b�t�@�쐬
//	CGraphicsManager::pd3dDevice->CreateIndexBuffer(
//		// �o�b�t�@�T�C�Y
//		numIDX * sizeof(WORD),
//		// VRAM ��Ɋm�ۂ��č����`��(CPU ����͓ǂ߂Ȃ�)
//		D3DUSAGE_WRITEONLY,
//		// �C���f�b�N�X�o�b�t�@16bit
//		D3DFMT_INDEX16,
//		// CPU ����͓ǂ߂Ȃ�
//		D3DPOOL_DEFAULT,
//		// �󂯎��p
//		&pd3dIndexBuffer,
//		NULL
//		);										
//
//	// �C���f�b�N�X�o�b�t�@�ɓK�p����C���f�b�N�X�o�b�t�@�̓��e��ݒ�
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
//	// �����O�p�`�̂ǂ���Ɣ������邩
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
//	// ���[���h�s��ݒ�
//	CMatrix SclMtx, RotMtx, PosMtx, WldMtx, WVPMtx;
//	// �g�k
//	D3DXMatrixScaling(&SclMtx, Scale.x, Scale.y, Scale.z );
//	// ��] : switch-case�c�N�H�[�^�j�I������]�s��XYZ�w�肩
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
//	// �ʒu
//	D3DXMatrixTranslation(&PosMtx, Position.x, Position.y, Position.z);
//	CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_CULLMODE, d3dCull);
//	// �f�o�b�O�p
//	//CGraphicsManager::pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//	// �V�F�[�_���g�p����ꍇ�J�����̃r���[�s��(0)�A�v���W�F�N�V�����s��(1)�����[���h�s��ɍ���
//	WldMtx = SclMtx * RotMtx * PosMtx;
//	WVPMtx = WldMtx * camera->getMatrix(CViewBehavior::VIEW) * camera->getMatrix(CViewBehavior::PROJECTION);
//	// �J�����̍��W���V�F�[�_�Ɏg�p���邽�߂̍s��ϊ�
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
//	// �V�F�[�_�ݒ�
//	Shader->setTechnique();
//	// �V�F�[�_�Ƀ��[���h�s���n��
//	Shader->getpd3dEffect()->SetMatrix(*Shader->getpWVP(), &WVPMtx);
//	// �V�F�[�_�[�ł�����
//	Shader->applyEffect(RotMtx, EyePos);
//}