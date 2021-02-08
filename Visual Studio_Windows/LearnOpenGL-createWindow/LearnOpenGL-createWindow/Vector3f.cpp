#include "Vector3f.h"

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3f Vector3f::operator*(float scalar)
{
	return Vector3f(x * scalar, y * scalar, z * scalar);
}

Vector3f Vector3f::operator+(const Vector3f& v)
{
	return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f Vector3f::operator-(const Vector3f& v)
{
	return Vector3f(x - v.x, y - v.y, z - v.z);
}

float Vector3f::operator*(const Vector3f& v)
{
	return x * v.x + y * v.y + z * v.z;
}

void Vector3f::operator=(const Vector3f& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3f Vector3f::cross(const Vector3f& v)
{
	return Vector3f(y * v.z - z * v.y, x * v.z - z * v.x, x * v.y - y * v.x);
}

void Vector3f::normalize()
{
	float mag = 1.0 / magnitude();
	this->operator*(mag);
}

float Vector3f::magnitude()
{
	return sqrtf(x*x+y*y+z*z);
}
