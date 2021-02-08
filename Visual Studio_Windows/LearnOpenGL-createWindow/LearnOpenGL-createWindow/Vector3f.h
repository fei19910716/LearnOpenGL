#pragma once
#include <math.h>

class Vector3f
{
public:
	/*
	* 数据域：可以用一个结构体或者一个float数组
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
	Vector3f operator+(const Vector3f& v); // 注意需要加const ，否则编译不通过
	Vector3f operator-(const Vector3f& v);
	float operator*(const Vector3f& v);
	void operator=(const Vector3f& v);
	/*
	* 两个向量的叉乘
	*/
	Vector3f cross(const Vector3f& v);
	/*
	* 向量归一化
	*/
	void normalize();
	float magnitude();
};

