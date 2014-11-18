//*********************************************************************
// �x�N�g�����
// Last Update : 2014.01.08
// Yuta Komatsu
//*********************************************************************
#pragma once

namespace KMT {

	class CQuaternion;
	class CMatrix;

	class CVector3;
	float Vector3Length(const CVector3* pV);
	float Vector3LengthSq(const CVector3 *pV);
	float Vector3Dot(const CVector3 *pV1, const CVector3 *pV2);
	CVector3* Vector3Cross(CVector3 *pOut, const CVector3 *pV1, const CVector3 *pV2);
	CVector3* Vector3Lerp(CVector3 *pOut, const CVector3 *pV1, const CVector3 *pV2, float s);
	CVector3* Vector3Normalize(CVector3 *pOut, const CVector3 *pV);
	CVector3* Vector3Hermite();

	//-----------------------------------------------------
	// 3DVector
	
	class CVector3
	{
	public :
		// x
		float x;
		// y
		float y;
		// z
		float z;
		
		// �R���X�g���N�^
		CVector3() : x(0), y(0), z(0) { }
		// �z��̗v�f012��XYZ�Ƃ���
		CVector3(const float *pf) : x(pf[0]), y(pf[1]), z(pf[2]) { }
		// �w����W�Ő���
		CVector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) { }
		// ���
		CVector3& operator=(const CVector3& v) {
			x = v.x, y = v.y, z = v.z;
			return *this;
		}
		// D3DXVECTOR3����̕ϊ�
		CVector3(const D3DXVECTOR3& v) : x(v.x), y(v.y), z(v.z) { }
		// D3DXVECTOR3�ւ̕ϊ�
		operator D3DXVECTOR3() const { return D3DXVECTOR3(x, y, z) ; }
		// D3DXVECTOR4����̕ϊ�
		CVector3( const D3DXVECTOR4& v ) : x( v.x ), y( v.y ), z( v.z ){}
		// D3DXVECTOR4�ւ̕ϊ�
		operator D3DXVECTOR4() const {
			return D3DXVECTOR4(x, y, z, 1);
		}
		// ��r
			// ==
		bool operator== (const CVector3& v) {
			return x == v.x && y == v.y && z == v.z;
		}
			// !=
		bool operator!= (const CVector3& v) {
			return x != v.x || y != v.y || z != v.z;
		}
		// ���Z
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator+ (const CVector3& v) const {
			return CVector3(x + v.x, y + v.y, z + v.z);
		}
		// ���Z
		// �����̃x�N�g���ɑ��
		CVector3& operator+= (const CVector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		// �������]
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator- () const {
			return CVector3(-x, -y, -z);
		}
		// ���Z
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator- (const CVector3& v) const {
			return CVector3(x - v.x, y - v.y, z - v.z);
		}
		// ���Z
		// �����̃x�N�g���ɑ��
		CVector3& operator-= (const CVector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		// ��Z
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator* (const CVector3& v) const {
			return CVector3(x * v.x, y * v.y, z * v.z);
		}
		// ��Z
		// �����̃x�N�g���ɑ��
		CVector3& operator*= (const CVector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		// ���Z
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator/ (const CVector3& v) const {
			return CVector3(x / v.x, y / v.y, z / v.z);
		}
		// ���Z
		// �����̃x�N�g���ɑ��
		CVector3& operator/= (const CVector3& v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		// �X�J����Z
		// ���ʂ̃x�N�g���𐶐�
		// �X�J��*�x�N�g���̏ꍇ
		friend CVector3 operator* (float f, const CVector3& v) {
			return CVector3(v.x * f, v.y * f, v.z * f);
		}
		// �X�J����Z
		// ���ʂ̃x�N�g���𐶐�
		// �x�N�g��*�X�J���̏ꍇ
		CVector3 operator*(float f) const {
			return CVector3(x * f, y * f, z * f);
		}
		// �X�J���[��Z
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator* (float f) {
			return CVector3(x * f, y * f, z * f);
		}
		// �X�J���[��Z
		// �����̃x�N�g���ɑ��
		CVector3& operator*= (float f) {
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}
		// �X�J���[���Z
		// ���ʂ̃x�N�g���𐶐�
		CVector3 operator/ (float f) const {
			return CVector3(x / f, y / f, z / f);
		}
		// �X�J���[���Z
		// �����̃x�N�g���ɑ��
		CVector3& operator/= (float f) {
			x /= f;
			y /= f;
			z /= f;
			return *this;
		}
		// ����
		float Dot(const CVector3& pv) {
			return Vector3Dot(this, &pv);
		}
		// ����
		friend float Dot(CVector3 a, const CVector3& b){
			return a.Dot(b);
		}
		// ���s����
		CVector3& Parallel(CVector3 to){
			to.Normalize();
			return *this = Dot(to) * to;
		}
		// ���s����
		friend CVector3 Parallel(CVector3 from, const CVector3& to) {
			return from.Parallel(to);
		}
		// ��������
		CVector3& Vertical(CVector3 to){
			to.Normalize();
			return *this -= Dot(to) * to;
		}
		// ��������
		friend CVector3 Vertical(CVector3 from, const CVector3& to) {
			return from.Vertical(to);
		}
		// �ˉe
		CVector3& Projection(CVector3 to) {
			return Parallel(to);
		}
		// �ˉe
		friend CVector3 Projection(CVector3 from, const CVector3& to) {
			return from.Parallel(to);
		}
		// �O��
		CVector3& Cross(const CVector3& pv) {
			return *Vector3Cross(this, this, &pv);
		}
		// �O��
		friend CVector3 Cross(CVector3 a, CVector3& b) {
			return a.Cross(b);
		}
		// ����
		float Length() const {
			return Vector3Length(this); 
		}
		// ����
		friend float Length(const CVector3& v) {
			return v.Length();
		}
		// ������2��
		float LengthSq() const {
			return Vector3LengthSq(this);
		}
		// ������2��
		friend float LengthSq(const CVector3& v) {
			return v.LengthSq();
		}
		// ���`���
		// tips: f = 0 �̂Ƃ�V1, f = 1 �̂Ƃ�V2�ƂȂ�
		friend CVector3 Lerp(const CVector3& a, const CVector3& b, float f) {
			return a * (1 - f) + b * f;
		}
		// ���K��
		CVector3& Unit() {
			Vector3Normalize(this, this);
			return *this;
		}
		// ���K��
		friend CVector3 Unit(CVector3 v) {
			return v.Normalize();
		}
		// ���K��
		CVector3& Normalize() {
			return Unit();
		}
		// ���K��
		friend CVector3 Normalize(CVector3 v) {
			return v.Unit();
		}
		// ��]
		// �����̃x�N�g����ύX
		CVector3& Rotate(const CQuaternion& q) {
			D3DXQUATERNION a(x, y, z, 0), &b(*(D3DXQUATERNION*)&q), c(-b.x, -b.y, -b.z, b.w);
			D3DXQUATERNION d(c * a * b);
			x = d.x; y = d.y; z = d.z;
			return *this;
		}
		// ��]
		// �����̃x�N�g����ύX
		CVector3& operator*= (const CQuaternion& q) {
			return Rotate(q);
		}
		// ��]
		// ���ʂ̃x�N�g���𐶐�
		friend CVector3 Rotate(CVector3 v, const CQuaternion& q) {
			return v.Rotate(q);
		}
		// ��]
		// ���ʂ̃x�N�g���𐶐�
		friend CVector3 operator*(CVector3 v, const CQuaternion& q) {
			return v.Rotate(q);
		}
		// ���S���w�肵����]
		CVector3& Rotate(const CQuaternion& q, const CVector3& center) {
			return *this = (*this - center) * q + center;
		}
		// ���S���w�肵����]
		friend CVector3 Rotate(CVector3 v, const CQuaternion& q, const CVector3& center){
			return v.Rotate(q, center);
		}
		// �s��ɂ��ϊ�
		CVector3& Transform(const CMatrix& m) {
			D3DXVec3TransformCoord((D3DXVECTOR3*)this, (D3DXVECTOR3*)this, (D3DXMATRIX*)&m);
			return *this;
		}
		// �s��ɂ��ϊ�
		// �����̃x�N�g���ɑ��
		CVector3& operator*= (const CMatrix& m) {
			return Transform(m);
		}
		// �s��ɂ��ϊ�
		// ���ʂ̃x�N�g���𐶐�
		friend CVector3 Transform(CVector3 v, const CMatrix& m) {
			return v.Transform(m);
		}
		// �s��ɂ��ϊ�
		// ���ʂ̃x�N�g���𐶐�
		friend CVector3 operator* (CVector3 v, const CMatrix& m) {
			return v.Transform(m);
		}
		// XYZ�����̍ő�l
		float Max() {
			return max(x, max(y, z));
		}
		// XYZ�����̍ŏ��l
		float Min() {
			return min(x, min(y, z));
		}
		// XYZ�����̍ő�l
		friend float Max(const CVector3& v) {
			return max(v.x, max(v.y, v.z));
		}
		// XYZ�����̍ŏ��l
		friend float Min(const CVector3& v) {
			return min(v.x, min(v.y, v.z));
		}
		// �Q�x�N�g����XYZ�����̍ő�l��g�ݍ��킹���x�N�g��
		friend CVector3 Max(const CVector3& a, const CVector3& b) {
			return CVector3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
		}
		// �Q�x�N�g���̂w�C�x�C�y�����̍ŏ��l��g�ݍ��킹���x�N�g��
		friend CVector3 Min(const CVector3& a, const CVector3& b) {
			return CVector3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
		}
		// �Y�����g����XYZ�����̑���(0, 1, 2)
		float& operator[](int index) const {
			return *((float*)this + index);
		}
	};

	//-----------------------------------------------------
	// 2DVector

	class CVector2
	{
	public :
		// x
		float x;
		// y
		float y;

		// ����0�̃x�N�g���𐶐�
		CVector2() : x(0), y(0) { }
		// �w�肵��x,y�̃x�N�g���𐶐�
		CVector2(float fx, float fy) : x(fx), y(fy) { }
		// ���
		CVector2& operator= (const CVector2& v) {
			x = v.x, y = v.y;
			return *this;
		}
		// CVector3����̕ϊ�
		CVector2(const CVector3& v) : x(v.x), y(v.y) { }
		// CVector3�ւ̕ϊ�
		operator CVector3() const {
			return CVector3(x, y, 0);
		}
		// D3DXVECTOR3����̕ϊ�
		CVector2(const D3DXVECTOR3& v) : x(v.x), y(v.y) { }
		// D3DXVECTOR3�ւ̕ϊ�
		operator D3DXVECTOR3() const { 
			return D3DXVECTOR3(x, y, 0); 
		}
		// D3DXVECTOR2����̕ϊ�
		CVector2(const D3DXVECTOR2& v) : x(v.x), y(v.y) { }
		// D3DXVECTOR2�ւ̕ϊ�
		operator D3DXVECTOR2() const { 
			return D3DXVECTOR2(x, y);
		}
		// ��r�B�x�N�g�����������Ƃ���true
		bool operator== (const CVector2& v) {
			return x == v.x && y == v.y;
		}
		// ��r�B�x�N�g�����������Ȃ��Ƃ���true
		bool operator!= (const CVector2& v) {
			return x != v.x || y != v.y;
		}
		// ���Z�B���ʂ̃x�N�g���𐶐�
		CVector2 operator+ (const CVector2& v) const {
			return CVector2(x + v.x, y + v.y);
		}
		// ���Z�B�����̃x�N�g����ύX
		CVector2& operator+= (const CVector2& v) {
			x += v.x, y += v.y;
			return *this;
		}
		// �������]�B���ʂ̃x�N�g���𐶐�
		CVector2 operator- () const {
			return CVector2(-x, -y);
		}
		// ���Z�B���ʂ̃x�N�g���𐶐�
		CVector2 operator- (const CVector2& v) const {
			return CVector2(x - v.x, y - v.y);
		}
		// ���Z�B�����̃x�N�g����ύX
		CVector2& operator-= (const CVector2& v) {
			x -= v.x, y -= v.y;
			return *this;
		}
		// ��Z�B���ʂ̃x�N�g���𐶐�
		CVector2 operator* (const CVector2& v) const {
			return CVector2(x * v.x, y * v.y);
		}
		// ��Z�B�����̃x�N�g����ύX
		CVector2& operator*= (const CVector2& v) {
			x *= v.x, y *= v.y;
			return *this;
		}
		// ���Z�B���ʂ̃x�N�g���𐶐�
		CVector2 operator/ (const CVector2& v) const {
			return CVector2(x / v.x, y / v.y);
		}
		// ���Z�B�����̃x�N�g����ύX
		CVector2& operator/= (const CVector2& v) {
			x /= v.x, y /= v.y;
			return *this;
		}

		// �X�J����Z�B���ʂ̃x�N�g���𐶐��B�X�J�����x�N�g���̏ꍇ
		friend CVector2 operator* (float f, const CVector2& v) {
			return CVector2(v.x * f, v.y * f);
		}
		// �X�J����Z�B���ʂ̃x�N�g���𐶐��B�x�N�g�����X�J���̏ꍇ
		CVector2 operator* (float f) const {
			return CVector2(x * f, y * f);
		}
		// �X�J����Z�B�����̃x�N�g����ύX
		CVector2& operator*= (float f) {
			x *= f, y *= f;
			return *this;
		}
		// �X�J�����Z�B���ʂ̃x�N�g���𐶐�
		CVector2 operator/ (float f) const {
			return CVector2(x / f, y / f);
		}
		// �X�J�����Z�B�����̃x�N�g����ύX
		CVector2& operator/= (float f) {
			x /= f, y /= f;
			return *this;
		}
		// ����
		float Length() const {
			return D3DXVec2Length((D3DXVECTOR2*)this); 
		}
		// ������2�� ���g��Ԃ�
		float LengthSq() const {
			return D3DXVec2LengthSq((D3DXVECTOR2*)this);
		}
		// ���ρB���ʂ̃X�J���l�𐶐�
		float Dot(const CVector2& v) const {
			return D3DXVec2Dot((D3DXVECTOR2*)this, (D3DXVECTOR2*)&v);
		}
		// ���ρB���ʂ̃X�J���l�𐶐�
		friend float Dot(const CVector2& a, const CVector2& b) {
			return a.Dot(b);
		}
		// ���K��
		CVector2& Normalize() {
			D3DXVec2Normalize((D3DXVECTOR2*)this, (D3DXVECTOR2*)this);
			return *this;
		}
		// �s��ɂ��ϊ�
		// �����̃x�N�g���ɑ��
		CVector2& Transform(const CMatrix& m) {
			D3DXVec2TransformCoord((D3DXVECTOR2*)this, (D3DXVECTOR2*)this, (D3DXMATRIX*)&m);
			return *this;
		}
		// �s��ɂ��ϊ�
		// �����̃x�N�g���ɑ��
		CVector2& operator*= (const CMatrix& m) {
			return Transform(m);
		}
		// �s��ɂ��ϊ�
		// ���ʂ̃x�N�g���𐶐�
		friend CVector2 Transform(CVector2 v, const CMatrix& m) {
			return v.Transform(m);
		}
		// �s��ɂ��ϊ�
		// ���ʂ̃x�N�g���𐶐�
		friend CVector2 operator* (CVector2 v, const CMatrix& m) {
			return v.Transform(m);
		}

	} ;

	//-----------------------------------------------------
	// 4DVector

	class CVector4 
	{
	public:
		// x
		float x;
		// y
		float y;
		// z
		float z;
		// w
		float w;

		// ����0�̃x�N�g���𐶐�
		CVector4() : x(0), y(0), z(0), w(0) { }
		// �w�肵��x, y, z, w�̃x�N�g���𐶐�
		CVector4(float fx, float fy, float fz, float fw) : x(fx), y(fy), z(fz), w(fw) { }
		// CVector3����̕ϊ�
		CVector4(const CVector3& v) : x(v.x), y(v.y), z(v.z), w(1.0f) { }
		// CVector3�ւ̕ϊ�
		operator CVector3() const { 
			return CVector3(x / w, y / w, z / w); 
		}
		// D3DXVECTOR3����̕ϊ�
		CVector4(const D3DXVECTOR3& v) : x(v.x), y(v.y), z(v.z), w(1.0f) { }
		// D3DXVECTOR3�ւ̕ϊ�
		operator D3DXVECTOR3() const { 
			return D3DXVECTOR3(x / w, y / w, z / w); 
		}
		// D3DXVECTOR4����̕ϊ�
		CVector4(const D3DXVECTOR4& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
		// D3DXVECTOR4�ւ̕ϊ�
		operator D3DXVECTOR4() const { 
			return D3DXVECTOR4(x, y, z, w);
		}
		// x��ݒ�
		CVector4& SetX(float fx) { 
			x = fx;
			return *this;
		}
		// y��ݒ�
		CVector4& SetY(float fy) { 
			y = fy;
			return *this;
		}
		// z��ݒ�
		CVector4& SetZ(float fz) { 
			z = fz;
			return *this;
		}
		// w��ݒ�
		CVector4& SetW(float fw) { 
			w = fw;
			return *this;
		}
		// ��r�B�x�N�g�����������Ƃ���true
		bool operator== (const CVector4& v) {
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}
		// ��r�B�x�N�g�����������Ȃ��Ƃ���true
		bool operator!= (const CVector4& v) {
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}
		// ���Z�B���ʂ̃x�N�g���𐶐�
		CVector4 operator+ (const CVector4& v) const {
			return CVector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		// ���Z�B�����̃x�N�g����ύX
		CVector4& operator+= (const CVector4& v) {
			x += v.x, y += v.y, z += v.z, w += v.w;
			return *this;
		}
		// �������]�B���ʂ̃x�N�g���𐶐�
		CVector4 operator- () const {
			return CVector4(-x, -y, -z, -w);
		}
		// ���Z�B���ʂ̃x�N�g���𐶐�
		CVector4 operator- (const CVector4& v) const {
			return CVector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		// ���Z�B�����̃x�N�g����ύX
		CVector4& operator-= (const CVector4& v) {
			x -= v.x, y -= v.y, z -= v.z, w -= v.w;
			return *this;
		}
		// ��Z�B���ʂ̃x�N�g���𐶐�
		CVector4 operator* (const CVector4& v) const {
			return CVector4(x * v.x, y * v.y, z * v.z, w * v.w);
		}
		// ��Z�B�����̃x�N�g����ύX
		CVector4& operator*=(const CVector4& v) {
			x *= v.x, y *= v.y, z *= v.z, w *= v.w;
			return *this;
		}
		// ���Z�B���ʂ̃x�N�g���𐶐�
		CVector4 operator/ (const CVector4& v) const {
			return CVector4(x / v.x, y / v.y, z / v.z, w / v.w);
		}
		// ���Z�B�����̃x�N�g����ύX
		CVector4& operator/= (const CVector4& v) {
			x /= v.x, y /= v.y, z /= v.z, w /= v.w;
			return *this;
		}
		// �X�J����Z�B���ʂ̃x�N�g���𐶐��B�X�J�����x�N�g���̏ꍇ
		friend CVector4 operator*(float f, const CVector4& v) {
			return CVector4(v.x * f, v.y * f, v.z * f, v.w * f);
		}
		// �X�J����Z�B���ʂ̃x�N�g���𐶐��B�x�N�g�����X�J���̏ꍇ
		CVector4 operator*(float f) const {
			return CVector4(x * f, y * f, z * f, w * f);
		}
		// �X�J����Z�B�����̃x�N�g����ύX
		CVector4& operator*= (float f) {
			x *= f, y *= f, z *= f, w *= f;
			return *this;
		}
		// �X�J�����Z�B���ʂ̃x�N�g���𐶐�
		CVector4 operator/ (float f) const {
			return CVector4(x / f, y / f, z / f, w / f);
		}
		// �X�J�����Z�B�����̃x�N�g����ύX
		CVector4& operator/= (float f) {
			x /= f, y /= f, z /= f, w /= f;
			return *this;
		}
		// ���ρB���ʂ̃X�J���l�𐶐�
		float Dot(const CVector4& v) const {
			return D3DXVec4Dot((D3DXVECTOR4*)this, (D3DXVECTOR4*)&v);
		}
		// ���ρB���ʂ̃X�J���l�𐶐�
		friend float Dot(const CVector4& a, const CVector4& b) {
			return a.Dot(b);
		}
		// �s��ɂ��ϊ��B�����̃x�N�g����ύX
		CVector4& Transform(const CMatrix& m) {
			D3DXVec4Transform((D3DXVECTOR4*)this, (D3DXVECTOR4*)this, (D3DXMATRIX*)&m);
			return *this;
		}
		// �s��ɂ��ϊ��B�����̃x�N�g����ύX
		CVector4& operator*= (const CMatrix& m) {
			return Transform(m);
		}
		// �s��ɂ��ϊ��B���ʂ̃x�N�g���𐶐�
		friend CVector4 Transform(CVector4 v, const CMatrix& m) {
			return v.Transform(m);
		}
		// �s��ɂ��ϊ��B���ʂ̃x�N�g���𐶐�
		friend CVector4 operator*(CVector4 v, const CMatrix& m) {
			return v.Transform(m);
		}
		//�Y�����g�����w,�x,�y�����̑���(0, 1, 2)
		float& operator[](int index) const {
			return *((float*)this + index);
		}

	};
}