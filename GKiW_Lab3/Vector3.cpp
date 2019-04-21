#include "stdafx.h"
#include "Vector3.h"


Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z) :
	x(x), y(y), z(z)  
{
}

Vector3::Vector3(const Vector3 & vec) :
	x(vec.x), y(vec.y), z(vec.z)
{
}

Vector3::~Vector3()
{
}

void Vector3::operator=(const Vector3 & vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

void Vector3::add(const Vector3 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}

void Vector3::mult(float num)
{
	this->x *= num;
	this->y *= num;
	this->z *= num;
}

void Vector3::div(float num)
{
	this->x /= num;
	this->y /= num;
	this->z /= num;
}

float Vector3::getLength()
{
	return sqrtf(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
}

void Vector3::normalize()
{
	float length = this->getLength();

	if (length > 0)
	{
		this->x = this->x / length;
		this->y = this->y / length;
		this->z = this->z / length;
	}
}
