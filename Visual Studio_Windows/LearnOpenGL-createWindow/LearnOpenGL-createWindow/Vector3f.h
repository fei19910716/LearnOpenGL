#pragma once
#include <math.h>

class Vector3f
{
public:
	/*
	* �����򣺿�����һ���ṹ�����һ��float����
	*/
	union
	{
		struct {
			float x, y, z;
		};
		float v[3];
	};
	
	Vector3f(float x, float y, float z); 
	Vector3f();

	Vector3f operator*(float scalar);
	Vector3f operator+(const Vector3f& v); // ע����Ҫ��const ��������벻ͨ��
	Vector3f operator-(const Vector3f& v);
	float operator*(const Vector3f& v);
	void operator=(const Vector3f& v);
	/*
	* ���������Ĳ��
	*/
	Vector3f cross(const Vector3f& v);
	/*
	* ������һ��
	*/
	void normalize();
	float magnitude();
};

