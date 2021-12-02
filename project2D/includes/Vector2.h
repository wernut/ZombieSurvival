#pragma once

struct Vector2
{
	/*-----------------------------------------*/
	Vector2();
	Vector2(const float x, const float y);
	float x, y;
	/*-----------------------------------------*/
	float magnitude();
	float magnitudeSqr();
	float dot(const Vector2& v);
	float angle(float normalisedX, float normalisedY);
	void normalise();
	static Vector2 normalised(const Vector2& v);
	Vector2 right();
	Vector2 left();
	/*-----------------------------------------*/
	Vector2 operator +(const Vector2& v) const;
	Vector2 operator -(const Vector2& v) const;
	Vector2 operator *(const Vector2& v) const;
	Vector2 operator *(const float value) const;
	Vector2 operator /(const float value) const;
	/*-----------------------------------------*/
	Vector2& operator +=(const Vector2& v);
	Vector2& operator -=(const Vector2& v);
	Vector2& operator *=(const Vector2& v);
	Vector2& operator /=(const Vector2& v);
	/*-----------------------------------------*/
	operator float*();
	float& operator[](int index);
	/*-----------------------------------------*/
};
	Vector2 operator *(const float v, Vector2 v2);
	/*-----------------------------------------*/

