#pragma once

struct Vector3
{
	/*-----------------------------------------*/
	Vector3();
	Vector3(float x, float y, float z);
	float x, y, z;
	/*-----------------------------------------*/
	float magnitude();
	float magnitudeSqr();
	float dot(const Vector3& v);
	void normalise();
	static Vector3 normalised(const Vector3& v);
	Vector3 cross(const Vector3& v);
	/*-----------------------------------------*/
	Vector3 operator +(const Vector3& v) const;
	Vector3 operator -(const Vector3& v) const;
	Vector3 operator *(const Vector3& v) const;
	Vector3 operator *(const float value) const;
	Vector3 operator /(const float value) const;
	/*-----------------------------------------*/
	Vector3& operator +=(const Vector3& v);
	Vector3& operator -=(const Vector3& v);
	Vector3& operator *=(const Vector3& v);
	Vector3& operator /=(const Vector3& v);
	/*-----------------------------------------*/
	operator float*();
	float& operator[](int index);
	/*-----------------------------------------*/
};
	Vector3 operator *(const float v, Vector3 v2);
	/*-----------------------------------------*/
