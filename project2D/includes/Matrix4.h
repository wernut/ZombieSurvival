#pragma once
#include "Vector4.h"
#include "Vector2.h"

struct Matrix4
{
	Matrix4();
	Matrix4(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7, float m8,
		float m9, float m10, float m11, float m12, float m13,
		float m14, float m15);
	float m[16];
	float rotation;
	Vector2 scale;

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setTranslation(Vector2 translation);
	void setScale(Vector2 scale);

	Vector2 getTranslation();
	Vector2 getScale();
	float   getRotation();
	Vector2 getForward() const;


	Matrix4 operator*(const Matrix4& matrix);
	Vector4 operator*(const Vector4& vector);
	Vector4& operator[](int index);
	operator float*();
};

