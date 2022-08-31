#include "Vector3.h"
#include<cmath>

Vector3::Vector3()
	:x(0), y(0), z(0)
{
}

Vector3::Vector3(float x_, float y_, float z_)
	: x(x_), y(y_), z(z_)
{
}


float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::normalaize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const
{
	Vector3 vec;
	double x1, y1, z1, x2, y2, z2;

	x1 = (double)x;
	y1 = (double)y;
	z1 = (double)z;
	x2 = (double)v.x;
	y2 = (double)v.y;
	z2 = (double)v.z;

	vec.x = (float)(y1 * z2 - z1 * y2);
	vec.y = (float)(z1 * x2 - x1 * z2);
	vec.z = (float)(x1 * y2 - y1 * z2);


	return vec;
}

Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;

	return *this;
}

//Vector3 ÉNÉâÉXÇ…ëÆÇ≥Ç»Ç¢ä÷êîåQ

const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v1, float s)
{
	Vector3 temp(v1);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v1)
{
	return s * v1;
}

const Vector3 operator/(const Vector3& v1, float s)
{
	Vector3 temp(v1);
	return temp /= s;
}
