//*********************************************
// ���O��ԃI�u�W�F�N�g�Ǘ�/�w���p�[�֐��Ǘ�
// Last Update : 2013.12.9
// Yuta Komatsu
//*********************************************
#pragma once

#include <memory>
#include "Math/Vector.h"

namespace KMT {

	const int SCREEN_WIDTH = 960, SCREEN_HEIGHT = 540;

	//* �V�X�e�� *//
	// �}���`�o�C�g�����^�ϊ�
	HRESULT DXconvAnsiToWide(WCHAR* wstrDest, const CHAR* strSrc, int ct);
	// �͈͎w�藐������
	// min : �͈͍ŏ��l, max : �͈͍ő�l
	int GetRandom(const int &min, const int &max);

	//* ���w *//
	// �̐όv�Z(��)
	// _rad : ���a
	float calculateSphereVolume(float _rad);
	// �̐όv�Z(������)
	// _width : ��, _height : ����, _depth : �[�� 
	float calculateCuboidVolume(float _width, float _height, float _depth);
	
	// �N�H�[�^�j�I���ɂ��x�N�g���̉�]
	// v : �v�Z�̊�ɂȂ�x�N�g��, qtn : �v�Z�̊�ɂȂ�N�H�[�^�j�I��
	D3DXVECTOR3 QuaternionTransformCoord(D3DXVECTOR3 v, D3DXQUATERNION qtn);
	
	// 2D�x�N�g���̊O�όv�Z 
	float Vector2Cross(CVector2& v1, CVector2& v2);
	
	// ������̍ŋߓ_�𓾂�
	// p : ��ɂȂ���W�x�N�g��, a : �����̎n�_, b : �����̏I�_
	CVector3 NearOnLine(const CVector3 &p, const CVector3 &a, const CVector3 &b);
	
	// 3���_�ō\������镽�ʂ̖@�����Z�o
	// v1 : ��_, 
	CVector3 NormalOnPlane(const CVector3 vA, const CVector3& vB, const CVector3& vC);
}