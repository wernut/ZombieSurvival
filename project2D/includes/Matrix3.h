#pragma once
#include "Vector3.h"
#include "Vector2.h"

struct Matrix3
{
	Matrix3();
	Matrix3(float m0,float m1, float m2, float m3, 
		    float m4,float m5, float m6,float m7,float m8);
	float m[9];
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

	Matrix3 operator*(const Matrix3& matrix);
	Vector3 operator*(const Vector3& vector);
	Vector3& operator[](int index);
	operator float*();

};

