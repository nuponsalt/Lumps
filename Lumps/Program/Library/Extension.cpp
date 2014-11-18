//*********************************************
// ���O��ԃI�u�W�F�N�g�Ǘ�/�w���p�[�֐��Ǘ�
// Last Update : 2013.12.9
// Yuta Komatsu
//*********************************************
#include "DXUT.h"
#include "Extension.h"

// 
#include <time.h>

namespace KMT {

	HRESULT DXconvAnsiToWide(WCHAR* wstrDest, const CHAR* strSrc, int ct){
		
		// ������*��NULL�̏ꍇ�ƁA��������1�ȉ��̏ꍇ�̓G���[
		if(wstrDest==NULL || strSrc==NULL || ct < 1)
			return E_INVALIDARG;

		int Result = MultiByteToWideChar(CP_ACP, 0, strSrc, -1, wstrDest, ct);
		wstrDest[ct - 1] = 0;

		if(Result == 0)
			return E_FAIL;
		return S_OK;

	}

	int GetRandom(const int &min, const int &max)
	{
		// ��ԍŏ��̊֐��Ăяo������time()�֐��Ăяo��
		static bool bflag = false;
		if (!bflag) 
		{
			srand((unsigned int)time(NULL));
			bflag = true;
		}
		// 
		return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
	}

	float calculateSphereVolume(float _rad)
	{
		return _rad * _rad * _rad * D3DX_PI * 3 / 4;
	}

	D3DXVECTOR3 QuaternionTransformCoord(D3DXVECTOR3 v, D3DXQUATERNION qtn)
	{
		D3DXVECTOR3 ret;
		D3DXQUATERNION wkQtn, wkAns, wkQtnC;
		wkQtn.x = v.x;
		wkQtn.y = v.y;
		wkQtn.z = v.z;
		wkQtn.w = 0.0f;
		wkAns = wkQtn * qtn;
		D3DXQuaternionConjugate(&wkQtnC, &qtn);	
		wkAns = wkQtnC * wkAns;
		ret = D3DXVECTOR3(wkAns.x, wkAns.y, wkAns.z);
		return ret;
	}

	float Vector2Cross(CVector2& v1, CVector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	CVector3 NearOnLine(const CVector3 &p, const CVector3 &a, const CVector3 &b)
	{
		//�x�N�g��AB AP
		CVector3 AB = b - a;
		CVector3 AP = p - a;		

		//AB�̒P�ʃx�N�g�����v�Z
		CVector3 nAB = Normalize(AB);

		//A�������ŋߓ_�܂ł̋���(AB�x�N�g���̌��ɂ���Ƃ��̓}�C�i�X�l)
		float distAX = Dot(nAB, AP);

		//����ŋߓ_
		CVector3 ret = a + (nAB * distAX);

		return ret;
	}

	CVector3 NormalOnPlane(const CVector3 vA, const CVector3& vB, const CVector3& vC)
	{
		// �e���_�����_�܂ł̃x�N�g��
		CVector3 vAB = vB - vA;
		CVector3 vAC = vC - vA;
		// �@���Z�o
		CVector3 v = Cross(vAB, vAC);
		return v.Normalize();
	}
}