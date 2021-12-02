#pragma once
struct Vector4
{
	/*-----------------------------------------*/
	Vector4();
	Vector4(float x, float y, float z, float w);
	float x, y, z, w;
	/*-----------------------------------------*/
	float magnitude();
	float magnitudeSqr();
	float dot(const Vector4& v);
	void normalise();
	static Vector4 normalised(const Vector4& v);
	Vector4 cross(const Vector4& v);
	/*-----------------------------------------*/
	Vector4 operator +(const Vector4& v) const;
	Vector4 operator -(const Vector4& v) const;
	Vector4 operator *(const Vector4& v) const;
	Vector4 operator *(const float value) const;
	Vector4 operator /(const float value) const;
	/*-----------------------------------------*/
	Vector4& operator +=(const Vector4& v);
	Vector4& operator -=(const Vector4& v);
	Vector4& operator *=(const Vector4& v);
	Vector4& operator /=(const Vector4& v);
	/*-----------------------------------------*/
	operator float*();
	float& operator[](int index);
	/*-----------------------------------------*/
};
	Vector4 operator *(const float v, Vector4 v2);
	/*-----------------------------------------*/

